//
//  main.cpp
//  constCopy
//
//  Created by Chikashi Miyama on 05/12/14.
//  Copyright (c) 2014 Chikashi Miyama. All rights reserved.
//

#include <iostream>

class Test{
public:
    Test(int v):someValue(v){};
    int getValue(){return someValue;}
private:
    const int someValue;
};

int main(int argc, const char * argv[]) {

    Test test(5);
    Test test2(3);
    test2 = test;
    std::cout << test2.getValue() << std::endl;
    return 0;
}
