#include <iostream>

using namespace std;
class Singleton{
	private:
    	Singleton(){}
    	Singleton(const Singleton& rhs);
    	Singleton& operator=(const Singleton& rhs);	
    	int value;
	public:
		static Singleton* getInstance(void){
			static Singleton singleton;
			return &singleton;
		}
		void setValue(int v){
			value = v;
		}
		int getValue(void){
			return value;
		}
};

int main(void){
	Singleton *instance = Singleton::getInstance();
	instance->setValue(35);
	cout << instance->getValue() << endl;
	Singleton *object = Singleton::getInstance();
	cout << object->getValue() << endl; 

}