/*
 *   Notes:
 */

#include <unistd.h>
#include <stdio.h>

int mod_extended_LTX_wave(void);

// a global variable definition
int mod_extended_LTX_size   = 1;
int mod_extended_LTX_pause  = 100;
int mod_extended_LTX_repeat = 5; 

int mod_extended_LTX_wave(void)
{
   int x;
   int y;
   int z;
   for(x = 0; x < mod_extended_LTX_repeat; x++)
   {
      for(y = 0; y < mod_extended_LTX_size; y++)
      {
         for(z = 0; z < y; z++)
            printf("  ");
         printf(">\n");
         usleep(mod_extended_LTX_pause);
      };
      for(z = 0; z < y; z++)
         printf("  ");
      printf("=-\n");
      usleep(mod_extended_LTX_pause);
      for(y = y-1; y >= 0; y--)
      {
         for(z = 0; z < y; z++)
            printf("  ");
         printf("<\n");
         usleep(mod_extended_LTX_pause);
      };
   };
   return(0);
} 

