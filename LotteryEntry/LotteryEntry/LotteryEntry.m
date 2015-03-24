//
//  LotteryEntry.m
//  LotteryEntry
//
//  Created by Chikashi Miyama on 15/01/15.
//  Copyright (c) 2015 Chikashi Miyama. All rights reserved.
//

#import "LotteryEntry.h"

@implementation LotteryEntry

- (NSString *) description
{
    NSDateFormatter *df = [[NSDateFormatter alloc] init];
    [df setTimeStyle:NSDateFormatterNoStyle];
    [df setDateStyle:NSDateFormatterMediumStyle];
    NSString *result;
    result = [[NSString alloc] initWithFormat:@"%@ = %d and %d", [df stringFromDate:entryDate], firstNumber, secondNumber];
    return result;
}

-(id) init
{
    return [self initWithEntryDate:[NSDate date]];
}

-(id) initWithEntryDate:(NSDate *)theDate
{
    self = [super init];
    if(self)
    {
        NSAssert(theDate != nil, @"date assert");
        entryDate = theDate;
        firstNumber = ((int) random() % 100);
        secondNumber = ((int) random() % 100);
    }
    return self;
}

-(void) setEntryDate:(NSDate *)date
{
    entryDate = date;
}

-(NSDate *)entryDate
{
    return entryDate;
}

-(int)firstNumber
{
    return  firstNumber;
}

-(int)secondNumber
{
    return secondNumber;
}
@end
