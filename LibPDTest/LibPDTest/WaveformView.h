//
//  WaveformView.h
//  LibPDTest
//
//  Created by Chikashi Miyama on 24/03/15.
//  Copyright (c) 2015 Chikashi Miyama. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface WaveformView : NSView
{
}
@property (assign) float * waveBuffer;
@property (assign) int size;
@end
