
#import <Foundation/Foundation.h>
#import "FirstClass.h"
#import "SecondClass.h"

int main(void);

int main(void)
{
   id first;
   id second;
   NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];

   first  = [[FirstClass alloc]  init];
   second = [[SecondClass alloc] init];

   [first setDenominator:5];
   [first setNumerator:56];

   [second setDenominator:[first denominator]];
   [second setNumerator:[first numerator]];

   [first  release];
   [second release];

   [pool release];

   return(0);
}
