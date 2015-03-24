//
//  AppDelegate.h
//  LibPDTest
//
//  Created by Chikashi Miyama on 15/03/15.
//  Copyright (c) 2015 Chikashi Miyama. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "PdFile.h"
#import "PdBase.h"
#import "WaveformView.h"
#include "portaudio.h"


@interface AppDelegate : NSObject <NSApplicationDelegate, PdReceiverDelegate>{

    
    unsigned int blockSize;
    unsigned int ticksPerBuffer;
    unsigned int bufferSize;
    float duration;
    
    PdFile* patch;
    PaStream* stream;

}
- (IBAction)stop:(id)sender;
- (IBAction)start:(id)sender;
- (IBAction)open:(id)sender;
- (IBAction)setGain:(id)sender;
- (IBAction)setPan:(id)sender;

@property (assign) IBOutlet WaveformView *waveformView;
@property (assign) IBOutlet NSSlider *progressSlider;

- (void)initPortAudio;
- (IBAction)setFreq:(id)sender;


@end

