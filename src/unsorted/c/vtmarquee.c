/*
 * xterm scrolling marquee
 */

#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

int main(int, char **);

int main(int argc, char *argv[]) {

   char *buff;
   int i,c,l,p,d;
   pid_t pp;

   if (argc < 2)
      return(0);

   if (argc > 2) {
      d = atol(argv[2]);
     } else {
      d = 0;
   };

   if (argc > 3) {
      pp = atol(argv[3]);
     } else {
      pp = getppid();
   };

   p = fork();
   switch(p) {
      case -1:
         perror("fork(): ");
         return(1);
      case 0:
         break;
      default:
         printf("running as %i\n", p);
         return(0);
   };
      

      l = strlen(argv[1]);
      buff = (char *) malloc(l+10);

      strncpy(buff, argv[1], l);

      for(i = l; i < (l+10); i++)
         buff[i] = ' ';
      l += 10;

   c = 0;
   while (kill(pp, 0) == 0) {
      for (c = 0; c < l+1; c++) {
         for(i = 0; i < l; i++) {
            if (i == c) {
               fprintf(stdout, "\a");
               fflush(stdout);
               if (c == 0)
                  sleep(d);
               fprintf(stdout, "]2;");
            };
            fprintf(stdout, "%c", buff[i]);
         };
         usleep(80000);
         //sleep(1);
      };
   };
   printf("\a]2; \a");
   fflush(stdout);

   return(0);

}
