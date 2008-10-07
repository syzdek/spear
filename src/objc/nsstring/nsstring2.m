
#import <Cocoa/Cocoa.h>
#import <Foundation/Foundation.h>
#import <stdio.h>

int main(int argc, char * argv[]);

int main(int argc, char * argv[])
{
   NSString * string;

   NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];

   if (argc < 2)
   {
      printf("usage: %s <string>\n", argv[0]);
      return(1);
   };

   printf("initializing string...\n");
   string = [NSString stringWithUTF8String:argv[1]];
   printf("string: %s\n", [string UTF8String]);

   [pool release];
   return(0);
}
