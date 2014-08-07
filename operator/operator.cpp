#include <iostream>

using namespace std;

class  OperatorTest{
public:
	int x;
	void operator +(int input);
	void operator *(int input);
	operator std::string();
};

void OperatorTest::operator +(int input){
	x += input;
}

void OperatorTest::operator *(int input){
	x *= input;
}

OperatorTest::operator std::string(){
	return std::string("converted string");
}

int main(){
	OperatorTest opt;
	opt.x = 20;
	opt + 10;
	opt * 10;
	std::string receivedString = opt;
	cout << receivedString;
	return 0;
}