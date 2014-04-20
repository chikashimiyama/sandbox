#include <iostream>
#include <iomanip>
using namespace std;
int main(void){
	float fnum = 0.078;
	double dnum = 0.078;
	double dnumFromFloat = static_cast<double>(fnum);

	if(dnum == dnumFromFloat){
		cout << "same" << endl;
	}else{
		cout << "different" << endl;
		cout << "dnumFromFloat:" << setprecision(64) << dnumFromFloat << endl;
		cout << "dnum         :" << setprecision(64) <<  dnum << endl;
	}
	return 0;
}