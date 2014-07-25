

__constant int table[] = { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160};

__kernel void d1Count( __global int* incoming, __global int* result){
	int id = get_global_id(0);
	result[id] =  table[id];
}
__kernel void d2Count( __global int* incoming, __global int* result){
	int x = get_global_id(0);
    int y = get_global_id(1);
    int id = x*4 + y;
	result[id] =  id;
}
__kernel void d3Count( __global int* incoming, __global int* result){
	int x = get_global_id(0);
    int y = get_global_id(1);
    int z = get_global_id(2);
    int id = x*8 + y*4 + z;
	result[id] =  id;
}
__kernel void sum( __global int* incoming, __global int* result){

	int x = get_global_id(0);
	incoming[x] = x;
	barrier(CLK_GLOBAL_MEM_FENCE);
	if(x == 0){
		int sum = 0;
		for(int i = 0; i < 16; i++){
			sum += incoming[i];
		}
		result[0] = sum;
	}
}
__kernel void locTest( __global int* incoming, __global int* result){
	int x = get_local_id(0);
	int y = get_global_id(0);
	local int l[4];
	l[x] = x;
	result[y] = x;
	barrier(CLK_LOCAL_MEM_FENCE);
	if(x == 0){
		result[y] = 0;
		for(int i = 0; i < 4; i++){
			result[y] += l[i];
		}
	}

	barrier(CLK_GLOBAL_MEM_FENCE);
	if(y == 0){
		int sum = 0;
		for(int i = 0; i < 16; i=i+4){
			sum += result[i];
		}
		result[0] = sum;
	}
}

__kernel void size( __global int* incoming, __global int* result){
	int size = get_global_size(0);
	int id = get_global_id(0);
	result[id] = size;
}

__kernel void atomic( __global int* incoming, __global int* result){
	int id = get_global_id(0);
	int temp;
	temp = atomic_inc(&incoming[0]);
	/*incoming[0]++;*/
	result[id] = temp;
}



