#include <iostream>

using namespace std;

class Root{

private:
	int value;

public:
	Root(){};
	Root(int x):value(x){};
	int getValue(){return value;};
};

class Sub: public Root{
public:
	Sub(){};
	Sub(int x):Root(x){};
};


int main(){

	Sub s(3);
	cout << s.getValue() << endl;
	return 0;
}