#include <stdio.h>

int main(void);

int main(void)
{
   unsigned num = 'a';
   void *ptr = &num;
   if (((char *)ptr)[0])
      printf("Little Endian\n");
   if (! ((char *)ptr)[0])
      printf("Big Endian\n");
   return(0);
}
