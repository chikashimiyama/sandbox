#include<iostream>
#include<typeinfo>
using namespace std;

class testType{
public:
  int someValue;
};


int main(void){
  testType a,*b;
  b = new testType;
  cout << "typeid:" << typeid(a).name() << "\n";
  cout << "typeid:" << typeid(b).name() << "\n";
  cout << "typeid:" << typeid(*b).name() << "\n";
  return 0;
}
