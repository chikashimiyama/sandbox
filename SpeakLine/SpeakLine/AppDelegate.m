//
//  AppDelegate.m
//  SpeakLine
//
//  Created by Chikashi Miyama on 15/01/15.
//  Copyright (c) 2015 Chikashi Miyama. All rights reserved.
//

#import "AppDelegate.h"


@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    // Insert code here to initialize your application
}

- (void)applicationWillTerminate:(NSNotification *)aNotification {
    // Insert code here to tear down your application
}

#pragma mark datasource

- (NSInteger) numberOfRowsInTableView:(NSTableView *)tv {
    return (NSInteger)[_voices count];
}

- (id)tableView:(NSTableView* )tv
    objectValueForTableColumn:(NSTableColumn *)tableColumn
    row:(NSInteger) row{
    
    NSString *v = [_voices objectAtIndex:row];
    NSDictionary *dict = [NSSpeechSynthesizer attributesForVoice:v];
    return [dict objectForKey:NSVoiceName];
}

- (void)tableViewSelectionDidChange:(NSNotification *)notification
{
    NSInteger row = [_tableView selectedRow];
    if(row == -1){
        return;
    }
    NSString *selectedVoice = [_voices objectAtIndex:row];
    [_speechSynth setVoice:selectedVoice];
    
}

- (id)init{
    self = [super init];
    if(self){
        _speechSynth = [[NSSpeechSynthesizer alloc] initWithVoice:nil];
        [_speechSynth setDelegate:self];
        _voices = [NSSpeechSynthesizer availableVoices];
        
    }
    
    return self;
}

- (IBAction)sayIt:(id)sender {
    NSString *string = [ _textField stringValue];
    [_speechSynth startSpeakingString:string];
    [_speakButton setEnabled:NO];
    [_stopButton setEnabled:YES];
}

- (IBAction)stopIt:(id)sender {
    [_speechSynth stopSpeaking];
}


- (void)speechSynthesizer: (NSSpeechSynthesizer*)sender didFinishSpeaking:(BOOL)finishedSpeaking
{
    [_speakButton setEnabled:YES];
    [_stopButton setEnabled:NO];

}

@end
