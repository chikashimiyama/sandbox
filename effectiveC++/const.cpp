#include <iostream>
using namespace std;

class Test{
public:
	Test(){};
	const void operator<<(int x) const {cout << "const" << endl;};
	void operator<<(int x) {cout << "no const" << endl;};
};

class ConstTest{
public:
	ConstTest(){};
	mutable int x;
	int y;
};

int main(){
	// normal
	char greeting1[] = "hello";
	char greeting2[] = "bye";

	greeting1[0] = 'H'; // possible to change

	char* p1 = greeting1;
	p1 = greeting2;

	// the data cannot be changed but the address can be changed
	const char* p2 = greeting1;
	// p2[0] = 'h'; error
	p2 = greeting2; 

	char const* p2a = greeting1;
	//p2a[0] = 'h'; error
	p2a = greeting2; 

	// the data can be changed but the address can not be changed
	char* const p3 = greeting1;
	p3[0] = 'h';
	//p3 = greeting2; error

	// the both data and address cannot be changed
	const char* const p4 = greeting1;
	//p4[0] = 'H';
	//p4 = greeting2;

	// invokes different functions
	Test t;
	const Test tc;
	t << 3;
	tc << 3;

	// mutable against const 
	ConstTest ct;
	ct.x = 9;
	ct.y = 10;

	const ConstTest ct2;
	ct2.x = 9;
	//ct2.y = 10; non mutable

	return 0;
}