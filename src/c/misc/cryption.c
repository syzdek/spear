
///////////////
//           //
//  Headers  //
//           //
///////////////

#include <openssl/blowfish.h>
#include <openssl/evp.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>


//////////////////
//              //
//  Prototypes  //
//              //
//////////////////

int generate_key();
int main(int argc, char *argv[]);

int generate_key()
{
   int i;
   int j;
   int fd;
   int len;
   uint8_t key[64];

   if ((fd = open("/dev/urandom", O_RDONLY)) == -1)
   {
      perror("open()");
      return(1);
   };

   if ((len = read(fd, key, 64)) == -1)
   {
      perror("read()");
      return(1);
   };

   printf("512 bit key:");
   for (i = 0; i < 64; i++)
      if (i % 32)
         printf ("%02X", key[i]);
      else
         printf ("\n%02X", key[i]);
   printf ("\n------ \n");

   return(0);
}


int main(int argc, char *argv[])
{
   generate_key();
   return(0);
}
