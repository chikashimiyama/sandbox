
#include <iostream>
using namespace std;

class OpTest{
	public:
	OpTest():someString("This is test"){};
	string someString;

	char operator[](int x){
		return someString[x];
	}
};

int main(int argc, char const *argv[])
{
	OpTest ot;
	cout << ot[3] << endl;
	return 0;
}
