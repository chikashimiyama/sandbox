#include <sstream>
#include <iostream>
using namespace std;

int main(void){
    
    string x = "/aaa/bbb ,iii 2 3 1";
    istringstream s(x);    
    string arg;

    while(s.good()){
	  s >> arg;
	  cout << arg << endl;
    }

    return 0;
}
