
#include <time.h>
#include <stdio.h>

int main(void);

int main(void)
{
   time_t t;
   struct tm * ts;

   t = time(NULL);
   ts = localtime(&t);

   printf("%s\n", ts->tm_zone);
   printf("%i\n", ts->tm_gmtoff);

   return(0);
}
