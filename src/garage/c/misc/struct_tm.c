
#include <stdio.h>
#include <time.h>

int main(void);

int main(void)
{
   time_t t;
   struct tm * tm;

   t = time(NULL);
   tm = localtime(&t);

   printf("%s",                  ctime(&t));
   printf("tm->tm_sec:    %i\n", tm->tm_sec);
   printf("tm->tm_min:    %i\n", tm->tm_min);
   printf("tm->tm_hour:   %i\n", tm->tm_hour);
   printf("tm->tm_mday:   %i\n", tm->tm_mday);
   printf("tm->tm_mon:    %i\n", tm->tm_mon);
   printf("tm->tm_year:   %i\n", tm->tm_year);
   printf("tm->tm_wday:   %i\n", tm->tm_wday);
   printf("tm->tm_yday:   %i\n", tm->tm_yday);
   printf("tm->tm_isdst:  %i\n", tm->tm_isdst);
   printf("tm->tm_zone:   %s\n", tm->tm_zone);
   printf("tm->tm_gmtoff: %i\n", tm->tm_gmtoff);

   return(0);
}
