//
//  AppDelegate.h
//  SpeakLine
//
//  Created by Chikashi Miyama on 15/01/15.
//  Copyright (c) 2015 Chikashi Miyama. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface AppDelegate : NSObject <NSApplicationDelegate>{
    NSSpeechSynthesizer *_speechSynth;
    NSArray *_voices;
}

@property (weak) IBOutlet NSTableView *tableView;
@property (weak) IBOutlet NSWindow *window;
@property (weak) IBOutlet NSTextField *textField;
@property (weak) IBOutlet NSButton *stopButton;
@property (weak) IBOutlet NSButton *speakButton;

- (id)init;
- (IBAction)sayIt:(id)sender;
- (IBAction)stopIt:(id)sender;

@end

