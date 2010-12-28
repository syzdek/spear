#include <stdio.h>
#include <inttypes.h>

int main(void);

int main(void)
{
   uint32_t u;
   int32_t i;
   printf(" uint8_t size: %u\n", sizeof(uint8_t));
   printf("         min:  %u\n", (uint8_t) 0x00);
   printf("         max:  %u\n", (uint8_t) 0xFF);
   printf("\n");

   printf("  int8_t size: %i\n", sizeof(int8_t));
   printf("         min:  %i\n", (int8_t) 0x80);
   printf("         max:  %i\n", (int8_t) 0x7F);
   printf("\n");

   printf("uint16_t size: %u\n", sizeof(uint16_t));
   printf("         min:  %u\n", (uint16_t) 0x0000);
   printf("         max:  %u\n", (uint16_t) 0xFFFF);
   printf("\n");

   printf("  int16_t size: %i\n", sizeof(int16_t));
   printf("         min:  %i\n", (int16_t) 0x8000);
   printf("         max:  %i\n", (int16_t) 0x7FFF);
   printf("\n");

   printf("uint32_t size: %u\n", sizeof(uint32_t));
   printf("         min:  %u\n", (uint32_t) 0x00000000);
   printf("         max:  %u\n", (uint32_t) 0xFFFFFFFF);
   printf("\n");

   printf("  int32_t size: %i\n", sizeof(int32_t));
   printf("         min:  %i\n", (int32_t) 0x80000000);
   printf("         max:  %i\n", (int32_t) 0x7FFFFFFF);
   printf("\n");

   printf("uint64_t size: %u\n", sizeof(uint64_t));
   printf("         min:  %u\n", (uint64_t) 0x0000000000000000);
   printf("         max:  %u\n", (uint64_t) 0xFFFFFFFFFFFFFFFF);
   printf("\n");

   printf("  int64_t size: %i\n", sizeof(int64_t));
   printf("         min:  %ju\n", (int64_t) 0x8000000000000000);
   printf("         max:  %ju\n", (int64_t) 0x7FFFFFFFFFFFFFFF);
   printf("\n");

   return(0);
}
