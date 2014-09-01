
class A{
public:
	A(int x):y(x){}

private:
	int y;
};

class B : public A{

};


int main(int argc, char const *argv[])
{
	B b(30);
	return 0;
}