//
//  Trajectory.m
//  CocoaOpenGL
//
//  Created by Chikashi Miyama on 23/03/15.
//  Copyright (c) 2015 Chikashi Miyama. All rights reserved.
//

#import "Trajectory.h"
#import <OpenGL/gl.h>

@implementation Trajectory
@synthesize centroidVisible;



- (instancetype)init{
    self = [super init];
    if(self){
        elements = [[NSMutableArray alloc] init];
        samplesRAM = [[NSMutableArray alloc] init];
        centroidVisible = NO;
    }
    return self;
}

- (void)addElement:(id)element{
    [elements addObject:element];
}

- (void)eraseAll{
    [elements removeAllObjects];
    [samplesRAM removeAllObjects];
    samplesVRAM = [[VBO alloc] initWithArray:nil];
}

- (void)copyToVbo{
    samplesVRAM = [[VBO alloc] initWithArray:samplesRAM];
}

- (NSPoint)interpolatedPoint:(float)findex{
    
    if([samplesRAM count]< 2){
        return NSMakePoint(0, 0);
    }
    if(findex >= [samplesRAM count]-2){
        findex = (float)([samplesRAM count]-2) + 0.999;
        
    }
    int index = (int)findex;
    float weight = findex - (float)index;
    

    NSPoint firstPoint = [[samplesRAM objectAtIndex:index] pointValue];
    NSPoint secondPoint = [[samplesRAM objectAtIndex:index+1] pointValue];
    NSSize gap = NSMakeSize(secondPoint.x - firstPoint.x, secondPoint.y -secondPoint.y);
    return NSMakePoint(firstPoint.x + gap.width * weight,
                       firstPoint.y + gap.height * weight);
}

- (void)render{
    if(centroidVisible)
        [self renderCentroid];
    [samplesVRAM render];
}

- (void)renderCentroid{
    if([elements count] == 0)
        return;
    glBegin(GL_QUADS);
    glVertex2f(centroid.x-0.01, centroid.y+0.01);
    glVertex2f(centroid.x-0.01, centroid.y-0.01);
    glVertex2f(centroid.x+0.01, centroid.y-0.01);
    glVertex2f(centroid.x+0.01, centroid.y+0.01);
    glEnd();
}

@end
