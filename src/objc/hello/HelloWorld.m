#import "HelloWorld.h"

@implementation HelloWorld

- (void)addNumber:(int)add;
{
   num += add;
   return;
}

- (int)getNumber
{
   return(num);
}

- (void) printHello
{
   printf("Hello World\n");
   return;
}

- (void) printVersion
{
   printf("version: %i\n", [HelloWorld version]);
   return;
}


- (void)sayHello
{
   NSLog(@"Hello, world, at %@", [NSCalendarDate calendarDate]);
   return;
}


@end
