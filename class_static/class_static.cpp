#include <iostream>

using namespace std;

class Parent{
    
};

class Child: public Parent{
public:
    static const int myValue;
};

const int Child::myValue = 3;

int main(void){
    class Child c;

    Parent *p = &c;
    cout << p->myValue << endl;

    return 0;
}
