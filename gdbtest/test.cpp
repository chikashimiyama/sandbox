
#include <iostream>
#include <cfloat>
#include <tgmath.h>
#define EPSILON 0.0000001

using namespace std;

bool isEqual(double a, double b){
	const double absA = fabs(a);
	const double absB = fabs(b);
	const double diff = fabs(a-b);

	cout << "a:" << a << endl;
	cout << "b:" << b << endl;
	cout << "diff:" << diff << endl;

	if(a == b){ // short cut
		return true;
	}else if( a == 0.0 || b == 0.0 || diff < DBL_MIN) { // if a or b is 0 or the difference is extremely small
		return diff > (EPSILON * DBL_MIN);
	}else{
		return diff / (absA + absB) < EPSILON;
	}
}

int main(void){
	float  a = 11153.251251324;
	double b = 11153.251251324;
	cout.precision(64);

	double casted_a = static_cast<double>(a);

	// with normal comparison
	cout << "-------- normal comparison -------- " << endl;
	if(casted_a == b){
		cout << "equal" << endl;
	}else{
		cout << "not equal" << endl;
		cout << "a:" << casted_a << endl;
		cout << "b:" << b << endl;
	}

	cout << " -------- comparison with epsilon --------" << endl;
	if(isEqual(casted_a, b)){
		cout << "equal" << endl;
	}else{
		cout << "not equal" << endl;
	}



	return 0;
}







