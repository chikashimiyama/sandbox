#include <iostream>
#include <limits>

int main(){
	int imax = std::numeric_limits<int>::max();
	std::cout << imax << std::endl;
	return 0;
}