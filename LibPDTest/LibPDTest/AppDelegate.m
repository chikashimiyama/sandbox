//
//  AppDelegate.m
//  LibPDTest
//
//  Created by Chikashi Miyama on 15/03/15.
//  Copyright (c) 2015 Chikashi Miyama. All rights reserved.
//

#import "AppDelegate.h"
#import "PdBase.h"
#import "PdFile.h"

@interface AppDelegate ()


@property (retain) IBOutlet NSWindow *window;
@end


static int patestCallback(const void*                     inputBuffer,
                          void*                           outputBuffer,
                          unsigned long                   framesPerBuffer,
                          const PaStreamCallbackTimeInfo* timeInfo,
                          PaStreamCallbackFlags           statusFlags,
                          void*                           userData )
{
    float *out = (float*)outputBuffer;
    unsigned long i;
    int finished = 0;
    (void) inputBuffer; /* Prevent unused argument warning. */
    
    float outBuffer[1024];

    [PdBase processFloatWithInputBuffer:inputBuffer outputBuffer:outBuffer ticks:8];
    int index = 0;
    for( i=0; i<framesPerBuffer; i++)
    {
        *out++ = outBuffer[index++]; /* Left */
        *out++ = outBuffer[index++]; /* Right */
    }
    return finished;
}


@implementation AppDelegate
@synthesize waveformView;
- (IBAction)setFreq:(id)sender{
    float value = [sender floatValue];
    
    [PdBase sendMessage:@"freq" withArguments:[NSArray arrayWithObjects:[NSNumber numberWithFloat:value], nil] toReceiver:@"fromApp"];
}

- (void)receiveMessage:(NSString *)message withArguments:(NSArray *)arguments fromSource:(NSString *)source{
    
    if ([message isEqualToString:@"progress"]) {
        float p = [[arguments objectAtIndex:0] floatValue] / duration * 1000;
        [_progressSlider setFloatValue:p];
    }else if([message isEqualToString:@"duration"]){
        duration = [[arguments objectAtIndex:0] floatValue];
        NSLog(@"duration %f", duration);
    }
}

- (void)initPortAudio{
    PaStreamParameters  outputParameters;
    PaError             err;
    
    if( !Pa_Initialize() ){
        NSLog(@"Error: Couldn't init.\n");
    }
    outputParameters.device = Pa_GetDefaultOutputDevice();
    if (outputParameters.device == paNoDevice) {
        NSLog(@"Error: No default output device.\n");
    }
    outputParameters.channelCount              = 2;
    outputParameters.sampleFormat              = paFloat32;
    outputParameters.hostApiSpecificStreamInfo = NULL;
    outputParameters.suggestedLatency          = Pa_GetDeviceInfo(outputParameters.device)
    ->defaultHighOutputLatency;
    err = Pa_OpenStream(&stream,
                        NULL,               /* no input */
                        &outputParameters,
                        44100,
                        0,
                        paClipOff,          /* No out of range samples should occur. */
                        patestCallback,
                        NULL);
    
    if( !Pa_StartStream( stream )){
        NSLog(@"Error: Couldn't start stream.\n");
    }
}


- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    // Insert code here to initialize your application

    
    [PdBase clearSearchPath];
    [PdBase addToSearchPath:@"/Users/chikashi/Development/sandbox/LibPDTest/LibPDTest/pdcore"];
    patch = [PdBase openFile:@"dsp.pd" path:@"/Users/chikashi/Development/sandbox/LibPDTest/LibPDTest/pdcore"];
    
    [PdBase setDelegate:self pollingEnabled:YES];
    [PdBase sendMessage:@"freq" withArguments:[NSArray arrayWithObjects:[NSNumber numberWithFloat:330.0], nil] toReceiver:@"fromApp"];
    
    [self initPortAudio];

    blockSize = [PdBase getBlockSize];

    ticksPerBuffer = 8;
    bufferSize = blockSize * ticksPerBuffer;
    
    [PdBase openAudioWithSampleRate:44100 inputChannels:0 outputChannels:2];
    [PdBase computeAudio:YES];
    

    [PdBase sendMessage:@"gain"
          withArguments:[NSArray arrayWithObject:[NSNumber numberWithFloat:70.0]]
             toReceiver:@"fromApp"];
    [PdBase subscribe:@"toApp"];
}

- (void)receivePrint:(NSString *)message{
    NSLog(@"%@", message);
}

- (void)applicationWillTerminate:(NSNotification *)aNotification {
    // Insert code here to tear down your application
    [PdBase closeFile:(void *)patch];
    
    Pa_StopStream( stream );
    Pa_CloseStream( stream );
    Pa_Terminate();
}

- (IBAction)open:(id)sender {
    NSOpenPanel * panel = [NSOpenPanel openPanel];
    if([panel runModal]){
        NSURL * url = [panel URL];
        NSString * path = [url path];
        [PdBase sendMessage:@"open" withArguments:[NSArray arrayWithObject:path] toReceiver:@"fromApp"];
    }
    
    
    int size = [PdBase arraySizeForArrayNamed:@"wave"];
    float * copiedArray = malloc(sizeof(float)*size);
    [PdBase copyArrayNamed:@"wave" withOffset:0 toArray:copiedArray count:size];
    NSLog(@"size %d ",size);
    
    [waveformView setSize:size];
    [waveformView setWaveBuffer:copiedArray];
    [waveformView setNeedsDisplay:YES];
}

- (IBAction)start:(id)sender {
    [PdBase sendMessage:@"start" withArguments:nil  toReceiver:@"fromApp"];

}

- (void)stop:(id)sender{
    [PdBase sendMessage:@"stop" withArguments:nil toReceiver:@"fromApp"];
}
- (void)setGain:(id)sender{
    float gain = [sender floatValue];
    [PdBase sendMessage:@"gain"
          withArguments:[NSArray arrayWithObject:[NSNumber numberWithFloat:gain]]
             toReceiver:@"fromApp"];
}

- (void)setPan:(id)sender{
    float pan = [sender floatValue];
    [PdBase sendMessage:@"panning"
          withArguments:[NSArray arrayWithObject:[NSNumber numberWithFloat:pan]]
             toReceiver:@"fromApp"];
}

@end
