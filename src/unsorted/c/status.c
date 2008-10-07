#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

int main(int, char **);

int main(int argc, char *argv[]) {

   char *buff;
   int i,c,l,p;

   if (argc < 2)
      return(0);

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
      

   c = 0;
   while (c < 1000) {
      l = strlen(argv[1]);
      buff = (char *) malloc(l+10);

      strncpy(buff, argv[1], l);

      for(i = l; i < (l+10); i++)
         buff[i] = ' ';
      l += 10;

      for (c = 0; c < l+1; c ++) {
         for(i = 0; i < l; i++) {
            if (i == c) {
               fprintf(stdout, "\a");
               fflush(stdout);
               fprintf(stdout, "]2;");
            };
            fprintf(stdout, "%c", buff[i]);
         };
         usleep(80000);
         //sleep(1);
      };
   };
   printf("\a");
   fflush(stdout);

   return(0);

}
