#include <iostream>
using namespace std;
class Test{
	int x;
public:
	Test(int x); // mandatory init
};

Test::Test(int x){
	Test::x = x;
}

class HasTest{
	Test t;
public:
	HasTest() : t(30){};
};

class Test2{
public:
	Test2(int input = 800):in(input){};
	int in;
};

int main(void){

	HasTest x;
	Test2 t2(200);

	cout << t2.in << endl;
	return 0 ;

}