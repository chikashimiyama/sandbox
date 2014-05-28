#include <time.h>
#include <math.h>
#include <stdio.h>
int main(int argc, char const *argv[])
{
	
	clock_t start, end;
	int repeat = 44100;
	int resolution = 8096;
	float table[resolution];
	float result;

	for(int i = 0; i < resolution; i++){
		table[i] = sin(M_PI_2/ resolution);
	}

	start = clock();
	while(repeat--){
		result = sin(repeat);
	}
	end = clock();
	printf("%.10f seconds elapsed\n",(double)(end-start)/CLOCKS_PER_SEC);

	start = clock();
	repeat = 44100;
	while(repeat--){
		result = table[repeat % resolution];
	}
	end = clock();
	printf("%.10f seconds elapsed\n",(double)(end-start)/CLOCKS_PER_SEC);


	return 0;
}