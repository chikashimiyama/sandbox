//
//  DirectDraw.m
//  CocoaOpenGL
//
//  Created by Chikashi Miyama on 23/03/15.
//  Copyright (c) 2015 Chikashi Miyama. All rights reserved.
//

#import "DirectDraw.h"
#import <OpenGL/gl.h>

@implementation DirectDraw
@synthesize recording;
@synthesize length;
@synthesize numSamples;

const float kSampleDistance = 0.02;

- (id)init{
    self = [super init];

    return self;
}

- (void)addElement:(id)element{
    [super addElement:element];
}

- (void)rasterize{
    [samplesRAM removeAllObjects];
    int count = (int)[elements count];
    if(count <= 1){
        NSLog(@"Trajectory is a point");
        return;
    }
    length = 0;
    
    NSMutableArray * distanceArray = [NSMutableArray array];
    for(int i = 0 ; i < count-1; i ++){
        NSPoint currentpoint = [[elements objectAtIndex:i] pointValue];
        NSPoint nextPoint = [[elements objectAtIndex:i+1] pointValue];
        float xdif = nextPoint.x - currentpoint.x;
        float ydif = nextPoint.y - currentpoint.y;
        float distance = sqrtf((xdif * xdif) + (ydif * ydif));
        [distanceArray addObject:[NSNumber numberWithFloat:distance]];
        length += distance;
    }
    numSamples = (int)(length / kSampleDistance);

    
    // sampling line
    float progress = 0.0;
    
    // set to first segment
    float nextTargetDistance = [[distanceArray firstObject] floatValue];
    int segmentIndex = 0;
    NSPoint firstPoint = [[elements objectAtIndex:0] pointValue];
    NSPoint secondPoint = [[elements objectAtIndex:1] pointValue];
    float segmentDistance = nextTargetDistance;
    float previousOffsetDistance = 0.0;

    NSPoint sumPoint = NSMakePoint(0, 0);
    NSPoint previousSamplePoint;
    for(int i = 0; i < numSamples; i++){
        //NSLog(@"sample %d prgress %f", i, progress);
        
        while(nextTargetDistance < progress){
            segmentIndex++;
            //NSLog(@"target reached:set segment between element %d and %d", segmentIndex, segmentIndex+1);
            segmentDistance = [[distanceArray objectAtIndex:segmentIndex] floatValue];
            previousOffsetDistance = nextTargetDistance;
            nextTargetDistance += segmentDistance;
            firstPoint = [[elements objectAtIndex:segmentIndex] pointValue];
            secondPoint = [[elements objectAtIndex:segmentIndex+1] pointValue];

        }

        // weight ... interpolation weight
        float weight = (progress - previousOffsetDistance) / segmentDistance;
        float interpolatedX = (secondPoint.x - firstPoint.x) * weight + firstPoint.x;
        float interpolatedY = (secondPoint.y - firstPoint.y) * weight + firstPoint.y;
        NSPoint samplePoint = NSMakePoint(interpolatedX, interpolatedY);
        [samplesRAM addObject:[NSValue valueWithPoint:samplePoint]];
        sumPoint.x += samplePoint.x;
        sumPoint.y += samplePoint.y;

        previousSamplePoint = samplePoint;
        progress += kSampleDistance;
    }
    
    centroid = NSMakePoint(sumPoint.x / numSamples, sumPoint.y / numSamples);
    
    

    [super copyToVbo];
}

-(void)render{
    if(recording){
        // draft rendering
        glBegin(GL_LINE_STRIP);
        for(int i = 0; i < [elements count]; i++){
            NSValue * dot = [elements objectAtIndex:i];
            NSPoint point = [dot pointValue];
            float x = point.x;
            float y = point.y;
            glVertex3f(x, y, 0);
        }
        glEnd();
    }else{
        // show the content of VBO
        [super render];
    }
    
}
@end
