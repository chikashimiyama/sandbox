//
//  VBO.m
//  CocoaOpenGL
//
//  Created by Chikashi Miyama on 22/03/15.
//  Copyright (c) 2015 Chikashi Miyama. All rights reserved.
//

#import "VBO.h"

#import <OpenGL/gl.h>
#import <OpenGL/gl3.h>

@implementation VBO

-(id)initWithArray:(NSArray*) array{
    self = [super init];
    
    if(self){
        
        numVertices = (GLsizei)[array count] ;
        GLsizei numCoords = numVertices * 3;
        GLsizei dataSize = numCoords * sizeof(GLfloat);
        
        GLfloat * points3D = (GLfloat *)malloc(dataSize);
        
        for(int i = 0; i < numVertices; i++){
            NSValue * dot = [array objectAtIndex:i];
            NSPoint point = [dot pointValue];
            int offset = i*3;
            points3D[offset] = point.x;
            points3D[offset+1] = point.y;
            points3D[offset+2] = 0.0;
        }

        
        glGenBuffers (1, &vboNumber);
        glBindBuffer (GL_ARRAY_BUFFER, vboNumber);
        glBufferData (GL_ARRAY_BUFFER, dataSize, points3D, GL_STATIC_DRAW);
        glBindBuffer (GL_ARRAY_BUFFER, 0);
        free(points3D);

    }
    return self;
}



-(void)render{
    glBindBuffer(GL_ARRAY_BUFFER, vboNumber);
    glEnableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glDrawArrays(GL_LINE_STRIP, 0, numVertices );
    glBindBuffer(GL_ARRAY_BUFFER, 0);


}
@end
