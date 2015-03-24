//
//  Trajectory.h
//  CocoaOpenGL
//
//  Created by Chikashi Miyama on 23/03/15.
//  Copyright (c) 2015 Chikashi Miyama. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "VBO.h"

@protocol TrajectoryProtocol
- (void)eraseAll;
- (void)rasterize;
- (void)copyToVbo;
- (void)render;
@end

/** 
 low level interface between CPU and GPU.
 we use GPU for drawing and GPU for calculating position
**/



@interface Trajectory : NSObject
{
    NSMutableArray * samplesRAM; // sampled trajectory Data in RAM
    VBO * samplesVRAM; // sampled trajectory Data in VRAM

    
    NSMutableArray * elements;
    NSPoint centroid;
}


- (void)addElement:(id)element; ///< add element to control trajectory
- (void)eraseAll; ///<  erase the data from both RAM and VRAM
- (void)copyToVbo; ///< copy to Vbo
- (void)render; ///< draw trajectory using VBO
- (NSPoint)interpolatedPoint:(float)findex;

@property (assign) BOOL centroidVisible;

@end
