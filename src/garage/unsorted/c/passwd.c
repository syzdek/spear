#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>

int main(int, char**);

int main(int argc, char *argv[])
{
   char * ptr;
   char * pass1;
   char * pass2;
   int i;
   pass1 = NULL;
   pass2 = NULL;
   if (argc < 2)
   {
   };
   printf("%s:  Changing password for %s\n", argv[0], argv[0]);
   for(i = 0; i < 3; i++)
   {
      free(pass1);
      free(pass2);
      ptr = getpass("New password: ");
      pass1 = strdup(ptr);
      ptr = getpass("Re-enter new password: ");
      pass2 = strdup(ptr);
      if (! strcmp(pass1, pass2))
      {
         i = 3;
        } else {
         printf("passwd(SYSTEM): They don't match; try again.\n");
      };
   };
   if (strcmp(pass1, pass2))
   {
      printf("passwd(SYSTEM): Too many tries; try again later\n");
      printf("Permission denied\n");
      return(1);
   };
   printf("passwd (SYSTEM): passwd successfully changed for syzdek\n");
   return(0);
}
