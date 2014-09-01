#include <iostream>

void count(const int* const arPtr ) {
	std::cout << sizeof(arPtr) / sizeof(int) << std::endl;
}

int main(){

	int array[] = {3, 5, 2, 1, 5, 23, 2};
	std::cout << sizeof(array) / sizeof(int) << std::endl;

	count(array);
 	return 0;
}
