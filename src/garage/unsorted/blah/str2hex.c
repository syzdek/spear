
#include <stdio.h>
#include <string.h>

int main(int argc, char * argv[]);
int main(int argc, char * argv[])
{
   unsigned x;
   unsigned y;
   unsigned c;
   if (argc < 2)
   {
      fprintf(stderr, "Usage: %s <string>\n", argv[0]);
      return(1);
   };
   c = 0;
   for(x = 1; x < argc; x++)
   {
      for(y = 0; y < strlen(argv[x]); y++)
      {
         if ((c))
         {
            if (!(c % 10))
               printf(",\n");
            else
               printf(", ");
         };
         printf("0x%02X", argv[x][y]);
         c++;
      };
   };
   printf("\n");
   return(0);
}
