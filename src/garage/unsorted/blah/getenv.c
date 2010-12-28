
#include <stdio.h>
#include <stdlib.h>

int main(void);

int main(void)
{
   char * home;
   char * display;
   char * editor;
   char * pager;

   home    = getenv("HOME");
   display = getenv("DISPLAY");
   editor  = getenv("EDITOR");
   pager   = getenv("PAGER");

   printf("home:   %s\n",  home);
   printf("display: %s\n", display);
   printf("editor:  %s\n", editor);
   printf("pager:   %s\n", pager);
   return(0);
}
