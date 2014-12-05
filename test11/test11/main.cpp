//
//  main.cpp
//  test11
//
//  Created by Chikashi Miyama on 12/10/14.
//  Copyright (c) 2014 Chikashi Miyama. All rights reserved.
//

#include <iostream>
#include <vector>



int main(int argc, const char * argv[])
{

    
    std::vector<int> myvector(10);
    auto index = 100;
    
    try {
        myvector.at(index)=100;
        
        
    }
    catch (const std::out_of_range& oor) {
        std::cerr << "Out of Range error: " << oor.what() << '\n';
        index = myvector.size()-1;
    }
    return 0;
    
}

