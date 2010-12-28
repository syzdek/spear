#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>

#define DELAY   40000
#define POSXY	"[%i;%iH"
#define CLRSCR	"[2J"
#define HOME	"[23;0H"

int main(void);

int main(void)
{
   int      H = 0;
   int      W = 0;
   int      h = 0;
   int      w = 0;
   int      fd;
   char     bubblex[10];
   char     bubbley[10];
   char     bubbler[10];
   char     buff[30];
   time_t   timer;
   unsigned i;

  struct termios my_tty;
  struct termios tmp_tty;

   /* seeds random number */
   if ((fd = open("/dev/urandom", O_RDONLY)) == -1)
   {
      perror("open()");
      return(1);
   };
   if (read(fd, (void *) &i, sizeof(unsigned int)) == -1)
   {
      perror("read()");
      close(fd);
      return(1);
   };
   close(fd);
   srand(i);

   /* verifies we are using a terminal */
   fd = fileno(stdin);
   if (! isatty(fd))
   {
      fprintf(stderr, "must be run from terminal\n");
      return(1);
   };
   if ( tcgetattr(fd, &my_tty) != 0 )
   {
      fprintf(stderr, "unable to read terminal\n");
      return(1);
   };

   /* clears bubble data */
   for (i = 0; i < 10; i++)
   {
      bubblex[i] = 0;
      bubbley[i] = 0;
      bubbler[i] = 0;
   };

   /* sets up new terminal settings */
   tmp_tty             = my_tty;
   tmp_tty.c_lflag     &= ~ ICANON;
   tmp_tty.c_lflag     &= ~(ECHO|ECHOE|ECHOK|ECHONL);
   tmp_tty.c_cc[VMIN]  = 1;
   tmp_tty.c_cc[VTIME] = 1;

   timer = time(NULL);
   while(200 > (int)(time(NULL) - timer))
   {
      /* determines whether the window has changed size */
      printf(HOME);
      tcsetattr(fd, TCSANOW, &tmp_tty);
      printf("\033[255;255H");
      printf("\033[6n");
      fflush(stdout);usleep(DELAY*4);
      while(getchar() != '\033');
      buff[0] = '\0';
      for(i = 0; buff[i-1] != 'R'; i++)
         buff[i] = getchar();
      tcsetattr(fd, TCSANOW, &my_tty);
      buff[i] = '\0';
      sscanf(buff, "[%d;%dR", &H, &W);
      if ((H != h)||(W != w))
      {
         /* clears screen */
         printf(CLRSCR);
         printf(HOME);
         fflush(stdout);
         /* sets new parameters */
         h = H; w = W;
      };

      /* displays tube */
      for(i = 0; i < h; i++)
      {
         printf(POSXY, h-i, 4);
         printf("|");
         printf(POSXY, h-i, 10);
         printf("|");
      };

      /* displays air bubbles */
      for(i = 0; i < 10; i++)
      {
         if (bubbley[i] == 0)
         {
            if ((rand()%(h/2)) == 0)
            {
               bubblex[i] = rand()%4+5;
               bubbley[i] = h;
            };
         } else {
            printf(POSXY, bubbley[i], bubblex[i]+bubbler[i]);
            printf(" ");
            bubbley[i]--;
            bubbler[i] = rand()%2;
            printf(POSXY, bubbley[i], bubblex[i]+bubbler[i]);
            printf("o");
         };
      };
   };

   return(0);
}

