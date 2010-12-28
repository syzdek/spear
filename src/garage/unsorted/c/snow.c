

#define SNOW_FLAKE_COUNT	150
#define DELAY   60000

#define BACKGROUND "[30m"
#define POSXY   "[%i;%iH"
#define CLRSCR  "[2J"
#define HOME    "[23;0H"

#define posxy(x, y) printf(POSXY, y, x);
#define clrscr() printf(CLRSCR);

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <termios.h>

typedef struct ascii_patterns
{
    int x;
    int y;
    char *str;
} ASCIIPattern;

ASCIIPattern snowman[] =
{
   { 8, 10, "[37m_"},
   { 9, 10, "[37m-"},
   {10, 10, "[37m-"},
   {11, 10, "[37m_"},
   {12, 10, "[37m_"},
   {13, 10, "[37m_"},
   {14, 10, "[37m-"},
   {15, 10, "[37m_"},
   {16, 10, "[37m/"},
   {17,  9, "[37m|"},
   {17,  8, "[37m|"},
   {16,  7, "[37m\\"},
   {15,  6, "[37m/"},
   {16,  5, "[37m|"},
   {15,  4, "[37m\\"},
   {16,  3, "[1;33m_"},
   {15,  3, "[1;33m_"},
   {14,  3, "[1;33m|"},
   {14,  2, "[1;33m|"},
   {14,  1, "[1;33m_"},
   {13,  1, "[1;33m_"},
   {12,  1, "[1;33m_"},
   {11,  1, "[1;33m_"},
   {10,  1, "[1;33m_"},
   { 9,  1, "[1;33m_"},
   { 9,  2, "[1;33m|"},
   { 9,  3, "[1;33m|"},
   { 8,  3, "[1;33m_"},
   { 7,  3, "[1;33m_"},
   { 8,  4, "[0;37m/"},
   { 7,  5, "[0;37m|"},
   { 8,  6, "[0;37m\\"},
   { 7,  7, "[0;37m/"},
   { 6,  8, "[0;37m|"},
   { 6,  9, "[0;37m|"},
   { 7, 10, "[0;37m\\"},
   { 6, 11, "[0;37m/"},
   { 5, 12, "[0;37m|"},
   { 5, 13, "[0;37m|"},
   { 6, 14, "[0;37m\\"},
   { 7, 14, "[0;37m_"},
   { 8, 14, "[0;37m_"},
   { 9, 14, "[0;37m_"},
   {10, 14, "[0;37m_"},
   {11, 14, "[0;37m_"},
   {12, 14, "[0;37m_"},
   {13, 14, "[0;37m_"},
   {14, 14, "[0;37m_"},
   {15, 14, "[0;37m_"},
   {16, 14, "[0;37m_"},
   {17, 14, "[0;37m/"},
   {18, 13, "[0;37m|"},
   {18, 12, "[0;37m|"},
   {17, 11, "[0;37m\\"},
   {11,  5, "[0;33m="},
   {10,  5, "[0;33m-"},
   {10,  6, "[0;31m\\"},
   {11,  6, "[0;31m_"},
   {12,  6, "[0;31m_"},
   {13,  6, "[0;31m/"},
   {13,  4, "[0;34mo"},
   {13,  3, "[1;33m="},
   {12,  3, "[1;33m="},
   {11,  3, "[1;33m="},
   {10,  3, "[1;33m="},
   {10,  4, "[0;34mo"},
   {13,  2, "[0;33m%%"},
   {11,  7, "[0;33m%%"},
   {11,  8, "[0;33m%%"},
   {11,  9, "[0;33m%%"},
   { 3, 11, "[0;34m|"},
   { 2, 11, "[0;34m/"},
   { 3, 10, "[0;34m/"},
   { 4,  9, "[0;34m_"},
   { 5,  9, "[0;34m/"},
   {18,  8, "[0;34m/"},
   {19,  7, "[0;34m/"},
   {20,  6, "[0;34m|"},
   {21,  6, "[0;34m_"},
   {22,  6, "[0;34m/"},
   {23,  5, "[0;34m/"},
   {20,  5, "[0;34m|"},
   {10,  2, "   "},
   { 9,  4, " "},
   {11,  4, "  "},
   {14,  4, " "},
   { 8,  5, "  "},
   {12,  5, "    "},
   { 9,  6, " "},
   {14,  6, " "},
   { 8,  7, "   [0;33m%%    "},
   { 7,  8, "    [0;33m%%     "},
   { 7,  9, "    [0;33m%%     "},
   { 7, 11, "          "},
   { 6, 12, "            "},
   { 6, 13, "            "},
   { 0,  0, NULL}
};

int main(void);

int main(void)
{
   /* declares local vars */
   int fd;
   unsigned u;
   int i;
   int offset;
   int snow[SNOW_FLAKE_COUNT][2];

   /* seeds random number */
   if ((fd = open("/dev/urandom", O_RDONLY)) < 0)
   {
      perror("open()");
      return(1);
   };
   if (read(fd, (void *) &u, sizeof(unsigned)) < 0)
   {
      perror("read()");
      close(fd);
      return(1);
   };
   close(fd);
   srand(u);

   /* verifies we are using a terminal */
   fd = fileno(stdin);
   if (! isatty(fd))
   {
      fprintf(stderr, "must be run from terminal\n");
      return(1);
   };

   /* clear screen */
   clrscr();fflush(stdout);

   /* generates snow placement */
   for(u = 0; u < SNOW_FLAKE_COUNT; u++)
   {
      snow[u][0] = (rand()%79)+1;
      snow[u][1] = (rand()%19)+1;
   };
   printf("[37m");
   for(i = 0; i < 20; i++)
   {
      clrscr();
      for(u = 0; u < SNOW_FLAKE_COUNT-1; u++)
      {
         if (snow[u][1] > (19-i))
         {
            posxy(snow[u][0], snow[u][1]-19+i);
            //posxy(snow[u][0]+((rand())&0x01), snow[u][1]-19+i);
            printf("*");
         };
      };
      posxy(0, 20);
      fflush(stdout);usleep(DELAY*3);
   };
   posxy(0, 20);
   fflush(stdout);

   /* draw snowman */
   offset = rand()%57;
   for(i = 0; snowman[i].str; i++)
   {
      posxy(snowman[i].x+offset, snowman[i].y+5);
      printf(snowman[i].str);
      fflush(stdout);usleep(DELAY);
   };

   /* resets color */
   printf("[0m");
   posxy(0, 20);
   fflush(stdout);
   
   /* ends function */
   return(0);
}
