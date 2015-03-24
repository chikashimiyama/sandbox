//
//  main.m
//  lottery
//
//  Created by Chikashi Miyama on 15/01/15.
//  Copyright (c) 2015 Chikashi Miyama. All rights reserved.
//

#import <Foundation/Foundation.h>

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        // insert code here...
        NSMutableArray *array;
        array = [[NSMutableArray alloc] init];
        int i;
        for(i = 0; i < 10; i++){
            NSNumber *newNumber = [[NSNumber alloc] initWithInt:(i*3)];
            [array addObject:newNumber];
        }
        
        for(i = 0; i < [array count]; i++){
            NSNumber *numberToPrint = [array objectAtIndex:i];
            NSLog(@"The number t index %d is %@", i, numberToPrint);

        }

        NSLog(@"Hello, World!");
    }
    return 0;
}
