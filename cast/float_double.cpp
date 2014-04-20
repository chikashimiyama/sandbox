#include <iostream>
using namespace std;
int main(void){
	double dvalue[3] = {2.45, 3.12, 5.55};
	void* vptr = dvalue;
	double* dptr = static_cast<double*>(dptr);
	float* fptr = static_cast<float*>(dptr);

	cout << fptr[0] << ' ' << fptr[1] << ' ' << fptr[2];

	return 0;
}