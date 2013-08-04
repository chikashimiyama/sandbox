#include <iostream>

class Origin{
public:
  void saySomething(){
    testFunc();
  };
  void testFunc(void){
    std::cout << "chikashi\n";
  };
};

class Derived : public Origin{
public:
  void testFunc(void){
    std::cout << "miyama\n";
  }
};

int main(){
   Origin *test = new Derived();
   Derived *casted = (Derived*)test;
    casted->testFunc();

  return 0;
}
