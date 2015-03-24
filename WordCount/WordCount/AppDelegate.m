//
//  AppDelegate.m
//  WordCount
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

- (IBAction)count:(id)sender {
    NSString * str = [_textField stringValue];
    int len = [str length];
    [_countField setIntegerValue:len];
}
@end
