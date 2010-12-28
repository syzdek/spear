#include <stdio.h>
#include <string.h>
#include <inttypes.h>

int main(int argc, char * argv[]);

int main(int argc, char * argv[])
{
   int      i;
   int      bit;
   uint32_t number;

   if (argc < 2)
   {
      fprintf(stderr, "Usage: %s <numberi1> <number2> ... <numberN>\n", argv[0]);
      return(1);
   };

   printf("%-10s   %10s   %12s   %-35s\n", "Hex", "Decimal", "Octal", "Binary");
   for(i = 1; i < argc; i++)
   {
      number = strtoul(argv[i], NULL, 0);
      printf("0x%08X   ", number);
      printf("%10lu   ", number);
      printf("%#12o   ", number);
      for(bit = 31; bit >= 0; bit--)
      {
         printf("%i", (int)((number >> bit)&(0x01)) );
         if (bit == 0)
            printf("\n");
         else if ((bit % 8) == 0)
            printf(" ");
      };
   };

   return(0);
}
