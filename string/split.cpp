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

    string s1 = "miyama";
    string s2 = "chikashi";

    if(s1 < s2){
	cout << "true" << endl;
    }
    return 0;
}
