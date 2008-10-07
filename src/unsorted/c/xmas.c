#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>

#define DELAY   40000
//#define DELAY   100000
#define POSXY	"[%i;%iH"
#define CLRSCR	"[2J"
#define HOME	"[23;0H"

int main(void);

int main(void) {

   /* declares local vars */
      unsigned int c;
      unsigned int i;
      int fd;
      time_t timer;

      struct termios my_tty;
      struct termios tmp_tty;

      char buff[30];

      char *slogan;

      int x[9];
      int y[9];

      int h = 0;
      int w = 0;

      int max = 0;
      int lim = 0;

   /* seeds random number */
      fd = open("/dev/urandom", O_RDONLY);
      if (fd < 0) {
         perror("open()");
         return(1);
      };
      if (read(fd, (void *) &i, sizeof(unsigned int)) < 0) {
         close(fd);
         perror("open()");
         return(-1);
      };
      close(fd);
      srand(i);

   /* verifies we are using a terminal */
      fd = fileno(stdin);
      if (! isatty(fd)) {
         fprintf(stderr, "must be run from terminal\n");
         return(1);
      };
      if ( tcgetattr(fd, &my_tty) != 0 ) {
         fprintf(stderr, "unable to read terminal\n");
         return(1);
      };

   /* sets up new terminal settings */
      tmp_tty = my_tty;
      tmp_tty.c_lflag &= ~ ICANON;
      tmp_tty.c_lflag &= ~(ECHO|ECHOE|ECHOK|ECHONL);
      tmp_tty.c_cc[VMIN] = 1;
      tmp_tty.c_cc[VTIME] = 1;

   /* determines window size */
      printf(HOME);
      tcsetattr(fd, TCSANOW, &tmp_tty);
      printf("\033[255;255H");
      printf("\033[6n");
      fflush(stdout);usleep(DELAY*4);
      while(getchar() != '\033');
      buff[0] = '\0';
      for(i = 0; buff[i-1] != 'R'; i++) {
         buff[i] = getchar();
      };
      tcsetattr(fd, TCSANOW, &my_tty);
      buff[i] = '\0';
      sscanf(buff, "[%d;%dR", &h, &w);

   /* determines X, y of center */
      if (h > (w*2)) {
         max = w;
        } else {
         max = h;
      };
      max -= 4;

   /* clears screen */
      printf(CLRSCR);fflush(stdout);

   /* draws star */
      printf("[1;33m");fflush(stdout);
      printf(POSXY, 1, (w/2));
      printf("/\\");
      fflush(stdout);usleep(DELAY);
      printf(POSXY, 2, (w/2));
      printf("<>");
      fflush(stdout);usleep(DELAY);
      printf(POSXY, 2, (w/2)-3);
      printf("-<");
      fflush(stdout);usleep(DELAY);
      printf(POSXY, 2, (w/2)+3);
      printf(">-");
      fflush(stdout);usleep(DELAY);
      printf(POSXY, 3, (w/2));
      printf("\\/");
      fflush(stdout);usleep(DELAY);

   /* draws ornaments */
      for(i = 3; i < (max-2)*2; i++) {
         switch (rand()%6) {
            case 0:
               printf("[1;31m");
               break;
            case 1:
               printf("[1;32m");
               break;
            case 2:
               printf("[1;33m");
               break;
            case 3:
               printf("[1;34m");
               break;
            case 4:
               printf("[1;35m");
               break;
            case 5:
               printf("[1;36m");
               break;
         };
         if (i%2) {
            printf(POSXY, (i/2)+3, ((w/2)+(rand()%(i/2))));
           } else {
            printf(POSXY, (i/2)+3, ((w/2)-(i/2)+(rand()%(i/2))));
         };
         printf("o");
         fflush(stdout);usleep(DELAY);
      };

   /* Draws tree */
      /* sets color for tree */
         printf("[32m");fflush(stdout);

      /* draws bottom line */
         lim = (w - (max*2))/2;
         for(i = 1; i < (max*2); i++) {
            printf(POSXY, 1+max, (w/2)-max+i);
            printf("_");
            fflush(stdout);usleep(DELAY);
         };

      /* draws left line */
         for(i = 0; i < max-1; i++) {
            printf(POSXY, 1+max-i, (w/2)+max-i);
            printf("\\");
            fflush(stdout);usleep(DELAY);
         };

      /* draws right line */
         for(i = 1; i < max; i++) {
            printf(POSXY, 2+i, (w/2)-i);
            printf("/");
            fflush(stdout);usleep(DELAY);
         };

   /* sets color for snow */
      printf("[37m");fflush(stdout);
      printf(POSXY, h-1, 0);
      for(i = 0; i < w; i++) {
         printf("^");
         fflush(stdout);usleep(DELAY);
      };

   /* draws stump */
      printf("[32m");
      printf(POSXY, max+2, (w/2)-2);
      printf("|");
      fflush(stdout);usleep(DELAY);
      printf(POSXY, max+3, (w/2)-2);
      printf("|");
      fflush(stdout);usleep(DELAY);
      printf(POSXY, max+3, (w/2)+2);
      printf("|");
      fflush(stdout);usleep(DELAY);
      printf(POSXY, max+2, (w/2)+2);
      printf("|");
      fflush(stdout);usleep(DELAY);
      

   /* Merry Christmas */
      slogan = strdup(" Merry Christmas 2004 from Syzler ");
      printf("[37m");
      printf(POSXY, max+3, 2);
      for(i = 0; i < strlen(slogan); i++) {
         printf("%c", slogan[i]);
         fflush(stdout);usleep(DELAY);
      };
      free(slogan);

   /* resets color */
      printf(POSXY, h, 0);
      printf("[0m");fflush(stdout);

   /* ends function */
      return(0);
}

