//
//  AppDelegate.h
//  KvcFun
//
//  Created by Chikashi Miyama on 16/01/15.
//  Copyright (c) 2015 Chikashi Miyama. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface AppDelegate : NSObject <NSApplicationDelegate> {
    int fido;
}

- (IBAction)incrementFido:(id)sender;
@end

