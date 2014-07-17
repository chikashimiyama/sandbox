
__kernel void average( __global int* incoming, __global int* result){
	int id = get_global_id(0);

	result[id] =  id/2;
}