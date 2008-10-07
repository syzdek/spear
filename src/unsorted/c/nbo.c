/* testing network byte order verses host byte order */

#include <netinet/in.h>
#include <stdio.h>

int main(void);

int main(void)
{
   unsigned int s;
   s = 389;
   printf("int:   %u\n", s);
   printf("htons: %u\n", htons(s));
   printf("ntohs: %u\n", ntohs(htons(s)));
   return(0);
   
}
