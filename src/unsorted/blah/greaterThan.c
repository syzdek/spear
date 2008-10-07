#include <stdio.h>

int main(int argc, char * argv[]);
int main(int argc, char * argv[])
{
   int x;
   int y;
   int z;

   if (argc < 4)
   {
      printf("usage:  %s (int)x (int)y (int)z\n", argv[0]);
      return(1);
   };

   x = atol(argv[1]);
   y = atol(argv[2]);
   z = atol(argv[3]);

   printf("%5i > %5i         == %i\n", x, y, (x > y));
   printf("        %5i > %5i == %i\n", y, z, (y > z));
   printf("%5i         > %5i == %i\n", x, z, (x > z));

   printf("%5i > %5i > %5i == ", x, y, z);
   if (x > y > z)
      printf("YES\n");
   else
      printf("NO\n");

   return(0);
}
