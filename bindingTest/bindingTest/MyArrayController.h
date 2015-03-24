//
//  MyArrayController.h
//  bindingTest
//
//  Created by Chikashi Miyama on 20/02/15.
//  Copyright (c) 2015 Chikashi Miyama. All rights reserved.
//

#import <Cocoa/Cocoa.h>
@interface MyObject: NSObject
@property NSString * name;
@property NSString * surName;
@property NSNumber * age;

@end

@interface MyArrayController : NSArrayController

- (IBAction)consoleOut:(id)sender;
@end
