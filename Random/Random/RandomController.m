//
//  RandomController.m
//  Random
//
//  Created by Chikashi Miyama on 15/01/15.
//  Copyright (c) 2015 Chikashi Miyama. All rights reserved.
//

#import "RandomController.h"

@implementation RandomController


- (void)awakeFromNib
{
    NSDate *now;
    now = [NSDate date];
    [textField setObjectValue:now];
}

- (IBAction)seed: (id)sender
{
    srandom((unsigned)time(NULL));
    [textField setStringValue:@"Generator seeded"];
}

- (IBAction)generate: (id)sender
{
    int generated;
    generated = (int)(random() % 100);
    NSLog(@"generated = %d", generated);
    [textField setIntValue:generated];
}

@end
