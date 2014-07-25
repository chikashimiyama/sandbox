
__constant int numParticles = 16;
__constant int resolution = 41;
__constant float isoValue = 0.000563;

typedef struct Particle{
    float orientation[3];
    float acceleration[3];
    int lifeSpan;
    int age;
}Particle;

typedef struct ParticleSetting{
    
    float origin[3];
    float originSpread[3];
    float orientation[3];
    float orientationSpread[3];
    float acceleration[3];
    float accelerationSpread[3];
    uint lifeSpan[2];
    uint numberOfSpawn;
    uint spawnIndex;
    int dummy[10];
}ParticleSetting;

typedef struct IsoPoint{
    float x;
    float y;
    float z;
    float xn;
    float yn;
    float zn;
    float isoValue;
    float dummy;
}IsoPoint;


__kernel void update(
                     __global Particle* pb,
                     __global ParticleSetting* init,
                     __global float *points,
                     __global float *randomTable){

    int id = get_global_id(0);
    __global Particle *p = &pb[id];
    __global float * pos = &points[id*3];
    __global float * rand  = &randomTable[id*3];

    
    pos[0] += p->orientation[0];
    pos[1] += p->orientation[1];
    pos[2] += p->orientation[2];
    
    p->orientation[0] += p->acceleration[0];
    p->orientation[1] += p->acceleration[1];
    p->orientation[2] += p->acceleration[2];
    p->age++;
    
    int endSpawnIndex = (init->spawnIndex + init->numberOfSpawn) % numParticles;
    bool wrapped = endSpawnIndex < init->spawnIndex;
    bool initFlag = false;
    if(wrapped){
        if((init->spawnIndex <= id) && (id < numParticles)){
            initFlag = true;
        }else if((0 <= id) && (id < endSpawnIndex)){
            initFlag = true;
        }
    }else{
        if(init->spawnIndex <= id  &&  id < endSpawnIndex){
            initFlag =true;
        }
    }
    
    if(initFlag){
        pos[0] = init->origin[0] + (init->originSpread[0] *rand[0] );
        pos[1] = init->origin[1] + (init->originSpread[1] *rand[1] );
        pos[2] = init->origin[2] + (init->originSpread[2] *rand[2] );
        p->orientation[0] = init->orientation[0] + (init->orientationSpread[0] * rand[0]);
        p->orientation[1] = init->orientation[1] + (init->orientationSpread[1] * rand[1]);
        p->orientation[2] = init->orientation[2] + (init->orientationSpread[2] * rand[2]);
        p->acceleration[0] = init->acceleration[0] + (init->accelerationSpread[0] * rand[0]);
        p->acceleration[1] = init->acceleration[1] + (init->accelerationSpread[1] * rand[1]);
        p->acceleration[2] = init->acceleration[2] + (init->accelerationSpread[2] * rand[2]);
        p->age = 0;
        p->lifeSpan = init->lifeSpan[0];
    }
}

//1D kernel
__kernel void updateIsoPoints(
                      __global IsoPoint* isoPoints, // iso point
                      __global float *points){ // gl vbo buffer of particles

    int id = get_global_id(0); // get index of iso point
    __global  IsoPoint *isoPoint = &isoPoints[id];
    //reset;
    isoPoint->isoValue = 0.0;
    isoPoint->xn = 0.0;
    isoPoint->yn = 0.0;
    isoPoint->zn = 0.0;
    
    for(int i= 0; i < numParticles; i++){
        __global float *pos = &points[i*3];

        // distance between this point and particle
        float px = pos[0] - isoPoint->x;
        float py = pos[1] - isoPoint->y;
        float pz = pos[2] - isoPoint->z;
        
        float weightedDistance = (px*px + py*py +pz*pz);
        
        isoPoint->xn -= px/weightedDistance;
        isoPoint->yn -= py/weightedDistance;
        isoPoint->zn -= pz/weightedDistance;
        
        // isoValue is increased radically when the distances between the point and particles are near
        isoPoint ->isoValue += 1.0/weightedDistance;
    }

    //normalize
    float length = sqrt(isoPoint->xn * isoPoint->xn +
                        isoPoint->yn * isoPoint->yn +
                        isoPoint->zn * isoPoint->zn);
    isoPoint->xn /= length;
    isoPoint->yn /= length;
    isoPoint->zn /= length;
}


int getPointPos(int x,int y, int z)
{
    //return x+(y*resolution)+(z*resolution*resolution);
    return x*resolution*resolution+y*resolution+z;
}

IsoPoint vertexInterpolation(__global IsoPoint *point1, __global IsoPoint *point2) {

    IsoPoint point;
    float isoValue1 = point1->isoValue;
    float isoValue2 = point2->isoValue;
    float diffValue = isoValue2-isoValue1;
    float diff = (isoValue-isoValue1) / diffValue;
    
    point.xn = point1->xn + diff * (point2->xn-point1->xn);
    point.yn = point1->yn + diff * (point2->yn-point1->yn);
    point.zn = point1->zn + diff * (point2->zn-point1->zn);
    
    point.x = point1->x + diff * (point2->x-point1->x);
    point.y = point1->y + diff * (point2->y-point1->y);
    point.z = point1->z + diff * (point2->z-point1->z);

    return point;
}


// 3D Kernel one workitem processes one isocube
__kernel void createIsoSurface(
                               __global  IsoPoint* isoPoints, // iso points
                               __global float *triangleVbo, // triangle vbo
                               __global int *numberOfValidPoint, // for triangle vbo
                               __global int *edgeTable, // const
                               __global int *triTable){ // const

    int i = get_global_id(0);
    int j = get_global_id(1);
    int k = get_global_id(2);
    
    // get pointer to 8 points that construct a cube
    __global  IsoPoint *p1 = &isoPoints[getPointPos(i,j,k)];
    __global  IsoPoint *p2 = &isoPoints[getPointPos(i+1,j,k)];
    __global  IsoPoint *p3 = &isoPoints[getPointPos(i+1,j,k+1)];
    __global  IsoPoint *p4 = &isoPoints[getPointPos(i,j,k+1)];
    __global  IsoPoint *p5 = &isoPoints[getPointPos(i,j+1,k)];
    __global  IsoPoint *p6 = &isoPoints[getPointPos(i+1,j+1,k)];
    __global  IsoPoint *p7 = &isoPoints[getPointPos(i+1,j+1,k+1)];
    __global  IsoPoint *p8 = &isoPoints[getPointPos(i,j+1,k+1)];
  

    // based on isoValue of each points, determine the type of cube (cube index)
    int cubeIndex = 0; // between 0 - 255
    if(p1->isoValue > isoValue) cubeIndex |= 1;
    if(p2->isoValue > isoValue) cubeIndex |= 2;
    if(p3->isoValue > isoValue) cubeIndex |= 4;
    if(p4->isoValue > isoValue) cubeIndex |= 8;
    if(p5->isoValue > isoValue) cubeIndex |= 16;
    if(p6->isoValue > isoValue) cubeIndex |= 32;
    if(p7->isoValue > isoValue) cubeIndex |= 64;
    if(p8->isoValue > isoValue) cubeIndex |= 128;
    
    // abort if iso value too week or strong
    if(cubeIndex == 0 || cubeIndex == 255){
        return;
    }
    
    // prepare the vertices of triangles
    IsoPoint vertices[12];
    for(int i = 0; i < 12; i++){
        vertices[i].x = 0.0;
        vertices[i].y = 0.0;
        vertices[i].z = 0.0;
        vertices[i].xn = 0.0;
        vertices[i].yn = 0.0;
        vertices[i].zn = 0.0;
        vertices[i].isoValue = 0.0;
    }
    
    int edge  = edgeTable[cubeIndex];
    if((edge & 1)==1)       vertices[0]  = vertexInterpolation(p1, p2);
    if((edge & 2)==2)       vertices[1]  = vertexInterpolation(p2, p3);
    if((edge & 4)==4)       vertices[2]  = vertexInterpolation(p3, p4);
    if((edge & 8)==8)       vertices[3]  = vertexInterpolation(p4, p1);
    if((edge & 16)==16)     vertices[4]  = vertexInterpolation(p5, p6);
    if((edge & 32)==32)     vertices[5]  = vertexInterpolation(p6, p7);
    if((edge & 64)==64)     vertices[6]  = vertexInterpolation(p7, p8);
    if((edge & 128)==128)   vertices[7]  = vertexInterpolation(p8, p5);
    if((edge & 256)==256)   vertices[8]  = vertexInterpolation(p1, p5);
    if((edge & 512)==512)   vertices[9]  = vertexInterpolation(p2, p6);
    if((edge & 1024)==1024) vertices[10] = vertexInterpolation(p3, p7);
    if((edge & 2048)==2048) vertices[11] = vertexInterpolation(p4, p8);
    
    //pointer to the triangleVbo
    
    __global float *targetIndex = &triangleVbo[*numberOfValidPoint];
    IsoPoint *tri0, *tri1, *tri2;

    for(int i=0; i<15; i+=3) { // 0, 3, 6, 9, 12

        if(triTable[cubeIndex*16+i] == -1) // [256][16] = 4096
            continue;
    
        tri0 = &vertices[triTable[cubeIndex*16+i]];
        tri1 = &vertices[triTable[cubeIndex*16+i+1]];
        tri2 = &vertices[triTable[cubeIndex*16+i+2]];

        targetIndex[0] = tri0->x;
        targetIndex[1] = tri0->y;
        targetIndex[2] = tri0->z;
        
        targetIndex[3] = tri1->x;
        targetIndex[4] = tri1->y;
        targetIndex[5] = tri1->z;
        
        targetIndex[6] = tri2->x;
        targetIndex[7] = tri2->y;
        targetIndex[8] = tri2->z;
    
        (*numberOfValidPoint) += 9; // advance index by 9 (x, y, z ) * 3;
    }

}
