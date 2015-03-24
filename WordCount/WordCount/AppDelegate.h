//
//  AppDelegate.h
//  WordCount
//
//  Created by Chikashi Miyama on 15/01/15.
//  Copyright (c) 2015 Chikashi Miyama. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface AppDelegate : NSObject <NSApplicationDelegate>{
    
}

@property (assign) IBOutlet NSWindow *window;
@property (weak) IBOutlet NSTextField *textField;
@property (weak) IBOutlet NSTextField *countField;

- (IBAction)count:(id)sender;
@end

