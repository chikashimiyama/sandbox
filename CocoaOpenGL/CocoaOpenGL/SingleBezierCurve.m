//
//  SingleBezierCurve.h
//  CocoaOpenGL
//
//  Created by Chikashi Miyama on 22/03/15.
//  Copyright (c) 2015 Chikashi Miyama. All rights reserved.
//

#import "SingleBezierCurve.h"
#import <OpenGL/gl.h>

@implementation SingleBezierCurve
@synthesize mirrorMode;
@synthesize enableForwardHandle;
@synthesize enableBackwardHandle;
@synthesize anchorPoint;
@synthesize forwardHandle;
@synthesize backwardHandle;
@synthesize targetControlPoint;

-(id)initWithAnchorPoint:(NSPoint)anchor{
    self = [super init];
    if(self){
        anchorPoint = anchor;
        forwardHandle = anchorPoint;
        backwardHandle = anchorPoint;
        enableForwardHandle = YES;
        enableBackwardHandle = YES;
        targetControlPoint = ENoGrab;
        mirrorMode = NO;
    }
    return self;
}



- (void)moveTargetControlPoint:(NSPoint)point withMirroring:(BOOL)mirroring{

    switch (targetControlPoint) {
        case EAnchorPoint:{
            NSPoint lastPoint = anchorPoint;
            anchorPoint = point;
            float xdif = anchorPoint.x - lastPoint.x;
            float ydif = anchorPoint.y - lastPoint.y;
            forwardHandle = NSMakePoint(forwardHandle.x+xdif, forwardHandle.y+ydif);
            backwardHandle = NSMakePoint(backwardHandle.x+xdif, backwardHandle.y+ydif);
            break;
        }
        case EForwardHandle:{
            forwardHandle = point;
            if(mirroring){
                float xdif = forwardHandle.x - anchorPoint.x;
                float ydif = forwardHandle.y - anchorPoint.y;
                backwardHandle.x = anchorPoint.x - xdif;
                backwardHandle.y = anchorPoint.y - ydif;
            }
            break;
        }
        case EBackwardHandle:{
            backwardHandle = point;
            if(mirroring){
                float xdif = backwardHandle.x - anchorPoint.x;
                float ydif = backwardHandle.y - anchorPoint.y;
                forwardHandle.x = anchorPoint.x - xdif;
                forwardHandle.y = anchorPoint.y - ydif;
            }
            break;
        }
        default:
            break;
    }
    mirrorMode = mirroring;
}

-(void)resetTargetControlPoint{
    targetControlPoint = ENoGrab;
}

-(void)renderAnchorPoint{
    glPointSize(4.0);
    glBegin(GL_POINTS);
    glVertex3f(anchorPoint.x, anchorPoint.y, 0.0);
    glEnd();
}


-(void)renderHandles{
    glLineWidth(0.5);

    if (targetControlPoint == EForwardHandle ||
        ((targetControlPoint == EBackwardHandle) && (mirrorMode == YES))){
        glColor3f(1.0,0.0,0.0);

    }else{
        glColor3f(0.3,0.3,0.3);
    }
    glBegin(GL_LINE_STRIP);
    glVertex2f(anchorPoint.x, anchorPoint.y);
    glVertex2f(forwardHandle.x, forwardHandle.y);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glVertex2f(forwardHandle.x-0.01, forwardHandle.y+0.01);
    glVertex2f(forwardHandle.x-0.01, forwardHandle.y-0.01);
    glVertex2f(forwardHandle.x+0.01, forwardHandle.y-0.01);
    glVertex2f(forwardHandle.x+0.01, forwardHandle.y+0.01);
    glEnd();
    if (targetControlPoint == EBackwardHandle ||
        ((targetControlPoint == EForwardHandle) && (mirrorMode == YES))){
            glColor3f(1.0,0.0,0.0);
    }else{
        glColor3f(0.3,0.3,0.3);
    }
    glBegin(GL_LINE_STRIP);
    glVertex2f(anchorPoint.x, anchorPoint.y);
    glVertex2f(backwardHandle.x, backwardHandle.y);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glVertex2f(backwardHandle.x-0.01, backwardHandle.y+0.01);
    glVertex2f(backwardHandle.x-0.01, backwardHandle.y-0.01);
    glVertex2f(backwardHandle.x+0.01, backwardHandle.y-0.01);
    glVertex2f(backwardHandle.x+0.01, backwardHandle.y+0.01);
    glEnd();
    glLineWidth(1.0);
    glColor3f(1.0,1.0,1.0);

}

-(void)renderControlPoints{
    [self renderAnchorPoint];
    [self renderHandles ];
}

-(BOOL)hitCheck:(NSPoint)target withPoint:(NSPoint)point{
    float torrelance = 0.02;
    if(((target.x - torrelance) < point.x) &&  (point.x < (target.x + torrelance))){
        if(((target.y - torrelance) < point.y) && (point.y < (target.y + torrelance))){
            return YES;
        }
    }
    return NO;
}

-(BOOL)checkOverlapWithAnchorPoint{
    float difx = (anchorPoint.x - forwardHandle.x);
    float dify = (anchorPoint.y - forwardHandle.y);
    float distAnchorAndForwardHandle = sqrtf(difx * difx + dify * dify);
    if(distAnchorAndForwardHandle < 0.01)
        return YES;
    
    difx = (anchorPoint.x - backwardHandle.x);
    dify = (anchorPoint.y - backwardHandle.y);
    float distAnchorAndBackwardHandle = sqrtf(difx * difx + dify * dify);
    if(distAnchorAndBackwardHandle < 0.01)
        return YES;
    
    return NO;
}

-(BOOL)examineGrab:(NSPoint)point{
    if([self hitCheck:[self forwardHandle] withPoint:point]){
        targetControlPoint =  EForwardHandle;
    }else if([self hitCheck:[self backwardHandle] withPoint:point]){
        targetControlPoint = EBackwardHandle;
    }else if([self hitCheck:[self anchorPoint] withPoint:point]){
        targetControlPoint = EAnchorPoint;
    }else{
        return NO;
    }
    return YES;
}

-(void)resetHandle{
    forwardHandle = anchorPoint;
    backwardHandle = anchorPoint;
}
@end
