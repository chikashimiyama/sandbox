#include <iostream>
using namespace std;

class Parent{
public:
    static const int x;
    static const int y[];

    bool isEqualToX(int inx);
};
const int Parent::x = 20;

bool Parent::isEqualToX(int inx){
    if(x == inx){
	return true;
    }
    return false;
}


const int Parent::y[] = {4, 5, 3};

int main(void){

    Parent c;
    if(c.isEqualToX(20)){
	cout << "same" << endl;
    }

    cout << c.x << endl;
    cout << sizeof(c.y)/sizeof(c.y[0]) << endl;

}
