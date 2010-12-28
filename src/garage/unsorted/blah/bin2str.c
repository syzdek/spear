
#include <stdio.h>
#include <string.h>
int main(int argc, char * argv[]);
int main(int argc, char * argv[])
{
   int      c;
   char     bin;
   unsigned x;
   unsigned y;
   if (argc < 2)
   {
      fprintf(stderr, "Usage: %s <string>\n", argv[0]);
      return(1);
   };
   c   = 7;
   bin = 0;
   for(x = 1; x < argc; x++)
   {
      for(y = 0; y < strlen(argv[x]); y++)
      {
         switch(argv[x][y])
         {
            case '1':
               bin |= (0x01 << c);
            case '0':
               if (c < 1)
               {
                  printf("%c", bin);
                  c   = 8;
                  bin = 0;
               };
               c--;
            default:
               break;
         };
      };
   };
   printf("\n");
   return(0);
}
