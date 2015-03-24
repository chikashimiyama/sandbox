//
//  main.m
//  ExceptionTest
//
//  Created by Chikashi Miyama on 15/01/15.
//  Copyright (c) 2015 Chikashi Miyama. All rights reserved.
//

#import <Foundation/Foundation.h>

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        NSArray *array = [[NSMutableArray new] init];
        BOOL flag =[array count] > 0;
        NSAssert(flag, @"array must contain something");

        
        [array objectAtIndex:0];
    }
    return 0;
}
