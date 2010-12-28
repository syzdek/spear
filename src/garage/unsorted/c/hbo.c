/* testing network byte order verses host byte order */
/*
 *  Build:
 *     gcc -o nbo nbo.c
 */

#include <netdb.h>
#include <sys/param.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>

int main(void);

int main(void)
{
   if (htonl(1024) == 1024)
   {
      printf("host is Big Endian\n");
     } else {
      printf("host if Little Endian\n");
   };
   return(0);
}
