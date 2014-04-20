#include <string>
#include <iostream>

using namespace std;

void stringAdd(string &givenString){

  givenString = "foo bar";

}

int main(void){

  string str;
  stringAdd(str);
  cout << str << endl;

  return 0;
}
