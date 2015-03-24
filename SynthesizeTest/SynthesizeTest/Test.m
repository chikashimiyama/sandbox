//
//  Test.m
//  SynthesizeTest
//
//  Created by Chikashi Miyama on 16/01/15.
//  Copyright (c) 2015 Chikashi Miyama. All rights reserved.
//

#import "Test.h"

@implementation Test
@synthesize myValue;
- (NSString *)description{
    return [NSString stringWithFormat:@"My Value: %d", [myValue intValue]];
}

@end
