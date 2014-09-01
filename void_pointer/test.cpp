#include <iostream>

using namespace std;

void testVPtr(void* const vPtr){
	double *dPtr = static_cast<double*>(vPtr);
	cout << dPtr[2] << endl;
}

int main(){
	double* dPtr = new double[3];

	dPtr[0] = 2.0;
	dPtr[1] = 3.0;
	dPtr[2] = 4.0;

	void* vPtr = dPtr;
	testVPtr(vPtr);

	return 0;
}