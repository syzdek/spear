
#include <time.h>
#include <stdio.h>

int main(void);

int main(void)
{
   time_t t;

   t = time(NULL);

   printf("%s", ctime(&t));

   return(0);
}
