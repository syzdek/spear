#import <Foundation/Foundation.h>
#import <stdio.h>
#import "HelloWorld.h"

int main (void);

int main (void)
{
   Class myClass;
   NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];

   // my stuff
   HelloWorld *hw = [HelloWorld alloc];
   [hw autorelease];
	
   [hw sayHello];
   [hw printHello];

   //if ( [HelloWorld isMemberOfClass:HelloWorld] )
   //   printf("yes\n");

   [hw addNumber:13];
   [hw addNumber:7];

   printf("number: %i\n", [hw getNumber]);

   myClass = [hw class];
   printf("version: %i\n", [myClass version]);

   //if ( [HelloWorld isMemberOfClass:HelloWorld] )
   //    printf("yes\n");

   [pool release];
   return 0;
}
