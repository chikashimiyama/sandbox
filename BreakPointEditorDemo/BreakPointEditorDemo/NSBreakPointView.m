//
//  NSBreakPointView.m
//  BreakPointEditorDemo
//
//  Created by Chikashi Miyama on 22/01/15.
//  Copyright (c) 2015 Chikashi Miyama. All rights reserved.
//

#import "NSBreakPointView.h"

@implementation NSBreakPointView

- (NSPoint)randomPoint{
    NSPoint result;
    NSRect r = [self bounds];
    result.x = r.origin.x + random() % (int) r.size.width;
    result.y = r.origin.y + random() % (int) r.size.height;
    return result;
}

- (void)awakeFromNib{
    
    circle = [NSBezierPath bezierPath];
    [circle appendBezierPathWithOvalInRect: [self bounds]];
    
    path = [NSBezierPath bezierPath];
    [path setLineWidth:1.0];
    NSPoint p1, p2 , c1, c2;
    p1.x = 100;
    p1.y = 200;
    p2.x = 300;
    p2.y = 100;
    
    c1.x = 100;
    c1.y = 100;
    c2.x = 100;
    c2.y = 200;
    [path moveToPoint:p1];
    [path curveToPoint:p2 controlPoint1:c1 controlPoint2:c2];
    
    
    
}

- (void)drawRect:(NSRect)dirtyRect {
    [super drawRect:dirtyRect];

    [[NSColor whiteColor] set];
    [NSBezierPath fillRect:_bounds];
    [[NSColor redColor] set];
    [path stroke];
    [circle stroke];
    
    
}

@end
