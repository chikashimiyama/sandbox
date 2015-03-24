//
//  Document.m
//  CoreDataRelations
//
//  Created by Chikashi Miyama on 21/01/15.
//  Copyright (c) 2015 Chikashi Miyama. All rights reserved.
//

#import "Document.h"

@interface Document ()

@end

@implementation Document


- (instancetype)init {
    self = [super init];
    if (self) {
        
    }
    return self;
}

- (void)windowControllerDidLoadNib:(NSWindowController *)aController {
    [super windowControllerDidLoadNib:aController];
    // Add any code here that needs to be executed once the windowController has loaded the document's window.
    
    NSManagedObject *mo1, *mo2, *dmo;
    mo1 = [NSEntityDescription insertNewObjectForEntityForName:@"Student"
                                       inManagedObjectContext:[self managedObjectContext]];
    [mo1 setValue:@"Chikashi" forKey:@"givenName"];
    [mo1 setValue:@"Miyama" forKey:@"familyName"];
    
    dmo = [NSEntityDescription insertNewObjectForEntityForName:@"Department"
                                        inManagedObjectContext:[self managedObjectContext]];
    
    [dmo setValue:@"IMA" forKey:@"deptName"];
    
    mo2 = [NSEntityDescription insertNewObjectForEntityForName:@"Student"
                                        inManagedObjectContext:[self managedObjectContext]];
    
    [mo2 setValue:@"David" forKey:@"givenName"];
    [mo2 setValue:@"Wagner" forKey:@"familyName"];
    
    NSLog(@"%@",[mo1 description]);
    NSLog(@"%@",[mo2 description]);
    NSLog(@"%@",[dmo description]);
    
    NSEntityDescription *entityDescription = [NSEntityDescription
                                              entityForName:@"Student" inManagedObjectContext:[self managedObjectContext]];
    NSFetchRequest *request = [[NSFetchRequest alloc] init];
    [request setEntity:entityDescription];

    // Set example predicate and sort orderings...
    NSPredicate *predicate = [NSPredicate predicateWithFormat:
                              @"(givenName LIKE[c] 'Bob')"];
    [request setPredicate:predicate];
    NSError *error;
    NSArray *array = [[self managedObjectContext] executeFetchRequest:request error:&error];
    NSLog(@"%@", array.description);
    [_label setStringValue:@""];
}

+ (BOOL)autosavesInPlace {
    return YES;
}

- (NSString *)windowNibName {
    // Override returning the nib file name of the document
    // If you need to use a subclass of NSWindowController or if your document supports multiple NSWindowControllers, you should remove this method and override -makeWindowControllers instead.
    return @"Document";
}

@end
