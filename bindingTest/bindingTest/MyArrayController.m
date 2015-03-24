//
//  MyArrayController.m
//  bindingTest
//
//  Created by Chikashi Miyama on 20/02/15.
//  Copyright (c) 2015 Chikashi Miyama. All rights reserved.
//

#import "MyArrayController.h"

@implementation MyObject

-(NSString *)description{
    return [self name];
}
@end

@implementation MyArrayController

-(void)awakeFromNib{
    MyObject * objectA = [[MyObject alloc] init];
    MyObject * objectB = [[MyObject alloc] init];

    objectA.name = @"chikashi";
    objectA.surName = @"miyama";
    objectA.age = [NSNumber numberWithInt:35];
    objectB.name = @"rie";
    objectB.surName = @"watanabe";
    objectB.age = [NSNumber numberWithInt:36];
    [self addObject:objectA];
    [self addObject:objectB];

}

- (IBAction)consoleOut:(id)sender{
    NSLog(@"%@",[[self selectedObjects] description]);
    NSLog(@"%lu",(unsigned long)[self selectionIndex]);

}

@end

