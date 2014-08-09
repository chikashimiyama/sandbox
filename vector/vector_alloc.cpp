#include <vector>
#include <iostream>

using namespace std;
int main(void){
	vector<int> test(29);
	cout << test.size();

	test.resize(5);
	cout << test.size();

	return 0;

}