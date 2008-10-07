
#import <Foundation/Foundation.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]);
int main(int argc, char * argv[])
{
   int    i;
   long double d;
   NSNumber          * num;
   NSNumberFormatter * fmt;
   NSString          * str;
   NSAutoreleasePool * pool;

   pool = [[NSAutoreleasePool alloc] init];

   fmt = [[NSNumberFormatter alloc] init];
   [fmt setUsesSignificantDigits:YES];
   [fmt setMaximumSignificantDigits:20];

   printf("max significant digits: %i\n", [fmt maximumSignificantDigits]);

   for(i = 1; i < argc; i++)
   {
      d = strtold(argv[i], NULL);
      [fmt setNumberStyle:NSNumberFormatterDecimalStyle];
      if (d < 0.000000001)
         [fmt setNumberStyle:NSNumberFormatterScientificStyle];
      if (d > 99999999999.0)
         [fmt setNumberStyle:NSNumberFormatterScientificStyle];
      num = [NSNumber numberWithDouble:d];
      str = [fmt stringFromNumber:num];
      printf("arg %-2i: %s\n", i, [str UTF8String]);
   };

   [fmt release];
   [pool release];
   return(0);
}
