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
#include <unistd.h>	/*  needed for usleep()           */
#include <syslog.h>	/*  Logs stuff for debugging      */


///////////////////
//               //
//  Definitions  //
//               //
///////////////////

#define TRUE	1
#define FALSE	0


/////////////////////
//                 //
//  Global values  //
//                 //
/////////////////////

   volatile GLfloat offset = 0;
   volatile char incre = FALSE;
   volatile time_t seconds = 0;
   volatile suseconds_t milseconds = 0;


//////////////////
//              //
//  Prototypes  //
//              //
//////////////////

   void choffset(void);				/*  Changes Offset          */
   void draw_square(void);			/*  draws square            */
   void idle(void);				/*  Idle loop               */
   void init(void);				/*  initializes the window  */
   void keypress(unsigned char, int, int);	/*  Interprets key strokes  */
   int  main(int, char **);			/*  umm, duh                */


/////////////////
//             //
//  Functions  //
//             //
/////////////////

/* Changes Offset */
void choffset() {
   if (incre == TRUE) {
      offset += 0.01;
      if (offset >= 0.24)
         incre = FALSE;
     } else {
      offset -= 0.01;
      if (offset <= 0.01)
         incre = TRUE;
   };
}


/* Draws Square */
void draw_square() {
   glutIdleFunc(idle);
   /* Draws Shapes */
      glClear(GL_COLOR_BUFFER_BIT);
      glPushMatrix();
      choffset();
      glColor3f(1.0, 1.0, 1.0);
      glBegin(GL_POLYGON);
         glVertex3f(0.25, 0.25, 0.0);
         glVertex3f(0.75, 0.25, 0.0);
         glVertex3f(0.75, 0.75, 0.0);
         glVertex3f(0.25, 0.75, 0.0);
      glEnd();
      glColor3f(0.0, 0.0, 0.75-(offset*2));
      glBegin(GL_POLYGON);
         glVertex3f(0.0+offset, 0.0+offset, 0.0);
         glVertex3f(0.25, 0.0, 0.0);
         glVertex3f(0.25-offset, 0.25-offset, 0.0);
         glVertex3f(0.0, 0.25, 0.0);
      glEnd();
      glColor3f(0.0, 0.0, 0.25+(offset*2));
      glBegin(GL_POLYGON);
         glVertex3f(0.75, 0.0, 0.0);
         glVertex3f(1.0-offset, 0.0+offset, 0.0);
         glVertex3f(1.0, 0.25, 0.0);
         glVertex3f(0.75+offset, 0.25-offset, 0.0);
      glEnd();
      glColor3f(0.0, 0.0, 0.75-(offset*2));
      glBegin(GL_POLYGON);
         glVertex3f(0.75+offset, 0.75+offset, 0.0);
         glVertex3f(1.0, 0.75, 0.0);
         glVertex3f(1.0-offset, 1.0-offset, 0.0);
         glVertex3f(0.75, 1.0, 0.0);
      glEnd();
      glColor3f(0.0, 0.0, 0.25+(offset*2));
      glBegin(GL_POLYGON);
         glVertex3f(0.0, 0.75, 0.0);
         glVertex3f(0.25-offset, 0.75+offset, 0.0);
         glVertex3f(0.25, 1.0, 0.0);
         glVertex3f(0.0+offset, 1.0-offset, 0.0);
      glEnd();
      glColor3f(0.25+(offset*2), 0.0, 0.0);
      glColor3f(0.25, 0.0, 0.0);
      glBegin(GL_POLYGON);
         glVertex3f(0.37, 0.37, 0.0);
         glVertex3f(0.63-offset, 0.37+offset, 0.0);
         glVertex3f(0.63, 0.63, 0.0);
         glVertex3f(0.37+offset, 0.63-offset, 0.0);
      glEnd();
      glPopMatrix();
      glutSwapBuffers();
}

void idle() {
   usleep(1000);
   usleep(1000);
   draw_square();                 
}

/* initializes the window */
void init() {
      glClearColor(0.0, 0.5, 0.0, 0.0);
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}


/* exits on key press */
void keypress(unsigned char key, int x, int y) {
   if (key == 'q')
      exit(0);
   if (key == '+') {
      glutPostRedisplay();
      choffset();
   };
}


/////////////////////
//                 //
//  Main Function  //
//                 //
/////////////////////
int main( int argc, char * argv[] ) {

   /* Window variables  */
      int count;
      int pos;
      long win;

   /* Opens log and logs debug info */
      openlog("alpined", LOG_PID, LOG_DAEMON);
      for (count = 0; count < argc; count++)
         syslog(LOG_NOTICE, "Arg %i: \"%s\"", count, argv[count]);

   /* Grabs commandline options */
      win = 0;
      for (count = 0; count < argc; count++) {
         if (!strcmp (argv[count], "-window-id")) {
            if ((argv[count + 1][0] == '0') && ((argv[count + 1][1] == 'x') || (argv[count + 1][1] == 'X'))) {
               win = strtol ((char *)(argv[count + 1] + 2), (char **)NULL, 16);
              } else {
               win = strtol ((char *)(argv[count + 1]), (char **)NULL, 10);
            };
            for (pos = count + 2; pos < argc; pos++) {
               argv[pos - 2] = argv[pos];
            };
            argc -= 2;
            break;
         };
      };
      //   syslog(LOG_NOTICE, "Specified Window: %i", win);
      //   syslog(LOG_NOTICE, "Current Window: %i", glutGetWindow());
      //   glutSetWindow(3800047+1);

   /* Set Initial Defaults  */
      //glutInitWindowSize(500, 500);
      //glutInitWindowPosition(100, 100);

   /* Initialize libs and parse GL commandline options */
      glutInit(&argc, argv);
      //glutInitDisplayMode(GLUT_DOUBLE);

   /* Creates New window */
      if (!win) {
         glutCreateWindow("My Test Window");
        } else {
         syslog(LOG_NOTICE, "Specified Window: %i", win);
         syslog(LOG_NOTICE, "Current Window: %i", glutGetWindow());
         glutSetWindow(3800047+1);
      };

   /* Defines how to handle events */
      init();
      //glutFullScreen();
      glutDisplayFunc(draw_square);
      glutKeyboardFunc(keypress);

   /* Kicks off the master loop */
      glutMainLoop();

   /* We never get Here */
      printf("See, I told you.\n");
      return(0);
}
