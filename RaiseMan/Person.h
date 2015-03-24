//
//  Person.h
//  RaiseMan
//
//  Created by Chikashi Miyama on 16/01/15.
//  Copyright (c) 2015 Chikashi Miyama. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface Person : NSObject{
    NSString *personName;
    float expectedRaise;
}

@property (readwrite, copy) NSString *personName;
@property (readwrite) float expectedRaise;

@end
