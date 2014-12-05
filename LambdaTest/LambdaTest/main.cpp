//
//  main.cpp
//  LambdaTest
//
//  Created by Chikashi Miyama on 24/09/14.
//  Copyright (c) 2014 Chikashi Miyama. All rights reserved.
//

#include <iostream>
#include <vector>

double square(double);

double square(double somenum){
    return somenum * somenum;
}

class Test{

public:
    Test(int v = 0):value(v){std::cout<< "constructed" << std::endl;}
    virtual ~Test(){std::cout<<"destructed" << std::endl;}
    Test(const Test &src){
        std::cout << "copied" << std::endl;
        value = src.value;
    }
    Test(const Test &&other){
        std::cout << "moved" << std::endl;
        value = other.value;
    }
    Test & operator= (const Test &src){std::cout << "assigned" << std::endl;
        value = src.value;
        return *this;
    }
    Test & operator= (const Test &&src){std::cout << "move assigned" << std::endl;
        value = src.value;
        return *this;
    }
    
    int value;
    void printValue(){ std::cout << "value:" << value << std::endl;};
};



int main(int argc, const char * argv[]){
    auto sum = [](const std::vector<int> &nums){
        auto sum = 0;
        for( auto v : nums){
            sum += v;
        }
        return sum;
    };
    
    std::cout << sum({20, 30, 40, 50}) << std::endl;
    std::cout << sum({1, 3, 4, 5}) << std::endl;
    std::cout << sum({20, 30, 402, 510}) << std::endl;
    std::cout << sum({20, 30, 40, 504}) << std::endl;
    std::cout << sum({201, 130, 420, 50}) << std::endl;
    
    Test original(3);
    original.printValue();
    
    Test copied {original};
    copied.printValue();
    
    Test assigned;
    assigned = original;
    assigned.printValue();
    
    Test moved;
    moved = std::move(original);
    moved.printValue();
    
     return 0;
    
}

