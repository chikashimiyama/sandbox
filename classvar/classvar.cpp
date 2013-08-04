#include <iostream>

typedef enum {
  RED , GREEN , BLUE 
}Ecolor;

class CVarTest{
public:
  Ecolor getColor(void){
    return color;
  }
private:
  const static Ecolor color;

};

const Ecolor CVarTest::color = BLUE;

int main(void){
  CVarTest a;
  std::cout  <<  a.getColor();
  return 0;
}
