#include <time.h>
#include <math.h>
#include <stdio.h>
int main(int argc, char const *argv[])
{
	
	clock_t start, end;
	int repeat = 44100;
	float result;
	start = clock();
	while(repeat--){
		result = cos(repeat);
	}
	end = clock();
	printf("%.10f seconds elapsed\n",(double)(end-start)/CLOCKS_PER_SEC);

	return 0;
}