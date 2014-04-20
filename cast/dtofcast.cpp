#include <iostream>
#include <iomanip>

using namespace std;

int main(void){
	double dval = 0.078;
	float fval = 0.078;
	float dtofval = static_cast<float>(dval);

	cout << "float  value 0.078 is:            " << setprecision(64)  << fval << endl;
	cout << "double value 0.078 is:            " << setprecision(64)  << dval << endl;
	cout << "float value casted from double is:" << setprecision(64)  << fval << endl;

	cout << "float value 0.078 and double value casted from float value is: ";
	
	if(fval == dtofval){
		cout << "same" << endl;
	}else{
		cout << "different" << endl;
	}

}