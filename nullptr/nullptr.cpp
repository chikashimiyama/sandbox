#include <iostream>

using namespace std;
int main(void){
    
    int *ptr;
    ptr = new int(3);


    cout <<ptr << endl;
    delete ptr;
    ptr = NULL;
    cout <<ptr << endl;
    delete ptr;
    ptr = new int(15);
    cout <<ptr << endl;
    delete ptr;
return 0;
}
