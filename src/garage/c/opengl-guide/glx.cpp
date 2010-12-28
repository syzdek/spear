#include <GL/glx.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <unistd.h>

static int attributeListSgl[] = {GLX_RGBA, GLX_RED_SIZE, 1, GLX_GREEN_SIZE, 1, GLX_BLUE_SIZE, 1, None};

static  int  attributeListDbl[]  =  {GLX_RGBA, GLX_DOUBLE_BUFFER, GLX_RED_SIZE, 1, GLX_GREEN_SIZE, 1, GLX_BLUE_SIZE, 1, None };

       static Bool WaitForNotify(Display *d, XEvent *e, char *arg) {
           return (e->type == MapNotify) && (e->xmap.window == (Window)arg); }

       int main(int argc, char **argv) {
           Display *dpy;
           XVisualInfo *vi;
           Colormap cmap;
           XSetWindowAttributes swa;
           Window win;
           GLXContext cx;
           XEvent event;
           int swap_flag = FALSE;

           dpy = XOpenDisplay(0);

           vi = glXChooseVisual(dpy, DefaultScreen(dpy), attributeListSgl);
           if (vi == NULL) {
              vi = glXChooseVisual(dpy, DefaultScreen(dpy), attributeListDbl);
              swap_flag = TRUE;
           }

           cx = glXCreateContext(dpy, vi, 0, GL_TRUE);

           cmap = XCreateColormap(dpy, RootWindow(dpy, vi->screen),                   vi->visual, AllocNone);

           swa.colormap = cmap;
           swa.border_pixel = 0;
           swa.event_mask = StructureNotifyMask;
           win = XCreateWindow(dpy, RootWindow(dpy, vi->screen), 0, 0, 100, 100,
                               0, vi->depth, InputOutput, vi->visual,
                               CWBorderPixel|CWColormap|CWEventMask, &swa);
           XMapWindow(dpy, win);
           XIfEvent(dpy, &event, WaitForNotify, (char*)win);

           glXMakeCurrent(dpy, win, cx);

           glClearColor(1,1,0,1);
           glClear(GL_COLOR_BUFFER_BIT);
           glFlush();
           if (swap_flag) glXSwapBuffers(dpy,win);

           sleep(10);
 }

