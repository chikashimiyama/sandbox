//
//  main.c
//  opengltest
//
//  Created by Chikashi Miyama on 10/19/13.
//  Copyright (c) 2013 Chikashi Miyama. All rights reserved.
//

#include <stdio.h>
#include <OpenGL/OpenGL.h>
#include <OpenGL/glu.h>
#include <GLUT/GLUT.h>

int main(int argc, const char * argv[])
{
    
    glutInit(&argc, argv);
    glutInitWindowPosition(100 , 50);
	glutInitWindowSize(200 , 100);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    
	glutCreateWindow("Kitty on your lap");


    const GLubyte *renderer = glGetString(GL_RENDERER);
    const GLubyte *vendor = glGetString(GL_VENDOR);
    const GLubyte *version = glGetString(GL_VERSION);
    const GLubyte *glsl_version = glGetString(GL_SHADING_LANGUAGE_VERSION);
    
    printf("vendor %s\n", vendor);
    printf("version %s\n", version);
    printf("render %s\n", renderer);
    printf("glsl version %s\n", glsl_version);
    return 0;
}

