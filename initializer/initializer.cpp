
class Test{
	int x;
public:
	Test(int x); // mandatory init
};

Test::Test(int x){
	Test::x = x;
}

class HasTest{
	Test t;
public:
	HasTest() : t(30){};
};

int main(void){

	HasTest x;
	return 0 ;
}