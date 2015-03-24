//
//  DirectDraw.h
//  CocoaOpenGL
//
//  Created by Chikashi Miyama on 23/03/15.
//  Copyright (c) 2015 Chikashi Miyama. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Trajectory.h"
@interface DirectDraw : Trajectory <TrajectoryProtocol>
{
}

@property (assign) BOOL recording;
@property (assign) float length;
@property (assign) int numSamples;
@end
