//
//  WaveformView.m
//  LibPDTest
//
//  Created by Chikashi Miyama on 24/03/15.
//  Copyright (c) 2015 Chikashi Miyama. All rights reserved.
//

#import "WaveformView.h"

@implementation WaveformView
@synthesize waveBuffer;
@synthesize size;

- (BOOL)isFlipped{
    return YES;
}

- (void)drawRect:(NSRect)dirtyRect {
    [super drawRect:dirtyRect];
    [[NSColor whiteColor] setFill];
    NSRectFill(dirtyRect);
    float width = [self frame].size.width;
    float ratio = width / (float)size ;
    
    float  height = [self frame].size.height;
    
    NSBezierPath * bezierPath = [NSBezierPath bezierPath];
    [bezierPath setLineWidth:0.5];
    [bezierPath moveToPoint:NSMakePoint(0, height/2)];
    for(int i = 0; i < size; i++) {
        float val = waveBuffer[i];
        [bezierPath lineToPoint:NSMakePoint(i*ratio, val * height/2+height/2)];
    }
    [bezierPath stroke];
}

@end
