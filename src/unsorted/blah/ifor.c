#include <stdio.h>

int main(void);
int main(void)
{
   int i;
   int var;

   i = 0;

   var = i ? 100 : 200;

   printf("var: %i\n", var);

   return(0);
}
