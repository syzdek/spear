/*
 * OpenGL Programming Examples
 * $Source$
 * $Revision$
 * $Date$
 * $Author$
 */
/*
 * Copyright (c) 2003 David M. Syzdek <syzdek@mosquitonet.com>
 * All Rights Reserved.
 */
/*  syzdek-001.c - Syzdek Playing around */
/*
 * Build:
 *    gcc -g -o syzdek-001.o syzdek-001.c -Wall  -lglut -L/usr/X11R6/lib
 */


///////////////
//           //
//  Headers  //
//           //
///////////////

#include <GL/glut.h>	/*  Loads GLUT to by pass libX11  */
#include <stdio.h>	/*  For print statements          */
#include <stdlib.h>     /*  needed for exit()             */


//////////////////
//              //
//  Prototypes  //
//              //
//////////////////

   int  main(int, char **);			/* umm, duh                          */


/////////////////
//             //
//  Functions  //
//             //
/////////////////

void init() {
      glClearColor(0.0, 0.5, 0.0, 0.0);
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
};

/* Draws Shape */
void example() {
   /* OpenGL Examples */
      glClear(GL_COLOR_BUFFER_BIT);
      glColor3f(1.0, 1.0, 1.0);
      glBegin(GL_POLYGON);
         glVertex3f(0.25, 0.25, 0.0);
         glVertex3f(0.75, 0.25, 0.0);
         glVertex3f(0.75, 0.75, 0.0);
         glVertex3f(0.25, 0.75, 0.0);
      glEnd();
      glColor3f(0.0, 0.0, 0.5);
      glBegin(GL_POLYGON);
         glVertex3f(0.0, 0.0, 0.0);
         glVertex3f(0.25, 0.0, 0.0);
         glVertex3f(0.25, 0.25, 0.0);
         glVertex3f(0.0, 0.25, 0.0);
      glEnd();
      glBegin(GL_POLYGON);
         glVertex3f(0.75, 0.0, 0.0);
         glVertex3f(1.0, 0.0, 0.0);
         glVertex3f(1.0, 0.25, 0.0);
         glVertex3f(0.75, 0.25, 0.0);
      glEnd();
      glBegin(GL_POLYGON);
         glVertex3f(0.75, 0.75, 0.0);
         glVertex3f(1.0, 0.75, 0.0);
         glVertex3f(1.0, 1.0, 0.0);
         glVertex3f(0.75, 1.0, 0.0);
      glEnd();
      glBegin(GL_POLYGON);
         glVertex3f(0.0, 0.75, 0.0);
         glVertex3f(0.25, 0.75, 0.0);
         glVertex3f(0.25, 1.0, 0.0);
         glVertex3f(0.0, 1.0, 0.0);
      glEnd();
      glColor3f(0.5, 0.0, 0.0);
      glBegin(GL_POLYGON);
         glVertex3f(0.37, 0.37, 0.0);
         glVertex3f(0.63, 0.37, 0.0);
         glVertex3f(0.63, 0.63, 0.0);
         glVertex3f(0.37, 0.63, 0.0);
      glEnd();
      glFlush();
}


/* exits on key press */
void key(unsigned char key, int x, int y) {
   if (key == 'q') {
      exit(0);
     } else {
      example();
   };
}


/////////////////////
//                 //
//  Main Function  //
//                 //
/////////////////////
int main( int argc, char * argv[] ) {

   /* Window variables  */
    
   /* Set Initial Defaults  */
      glutInitWindowSize(500, 500);
      glutInitWindowPosition(400, 400);

   /* Initialize libs and parse GL commandline options */
      glutInit(&argc, argv);

   /* Creates New window */
      glutCreateWindow("My Test Window");

   /* Defines how to handle events */
      init();
      glutDisplayFunc(example);
      glutKeyboardFunc(key);

   /* Kicks off the master loop */
      glutMainLoop();

   /* We never get Here */
      printf("See, I told you.\n");
      return(0);
}
