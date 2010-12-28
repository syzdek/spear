#include <stdio.h>
#include <pwd.h>
#include <unistd.h>

int main(void);

int main(void)
{
   char * pass;
   pass = (char *) getpass("Enter test message: ");
   printf("You entered: %s\n", pass);
   return(0);
}
