
#include <stdio.h>
#include <string.h>

#define DELAY   40000
//#define DELAY   1

#define COLOR_BOX_01	"[0;36m"		/* Far right box */
#define COLOR_BOX_02	"[1;36m"		/* lowest box */
#define COLOR_BOX_03	"[1;32m"		/* second lowest box */
#define COLOR_BOX_04	"[1;33m"		/* second lowest box */
#define COLOR_BOX_05	"[0;32m"		/* second lowest box */
#define COLOR_BOX_06	"[1;34m"		/* second lowest box */
#define COLOR_BOX_07	"[0;35m"		/* second lowest box */

#define POSXY	"[%i;%iH"
#define CLRSCR	"[2J"
#define HOME	"[23;0H"

/* Misc Pictures */
const char *mesg[] = { "Animated by",
                       "       Syzmations    ",
                       "Copyright (c) 2004 David Syzdek"
};

int main(void);

int main(void) {

   int c,i;

   /* clear screen */
      printf(CLRSCR);
      printf(POSXY, 0, 0);

   /* Far right square */
      /* set color */
         printf(COLOR_BOX_01);

      /* top of box */
         for (i = 0; i < 2; i++) {
            printf(POSXY, 11-i, 49+i);
            printf("/");
            printf(HOME);
            fflush(stdout); usleep(DELAY);
         };
         for (i = 0; i < 2; i++) {
            printf(POSXY, 10+i, 51+i);
            printf("\\");
            printf(HOME);
            fflush(stdout); usleep(DELAY);
         };
         for (i = 0; i < 2; i++) {
            printf(POSXY, 12+i, 52-i);
            printf("/");
            printf(HOME);
            fflush(stdout); usleep(DELAY);
         };
         for (i = 0; i < 2; i++) {
            printf(POSXY, 13-i, 50-i);
            printf("\\");
            printf(HOME);
            fflush(stdout); usleep(DELAY);
         };

      /* horz walls of box */
         for (i = 0; i < 3; i++) {
            printf(POSXY, 9, 50-i);
            printf("_");
            printf(POSXY, 11, 48-i);
            printf("_");
            printf(POSXY, 13, 49-i);
            printf("_");
            printf(HOME);
            fflush(stdout); usleep(DELAY);
         };
         printf(POSXY, 9, 50-i);
         printf("_");
         printf(HOME);
         fflush(stdout); usleep(DELAY);

      /* bottom of box */
         for (i = 0; i < 2; i++) {
            printf(POSXY, 10+i, 46-i);
            printf("/");
            printf(HOME);
            fflush(stdout); usleep(DELAY);
         };
         for (i = 0; i < 2; i++) {
            printf(POSXY, 12+i, 45+i);
            printf("\\");
            printf(HOME);
            fflush(stdout); usleep(DELAY);
         };

   /* Far right square */
      /* set color */
         printf(COLOR_BOX_02);

      /* left edges of box */
         for (i = 0; i < 2; i++) {
            printf(POSXY, 18+i, 16-i);
            printf("/");
            printf(HOME);
            fflush(stdout); usleep(DELAY);
         };
         for (i = 0; i < 2; i++) {
            printf(POSXY, 20+i, 15+i);
            printf("\\");
            printf(HOME);
            fflush(stdout); usleep(DELAY);
         };
   
      /* bottom wall of box */
         for (i = 0; i < 4; i++) {
            printf(POSXY, 21, 17+i);
            printf("_");
            printf(HOME);
            fflush(stdout); usleep(DELAY);
         };

      /* top of box */
         for (i = 0; i < 2; i++) {
            printf(POSXY, 21-i, 21-i);
            printf("\\");
            printf(HOME);
            fflush(stdout); usleep(DELAY);
         };
         for (i = 0; i < 2; i++) {
            printf(POSXY, 19-i, 20+i);
            printf("/");
            printf(HOME);
            fflush(stdout); usleep(DELAY);
         };
         for (i = 0; i < 2; i++) {
            printf(POSXY, 18+i, 22+i);
            printf("\\");
            printf(HOME);
            fflush(stdout); usleep(DELAY);
         };
         for (i = 0; i < 2; i++) {
            printf(POSXY, 20+i, 23-i);
            printf("/");
            printf(HOME);
            fflush(stdout); usleep(DELAY);
         };

      /* walls of box */
         for (i = 0; i < 4; i++) {
            printf(POSXY, 19, 19-i);
            printf("_");
            printf(POSXY, 17, 21-i);
            printf("_");
            printf(HOME);
            fflush(stdout); usleep(DELAY);
         };
            printf(POSXY, 17, 21-i);
            printf("_");
            printf(HOME);
            fflush(stdout); usleep(DELAY);

   /* Far right square */
      /* set color */
         printf(COLOR_BOX_03);

      /* center edge of box */
         for (i = 0; i < 10; i++) {
            printf(POSXY, 16, 14+i);
            printf("_");
            printf(HOME);
            fflush(stdout); usleep(DELAY);
         };

      /* build top of box */
         for (i = 0; i < 4; i++) {
            printf(POSXY, 17+i, 24+i);
            printf("\\");
            printf(HOME);
            fflush(stdout); usleep(DELAY);
         };
         for (i = 0; i < 4; i++) {
            printf(POSXY, 20-i, 28+i);
            printf("/");
            printf(HOME);
            fflush(stdout); usleep(DELAY);
         };
         for (i = 0; i < 4; i++) {
            printf(POSXY, 16-i, 31-i);
            printf("\\");
            printf(HOME);
            fflush(stdout); usleep(DELAY);
         };
         for (i = 0; i < 4; i++) {
            printf(POSXY, 13+i, 27-i);
            printf("/");
            printf(HOME);
            fflush(stdout); usleep(DELAY);
         };

      /* top edge */
         for (i = 0; i < 11; i++) {
            printf(POSXY, 12, 27-i);
            printf("_");
            printf(HOME);
            fflush(stdout); usleep(DELAY);
         };

      /* left edge of box */
         for (i = 0; i < 4; i++) {
            printf(POSXY, 13+i, 16-i);
            printf("/");
            printf(HOME);
            fflush(stdout); usleep(DELAY);
         };
         for (i = 0; i < 2; i++) {
            printf(POSXY, 17+i, 13+i);
            printf("\\");
            printf(HOME);
            fflush(stdout); usleep(DELAY);
         };

      /* bottom edge */
         for (i = 0; i < 3; i++) {
            printf(POSXY, 20, 24+i);
            printf("_");
            printf(HOME);
            fflush(stdout); usleep(DELAY);
         };

   /* far top box */
      /* set color */
         printf(COLOR_BOX_04);

      /* center edge of box */
         for (i = 0; i < 4; i++) {
            printf(POSXY, 6-i, 23-i);
            printf("\\");
            printf(HOME);
            fflush(stdout); usleep(DELAY);
         };

      /* top of box */
         for (i = 0; i < 2; i++) {
            printf(POSXY, 2, 19-i);
            printf("_");
            printf(HOME);
            fflush(stdout); usleep(DELAY);
         };
         printf(POSXY, 2, 19-i);
         printf("/");
         printf(HOME);
         fflush(stdout); usleep(DELAY);
         for (i = 0; i < 3; i++) {
            printf(POSXY, 1, 18+i);
            printf("_");
            printf(HOME);
            fflush(stdout); usleep(DELAY);
         };
         printf(POSXY, 2, 20);
         printf("/");
         printf(HOME);
         fflush(stdout); usleep(DELAY);

      /* far right edge */
         for (i = 0; i < 4; i++) {
            printf(POSXY, 2+i, 21+i);
            printf("\\");
            printf(HOME);
            fflush(stdout); usleep(DELAY);
         };

      /* bottom edges */
         printf(POSXY, 6, 24);
         printf("/");
         printf(HOME);
         fflush(stdout); usleep(DELAY);
         printf(POSXY, 6, 22);
         printf("_");
         printf(HOME);
         fflush(stdout); usleep(DELAY);
         printf(POSXY, 6, 21);
         printf("_");
         printf(HOME);
         fflush(stdout); usleep(DELAY);
         
      /* left edge */
         for(i = 0; i < 4; i++) {
            printf(POSXY, 6-i, 20-i);
            printf("\\");
            printf(HOME);
            fflush(stdout); usleep(DELAY);
         };

   /* second to right box */
      /* set color */
         printf(COLOR_BOX_05);

      /* top of box */
         for (i = 0; i < 4; i++) {
            printf(POSXY, 15-i, 46-i);
            printf("\\");
            printf(HOME);
            fflush(stdout); usleep(DELAY);
         };
         for (i = 0; i < 4; i++) {
            printf(POSXY, 11-i, 43+i);
            printf("/");
            printf(HOME);
            fflush(stdout); usleep(DELAY);
         };
         for (i = 0; i < 2; i++) {
            printf(POSXY, 8+i, 47+i);
            printf("\\");
            printf(HOME);
            fflush(stdout); usleep(DELAY);
         };
         for (i = 0; i < 2; i++) {
            printf(POSXY, 14+i, 48-i);
            printf("/");
            printf(HOME);
            fflush(stdout); usleep(DELAY);
         };

      /* outline edge */
         for (i = 0; i < 8; i++) {
            printf(POSXY, 15, 45-i);
            printf("_");
            printf(HOME);
            fflush(stdout); usleep(DELAY);
         };
         for (i = 0; i < 4; i++) {
            printf(POSXY, 15-i, 37-i);
            printf("\\");
            printf(HOME);
            fflush(stdout); usleep(DELAY);
         };
         for (i = 0; i < 4; i++) {
            printf(POSXY, 11-i, 34+i);
            printf("/");
            printf(HOME);
            fflush(stdout); usleep(DELAY);
         };
         for (i = 0; i < 9; i++) {
            printf(POSXY, 7, 38+i);
            printf("_");
            printf(HOME);
            fflush(stdout); usleep(DELAY);
         };
         for (i = 0; i < 8; i++) {
            printf(POSXY, 11, 42-i);
            printf("_");
            printf(HOME);
            fflush(stdout); usleep(DELAY);
         };

   /* second box from top */
      /* set color */
         printf(COLOR_BOX_06);

      /* body */
         for (i = 0; i < 3; i++) {
            printf(POSXY, 5+i, 27-i);
            printf("/");
            printf(HOME);
            fflush(stdout); usleep(DELAY);
         };
         for (i = 0; i < 7; i++) {
            printf(POSXY, 7, 24-i);
            printf("_");
            printf(HOME);
            fflush(stdout); usleep(DELAY);
         };
         for (i = 0; i < 2; i++) {
            printf(POSXY, 7-i, 17+i);
            printf("/");
            printf(HOME);
            fflush(stdout); usleep(DELAY);
         };
         for (i = 0; i < 4; i++) {
            printf(POSXY, 4, 24+i);
            printf("_");
            printf(HOME);
            fflush(stdout); usleep(DELAY);
         };
         for (i = 0; i < 3; i++) {
            printf(POSXY, 5+i, 28+i);
            printf("\\");
            printf(HOME);
            fflush(stdout); usleep(DELAY);
         };
         for (i = 0; i < 3; i++) {
            printf(POSXY, 8+i, 30-i);
            printf("/");
            printf(HOME);
            fflush(stdout); usleep(DELAY);
         };
         for (i = 0; i < 8; i++) {
            printf(POSXY, 10, 27-i);
            printf("_");
            printf(HOME);
            fflush(stdout); usleep(DELAY);
         };
         for (i = 0; i < 3; i++) {
            printf(POSXY, 10-i, 19-i);
            printf("\\");
            printf(HOME);
            fflush(stdout); usleep(DELAY);
         };
         for (i = 0; i < 3; i++) {
            printf(POSXY, 10-i, 27-i);
            printf("\\");
            printf(HOME);
            fflush(stdout); usleep(DELAY);
         };

   /* main box */
      /* set color */
         printf(COLOR_BOX_07);

      /* body */
         for (i = 0; i < 3; i++) {
            printf(POSXY, 12+i, 12+i);
            printf("\\");
            printf(HOME);
            fflush(stdout); usleep(DELAY);
         };
         for (i = 0; i < 6; i++) {
            printf(POSXY, 17, 32+i);
            printf("_");
            printf(HOME);
            fflush(stdout); usleep(DELAY);
         };
         for (i = 0; i < 2; i++) {
            printf(POSXY, 17-i, 38+i);
            printf("/");
            printf(HOME);
            fflush(stdout); usleep(DELAY);
         };
         for (i = 0; i < 2; i++) {
            printf(POSXY, 7-i, 39-i);
            printf("\\");
            printf(HOME);
            fflush(stdout); usleep(DELAY);
         };
         for (i = 0; i < 6; i++) {
            printf(POSXY, 6+i, 37-i);
            printf("/");
            printf(HOME);
            fflush(stdout); usleep(DELAY);
         };
         for (i = 0; i < 6; i++) {
            printf(POSXY, 12+i, 32+i);
            printf("\\");
            printf(HOME);
            fflush(stdout); usleep(DELAY);
         };
         for (i = 0; i < 19; i++) {
            printf(POSXY, 11, 31-i);
            printf("_");
            printf(HOME);
            fflush(stdout); usleep(DELAY);
         };
         for (i = 0; i < 6; i++) {
            printf(POSXY, 11-i, 12+i);
            printf("/");
            printf(HOME);
            fflush(stdout); usleep(DELAY);
         };
         printf(POSXY, 11-i, 12+i);
         printf("_");
         printf(HOME);
         fflush(stdout); usleep(DELAY);
         for (i = 0; i < 9; i++) {
            printf(POSXY, 5, 29+i);
            printf("_");
            printf(HOME);
            fflush(stdout); usleep(DELAY);
         };

   /* lowest box */
      /* set color */
         printf(COLOR_BOX_04);

      /* body */
         for (i = 0; i < 4; i++) {
            printf(POSXY, 18+i, 31+i);
            printf("\\");
            printf(HOME);
            fflush(stdout); usleep(DELAY);
         };
         for (i = 0; i < 3; i++) {
            printf(POSXY, 21, 35+i);
            printf("_");
            printf(HOME);
            fflush(stdout); usleep(DELAY);
         };
         printf(POSXY, 21, 38);
         printf("/");
         printf(HOME);
         fflush(stdout); usleep(DELAY);
         for (i = 0; i < 3; i++) {
            printf(POSXY, 20-i, 38-i);
            printf("\\");
            printf(HOME);
            fflush(stdout); usleep(DELAY);
         };
         for (i = 0; i < 4; i++) {
            printf(POSXY, 18+i, 34+i);
            printf("\\");
            printf(HOME);
            fflush(stdout); usleep(DELAY);
         };

   /* second from back */
      /* set color */
         printf(COLOR_BOX_03);
                           
      /* body */
         printf(POSXY, 7, 40);
         printf("/");
         printf(HOME);
         fflush(stdout); usleep(DELAY);
         for (i = 0; i < 4; i++) {
            printf(POSXY, 6-i, 40-i);
            printf("\\");
            printf(HOME);
            fflush(stdout); usleep(DELAY);
         };
         for (i = 0; i < 10; i++) {
            printf(POSXY, 2, 36-i);
            printf("_");
            printf(HOME);
            fflush(stdout); usleep(DELAY);
         };
         for (i = 0; i < 2; i++) {
            printf(POSXY, 3+i, 26-i);
            printf("/");
            printf(HOME);
            fflush(stdout); usleep(DELAY);
         };
         for (i = 0; i < 3; i++) {
            printf(POSXY, 5-i, 34+i);
            printf("/");
            printf(HOME);
            fflush(stdout); usleep(DELAY);
         };

   /* second from left */
      /* set color */
         printf(COLOR_BOX_05);
                           
      /* body */
         for (i = 0; i < 5; i++) {
            printf(POSXY, 15, 13-i);
            printf("_");
            printf(HOME);
            fflush(stdout); usleep(DELAY);
         };
         for (i = 0; i < 4; i++) {
            printf(POSXY, 15-i, 8-i);
            printf("\\");
            printf(HOME);
            fflush(stdout); usleep(DELAY);
         };
         for (i = 0; i < 4; i++) {
            printf(POSXY, 11-i, 5+i);
            printf("/");
            printf(HOME);
            fflush(stdout); usleep(DELAY);
         };
         for (i = 0; i < 7; i++) {
            printf(POSXY, 7, 9+i);
            printf("_");
            printf(HOME);
            fflush(stdout); usleep(DELAY);
         };
         for (i = 0; i < 6; i++) {
            printf(POSXY, 11, 11-i);
            printf("_");
            printf(HOME);
            fflush(stdout); usleep(DELAY);
         };
      
   /* far left box */
      /* set color */
         printf(COLOR_BOX_01);
                          
      /* body */
         printf(POSXY, 13, 5);
         printf("_");
         printf(HOME);
         fflush(stdout); usleep(DELAY);
         for (i = 0; i < 2; i++) {
            printf(POSXY, 13-i, 4-i);
            printf("\\");
            printf(HOME);
            fflush(stdout); usleep(DELAY);
         };
         for (i = 0; i < 2; i++) {
            printf(POSXY, 11-i, 3+i);
            printf("/");
            printf(HOME);
            fflush(stdout); usleep(DELAY);
         };
         for (i = 0; i < 2; i++) {
            printf(POSXY, 9, 5+i);
            printf("_");
            printf(HOME);
            fflush(stdout); usleep(DELAY);
         };
         printf(POSXY, 11, 4);
         printf("_");
         printf(HOME);
         fflush(stdout); usleep(DELAY);

   /* far back box */
      /* set color */
         printf(COLOR_BOX_02);

      /* body */
         printf(POSXY, 2, 30);
         printf("/");
         printf(HOME);
         fflush(stdout); usleep(DELAY);
         for (i = 0; i < 6; i++) {
            printf(POSXY, 1, 31+i);
            printf("_");
            printf(HOME);
            fflush(stdout); usleep(DELAY);
         };
         for (i = 0; i < 2; i++) {
            printf(POSXY, 2+i, 37+i);
            printf("\\");
            printf(HOME);
            fflush(stdout); usleep(DELAY);
         };
         printf(POSXY, 2, 36);
         printf("/");
         printf(HOME);
         fflush(stdout); usleep(DELAY);

   /* resets color */
      printf("[0m");

   /* Disaplays messages */
      printf(POSXY, 19, 45);
      for (i = 0; i < strlen(mesg[0]); i++) {
         printf("%c", mesg[0][i]);
         fflush(stdout);
         usleep(DELAY);
      };
      printf(POSXY, 20, 45);
      for (i = 0; i < strlen(mesg[1]); i++) {
         printf("%c", mesg[1][i]);
         fflush(stdout);
         usleep(DELAY);
      };
      printf(POSXY, 22, 31);
      for (i = 0; i < strlen(mesg[2]); i++) {
         printf("%c", mesg[2][i]);
         fflush(stdout);
         usleep(DELAY);
      };

   /* Home cursor */
      printf(HOME);
      fflush(stdout);

   /* ends function */
   return(0);
}
