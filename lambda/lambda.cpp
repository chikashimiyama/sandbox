#include <iostream>
using namespace std;
int main(int argc, char const *argv[])
{
    auto test = [](string const &str){ std::cout << str << std::endl; };
    return 0;
}