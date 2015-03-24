//
//  ConcatanatedBezierCurve.h
//  CocoaOpenGL
//
//  Created by Chikashi Miyama on 23/03/15.
//  Copyright (c) 2015 Chikashi Miyama. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "DirectDraw.h"
#import "SingleBezierCurve.h"

@interface ConcatanatedBezierCurve : DirectDraw 
{
}

@property (retain) SingleBezierCurve * targetBezier;
@property (retain) NSMutableArray * bezierCurves;
@property (assign) BOOL editing;

-(void)setHandleOfLastElement:(NSPoint)point;
-(void)eraseAll;
-(void)render;
-(BOOL)examineGrab:(NSPoint)location;
-(void)resetHandleOfTargetBezier;
-(void)removeTargetBezier;
-(BOOL)checkOverlapWithAnchorPoint:(EControlPoint)handle;

-(EControlPoint)targetControlPointOfTargetBezier;

@end
