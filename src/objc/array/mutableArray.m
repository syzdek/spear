
#import <Foundation/Foundation.h>
#import <stdio.h>

int main(void);
int main(void)
{
   NSAutoreleasePool * pool;
   NSMutableArray    * data;
   NSNumber          * number;

   pool = [[NSAutoreleasePool alloc] init];

   data = [NSMutableArray arrayWithCapacity:15];
   printf("data size: %i\n", [data count]);

   [data addObject:[NSNumber numberWithDouble:0.00123123]];
   printf("data size: %i\n", [data count]);

   [data addObject:[data lastObject]];
   printf("data size: %i\n", [data count]);


   [pool release];

   return(0);
}
