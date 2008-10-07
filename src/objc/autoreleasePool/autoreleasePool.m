
#include <Foundation/Foundation.h>
#include <stdlib.h>
#include <unistd.h>

#define USE_AUTORELEASE_POOL 1


int main(int argc, char * argv[]);

int main(int argc, char * argv[])
{
   int i;
   int max;
   int delay;
   int autorelease;
   NSString * str;
   NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
   NSAutoreleasePool * subPool;

   if (argc < 4)
   {
      fprintf(stderr, "Usage: %s <use autorelease> <iterations> <delay>\n", argv[0]);
      return(0);
   };
   autorelease = atol(argv[1]);
   max         = atol(argv[2]);
   delay       = atol(argv[3]);

   for (i = 0; i < max; i++)
   {
      if (autorelease)
         subPool = [[NSAutoreleasePool alloc] init];
      str = [NSString stringWithUTF8String:"adjkasdf;ad;fja;dlfkj;adlfasdfsdfadghrpuhrgqe;jasd;flkja;ldsfkj;aldkfj;alkdsjf;alkdsjf;alkdsjf;alkdjf;aksdjf;alskdjf;lkadjsf;alksjdfl;askdjfal;kdsjfa;lskdfj;alksdfj;alkdsfthis is a test string"];
      if (autorelease)
         [subPool release];
   };

   [pool release];
   sleep(delay);

   return(0);
}
