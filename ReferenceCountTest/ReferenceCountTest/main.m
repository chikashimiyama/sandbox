//
//  main.m
//  ReferenceCountTest
//
//  Created by Chikashi Miyama on 15/01/15.
//  Copyright (c) 2015 Chikashi Miyama. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>

int main(int argc, const char * argv[]) {
    
        NSDate *date = [NSDate date];
        
        NSLog(@"rc = %d", (unsigned)[date  retainCount]);
        
        
        NSMutableArray *array = [[NSMutableArray alloc] init];
        [array addObject:date];
        
        NSLog(@"rc = %d", (unsigned)[date  retainCount]);

        [array release];

        NSLog(@"rc = %d", (unsigned)[date  retainCount]);
        [date release];

        

    return 0;
}
