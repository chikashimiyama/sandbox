//
//  NSBreakPointView.h
//  BreakPointEditorDemo
//
//  Created by Chikashi Miyama on 22/01/15.
//  Copyright (c) 2015 Chikashi Miyama. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface NSBreakPointView : NSView{
    NSBezierPath *path;
    NSBezierPath *circle;
}

-(NSPoint)randomPoint;

@end
