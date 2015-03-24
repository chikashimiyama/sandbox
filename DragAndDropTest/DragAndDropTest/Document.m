//
//  Document.m
//  DragAndDropTest
//
//  Created by Chikashi Miyama on 17/01/15.
//  Copyright (c) 2015 Chikashi Miyama. All rights reserved.
// 

#import "Document.h"

@interface Document ()
- (NSString*) extractPath:(NSURL *)url;
- (void)updateLocalFolder;
@end


@implementation Document
@synthesize soundFileArrayController;
@synthesize localFolderLabel;
@synthesize dropRegion;

- (void)updateLocalFolder{
    NSURL *url = [self fileURL];
    if(url != nil){
        
        // baseURL = the directory that the file exist
        baseDirURL =  [[self fileURL] URLByDeletingLastPathComponent];
        
        // add the name of the directory "soundfiles"
        soundFilesDirURL = [baseDirURL URLByAppendingPathComponent:@"soundfiles/"];
        
        [localFolderLabel setStringValue:[soundFilesDirURL absoluteString]];
        
        
    }
}

- (void)observeValueForKeyPath:(NSString*)keyPath
                      ofObject:(id)object
                        change:(NSDictionary*)change
                       context:(void*)context {
    
    if([keyPath isEqualToString:@"fileURL"]){
        [self updateLocalFolder];
    }
    
    NSFileManager * fm = [NSFileManager defaultManager];
    NSString * soundFilePath = [soundFilesDirURL path];
    BOOL directoryExist;
    BOOL fileExist = [fm fileExistsAtPath:soundFilePath isDirectory:&directoryExist];
    
    if(fileExist && directoryExist){
        NSLog(@"directory already exist");
    }else if(fileExist && !directoryExist){
        NSLog(@"need to be rename the file");
    }else{
        NSError *error = nil;
        if([fm createDirectoryAtPath:soundFilePath withIntermediateDirectories:YES attributes:nil error:&error]){
            NSLog(@"sound file directory automatically created");
        }else{
            NSLog(@"directory not created");
            NSLog(@"%@", error);
        }
    }
}


- (void)processApeendSoundFileNotification:(NSNotification *)notification{
    if ([[notification name] isEqualToString:@"AppendSoundFileNotification"]){
        NSURL *url = [NSURL fileURLWithPath:[notification object]];
        
        // separate filename and path from the given URL
        NSMutableArray *pathComponents = [NSMutableArray arrayWithArray:[url pathComponents]];
        NSString *filename = [pathComponents lastObject];
        NSString * path = [self extractPath:url];
        
        // create managed object (i.e. a new entity of Soundfile) and set value
        NSManagedObject *mo;
        mo = [NSEntityDescription insertNewObjectForEntityForName:@"SoundFile"
                                           inManagedObjectContext:[self managedObjectContext]];
        
        
        [mo setValue:filename forKey:@"filename"];
        [mo setValue:path forKey:@"path"];
    }
}

- (NSString*) extractPath:(NSURL *)url{
    NSMutableArray *pathComponents = [NSMutableArray arrayWithArray:[url pathComponents]];
    [pathComponents removeObject:[pathComponents lastObject]];
    NSMutableString * path = (NSMutableString *)[[pathComponents valueForKey:@"description"] componentsJoinedByString:@"/"];
    NSRange range = {0,1};
    [path deleteCharactersInRange:range];

    return path;
}

- (IBAction)localizeSoundfiles:(id)sender{

    NSURL *url = [self fileURL];
    
    if(url == nil){
        NSAlert *alert = [[NSAlert alloc] init];
        [alert setMessageText:@"File not saved"];
        [alert addButtonWithTitle:@"OK"];
        [alert setInformativeText:@"Save the file before localizing soundfiles"];
        [alert runModal];
        return;
    }
    
    
    NSFetchRequest* fetchRequest = [NSFetchRequest fetchRequestWithEntityName:@"SoundFile"];
    NSArray* manageObjectArray = [[self managedObjectContext] executeFetchRequest:fetchRequest error:nil];

    NSFileManager *fm = [NSFileManager defaultManager];
    for (NSManagedObject* mo in manageObjectArray){
        
        NSString *fileName = [mo valueForKey:@"filename"];
        NSString *path = [mo valueForKey:@"path"];
        NSString *fullPath = [NSString stringWithFormat:@"%@/%@",path, fileName];
        NSURL *toURL = [NSURL URLWithString:fileName relativeToURL:soundFilesDirURL];
        NSString *toPath = [toURL path];
        NSError *error;
        
        if(![fm copyItemAtPath:fullPath toPath:toPath error:&error]){
            NSLog(@"%@",[error description]);
        }
        
        [mo setValue:@"local" forKey:@"path"];
    }

}


- (instancetype)init {
    self = [super init];
    [[NSNotificationCenter defaultCenter]
     addObserver:self
     selector:@selector(processApeendSoundFileNotification:)
     name:@"AppendSoundFileNotification"
     object:nil];
    
    [self addObserver:self
           forKeyPath:@"fileURL"
            options:NSKeyValueObservingOptionNew
              context:nil];
     
    return self;
}


- (void)windowControllerDidLoadNib:(NSWindowController *)aController {
    [super windowControllerDidLoadNib:aController];
    [dropRegion registerForDraggedTypes:[NSArray arrayWithObjects:NSFilenamesPboardType, nil]];
    [self updateLocalFolder];
}


- (NSString *)windowNibName {
    // Override returning the nib file name of the document
    // If you need to use a subclass of NSWindowController or if your document supports multiple NSWindowControllers, you should remove this method and override -makeWindowControllers instead.
    return @"Document";
}



- (IBAction)addSoundFile:(id)sender {
    
    // ask user for a file
    NSOpenPanel *op =[NSOpenPanel openPanel];
    if(NSFileHandlingPanelCancelButton == [op runModal]){
        return;
    }
    NSURL *url = [op URL];
    
    // separate filename and path from the given URL
    NSMutableArray *pathComponents = [NSMutableArray arrayWithArray:[url pathComponents]];
    NSString *filename = [pathComponents lastObject];
    NSString * path = [self extractPath:url];
    
    // create managed object (i.e. a new entity of Soundfile) and set value
    NSManagedObject *mo;
    mo = [NSEntityDescription insertNewObjectForEntityForName:@"SoundFile"
                                        inManagedObjectContext:[self managedObjectContext]];

    
    [mo setValue:filename forKey:@"filename"];
    [mo setValue:path forKey:@"path"];

}
@end
