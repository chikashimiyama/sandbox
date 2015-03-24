//
//  ConcatanatedBezierCurve.m
//  CocoaOpenGL
//
//  Created by Chikashi Miyama on 23/03/15.
//  Copyright (c) 2015 Chikashi Miyama. All rights reserved.
//

#import "ConcatanatedBezierCurve.h"
#import "SingleBezierCurve.h"
#import <OpenGL/gl.h>

@implementation ConcatanatedBezierCurve
@synthesize targetBezier;
@synthesize bezierCurves;
@synthesize editing;

const float kPerSegmentSampling = 50.0;

-(id)init{
    self = [super init];
    if (self) {
        bezierCurves = [[NSMutableArray alloc] init];
        targetBezier = nil;
    }
    return self;
}

-(void)addElement:(id)element{
    
    NSPoint point = [element pointValue];
    SingleBezierCurve * newCurve = [[SingleBezierCurve alloc] initWithAnchorPoint:point];
    
    [bezierCurves addObject:newCurve]; // add bezier as an element
}

-(void)setHandleOfLastElement:(NSPoint)point{
    NSPoint anchor = [[bezierCurves lastObject] anchorPoint];
    float distX = point.x - anchor.x;
    float distY = point.y - anchor.y;
    NSPoint mirroredPoint = NSMakePoint(anchor.x - distX, anchor.y - distY);
    
    SingleBezierCurve * lastCurve = [bezierCurves lastObject];
    [lastCurve setForwardHandle:point];
    [lastCurve setBackwardHandle:mirroredPoint];
}

- (void)rasterize{
    
    [self calcBezier];
    [super rasterize]; // raster
}


-(void)calcBezier{
    if([bezierCurves count] < 2)
        return; // needless to raster
    
    [elements removeAllObjects];
    unsigned long count = [bezierCurves count];
    for(int i = 0 ;i < count-1; i ++){
        SingleBezierCurve* firstElement = [bezierCurves objectAtIndex:i];
        SingleBezierCurve* secondElement = [bezierCurves objectAtIndex:i+1];
        NSPoint p0 = [firstElement anchorPoint];
        NSPoint p1 = [firstElement forwardHandle];
        NSPoint p2 = [secondElement backwardHandle];
        NSPoint p3 = [secondElement anchorPoint];
        
        NSSize p1p0 = NSMakeSize(p1.x - p0.x, p1.y- p0.y);
        NSSize p2p1 = NSMakeSize(p2.x - p1.x, p2.y- p1.y);
        NSSize p3p2 = NSMakeSize(p3.x - p2.x, p3.y- p2.y);
        
        
        for(int j = 0; j < kPerSegmentSampling; j++){
            float phase = (float)j / kPerSegmentSampling;
            NSPoint p4 = NSMakePoint(p1p0.width * phase + p0.x,
                                     p1p0.height * phase +p0.y);
            NSPoint p5 = NSMakePoint(p2p1.width * phase + p1.x,
                                     p2p1.height * phase +p1.y);
            NSPoint p6 = NSMakePoint(p3p2.width * phase + p2.x,
                                     p3p2.height * phase +p2.y);
            
            NSSize p5p4 = NSMakeSize(p5.x - p4.x, p5.y- p4.y);
            NSSize p6p5 = NSMakeSize(p6.x - p5.x, p6.y- p5.y);
            
            NSPoint p7 = NSMakePoint(p5p4.width * phase + p4.x,
                                     p5p4.height * phase +p4.y);
            NSPoint p8 = NSMakePoint(p6p5.width * phase + p5.x,
                                     p6p5.height * phase +p5.y);
            
            NSSize p8p7 = NSMakeSize(p8.x - p7.x, p8.y- p7.y);
            NSPoint p9 = NSMakePoint(p8p7.width * phase + p7.x,
                                     p8p7.height * phase + p7.y);
            [super addElement: [NSValue valueWithPoint:p9]];
        }
    }
}


-(BOOL)examineGrab:(NSPoint)location{
    if(targetBezier){
        [targetBezier resetTargetControlPoint];
    }
    for(SingleBezierCurve * curve in bezierCurves){
        if([curve examineGrab:location]){
            targetBezier = curve;
            return YES;
            break;
        }
    }
    return NO;
}

-(EControlPoint)targetControlPointOfTargetBezier{
    if(targetBezier){
        return [targetBezier targetControlPoint];
    }
    return ENoGrab;
}

-(void)removeTargetBezier{
    if(targetBezier){
        [bezierCurves removeObject:targetBezier];
    }
}

-(void)resetHandleOfTargetBezier{
    [targetBezier resetHandle];
}

-(void)eraseAll{
    [bezierCurves removeAllObjects];
    [super eraseAll];
}

-(void)render{
    for(SingleBezierCurve * curve in bezierCurves){
        [curve renderControlPoints];
    }
    if([self recording]){
        [self calcBezier];
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_LINE_STRIP);
        for (NSValue * point in elements) {
            NSPoint p = [point pointValue];
            glVertex2f(p.x, p.y);
        }
        glEnd();
    }else{
    
        [super render];
    }
}
    
@end
