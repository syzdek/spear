/*
 * Animated ASCII Art
 * $Source: /repos/development/blips/blips/src/blipsd/blipsd.c,v $
 * $Revision: 1.13.2.8 $
 * $Date: 2004/07/14 09:33:59 $
 * $Author: syzdek $
 */
/*
 * Copyright (c) 2004 David M. Syzdek <syzdek@mosquitonet.com>
 * All Rights Reserved.
 * COPYING RESTRICTIONS APPLY, see LICENSE.TXT file
 */
/*  pumpkin.c - Animates the drawing of a pumpkin
*/
/*
 * Build:
 *    gcc -O2 -o pumpkin pumpkin.c 
 */
#define _ANIMATED_ASCII_PUMPKIN_C
#include "pumpkin.h"


///////////////
//           //
//  Credits  //
//           //
///////////////

/* Misc Pictures */
const char *credits[] = { 
   "Animated by",
   "Syzmations",
   "Copyright (c) 2004 David Syzdek"
};


/////////////////
//             //
//  Functions  //
//             //
/////////////////

/* animates first type of carving */
   int animate_carving1(int x, int y) {

      /* declares local vars */
         int i;

      /* changes color */
         printf(PUMPKIN_COLOR_CARVING);

      /* top right side */
         printf(POSXY, y, x+2);
         printf(".");
         fflush(stdout); usleep(DELAY*2);
         printf(POSXY, y+1, x+2);
         printf(" \\");
         fflush(stdout); usleep(DELAY*2);
         printf(POSXY, y+2, x+4);
         printf("\\");
         fflush(stdout); usleep(DELAY*2);

      /* bottom side */
         for(i = 0; i < 3; i++) {
            printf(POSXY, y+2, x+3-i);
            printf("_");
            fflush(stdout); usleep(DELAY*2);
         };

      /* top left side */
         printf(POSXY, y+2, x);
         printf("/");
         fflush(stdout); usleep(DELAY*2);
         printf(POSXY, y+1, x+1);
         printf("/");
         fflush(stdout); usleep(DELAY*2);

      /* ends function */
         return(0);
   }


/* animates first type of carving */
   int animate_carving2(int x, int y) {

      /* declares local vars */
         int i;

      /* changes color */
         printf(PUMPKIN_COLOR_CARVING);

      /* top side */
         for(i = 0; i < 5; i++) {
            printf(POSXY, y, x+i);
            printf("_");
            fflush(stdout); usleep(DELAY*2);
         };

      /* bottom right side */
         for(i = 0; i < 2; i++) {
            printf(POSXY, y+1+i, x+3-i);
            printf(" /");
            fflush(stdout); usleep(DELAY*2);
         };

      /* bottom tip */
         printf(POSXY, y+3, x+2);
         printf("`");
         fflush(stdout); usleep(DELAY*2);

      /* bottom left side */
         for(i = 0; i < 2; i++) {
            printf(POSXY, y+2-i, x+1-i);
            printf("\\ ");
            fflush(stdout); usleep(DELAY*2);
         };

      /* ends function */
         return(0);
   }


/* animates first type of carving */
   int animate_carving3(int x, int y) {

      /* declares local vars */
         int i;

      /* changes color */
         printf(PUMPKIN_COLOR_CARVING);

      /* top side */
         for(i = 0; i < 5; i++) {
            printf(POSXY, y, x+i);
            printf("_");
            fflush(stdout); usleep(DELAY*2);
         };

      /* right side */
         printf(POSXY, y+1, x+2);
         printf("  |");
         fflush(stdout); usleep(DELAY*2);
         printf(POSXY, y+2, x+4);
         printf("|");
         fflush(stdout); usleep(DELAY*2);

      /* bottom side */
         for(i = 0; i < 3; i++) {
            printf(POSXY, y+2, x+3-i);
            printf("_");
            fflush(stdout); usleep(DELAY*2);
         };

      /* left side */
         printf(POSXY, y+1, x);
         printf("| ");
         fflush(stdout); usleep(DELAY*2);
         printf(POSXY, y+2, x);
         printf("|");
         fflush(stdout); usleep(DELAY*2);

      /* ends function */
         return(0);
   }



/* animates credits */
   int animate_credits_from_left(int x, int y, int l, const char *str) {

      /* declares local vars */
         int s;
         int i;

      /* changes color */
         printf(PUMPKIN_COLOR_CREDITS);

      /* determines length of string */
         s = strlen(str);

      /* display string */
         for(i = 0; i < s; i++) {
            printf(POSXY, y, x);
            printf("%s", &str[s-i]);
            fflush(stdout); usleep(DELAY*2);
         };

      /* slides string */
         for(i = 0; i < l; i++) {
            printf(POSXY, y, x+i);
            printf(" %s", str);
            fflush(stdout); usleep(DELAY*2);
         };

      /* ends function */
         return(0);
   }


/* animates credits */
   int animate_credits_from_top(int x, int y, int l, const char *str) {

      /* declares local vars */
         int s;
         int i;
         char *clear;

      /* makes clear string */
         s = strlen(str);
         clear = (char *) malloc(s+1);
         memset(clear, ' ', s);
         clear[s] = '\0';

      /* changes color */
         printf(PUMPKIN_COLOR_CREDITS);

      /* slides string */
         for(i = 0; i < l-1; i++) {
            printf(POSXY, y+i, x);
            printf("%s", str);
            fflush(stdout); usleep(DELAY*2);
            printf(POSXY, y+i, x);
            printf("%s", clear);
         };
         printf(POSXY, y+i, x);
         printf("%s", str);
         fflush(stdout); usleep(DELAY*2);

      /* clears memory */
         free(clear);

      /* ends function */
         return(0);
   }


/* animates credits */
   int animate_credits_type(int x, int y, const char *str) {

      /* declares local vars */
         int s;
         int i;

      /* changes color */
         printf(PUMPKIN_COLOR_CREDITS);

      /* gets size of string */
         s = strlen(str);

      /* displays string */
         for(i = 0; i < s; i++) {
            printf(POSXY, y, x+i);
            printf("%c", str[i]);
            fflush(stdout); usleep(DELAY*2);
         };

      /* ends function */
         return(0);
   }


/* animates first type of mouth */
   int animate_mouth1(int x, int y) {

      /* declares local vars */
         int i;

      /* changes color */
         printf(PUMPKIN_COLOR_CARVING);

      /* left side */
         for(i = 0; i < 3; i++) {
            printf(POSXY, y+19-i, x+10-i);
            printf("\\");
            fflush(stdout); usleep(DELAY*2);
         };

      /* top of mouth */
         for(i = 0; i < 2; i++) {
            printf(POSXY, y+16, x+8+i);
            printf("_");
            fflush(stdout); usleep(DELAY);
         };
         printf(POSXY, y+17, x+10);
         printf("`");
         fflush(stdout); usleep(DELAY);
         printf(POSXY, y+17, x+11);
         printf("\\");
         fflush(stdout); usleep(DELAY);
         printf(POSXY, y+18, x+12);
         printf("\\");
         fflush(stdout); usleep(DELAY);
         printf("/");
         fflush(stdout); usleep(DELAY);
         printf(POSXY, y+17, x+14);
         printf("/");
         fflush(stdout); usleep(DELAY);
         printf(POSXY, y+16, x+15);
         printf(".");
         fflush(stdout); usleep(DELAY);
         printf(POSXY, y+17, x+16);
         printf("\\");
         fflush(stdout); usleep(DELAY);
         printf(POSXY, y+18, x+17);
         printf("\\");
         fflush(stdout); usleep(DELAY);
         printf("/");
         fflush(stdout); usleep(DELAY);
         printf(POSXY, y+17, x+19);
         printf("/");
         fflush(stdout); usleep(DELAY);
         printf(POSXY, y+16, x+20);
         printf(".");
         fflush(stdout); usleep(DELAY);
         printf(POSXY, y+17, x+21);
         printf("\\");
         fflush(stdout); usleep(DELAY);
         printf(POSXY, y+18, x+22);
         printf("\\");
         fflush(stdout); usleep(DELAY);
         printf("/");
         fflush(stdout); usleep(DELAY);
         printf(POSXY, y+17, x+24);
         printf("/");
         fflush(stdout); usleep(DELAY);
         printf(POSXY, y+16, x+25);
         printf(".");
         fflush(stdout); usleep(DELAY);
         printf(POSXY, y+17, x+26);
         printf("\\");
         fflush(stdout); usleep(DELAY);
         printf(POSXY, y+18, x+27);
         printf("\\");
         fflush(stdout); usleep(DELAY);
         printf("/");
         fflush(stdout); usleep(DELAY);
         printf(POSXY, y+17, x+29);
         printf("/");
         fflush(stdout); usleep(DELAY);
         printf(POSXY, y+16, x+30);
         printf(",");
         fflush(stdout); usleep(DELAY);
         printf("_");
         fflush(stdout); usleep(DELAY);
         printf("_");
         fflush(stdout); usleep(DELAY);

      /* right side */
         for(i = 0; i < 3; i++) {
            printf(POSXY, y+17+i, x+32-i);
            printf("/");
            fflush(stdout); usleep(DELAY);
         };

      /* bottom side */
         for(i = 0; i < 19; i ++) {
            printf(POSXY, y+19, x+29-i);
            printf("_");
            fflush(stdout); usleep(DELAY);
         };

      /* ends function */
         return(0);
   }


/* Draws pumpkin at the coordinates X Y */
   int animate_pumpkin(int x, int y) {

      /* declares local vars */
         int i;

      /* changes color */
         printf(PUMPKIN_COLOR_BODY);

      /* draws inside oval */
         /* bottom of oval */
            printf(POSXY, y+20, x+20);
            printf("_");
            fflush(stdout); usleep(DELAY);

         /* bottom of left side 1/3 */
            printf(POSXY, y+20, x+19);
            printf("\\");
            fflush(stdout); usleep(DELAY);
            printf(POSXY, y+19, x+18);
            printf("\\");
            fflush(stdout); usleep(DELAY);

         /* bottom of left side 2/3 */
            printf(POSXY, y+18, x+18);
            printf("\\");
            fflush(stdout); usleep(DELAY);
            printf(POSXY, y+17, x+17);
            printf("\\");
            fflush(stdout); usleep(DELAY);

         /* bottom of left side 3/3 */
            printf(POSXY, y+16, x+17);
            printf("\\");
            fflush(stdout); usleep(DELAY);
            printf(POSXY, y+15, x+16);
            printf("\\");
            fflush(stdout); usleep(DELAY);

         /* middle of the left side */
            printf(POSXY, y+14, x+16);
            printf("\\");
            fflush(stdout); usleep(DELAY);
            printf(POSXY, y+13, x+16);
            printf("(");
            fflush(stdout); usleep(DELAY);
            printf(POSXY, y+12, x+16);
            printf("/");
            fflush(stdout); usleep(DELAY);

         /* top of left side 1/3 */
            printf(POSXY, y+11, x+16);
            printf("/");
            fflush(stdout); usleep(DELAY);
            printf(POSXY, y+10, x+17);
            printf("/");
            fflush(stdout); usleep(DELAY);

         /* top of left side 2/3 */
            printf(POSXY, y+9, x+17);
            printf("/");
            fflush(stdout); usleep(DELAY);
            printf(POSXY, y+8, x+18);
            printf("/");
            fflush(stdout); usleep(DELAY);

         /* top of left side 3/3 */
            printf(POSXY, y+7, x+18);
            printf("/");
            fflush(stdout); usleep(DELAY);
            printf(POSXY, y+6, x+19);
            printf("/");
            fflush(stdout); usleep(DELAY);

         /* top of oval */
            printf(POSXY, y+5, x+20);
            printf("_");
            fflush(stdout); usleep(DELAY);

         /* top of right side 1/3 */
            printf(POSXY, y+6, x+21);
            printf("\\");
            fflush(stdout); usleep(DELAY);
            printf(POSXY, y+7, x+22);
            printf("\\");
            fflush(stdout); usleep(DELAY);

         /* top of right side 2/3 */
            printf(POSXY, y+8, x+22);
            printf("\\");
            fflush(stdout); usleep(DELAY);
            printf(POSXY, y+9, x+23);
            printf("\\");
            fflush(stdout); usleep(DELAY);

         /* top of right side 3/3 */
            printf(POSXY, y+10, x+23);
            printf("\\");
            fflush(stdout); usleep(DELAY);
            printf(POSXY, y+11, x+24);
            printf("\\");
            fflush(stdout); usleep(DELAY);

         /* middle of the left side */
            printf(POSXY, y+12, x+24);
            printf("\\");
            fflush(stdout); usleep(DELAY);
            printf(POSXY, y+13, x+24);
            printf(")");
            fflush(stdout); usleep(DELAY);
            printf(POSXY, y+14, x+24);
            printf("/");
            fflush(stdout); usleep(DELAY);

         /* bottom of right side 1/3 */
            printf(POSXY, y+15, x+24);
            printf("/");
            fflush(stdout); usleep(DELAY);
            printf(POSXY, y+16, x+23);
            printf("/");
            fflush(stdout); usleep(DELAY);

         /* bottom of right side 2/3 */
            printf(POSXY, y+17, x+23);
            printf("/");
            fflush(stdout); usleep(DELAY);
            printf(POSXY, y+18, x+22);
            printf("/");
            fflush(stdout); usleep(DELAY);

         /* bottom of right side 3/3 */
            printf(POSXY, y+19, x+22);
            printf("/");
            fflush(stdout); usleep(DELAY);
            printf(POSXY, y+20, x+21);
            printf("/");
            fflush(stdout); usleep(DELAY);

         /* pauses to get past bottom */
            printf(POSXY, y+20, x+20);
            fflush(stdout); usleep(DELAY);
            printf(POSXY, y+20, x+19);
            fflush(stdout); usleep(DELAY);

      /* draws middle oval */
         /* left side of bottom */
            for(i = 0; i < 3; i++) {
               printf(POSXY, y+20, x+18-i);
               printf("_");
               fflush(stdout); usleep(DELAY);
            };

         /* bottom of left side */
            for(i = 0; i < 7; i++) {
               printf(POSXY, y+20-i, x+15-i);
               printf("\\");
               fflush(stdout); usleep(DELAY);
            };

         /* middle of left side */
            printf(POSXY, y+13, x+9);
            printf("(");
            fflush(stdout); usleep(DELAY);

         /* top of left side 1/2 */
            for(i = 0; i < 5; i++) {
               printf(POSXY, y+12-i, x+9+i);
               printf("/");
               fflush(stdout); usleep(DELAY);
            };

         /* top of left side 2/2 */
            printf(POSXY, y+7, x+14);
            printf(",");
            fflush(stdout); usleep(DELAY);
            printf("/");
            fflush(stdout); usleep(DELAY);
            printf(POSXY, y+6, x+16);
            printf(",");
            fflush(stdout); usleep(DELAY);
            printf("/");
            fflush(stdout); usleep(DELAY);

         /* top of oval */
            printf(POSXY, y+5, x+18);
            for(i = 0; i < 5; i++) {
               printf("_");
               fflush(stdout); usleep(DELAY);
            };

         /* top of left side 1/2 */
            printf(POSXY, y+6, x+23);
            printf("\\");
            fflush(stdout); usleep(DELAY);
            printf(POSXY, y+7, x+24);
            printf("`");
            fflush(stdout); usleep(DELAY);
            printf("\\");
            fflush(stdout); usleep(DELAY);
            printf(POSXY, y+8, x+26);
            printf("`");
            fflush(stdout); usleep(DELAY);

         /* top of left side 2/2 */
            for (i = 0; i < 5; i++) {
               printf(POSXY, y+8+i, x+27+i);
               printf("\\");
               fflush(stdout); usleep(DELAY);
            };

         /* middle of right side */
            printf(POSXY, y+13, x+31);
            printf(")");
            fflush(stdout); usleep(DELAY);

         /* bottom of left side */
            for (i = 0; i < 7; i++) {
               printf(POSXY, y+14+i, x+31-i);
               printf("/");
               fflush(stdout); usleep(DELAY);
            };

         /* right side of bottom */
            for(i = 0; i < 3; i++) {
               printf(POSXY, y+20, x+24-i);
               printf("_");
               fflush(stdout); usleep(DELAY);
            };

         /* pauses to get past bottom */
            for (i = 0; i < 7; i++) {
               printf(POSXY, y+20, x+21-i);
               fflush(stdout); usleep(DELAY);
            };

      /* draws out side oval */
         /* left side of bottom */
            for(i = 0; i < 5; i++) {
               printf(POSXY, y+20, x+14-i);
               printf("_");
               fflush(stdout); usleep(DELAY);
            };

         /* bottom of left side 1/2 */
            printf(POSXY, y+20, x+9);
            printf("\\");
            fflush(stdout); usleep(DELAY);
            printf(POSXY, y+20, x+8);
            printf("`");
            fflush(stdout); usleep(DELAY);
            printf(POSXY, y+19, x+7);
            printf("\\");
            fflush(stdout); usleep(DELAY);
            printf(POSXY, y+19, x+6);
            printf("`");
            fflush(stdout); usleep(DELAY);

         /* bottom of left side 2/2 */
            for(i = 0; i < 3; i++) {
               printf(POSXY, y+18-i, x+5-i);
               printf("\\");
               fflush(stdout); usleep(DELAY);
            };

         /* middle of left side */
            printf(POSXY, y+15, x+2);
            printf("\\");
            fflush(stdout); usleep(DELAY);
            printf(POSXY, y+14, x+1);
            printf("\\");
            fflush(stdout); usleep(DELAY);
            printf(POSXY, y+13, x+1);
            printf("(");
            fflush(stdout); usleep(DELAY);
            printf(POSXY, y+12, x+1);
            printf("/");
            fflush(stdout); usleep(DELAY);
            printf(POSXY, y+11, x+1);
            printf("/");
            fflush(stdout); usleep(DELAY);
            printf(POSXY, y+10, x+2);
            printf("/");
            fflush(stdout); usleep(DELAY);

         /* top of left side 1/3 */
            for (i = 0; i < 3; i++) {
               printf(POSXY, y+9-i, x+2+i);
               printf("/");
               fflush(stdout); usleep(DELAY);
            };

         /* top of left side 2/3 */
            printf(POSXY, y+6, x+5);
            printf(",");
            fflush(stdout); usleep(DELAY);
            printf("/");
            fflush(stdout); usleep(DELAY);
            printf(POSXY, y+5, x+7);
            printf(",");
            fflush(stdout); usleep(DELAY);
            printf("_");
            fflush(stdout); usleep(DELAY);
            printf("-");
            fflush(stdout); usleep(DELAY);
            printf("-");
            fflush(stdout); usleep(DELAY);

         /* top of left side 3/3 */
            for (i = 0; i < 4; i++) {
               printf(POSXY, y+4, x+11+i);
               printf("_");
               fflush(stdout); usleep(DELAY);
            };

         /* top of oval 1/3 */
            printf(POSXY, y+5, x+15);
            printf("`");
            fflush(stdout); usleep(DELAY);
            printf("\\");
            fflush(stdout); usleep(DELAY);

         /* top of oval 2/3 */
            animate_stem(x, y);
            printf(PUMPKIN_COLOR_BODY);

         /* top of oval 3/3 */
            printf("/");
            fflush(stdout); usleep(DELAY);
            printf(POSXY, y+4, x+25);
            printf(",");
            fflush(stdout); usleep(DELAY);

         /* top of right side 1/3 */
            for(i = 0; i < 4; i++) {
               printf("_");
               fflush(stdout); usleep(DELAY);
            };

         /* top of right side 2/3 */
            printf(POSXY, y+5, x+30);
            printf("-");
            fflush(stdout); usleep(DELAY);
            printf("-");
            fflush(stdout); usleep(DELAY);
            printf("_");
            fflush(stdout); usleep(DELAY);
            printf(POSXY, y+6, x+33);
            printf("`");
            fflush(stdout); usleep(DELAY);
            printf("\\");
            fflush(stdout); usleep(DELAY);
            printf(POSXY, y+7, x+35);
            printf("`");
            fflush(stdout); usleep(DELAY);

         /* top of right side 3/3 */
            for(i = 0; i < 3; i++) {
               printf(POSXY, y+7+i, x+36+i);
               printf("\\");
               fflush(stdout); usleep(DELAY);
            };

         /* middle of right side */
            printf(POSXY, y+10, x+38);
            printf("\\");
            fflush(stdout); usleep(DELAY);
            printf(POSXY, y+11, x+39);
            printf("\\");
            fflush(stdout); usleep(DELAY);
            printf(POSXY, y+12, x+39);
            printf("\\");
            fflush(stdout); usleep(DELAY);
            printf(POSXY, y+13, x+39);
            printf(")");
            fflush(stdout); usleep(DELAY);
            printf(POSXY, y+14, x+39);
            printf("/");
            fflush(stdout); usleep(DELAY);
            printf(POSXY, y+15, x+38);
            printf("/");
            fflush(stdout); usleep(DELAY);

         /* bottom of right side 1/2 */
            for (i = 0; i < 3; i++) {
               printf(POSXY, y+16+i, x+38-i);
               printf("/");
               fflush(stdout); usleep(DELAY);
            };

         /* bottom of right side 2/2 */
            printf(POSXY, y+18, x+35);
            printf(",");
            fflush(stdout); usleep(DELAY);
            printf(POSXY, y+19, x+34);
            printf("/");
            fflush(stdout); usleep(DELAY);
            printf(POSXY, y+19, x+33);
            printf("_");
            fflush(stdout); usleep(DELAY);
            printf(POSXY, y+19, x+32);
            printf(",");
            fflush(stdout); usleep(DELAY);
            printf(POSXY, y+20, x+31);
            printf("/");
            fflush(stdout); usleep(DELAY);

         /* right side of bottom */
            for(i = 0; i < 5; i++) {
               printf(POSXY, y+20, x+30-i);
               printf("_");
               fflush(stdout); usleep(DELAY);
            };

      /* ends function */
         return(0);
   }


/* prints stem of the pumpkin */
   int animate_stem(int x, int y) {

      /* declares local vars */
         int i;

      /* changes color */
         printf(PUMPKIN_COLOR_STEM);

      /* left side of stem */
         for(i = 0; i < 4; i++) {
            printf(POSXY, y+5-i, x+17+i);
            printf("/");
            fflush(stdout); usleep(DELAY);
         };

      /* top of stem */
         for(i = 0; i < 3; i++) {
            printf(POSXY, y+1, x+21+i);
            printf("_");
            fflush(stdout); usleep(DELAY);
         };

      /* right side of stem */
         printf(POSXY, y+2, x+23);
         printf("/");
         fflush(stdout); usleep(DELAY);
         printf(POSXY, y+3, x+22);
         printf("(");
         fflush(stdout); usleep(DELAY);
         printf(POSXY, y+4, x+22);
         printf("\\");
         fflush(stdout); usleep(DELAY);
         printf(POSXY, y+5, x+23);
         printf("\\");
         fflush(stdout); usleep(DELAY);

      /* ends function */
         return(0);
   };


int main(void) {

   /* declares local vars */
      int x,y;
      int e, n, m;

   /* Sets position */
      x = 3;
      y = 0;

   /* determines which features to use */
      srand((int)time(NULL));
      e = rand() % 3;
      n = rand() % 3;
      m = rand() % 1;

   /* clear screen */
      printf(CLRSCR);
      printf(POSXY, 0, 0);

   /* displays body */
      animate_pumpkin(x, y);

   /* draws eyes */
      if (e == 0) {
         animate_carving1(x+9, y+8);
         animate_carving1(x+27, y+8);
        } else if (e == 1) {
         animate_carving2(x+9, y+8);
         animate_carving2(x+27, y+8);
        } else {
         animate_carving3(x+9, y+8);
         animate_carving3(x+27, y+8);
      };

   /* draws nose */
      if (n == 0) {
         animate_carving1(x+18, y+12);
        } else if (n == 1) {
         animate_carving2(x+18, y+12);
        } else {
         animate_carving3(x+18, y+12);
      };

   /* draws mouth */
      animate_mouth1(x, y);

   /* display credits */
      animate_credits_from_left(x+37, y+7, 5, credits[0]);
      animate_credits_from_left(x+38, y+8, 10, credits[1]);
      animate_credits_from_top(x+42, 1, y+20, credits[2]);
      usleep(DELAY*10);
      animate_credits_from_left(x+42, y+20, strlen(credits[2]), " ");
      animate_credits_type(x+45, y+9, "Happy");
      animate_credits_type(x+50, y+11, "Halloween");

   /* Home cursor */
      printf(COLOR_RESET);
      printf(HOME);
      fflush(stdout);

   /* ends function */
   return(0);
}
