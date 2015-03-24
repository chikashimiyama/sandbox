//
//  BezierCurve.h
//  CocoaOpenGL
//
//  Created by Chikashi Miyama on 22/03/15.
//  Copyright (c) 2015 Chikashi Miyama. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>

typedef NS_ENUM(NSInteger, EControlPoint){
    EAnchorPoint,
    EForwardHandle,
    EBackwardHandle,
    ENoGrab
};

@interface SingleBezierCurve : NSObject{
}

@property (assign) EControlPoint targetControlPoint;
@property (assign) BOOL enableForwardHandle;
@property (assign) BOOL enableBackwardHandle;
@property (assign) BOOL mirrorMode;

@property (assign) NSPoint anchorPoint;
@property (assign) NSPoint forwardHandle;
@property (assign) NSPoint backwardHandle;
@property (assign) SingleBezierCurve *nextBezierCurve;

-(id)initWithAnchorPoint:(NSPoint)anchor;
-(BOOL)examineGrab:(NSPoint)point;
-(BOOL)checkOverlapWithAnchorPoint;
-(void)resetTargetControlPoint;
-(void)moveTargetControlPoint:(NSPoint)point withMirroring:(BOOL)mirroring;
-(void)renderControlPoints;
-(void)resetHandle;
@end

