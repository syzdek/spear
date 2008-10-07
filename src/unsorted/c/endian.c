

#include <arpa/inet.h>
#include <stdio.h>
#include <inttypes.h>

uint32_t my_ntohl(uint32_t u);
int main(void);

uint32_t my_ntohl(uint32_t u)
{
   uint32_t t;
   t = 0x00000011;
   if ( ! (((char *)&t)[0]) )
      return(u);
   u = ((u >>  8) & 0x00FF00FF) | ((u <<  8) & 0xFF00FF00);
   u = ((u >> 16) & 0x0000FFFF) | ((u << 16) & 0xFFFF0000);
   return(u);
}

int main(void)
{
   uint32_t u;
   uint32_t t;

   u = 0x00000011;
   u = ntohl(u);
   printf("ntohl(u)    == %u\n", u);

   u = 0x00000011;
   u = my_ntohl(u);
   printf("my_ntohl(u) == %u\n", u);

   t = 0x00000011;
   if ( ! (((char *)&t)[0]) )
      printf("little endian\n");
   else
      printf("big endian\n");
   
   return(0);
}
