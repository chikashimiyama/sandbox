#include <iostream>

using namespace std;

class Sceond;

class First{
  friend class Second;
private:
  First(void){
    //private constructor
    cout << "test" << endl; 
  }
};

class Second{
public: 
  void doIt(void){
    First ff = First();
  }
};

int main(void){
  // First f;  cause an error
  Second s;
  s.doIt();
  return 0;
}
