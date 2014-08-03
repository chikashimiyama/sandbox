#include <iostream>
using namespace std;

template<typename T>
T multi(T a, T b){
	return a * b;
}

int main(){
	float x = multi(2.3 , 3.1);
	cout << x << endl;
}