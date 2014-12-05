#include<iostream>
#include<typeinfo>
using namespace std;
int main(void){
  unsigned int x;
  cout << "typeid:" << typeid(x).name() << "\n";
  return 0;
}
