//
//  DropView.m
//  DragAndDropTest
//
//  Created by Chikashi Miyama on 18/01/15.
//  Copyright (c) 2015 Chikashi Miyama. All rights reserved.
//

#import "DropView.h"

@implementation DropView


- (void)drawRect:(NSRect)dirtyRect {
    [super drawRect:dirtyRect];
}

- (NSDragOperation)draggingEntered:(id<NSDraggingInfo>)sender{
    NSLog(@"entered");
    return NSDragOperationLink;
}

- (void)draggingExited:(id<NSDraggingInfo>)sender{
    NSLog(@"exited");
}

- (BOOL)prepareForDragOperation:(id<NSDraggingInfo>)sender{
    return YES;
}

- (BOOL)performDragOperation:(id<NSDraggingInfo>)sender{
    
    NSPasteboard *pboard = [sender draggingPasteboard];
    
    
    if ( [[pboard types] containsObject:NSFilenamesPboardType] ) {
        
        NSArray *filesArray = [pboard propertyListForType:NSFilenamesPboardType];
        
        for(id file in filesArray){
            [[NSNotificationCenter defaultCenter]
             postNotificationName:@"AppendSoundFileNotification"
             object:file];
        }
        
    }
    return YES;
}

- (void)concludeDragOperation:(id<NSDraggingInfo>)sender{
    
}

@end
