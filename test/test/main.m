//
//  main.m
//  test
//
//  Created by Chikashi Miyama on 11/01/15.
//  Copyright (c) 2015 Chikashi Miyama. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "TestClass.h"

@class TestClass;

int main(int argc, const char * argv[]) {
    @autoreleasepool {

        TestClass * myTest = [TestClass alloc];
        [myTest setAge:35];
        [myTest debug];
        
        NSLog(@"Age of Chikashi is %d", [myTest age]);
    }
    return 0;
}
