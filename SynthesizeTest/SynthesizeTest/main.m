//
//  main.m
//  SynthesizeTest
//
//  Created by Chikashi Miyama on 16/01/15.
//  Copyright (c) 2015 Chikashi Miyama. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Test.h"

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        Test * testing = [[Test alloc] init];
        [testing setValue:[NSNumber numberWithInt:300] forKey:@"myValue"];
        NSLog(@"%@",[testing description]);
        [testing setMyValue:[NSNumber numberWithInt:500]];
        NSLog(@"%@",[testing description]);
        
    }
    return 0;
}
