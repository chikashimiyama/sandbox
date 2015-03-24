//
//  Document.h
//  RaiseMan
//
//  Created by Chikashi Miyama on 16/01/15.
//  Copyright (c) 2015 Chikashi Miyama. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface Document : NSDocument{
    NSMutableArray * employees;
}

- (void) setEmployees: (NSMutableArray *)a;

@end

