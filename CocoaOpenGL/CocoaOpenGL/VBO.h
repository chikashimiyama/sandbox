//
//  VBO.h
//  CocoaOpenGL
//
//  Created by Chikashi Miyama on 22/03/15.
//  Copyright (c) 2015 Chikashi Miyama. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <OpenGL/OpenGL.h>
@interface VBO : NSObject{
    GLuint vboNumber;
    GLsizei numVertices;
}
-(id)initWithArray:(NSArray*) array;
-(void)render;
@end
