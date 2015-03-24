//
//  Person.m
//  RaiseMan
//
//  Created by Chikashi Miyama on 16/01/15.
//  Copyright (c) 2015 Chikashi Miyama. All rights reserved.
//

#import "Person.h"

@implementation Person
@synthesize personName;
@synthesize expectedRaise;

- (id)init
{
    self = [super init];
    if(self){
        expectedRaise = 0.05;
        personName = @"New Person";
        
    }
    return  self;
}

@end
