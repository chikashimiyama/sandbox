//
//  AppDelegate.h
//  bindingTest
//
//  Created by Chikashi Miyama on 20/02/15.
//  Copyright (c) 2015 Chikashi Miyama. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface AppDelegate : NSObject <NSApplicationDelegate>
- (IBAction)reset:(id)sender;

@property (nonatomic, retain) NSNumber* val;

@end

