#include <iostream>

class Test{
public:
	int a;
	const int &getA() const{return a;} ;
};

using namespace std;

void changeTest(Test t);
void changeTestWithRef(Test &t);
void changeTestWithConstRef(const Test &t);
void changeTestWithPtr(Test *t);
void changeTestWithConstPtr(const Test *t);


int main(void){

	Test test;
	test.a = 25;

	cout << test.getA() << endl;
	int &x = test.getA();
	x = 30;

	cout << test.getA() << endl;


	changeTest(test); // normal. will be copied
	cout << test.a	 << endl;

	changeTestWithRef(test); 
	cout << test.a	 << endl;

	changeTestWithConstRef(test); 
	cout << test.a	 << endl;

	changeTestWithPtr(&test);
	cout << test.a	 << endl;

	changeTestWithConstPtr(&test); 
	cout << test.a	 << endl;


	return 0;
}


void changeTest(Test t){
	t.a = 125;
}

void changeTestWithRef(Test &t){
	t.a = 225;
}

void changeTestWithConstRef(const Test &t){
	//t.a = 325; impossible
}

void changeTestWithPtr(Test *t){
	t->a = 425;
}

void changeTestWithConstPtr(const Test *t){
	//t->a = 525;
}