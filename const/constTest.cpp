#include <iostream>


void constFunc(int given){
	given += 30;
} 


// this is useful when I do not want to copy the value but do not want to change the value
void referenceTest(const int& given){
	std::cout << given << std::endl;
	//given += 20;
}

void funcTest(const int given){
	std::cout << given << std::endl;
	// given += 20; impossible
}

int main(){
	const int fixedValue = 30;
	int unfixedValue = 40;

	// fixedValue += 10; // cannot change

	funcTest(unfixedValue);
	referenceTest(unfixedValue);

	return 0;
}