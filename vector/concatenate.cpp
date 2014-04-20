#include <vector>
#include <iostream>

using namespace std;
int main(void){
	vector<int> first(3, 3);
	vector<int> second(4, 4);
	
	first.insert(first.end(), second.begin(), second.end());

	vector<int>::iterator it = first.begin();
	while(it != first.end()){
		cout << *it << endl; 
		it++;
	}
	return 0;
}
