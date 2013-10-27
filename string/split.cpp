#include <string>
#include <sstream>
#include <iostream>
using namespace std;

int main(){

    string str = "media direct-to-one interpolation";
    istringstream iss(str);
    
    while(iss.good()){
	string split;
	iss >> split;
	cout << split << endl;
    }
    return 0;
}
