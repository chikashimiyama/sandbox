#include <iostream>
using namespace std;
int main(int argc, char const *argv[])
{
    [](string const &str){ std::cout<<str<<std::endl;}("fff");
    return 0;
}