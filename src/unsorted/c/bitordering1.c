#include <stdio.h>

int main(void);

int main(void)
{
   unsigned num;
   unsigned i;
   void *ptr;
   num = 0;
   for(i = 0; i < sizeof(int); i++)
      num = (num << 8) | ('a' +i);
   ptr = (void *) &num;
   printf("%u\n", num);
   for(i = 0; i < sizeof(int); i++)
      printf("%c", ((char *)ptr)[i]);
   printf("\n");
   return(0);
}
