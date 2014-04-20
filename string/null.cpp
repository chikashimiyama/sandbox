#include <iostream>
#include <string>

using namespace std;
int main(void){
  string str;
  char *c = "test\0one";
  str = c;
  cout << str[6]<<endl;
  cout << c[6]<<endl;
  return 0; 

}
