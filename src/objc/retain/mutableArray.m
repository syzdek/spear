
#import <Foundation/Foundation.h>
#import <stdio.h>

int main(void);
int main(void)
{
   NSNumber          * number;
   NSMutableArray    * list;
   NSAutoreleasePool * pool;

   pool = [[NSAutoreleasePool alloc] init];

   list = [[NSMutableArray alloc] initWithCapacity:15];

   number = [NSNumber numberWithInt:123];
   printf("retainers after init:         %u\n", CFGetRetainCount(number));

   [list addObject:number];
   printf("retainers after addObject:    %u\n", [number retainCount]);

   [number retain];
   printf("retainers after retain:       %u\n", [number retainCount]);

   [number release];
   printf("retainers after release:      %u\n", [number retainCount]);

   [list release];
   printf("retainers after removeObject: %u\n", [number retainCount]);

   [pool release];

   return(0);
}
