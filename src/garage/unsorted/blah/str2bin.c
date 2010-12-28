
#include <stdio.h>
#include <string.h>

int main(int argc, char * argv[]);
int main(int argc, char * argv[])
{
   unsigned x;
   unsigned y;
   unsigned z;
   unsigned c;
   if (argc < 2)
   {
      fprintf(stderr, "Usage: %s <string>\n", argv[0]);
      return(1);
   };
   for(x = 1; x < argc; x++)
   {
      for(y = 0; y < strlen(argv[x]); y++)
      {
         printf("%c: 0x%02X: ", argv[x][y], argv[x][y]);
         for(z = 0; z < 8; z++)
         {
            if ( argv[x][y] & (0x01 << (7-z)) )
               printf("1");
            else
               printf("0");
         };
         printf("\n");
      };
   };
   c = 0;
   for(x = 1; x < argc; x++)
   {
      for(y = 0; y < strlen(argv[x]); y++)
      {
         for(z = 0; z < 8; z++)
         {
            if ( argv[x][y] & (0x01 << (7-z)) )
               printf("1");
            else
               printf("0");
         };
         c++;
         if (!(c%8))
            printf("\n");
         else
            printf(" ");
      };
   };
   printf("\n");
   return(0);
}
