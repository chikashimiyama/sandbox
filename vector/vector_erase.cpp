#include <vector>
#include <iostream>

using namespace std;
int main(void){
	vector<int> test;
	test.push_back(3);
	test.push_back(4);
	test.push_back(5);


	cout << test.size() << ' ' << test[0] << ' ' <<test[1] << endl;


}