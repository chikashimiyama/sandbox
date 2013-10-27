
#include <iostream>

using namespace std;

class classA{
public:
  virtual void doSomething(){
    std::cout << "test" << std::endl;
  }
};

class classB: public classA{
public:
  void doSomething(){
    std::cout << "exam!" << std::endl;
  }

};

int main(void){
  classB b;  
  b.doSomething();
  classA *bPtr = &b;
  bPtr->doSomething();
  return 0;
}
