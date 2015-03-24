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
    NSMutableArray * bezierCurves;
}

@property (retain) SingleBezierCurve * targetBezier;

-(void)setHandleOfLastElement:(NSPoint)point;
- (void)eraseAll;
- (void)render;
-(void)examineGrab:(NSPoint)location;
@end
