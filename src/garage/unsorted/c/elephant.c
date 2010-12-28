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
 *    gcc -O2 -o elephant elephant.c 
 */
#define _ANIMATED_ASCII_ELEPHANT_C
#include "elephant.h"

///////////////
//           //
//  Credits  //
//           //
///////////////

/* Misc Pictures */
const char *credits[] = { 
   "Animated by",
   "Syzmations",
   "Copyright (c) 2005 David Syzdek"
};

/////////////////
//             //
//  Functions  //
//             //
/////////////////

/* animates credits */
int animate_credits_from_left(int x, int y, int l, const char *str) {

   /* declares local vars */
   int s;
   int i;

   /* changes color */
   printf(COLOR_CREDITS);

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
   printf(COLOR_CREDITS);

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
   printf(COLOR_CREDITS);

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

int elephant(int x, int y)
{
   /* declares local vars */
   int i;
   const char *str;

   /* changes color */
   printf(COLOR_ELEPHANT);

   /* draw trunk */
   for(i = 0; i < 3; i++)
   {
      printf(POSXY, y+8+i, x+8-i);
      printf("/");
      fflush(stdout); usleep(DELAY);
   };
   printf(POSXY, y+10, x+5);
   printf("_");
   fflush(stdout); usleep(DELAY);
   printf(POSXY, y+10, x+4);
   printf("\\");
   fflush(stdout); usleep(DELAY);
   printf(POSXY, y+9, x+3);
   printf("\\");
   fflush(stdout); usleep(DELAY);
   printf(POSXY, y+8, x+2);
   printf("_");
   fflush(stdout); usleep(DELAY);
   printf(POSXY, y+9, x+1);
   printf("(");
   fflush(stdout); usleep(DELAY);
   printf("\"");
   fflush(stdout); usleep(DELAY);
   printf(POSXY, y+10, x+3);
   printf("'");
   fflush(stdout); usleep(DELAY);
   printf(POSXY, y+10, x+2);
   printf("\\");
   fflush(stdout); usleep(DELAY);
   printf(POSXY, y+10, x+1);
   printf("`");
   fflush(stdout); usleep(DELAY);
   printf(POSXY, y+11, x+3);
   printf("`");
   fflush(stdout); usleep(DELAY);
   printf(".");
   fflush(stdout); usleep(DELAY);
   printf("_");
   fflush(stdout); usleep(DELAY);
   printf(".");
   fflush(stdout); usleep(DELAY);
   printf("'");
   fflush(stdout); usleep(DELAY);
   printf(POSXY, y+10, x+7);
   printf("`");
   fflush(stdout); usleep(DELAY);
   printf("/");
   fflush(stdout); usleep(DELAY);
   printf(POSXY, y+9, x+8);
   printf("`");
   fflush(stdout); usleep(DELAY);
   printf("/");
   fflush(stdout); usleep(DELAY);
   printf(POSXY, y+8, x+9);
   printf(":");
   fflush(stdout); usleep(DELAY);
   printf("-");
   fflush(stdout); usleep(DELAY);
   printf("-");
   fflush(stdout); usleep(DELAY);
   printf("`");
   fflush(stdout); usleep(DELAY);
   printf(POSXY, y+7, x+5);
   printf("`");
   fflush(stdout); usleep(DELAY);
   printf("-");
   fflush(stdout); usleep(DELAY);
   printf(".");
   fflush(stdout); usleep(DELAY);
   printf(" ");
   fflush(stdout); usleep(DELAY);
   printf("`");
   fflush(stdout); usleep(DELAY);
   printf("-");
   fflush(stdout); usleep(DELAY);
   printf("-");
   fflush(stdout); usleep(DELAY);
   printf("'");
   fflush(stdout); usleep(DELAY);
   printf("_");
   fflush(stdout); usleep(DELAY);
   printf(".");
   fflush(stdout); usleep(DELAY);
   printf("'");
   fflush(stdout); usleep(DELAY);
   printf(POSXY, y+6, x+15);
   printf(".");
   fflush(stdout); usleep(DELAY);
   printf(POSXY, y+6, x+14);
   printf("-");
   fflush(stdout); usleep(DELAY);
   printf(POSXY, y+6, x+13);
   printf(".");
   fflush(stdout); usleep(DELAY);
   printf(POSXY, y+7, x+16);
   printf("-");
   fflush(stdout); usleep(DELAY);
   printf(".");
   fflush(stdout); usleep(DELAY);
   str = ";||.";
   for (i = 0; i < 4; i++)
   {
      printf(POSXY, y+7+i, x+18);
      printf("%c", str[i]);
      fflush(stdout); usleep(DELAY);
   };
   str = "\\\\\\Y";
   for (i = 0; i < 4; i++)
   {
      printf(POSXY, y+10+i, x+19+i);
      printf("%c", str[i]);
      fflush(stdout); usleep(DELAY);
   };
   printf(POSXY, y+14, x+22);
   printf("|");
   fflush(stdout); usleep(DELAY);
   str = "/___|";
   printf(POSXY, y+15, x+21);
   for (i = 0; i < 5; i++)
   {
      printf("%c", str[i]);
      fflush(stdout); usleep(DELAY);
   };
   str = "||||/";
   for (i = 0; i < 5; i++)
   {
      printf(POSXY, y+14-i, x+25);
      printf("%c", str[i]);
      fflush(stdout); usleep(DELAY);
   };
   str = "`~`=-.:";
   for (i = 0; i < 7; i++)
   {
      printf("%c", str[i]);
      fflush(stdout); usleep(DELAY);
   };
   str = "../'/";
   for (i = 0; i < 5; i++)
   {
      printf(POSXY, y+6+i, x+29-i);
      printf("%c", str[i]);
      fflush(stdout); usleep(DELAY);
   };
   for (i = 0; i < 3; i++)
      usleep(DELAY);
   str = "//|";
   for (i = 0; i < 3; i++)
   {
      printf(POSXY, y+12+i, x+20-i);
      printf("%c", str[i]);
      fflush(stdout); usleep(DELAY);
   };
   str = "\"___\"";
   for (i = 0; i < 5; i++)
   {
      printf(POSXY, y+15, x+18-i);
      printf("%c", str[i]);
      fflush(stdout); usleep(DELAY);
   };
   str = "/J//";
   for (i = 0; i < 4; i++)
   {
      printf(POSXY, y+14-i, x+15+i);
      printf("%c", str[i]);
      fflush(stdout); usleep(DELAY);
   };
   printf("`");
   fflush(stdout); usleep(DELAY);
   printf(POSXY, y+7, x+35);
   printf(".");
   fflush(stdout); usleep(DELAY);
   usleep(DELAY);
   printf(POSXY, y+8, x+33);
   printf("/");
   fflush(stdout); usleep(DELAY);
   printf(POSXY, y+9, x+32);
   printf("'");
   printf(POSXY, y+10, x+32);
   fflush(stdout); usleep(DELAY);
   printf(POSXY, y+11, x+32);
   printf("`");
   fflush(stdout); usleep(DELAY);
   printf("\\");
   fflush(stdout); usleep(DELAY);
   printf(POSXY, y+12, x+34);
   printf("`");
   fflush(stdout); usleep(DELAY);
   str = "Y||";
   for (i = 0; i < 3; i++)
   {
      printf(POSXY, y+12+i, x+35);
      printf("%c", str[i]);
      fflush(stdout); usleep(DELAY);
   };
   str = "/___|";
   printf(POSXY, y+15, x+34);
   for (i = 0; i < 5; i++)
   {
      printf("%c", str[i]);
      fflush(stdout); usleep(DELAY);
   };
   printf(POSXY, y+14, x+38);
   printf("|");
   fflush(stdout); usleep(DELAY);
   str = "/////'";
   for (i = 0; i < 6; i++)
   {
      if (i == 5)
      {
         printf(POSXY, y+8, x+42);
         printf(".");
         fflush(stdout); usleep(DELAY);
      };
      printf(POSXY, y+13-i, x+38+i);
      printf("%c", str[i]);
      fflush(stdout); usleep(DELAY);
   };
   printf(POSXY, y+7, x+43);
   printf("|");
   fflush(stdout); usleep(DELAY);
   printf(POSXY, y+6, x+42);
   printf("`");
   fflush(stdout); usleep(DELAY);
   printf(";");
   fflush(stdout); usleep(DELAY);
   str = "\\\\\\:";
   for (i=0; i < 4; i++)
   {
      printf(POSXY, y+6+i, x+44+i);
      printf("%c", str[i]);
      fflush(stdout); usleep(DELAY);
   };
   printf(POSXY, y+10, x+47);
   printf("`");
   fflush(stdout); usleep(DELAY);
   printf("`");
   fflush(stdout); usleep(DELAY);
   printf(POSXY, y+9, x+49);
   printf(";");
   fflush(stdout); usleep(DELAY);
   str = "`\\\\\\\\\\";
   for (i=0; i < 6; i++)
   {
      printf(POSXY, y+9-i, x+48-i);
      printf("%c", str[i]);
      fflush(stdout); usleep(DELAY);
   };
   printf(POSXY, y+4, x+42);
   printf("`");
   fflush(stdout); usleep(DELAY);
   printf(POSXY, y+3, x+41);
   printf("\\");
   fflush(stdout); usleep(DELAY);
   printf(POSXY, y+3, x+40);
   printf("`");
   fflush(stdout); usleep(DELAY);
   str = ".-``";
   for (i=0; i < 4; i++)
   {
      printf(POSXY, y+2, x+39-i);
      printf("%c", str[i]);
      fflush(stdout); usleep(DELAY);
   };
   str = "__....__";
   for (i=0; i < 8; i++)
   {
      printf(POSXY, y+1, x+35-i);
      printf("%c", str[i]);
      fflush(stdout); usleep(DELAY);
   };
   str = "~\"~";
   for (i=0; i < 3; i++)
   {
      printf(POSXY, y+2, x+27-i);
      printf("%c", str[i]);
      fflush(stdout); usleep(DELAY);
   };
   str = "_.-~\"~-.___";
   for (i=0; i < 11; i++)
   {
      printf(POSXY, y+1, x+24-i);
      printf("%c", str[i]);
      fflush(stdout); usleep(DELAY);
   };
   printf(POSXY, y+2, x+13);
   printf("'");
   fflush(stdout); usleep(DELAY);
   str = ".//:";
   for (i=0; i < 4; i++)
   {
      printf(POSXY, y+2+i, x+12-i);
      printf("%c", str[i]);
      fflush(stdout); usleep(DELAY);
   };
   str = "`|_.-`<";
   for (i=0; i < 7; i++)
   {
      printf(POSXY, y+6, x+10-i);
      printf("%c", str[i]);
      fflush(stdout); usleep(DELAY);
   };
   str = "(\\\\|";
   for (i=0; i < 4; i++)
   {
      printf(POSXY, y+11+i, x+41+i);
      printf("%c", str[i]);
      fflush(stdout); usleep(DELAY);
   };
   str = "|__/";
   for (i=0; i < 4; i++)
   {
      printf(POSXY, y+15, x+44-i);
      printf("%c", str[i]);
      fflush(stdout); usleep(DELAY);
   };
   printf(POSXY, y+14, x+41);
   printf("|");
   fflush(stdout); usleep(DELAY);
   printf(POSXY, y+13, x+40);
   printf("\\");
   fflush(stdout); usleep(DELAY);
   printf(POSXY, y+13, x+39);
   printf("`");
   fflush(stdout); usleep(DELAY);
   printf(POSXY, y+2, x+18);
   printf("`");
   fflush(stdout); usleep(DELAY);
   printf(POSXY, y+3, x+12);
   printf("`");
   fflush(stdout); usleep(DELAY);
   printf(POSXY, y+4, x+11);
   printf("`");
   fflush(stdout); usleep(DELAY);
   printf(POSXY, y+5, x+10);
   printf("`");
   fflush(stdout); usleep(DELAY);
   printf(POSXY, y+3, x+14);
   printf("_");
   fflush(stdout); usleep(DELAY);
   printf(POSXY, y+4, x+14);
   printf("a");
   fflush(stdout); usleep(DELAY);
   printf(")");
   fflush(stdout); usleep(DELAY);
   printf(POSXY, y+2, x+23);
   printf("\\");
   fflush(stdout); usleep(DELAY);
   printf(POSXY, y+3, x+24);
   printf("`");
   fflush(stdout); usleep(DELAY);
   printf("\\");
   fflush(stdout); usleep(DELAY);
   printf(POSXY, y+4, x+26);
   printf("|");
   fflush(stdout); usleep(DELAY);
   printf(POSXY, y+5, x+26);
   printf("|");
   fflush(stdout); usleep(DELAY);
   printf(POSXY, y+6, x+25);
   printf("/");
   fflush(stdout); usleep(DELAY);
   str = "'/___\\";
   for(i = 0; i < 6; i++)
   {
      printf(POSXY, y+7, x+24-i);
      printf("%c", str[i]);
      fflush(stdout); usleep(DELAY);
   };
   str = "(//)";
   for(i = 0; i < 4; i++)
   {
      printf(POSXY, y+6-i, x+18+i);
      printf("%c", str[i]);
      fflush(stdout); usleep(DELAY);
   };
   str = "'\"\"\"";
   for(i = 0; i < 4; i++)
   {
      printf(POSXY, y+16, x+21+i);
      printf("%c", str[i]);
      fflush(stdout); usleep(DELAY);
   };
   str = "'\"\"\"";
   for(i = 0; i < 4; i++)
   {
      printf(POSXY, y+16, x+34+i);
      printf("%c", str[i]);
      fflush(stdout); usleep(DELAY);
   };
   str = "'\"\"\"";
   for(i = 0; i < 4; i++)
   {
      printf(POSXY, y+16, x+40+i);
      printf("%c", str[i]);
      fflush(stdout); usleep(DELAY);
   };

   /* reset color */
   printf(COLOR_RESET);

   /* end function */
   return(0);
}

int flag(int x, int y)
{
   /* declares local vars */
   int i;
   const char *str1;
   const char *str2;

   /* reset color */
   printf(COLOR_RESET);

   /* draws pole */
   for(i = 0; i < (18-y); i++)
   {
      printf(POSXY, 19-i, x);
      printf("||");
      fflush(stdout); usleep(DELAY);
   };

   /* changes color */
   printf(COLOR_FLAG);

   /* draws flag */
   for (i = 0; i < 5; i++) 
   {
      printf(POSXY, y+2+i, x+2);
      printf("|");
   };
   for (i = 0; i < 3; i++)
   {
      printf(POSXY, y+1, x+3+i);
      printf("_");
      printf(POSXY, y+6, x+3+i);
      printf("_");
      fflush(stdout); usleep(DELAY);
   };
   str1 = "\"\"~~--..";
   str2 = "..--~~\"\"";
   for(i = 0; i < 8; i++)
   {
      printf(POSXY, y+2, x+6+i);
      printf("%c", str1[i]);
      printf(POSXY, y+6, x+6+i);
      printf("%c", str2[i]);
      fflush(stdout); usleep(DELAY);
   };
   for(i = 0; i < 2; i++)
   {
      printf(POSXY, y+2, x+14+i);
      printf("_");
      printf(POSXY, y+5, x+14+i);
      printf("_");
      fflush(stdout); usleep(DELAY);
   };
   str1 = "\"\"~~--..";
   str2 = "..--~~\"\"";
   for(i = 0; i < 8; i++)
   {
      printf(POSXY, y+3, x+16+i);
      printf("%c", str1[i]);
      printf(POSXY, y+5, x+16+i);
      printf("%c", str2[i]);
      fflush(stdout); usleep(DELAY);
   };
   for(i = 0; i < 2; i++)
   {
      printf(POSXY, y+3, x+24+i);
      printf("_");
      printf(POSXY, y+4, x+24+i);
      printf("_");
      fflush(stdout); usleep(DELAY);
   };
   printf(POSXY, y+4, x+26);
   printf("\"");
   fflush(stdout); usleep(DELAY);

   /* end function */
   return(0);
}


int main(void)
{
   /* declare local vars */
   int x,y;

   /* Sets position */
   x = 3;
   y = 0;

   /* seeds random */
   srand((int)time(NULL));

   /* clear screen and home cursor */
   printf(CLRSCR);
   printf(POSXY, 0, 0);

   elephant(25,3);
   flag(2,2);

   /* display credits */
   animate_credits_type(8, 6, "Circus Fun!!!");
//   animate_credits_from_left(x+37, y+7, 5, credits[0]);
//   animate_credits_from_left(x+38, y+8, 10, credits[1]);
//   animate_credits_from_top(x+42, 1, y+19, credits[2]);
//   usleep(DELAY*10);
//   animate_credits_from_left(x+42, y+19, strlen(credits[2]), " ");
//   animate_credits_type(x+45, y+9, "Happy");
//   animate_credits_type(x+50, y+11, "Halloween");
//
   /* Home cursor */
   printf(COLOR_RESET);
   printf(HOME);
   fflush(stdout);

   /* ends function */
   return(0);
}
