/* compile with gcc -lcurses -o target target.c */
#include <ncurses.h>
#include <string.h>

/* draws border */
int draw_border(int x, int y)
{
   int i;
   mvaddch(0,   0,   '+');
   mvaddch(y-1, 0 ,  '+');
   mvaddch(0,   x-1, '+');
   mvaddch(y-1, x-1, '+');
   for(i = 1; i < (x-1); i++)
      if (i%2)
      {
         mvaddch(0, i, '-');
         mvaddch(y-1, i, '-');
      } else {
         mvaddch(0, i, '=');
         mvaddch(y-1, i, '=');
      };
   for(i = 1; i < (y-1); i++)
   {
      mvaddch(i, 0, '|');
      mvaddch(i, (x-1), '|');
   };
   move(y-1, (x-18)/2);
   printw("Press 'Q' to exit");
   move(y-1, x-1);
   return(0);
}


/* print coordinates */
int draw_coordinates(int x, int y, int posx, int posy)
{
   int len;
   char buff[512];
   len = snprintf(buff, 511, "(%03i,%03i)", posx, posy);
   move(0, (x-len)/2);
   printw("%s", buff);
   move(y-1, x-1);
   return(0);
}


/* draws target */
int draw_target(int x, int y, int posx, int posy, char vert, char horz, char cen)
{
   /* declares local vars */
   int i;

   /* draws x axis */
   for(i = 1; i < (x-1); i++)
      mvaddch(posy, i, horz);

   /* draws y axis */
   for(i = 1; i < (y-1); i++)
      mvaddch(i, posx, vert);

   /* prints center */
   mvaddch(posy, posx, cen);
   draw_coordinates(x, y, posx, posy);
   move(y-1, x-1);

   /* ends function */
   return(0);
}


/* main statement */
int main()
{
   int ch;
   int x;
   int y;
   int posx;
   int posy;

   initscr();			/* Start curses mode 		*/
   getmaxyx(stdscr,y,x);
   raw();				/* Line buffering disabled	*/
   keypad(stdscr, TRUE);		/* We get F1, F2 etc..		*/
   noecho();			/* Don't echo() while we do getch */

   /* sets initial values */
   posx = (x/2);
   posy = (y/2);

   /* draw border */
   draw_border(x, y);

   /* draws initial target */
   draw_target(x, y, posx, posy, '|', '-', '+');

   /* loops until end */
   ch = 0;
   while ((ch != 'q')&&(ch != 'Q'))
   {
      ch = getch();
      getmaxyx(stdscr,y,x);
      if (posx > (x-1))
         posx = x-1;
      if (posy > (y-1))
         posy = y-1;
      switch(ch)
      {
         case 's':
         case 'j':
         case 0x102:	/* down arrow */
            if ((posy+1) < (y-1))
               posy++;
            break;
         case 'w':
         case 'k':
         case 0x103:	/* up arrow */
            if ((posy-1) > 0)
               posy--;
            break;
         case 'h':
         case 'a':
         case 0x104:	/* left arrow */
            if ((posx-1) > 0)
               posx--;
            break;
         case 'l':
         case 'd':
         case 0x105:	/* right arrow */
            if ((posx+1) < (x-1))
               posx++;
            break;
         default:
            break;
      };
      clear();
      draw_border(x, y);
      draw_target(x, y, posx, posy, '|', '-', '+');
      refresh();
   };

   /* ends curses mode */
   endwin();

   /* ends function */
   return 0;
}

/* end of source file */
