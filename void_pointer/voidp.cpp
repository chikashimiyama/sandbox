#include <iostream>

using namespace std;

void* void_alloc(){
  
  float* test =  new float[3];
  
  return static_cast<void *>(test);
}

int main(void){

  void* vptr;
  vptr = void_alloc();
  
  float* fptr;
  fptr = static_cast<float*>(vptr);

  fptr[0] = 3.0;
  fptr[1] = 2.0;
  fptr[2] = 5.0;

  delete fptr;

  return 0;
}

