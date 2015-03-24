//
//  RandomController.h
//  Random
//
//  Created by Chikashi Miyama on 15/01/15.
//  Copyright (c) 2015 Chikashi Miyama. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>

@interface RandomController : NSObject{
    IBOutlet NSTextField *textField;
}

- (IBAction)seed: (id)sender;
- (IBAction)generate: (id)sender;

@end
