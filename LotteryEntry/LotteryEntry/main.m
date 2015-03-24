//
//  main.m
//  LotteryEntry
//
//  Created by Chikashi Miyama on 15/01/15.
//  Copyright (c) 2015 Chikashi Miyama. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "LotteryEntry.h"

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        NSDate *now = [[NSDate alloc] init];
        NSCalendar *cal = [NSCalendar currentCalendar];
        NSDateComponents *weekComponents = [[NSDateComponents alloc] init];
        srandom((unsigned) time (NULL));
        NSMutableArray *array;
        array = [[NSMutableArray alloc] init];
        
        int i;
        for(i = 0; i < 10; i++){
            [weekComponents setWeek:i];
            
            NSDate *iWeeksFromNow;
            iWeeksFromNow = [cal dateByAddingComponents:weekComponents toDate:now options:0];
            
            LotteryEntry *newEntry = [[LotteryEntry alloc]initWithEntryDate:iWeeksFromNow];
            [newEntry setEntryDate:iWeeksFromNow];
            [array addObject:newEntry];
        }
        [now release];
        [weekComponents release];
        for(LotteryEntry *entryToPrint in array){
            NSLog(@"%@", entryToPrint);
        }
        [array release];
    }
    return 0;
}
