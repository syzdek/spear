
#include <unistd.h>
#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]);

const char *board[] = {
   "                                                       ",
   "                      ASCII PACMAN                     ",
   "         1UP          HIGH   SCORE                     ",
   "           00                 00                       ",
   "+-------------------------+-+-------------------------+",
   "| . . . . . . . . . . . . | | . . . . . . . . . . . . |",
   "| . +-----+ . +-------+ . | | . +-------+ . +-----+ . |",
   "| * |     | . |       | . | | . |       | . |     | * |",
   "| . +-----+ . +-------+ . +-+ . +-------+ . +-----+ . |",
   "| . . . . . . . . . . . . . . . . . . . . . . . . . . |",
   "| . +-----+ . +-+ . +-------------+ . +-+ . +-----+ . |",
   "| . +-----+ . | | . +-----+ +-----+ . | | . +-----+ . |",
   "| . . . . . . | | . . . . | | . . . . | | . . . . . . |",
   "+---------+ . | +-----+   | |   +-----+ | . +---------+",
   "          | . | +-----+   +-+   +-----+ | . |          ",
   "          | . | |          &          | | . |          ",
   "          | . | |   +-----###-----+   | | . |          ",
   "+---------+ . +-+   |             |   +-+ . +---------+",
   "X           .       |    & & &    |       .           X",
   "+---------+ . +-+   |             |   +-+ . +---------+",
   "          | . | |   +-------------+   | | . |          ",
   "          | . | |          C          | | . |          ",
   "          | . | |   +-------------+   | | . |          ",
   "+---------+ . +-+   +-----+ +-----+   +-+ . +---------+",
   "| . . . . . . . . . . . . | | . . . . . . . . . . . . |",
   "| . +-----+ . +-------+ . | | . +-------+ . +-----+ . |",
   "| . +---+ | . +-------+ . +-+ . +-------+ . | +---+ . |",
   "| * . . | | . . . . . . . . . . . . . . . . | | . . * |",
   "+---+ . | | . +-+ . +-------------+ . +-+ . | | . +---+",
   "+---+ . +-+ . | | . +-----+ +-----+ . | | . +-+ . +---+",
   "| . . . . . . | | . . . . | | . . . . | | . . . . . . |",
   "| . +---------+ +-----+ . | | . +-----+ +---------+ . |",
   "| . +-----------------+ . +-+ . +-----------------+ . |",
   "| . . . . . . . . . . . . . . . . . . . . . . . . . . |",
   "+-----------------------------------------------------+",
   "  (<  (<  (<  (<                          @ % % % % %  ",
   NULL
};

const char *intro = "Coming soon to a server near you...";
const char *release = "Server wide in early March";
const char *banner = "From the Asciimation Studios of David Syzdek.";
const char *exitmsg = "Press any key to exit.";

int main(int argc, char *argv[])
{
   int i;
   int j;
   int h;
   int w;
   int x;
   int y;
   int z;

   initscr();
   getmaxyx(stdscr, y, x);

   w = 0;
   for(i = 0; board[i]; i++)
      if (strlen(board[i]) > w)
         w = strlen(board[i]);
   h = i;

   if ((x < (w+4)) || (y < (h+5)))
   {
      clear();
      move(0,0);
      refresh();
      endwin();
      printf("Screen must be at least %i columns by %i rows in size.\n", x+4, y+2);
      return(1);
   };

   z = strlen(intro);
   for(i = 0; intro[i]; i++)
   {
      mvaddch(y/2, ((x-z)/2)+i, intro[i]);
      move(y-1, x-1);
      refresh();
      usleep(50000);
   };
   sleep(2);

   clear();
   for(i = 0; i < h; i++)
   {
      clear();
      for(j = 0; j <= i; j++)
      {
         move(i-j, (x-w)/2);
         printw("%s", board[h-1-j]);
      };
      move(y-1, x-1);
      refresh();
      usleep(50000);
   };
   refresh();

   w = strlen(banner);
   for(i = 0; banner[i]; i++)
   {
      mvaddch(h+2, ((x-w)/2)+i, banner[i]);
      move(y-1, x-1);
      refresh();
      usleep(50000);
   };
   w = strlen(exitmsg);
   move(h+4, (x-w)/2);
   printw("%s", exitmsg);
   move(y-1, x-1);
   refresh();


   getch();

   clear();
   refresh();
   endwin();
   printf("%s\n", release);
   return(0);
}


