//
//  AppDelegate.m
//  bindingTest
//
//  Created by Chikashi Miyama on 20/02/15.
//  Copyright (c) 2015 Chikashi Miyama. All rights reserved.
//

#import "AppDelegate.h"

@interface AppDelegate ()

@property (weak) IBOutlet NSWindow *window;
@end

@implementation AppDelegate
@synthesize val;
- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    // Insert code here to initialize your application
    
}

- (void)applicationWillTerminate:(NSNotification *)aNotification {
    // Insert code here to tear down your application
}

- (IBAction)reset:(id)sender {
    
    // option 1
//    [self willChangeValueForKey:@"val"];
//    val = [NSNumber numberWithInt:0];
//    [self didChangeValueForKey:@"val"];
    
    // option 2
//    [self setValue:[NSNumber numberWithInt:0] forKey:@"val"];
    
    // option3
    [self setVal: [NSNumber numberWithInt:0]];
}
@end
