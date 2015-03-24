//
//  testClass.h
//  test
//
//  Created by Chikashi Miyama on 11/01/15.
//  Copyright (c) 2015 Chikashi Miyama. All rights reserved.
//

#ifndef test_TestClass_h
#define test_TestClass_h

#import "StreetLegel.h"


@interface TestClass : NSObject <StreetLegel>{
    
}

@property int age;

- (void) debug;

@end

#endif
