
#include <string>
#include <iostream>
class StrTest{
	public:
	StrTest(bool flag){
		std::cout << "bool invoked" << std::endl;
	};
	StrTest(const char* const cstr){
		StrTest(std::string(cstr));
	}
	StrTest(const std::string &inStr){
		std::cout << "str invoked" << std::endl;
	};
};

int main(void){

	StrTest("testest");
	return 0;

}