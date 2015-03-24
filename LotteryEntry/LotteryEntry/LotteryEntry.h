//
//  LotteryEntry.h
//  LotteryEntry
//
//  Created by Chikashi Miyama on 15/01/15.
//  Copyright (c) 2015 Chikashi Miyama. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface LotteryEntry : NSObject {
    NSDate *entryDate;
    int firstNumber;
    int secondNumber;
}

-(id)init;
-(id)initWithEntryDate: (NSDate *)theDate;
-(void)setEntryDate: (NSDate *)date;
-(NSDate *) entryDate;
-(int)firstNumber;
-(int)secondNumber;


@end
