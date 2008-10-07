#include <stdio.h>
#include <inttypes.h>

int main(void);

int main(void)
{
   int32_t u;
   int32_t i;
   u = (unsigned) 0x7FFFFFFF;
   i = (int32_t) u;
   printf("signed:  0x%08X  %i\n", i, i);
   printf("unsigned 0x%08X  %u\n", u, u);
   return(0);
}
