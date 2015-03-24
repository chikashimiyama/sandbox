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
@synthesize enableForwardHandle;
@synthesize enableBackwardHandle;
@synthesize anchorPoint;
@synthesize forwardHandle;
@synthesize backwardHandle;

-(id)initWithAnchorPoint:(NSPoint)anchor{
    self = [super init];
    if(self){
        anchorPoint = anchor;
        forwardHandle = anchorPoint;
        backwardHandle = anchorPoint;
        enableForwardHandle = YES;
        enableBackwardHandle = YES;
        targetControlPoint = ENoGrab;
    }
    return self;
}

- (void)moveTargetControlPoint:(NSPoint)point{
    switch (targetControlPoint) {
        case EAnchorPoint:
            anchorPoint = point;
            break;
        case EForwardHandle:
            forwardHandle = point;
            break;
        case EBackwardHandle:
            backwardHandle = point;
            break;
        default:
            break;
    }
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

    if(enableForwardHandle){
        if (targetControlPoint == EForwardHandle) {
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
    }
    if(enableBackwardHandle){
        if (targetControlPoint == EBackwardHandle) {
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
    }
    glLineWidth(1.0);
    glColor3f(1.0,1.0,1.0);

}

-(void)renderControlPoints{
    [self renderAnchorPoint];
    [self renderHandles];
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
@end
