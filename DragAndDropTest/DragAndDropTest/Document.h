//
//  Document.h
//  DragAndDropTest
//
//  Created by Chikashi Miyama on 17/01/15.
//  Copyright (c) 2015 Chikashi Miyama. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "DropView.h"

@interface Document : NSPersistentDocument{
    NSURL* baseDirURL;
    NSURL* soundFilesDirURL;
}

- (IBAction)addSoundFile:(id)sender;
- (IBAction)localizeSoundfiles:(id)sender;

- (void) processApeendSoundFileNotification:(NSNotification *) notification;

@property (weak) IBOutlet NSArrayController *soundFileArrayController;
@property (weak) IBOutlet NSTextField *localFolderLabel;
@property (weak) IBOutlet DropView *dropRegion;

@end



