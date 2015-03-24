//
//  MyOpenGLView.h
//  CocoaOpenGL
//
//  Created by Chikashi Miyama on 21/03/15.
//  Copyright (c) 2015 Chikashi Miyama. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "DirectDraw.h"
#import "ConcatanatedBezierCurve.h"

typedef NS_ENUM(NSInteger, EDrawingMode){
    EDirectDraw,
    EBezier,
    ESpline
};

@interface MyOpenGLView : NSOpenGLView{
    EDrawingMode mode;
    bool mousePressed;
    GLuint shaderProgram;
    
    DirectDraw * directDraw;
    ConcatanatedBezierCurve * bezierCurve;
    float halfX, halfY;
    IBOutlet NSTextField * elapsedTimeField;
    float phase;
    NSTimer * timer;
}

-(IBAction)redraw:(id)sender;
-(IBAction)setMode:(id)sender;
-(IBAction)eraseAll:(id)sender;
-(IBAction)setPhase:(id)sender;
@end
