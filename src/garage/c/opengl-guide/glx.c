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

#include <GL/glx.h>
#include <stdio.h>	/*  For print statements          */
#include <stdlib.h>     /*  needed for exit()             */
#include <string.h>	
#include <unistd.h>	/*  needed for usleep()           */
#include <syslog.h>	/*  logging parameters */


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

   static int sglbuf[] = { 
      GLX_RGBA,
      GLX_RED_SIZE, 1,
      GLX_GREEN_SIZE, 1,
      GLX_BLUE_SIZE, 1,
      GLX_DEPTH_SIZE, 12,
      None 
   };

   static int dblbuf[] = {
      GLX_RGBA,
      GLX_RED_SIZE, 1,
      GLX_GREEN_SIZE, 1,
      GLX_BLUE_SIZE, 1,
      GLX_DEPTH_SIZE, 12,
      GLX_DOUBLEBUFFER,
      None
   };


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
   //glutIdleFunc(idle);
   /* Draws Shapes */
      glNewList(1,GL_COMPILE_AND_EXECUTE);
      glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
      //glPushMatrix();
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
      glBegin(GL_POLYGON);
         glVertex3f(0.37, 0.37, 0.0);
         glVertex3f(0.63-offset, 0.37+offset, 0.0);
         glVertex3f(0.63, 0.63, 0.0);
         glVertex3f(0.37+offset, 0.63-offset, 0.0);
      glEnd();
      glEndList();
      //glPopMatrix();
      //glutSwapBuffers();
}

void idle() {
   usleep(1000);
   usleep(1000);
   draw_square();                 
}

/* initializes the window */
void init() {
      glEnable(GL_DEPTH_TEST);
      glClearColor(0.0, 0.5, 0.0, 0.0);
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}


/* exits on key press */
//void keypress(unsigned char key, int x, int y) {
//   if (key == 'q')
//      exit(0);
//   if (key == '+') {
//      glutPostRedisplay();
//      choffset();
//   };
//}


/////////////////////
//                 //
//  Main Function  //
//                 //
/////////////////////
int main( int argc, char * argv[] ) {

   /* Local Vars  */
      Display *dpy;
      char *dpy_name = NULL;
      XVisualInfo *vi = NULL;
      GLXContext cx;
      Colormap cmap;
      XSetWindowAttributes swa;
      Window win;
      int doublebuf = TRUE;
      int dummy;
      int i;

      int width = 320;
      int height = 240;

   /* Opens syslog */
      openlog("glx.o", LOG_PID, LOG_DAEMON);
      for (i = 0; i < argc; i++)
         syslog(LOG_NOTICE, "Arg %i: \"%s\"", i, argv[i]);

   /* Connect to the X server */
      if(!(dpy = XOpenDisplay(NULL))) {
         fprintf(stderr, "%s: unable to open display %s\n", argv[0], dpy_name);
         return(1);
      };

   /* Check for GLX Extensions */
      if(!glXQueryExtension(dpy, &dummy, &dummy)) {
         fprintf(stderr, "%s: X server has no OpenGL GLX extension\n", argv[0]);
         return(1);
      };

   /* Find an OpenGL-capable visua */
      if (!(vi = glXChooseVisual(dpy, DefaultScreen(dpy), dblbuf))) {
         if(!(vi = glXChooseVisual(dpy, DefaultScreen(dpy), sglbuf))) {
            fprintf(stderr, "%s: no RGB visual with depth buffer\n", argv[0]);
            return(1);
         };
         doublebuf = False;
      };
      if(vi->class != TrueColor) {
         fprintf(stderr, "%s: TrueColor visual required for this program\n", argv[0]);
         return(1);
      };

   /* Create an OpenGL rendering context */
      if(!(cx = glXCreateContext(dpy, vi, None, True))) {
         fprintf(stderr, "%s: could not create rendering context\n", argv[0]);
         return(1);
      };

   /* create an X colormap */
      cmap = XCreateColormap(dpy,RootWindow(dpy,vi->screen),vi->visual,AllocNone);
      swa.colormap = cmap;
      swa.border_pixel = 0;
      swa.event_mask = ExposureMask | ButtonPressMask | StructureNotifyMask;

   /* Create Window */
      win = XCreateWindow(dpy,RootWindow(dpy,vi->screen),0,0,300,300,0,vi->depth,InputOutput,vi->visual,CWBorderPixel | CWColormap | CWEventMask,&swa);
      XSetStandardProperties(dpy,win,"glx.o","glx.o",None,argv,argc,NULL);

   /* Bind the rendering context to the window. */
      glXMakeCurrent(dpy, win, cx);

   /* Display the X window on the screen. */
      XMapWindow(dpy, win);

   /* initialize OpenGL */
      glFrustum(-1.0,1.0,-1.0,1.0,1.0,10.0);
      init();

   /* Main Loop */
      while (TRUE) {
         idle();
         if(doublebuf) {
            glXSwapBuffers(dpy,win);
           } else {
            glFlush();
         };
      };
      

   /* We never get Here */
      printf("See, I told you.\n");
      return(0);
}
