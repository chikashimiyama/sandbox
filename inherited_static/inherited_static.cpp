#include <iostream>

using namespace std;

class Test{
public:
	int getCheck(int *checkPtr, int index){
		return checkPtr[index];
	}
};


// static array in subclass but function is in superclass
class Test2: public Test{
public:
	static int check[];
};

int Test2::check[5] ={40,20,30,10,80};

int main(){

	Test2 obj;
	cout << obj.getCheck(Test2::check, 3) << endl;
	return 0;
}