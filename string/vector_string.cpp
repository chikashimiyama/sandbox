#include <string>
#include <vector>
#include <iostream>

using namespace std;

vector<string> testfunc(){
  vector<string> strVec;
  strVec.push_back("foo");
  strVec.push_back("bar");
  return strVec;
}

int main(void){
  vector<string> sv =  testfunc();
  cout << sv[0] << endl;
  cout << sv[1] << endl;
  return 0;
}
