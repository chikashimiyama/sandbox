#include <iostream>

class Pure{

  virtual void testFunc(void) = 0;  
};

void Pure::testFunc(void){

  std::cout << "test\n";
}

class Pure2 : Pure{
  void testFunc(void){
    cout << "testest\n";
  }
}

int main(void){

  return 0;
}
