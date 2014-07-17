
__kernel void average( __global float* incoming, __global float* average){
	float sum = 0.0;
	for(int i = 0; i< 10000; i++){
		sum = sum + incoming[i];
	}
	average[0] = sum / 10000.0;
}