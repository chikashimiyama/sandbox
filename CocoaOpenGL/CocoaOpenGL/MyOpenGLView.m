//
//  MyOpenGLView.m
//  CocoaOpenGL
//
//  Created by Chikashi Miyama on 21/03/15.
//  Copyright (c) 2015 Chikashi Miyama. All rights reserved.
//

#import "MyOpenGLView.h"
#import <OpenGL/OpenGL.h>
#import <OpenGL/gl3.h>
#import <GLUT/glut.h>
#import "VBO.h"

#import "SingleBezierCurve.h"

@implementation MyOpenGLView

- (BOOL)isFlipped{
    return YES;
}


- (IBAction)play:(id)sender{
    phase = 0.0;
    timer = [NSTimer scheduledTimerWithTimeInterval:0.025 target:self selector:@selector(updateTick:) userInfo:nil repeats:YES];
}

- (void)updateTick:(NSTimer*)tm{
    phase += 0.01;
    if(phase > 1.0){
        [tm invalidate];
    }
    [self setNeedsDisplay:YES];
}

- (void)redraw:(id)sender{
    [self setNeedsDisplay:YES];
}

-(void)setMode:(id)sender{
    NSMenuItem* item = sender;
    NSString * title = [item title];
    if([title isEqualToString:@"Direct"]){
        mode =EDirectDraw;
    }else if([title isEqualToString:@"Bezier"]){
        mode = EBezier;
    }else if([title isEqualToString:@"Spline"]){
        mode = ESpline;
    }
    [self eraseAll:self];
}

-(void)setPhase:(id)sender{
    phase = [sender floatValue]/1000.0;
    [self setNeedsDisplay:YES];
}

- (void)awakeFromNib{
    mode = EDirectDraw;
    directDraw = [[DirectDraw alloc] init];
    bezierCurve = [[ConcatanatedBezierCurve alloc] init];
    
    NSOpenGLContext *glContext = [self openGLContext];
    [glContext makeCurrentContext];

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    
    NSString * vertexPath = @"/Users/chikashi/Development/sandbox/CocoaOpenGL/CocoaOpenGL/test.vert";
    NSString * fragPath = @"/Users/chikashi/Development/sandbox/CocoaOpenGL/CocoaOpenGL/test.frag";
    
    NSString* vertexShaderString = [NSString stringWithContentsOfFile:vertexPath encoding:NSASCIIStringEncoding error:nil];
    NSString* fragShaderString = [NSString stringWithContentsOfFile:fragPath encoding:NSASCIIStringEncoding error:nil];
    
    
    const GLchar*  vertexShaderCString = [vertexShaderString cStringUsingEncoding:NSASCIIStringEncoding];
    const GLchar*  fragShaderCString = [fragShaderString cStringUsingEncoding:NSASCIIStringEncoding];
    
    glShaderSource(vertexShader, 1, &vertexShaderCString, NULL);
    glCompileShader(vertexShader);
    
    if(GL_NO_ERROR != glGetError()){
        NSLog(@"error found");
    }
    
    glShaderSource(fragmentShader, 1, &fragShaderCString, NULL);
    glCompileShader(fragmentShader);
    if(GL_NO_ERROR != glGetError()){
        NSLog(@"error found");
    }
    
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    if(GL_NO_ERROR != glGetError()){
        NSLog(@"error found");
    }
    
}
-(void)reshape{
    halfX = [self frame].size.width / 2.0;
    halfY = [self frame].size.height / 2.0;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, 10, 10);
    glMatrixMode(GL_MODELVIEW);
}

- (void)normalize:(NSPoint *)point{
    point->x  = point->x / halfX - 1.0;
    point->y  = -point->y / halfY + 1.0;
}

- (void)mouseDragged:(NSEvent *)theEvent{
    NSPoint location = [self convertPoint:[theEvent locationInWindow] fromView:nil];
    [self normalize:&location];
    
    if(mode == EDirectDraw){
        [directDraw addElement:[NSValue valueWithPoint:location]];
        
    }else if(mode == EBezier){
        NSEventModifierFlags modifier = [[NSApp currentEvent] modifierFlags];
        BOOL shiftPressed = (modifier & NSShiftKeyMask )? YES:NO;
        if (shiftPressed) {
            SingleBezierCurve * targetBezier = [bezierCurve targetBezier];
            if(targetBezier){
                [targetBezier moveTargetControlPoint:location];
            }
        }else{
            // new point
            [bezierCurve setHandleOfLastElement:location];
        }
    }else if(mode == ESpline){
        
    }
    [self setNeedsDisplay:YES];
}

- (void)eraseAll:(id)sender{
    
    [bezierCurve eraseAll];
    [directDraw eraseAll];
    [self setNeedsDisplay:YES];
}

- (void)mouseDown:(NSEvent *)theEvent{
    mousePressed = YES;
    NSPoint location = [self convertPoint:[theEvent locationInWindow] fromView:nil];
    [self normalize:&location];
    NSEventModifierFlags modifier = [[NSApp currentEvent] modifierFlags];
    BOOL shiftPressed = (modifier & NSShiftKeyMask )? YES:NO;
    switch (mode) {
        case EDirectDraw:
            [directDraw setRecording:YES];
            [directDraw addElement:[NSValue valueWithPoint:location]];
            break;
        case EBezier:
            if(shiftPressed){
                [bezierCurve examineGrab:location];
            }else{
                [bezierCurve setRecording:YES];
                [bezierCurve addElement:[NSValue valueWithPoint:location]];
            }
            break;
        default:
            break;
    }
    [self setNeedsDisplay:YES];
}

- (void)mouseUp:(NSEvent *)theEvent{
    mousePressed = NO;
    
    // set up vbo
    switch(mode){
        case EDirectDraw:
            [directDraw setRecording:NO];
            [directDraw rasterize];
            break;
        case EBezier:
            [bezierCurve setRecording:NO];
            [bezierCurve rasterize];
            break;
        case ESpline:
            break;
    }
    [self setNeedsDisplay:YES];
}

- (void)drawRect:(NSRect)dirtyRect {
    [super drawRect:dirtyRect];
    
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    
    NSDate *start = [NSDate date];
    
    if(mode == EDirectDraw){
        [directDraw render];
    }else if(mode == EBezier){
        [bezierCurve render];
    }
    [self drawIDs];
    [[self openGLContext] flushBuffer];
    
    NSTimeInterval timeInterval = [start timeIntervalSinceNow]*-1.0;
    [elapsedTimeField setStringValue:[NSString stringWithFormat:@"%f msec",timeInterval * 1000.0]];
    
    
}


- (void)drawIDs{
    id trajectory;
    switch (mode) {
        case EDirectDraw:
            trajectory = directDraw;
            break;
        case EBezier:
            trajectory = bezierCurve;
            break;
        case ESpline:
            break;
    }
    
    int samples = [trajectory numSamples];
    if(samples == 0){
        return;
    }
    float findex = (float)samples * phase;

    NSPoint interpolatedPoint = [trajectory interpolatedPoint:findex];
    glColor3f(0.9, 0.5, 0.3);
    glPushMatrix();
    glLoadIdentity();
    glTranslatef( interpolatedPoint.x, interpolatedPoint.y, 0);
    glutSolidSphere(0.03, 20, 20);
    glPopMatrix();
    glColor3f(1.0, 1.0, 1.0);
}

@end
