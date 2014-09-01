#include <iostream>

using namespace std;

class Test{
public:
	double member;

	Test(){ cout << "constructed" << endl;};
	Test(const Test &rhs){ 
		this->member = rhs.member;
		cout << "constructed from copy" << endl;
	}
	~Test(){ cout << "destructed" << endl;}
	Test &operator= (const Test &rhs){
		this->member = rhs.member;
		cout << "assigned" << endl;
		return *this;
	}

	
};

int main(int argc, char const *argv[])
{
	Test t1;
	t1.member = 30.0;
	cout << "Test t2(t1)" << endl;
	Test t2(t1);
	cout << "Test t3 = t2;" <<endl;
	Test t3 = t2;
	Test t4, t5;
	cout << "t4 = t3;" <<endl;
	t5 = t4 = t3;
	cout << t4.member << endl;

	return 0;
}