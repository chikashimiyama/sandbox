//
//  CustomView.m
//  CustomView
//
//  Created by Chikashi Miyama on 01/03/15.
//  Copyright (c) 2015 Chikashi Miyama. All rights reserved.
//

#import "CustomView.h"

@implementation CustomView

- (void)drawRect:(NSRect)dirtyRect {
    [super drawRect:dirtyRect];

    [[NSColor greenColor] setStroke];
    NSBezierPath * path = [NSBezierPath bezierPath];
    [path setLineWidth:3.5f];

    [path moveToPoint:NSMakePoint(0, 0)];
    [path lineToPoint:NSMakePoint(300, 300)];
    [path stroke];
    // Drawing code here.
}

@end
