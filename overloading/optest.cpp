
#include <iostream>
using namespace std;

class OpTest{
	string someString;

	public:
	OpTest():someString("This is test"){};

	char &operator[](int const x) {
		return someString[x];
	}

	operator std::string(){
		return someString;
	}

};

int main(int argc, char const *argv[])
{
	OpTest ot;
	std::string str;
	cout << ot[0] << endl;
	ot[0] = 't';
	str = ot;
	cout << str << endl;
	return 0;
}
