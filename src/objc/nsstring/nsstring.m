
#import <Cocoa/Cocoa.h>
#import <Foundation/Foundation.h>
#import <stdio.h>

int main(int argc, char * argv[]);

int main(int argc, char * argv[])
{
   NSString * userName;
   NSString * user;
   NSString * domain;
   NSRange    range;
   //NSCharacterSet * chr;

   NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];

   if (argc < 2)
   {
      printf("usage: %s <string>\n", argv[0]);
      return(1);
   };

   printf("initializing string...\n");
   userName = [NSString stringWithFormat:@"%s", argv[1]];
   printf("string: %s\n", [userName UTF8String]);

   printf("generates range...\n");
   range = [userName rangeOfCharacterFromSet:[NSCharacterSet characterSetWithCharactersInString:@"@"]];
   if (range.location != NSNotFound)
   {
      user = [userName substringToIndex:range.location];
      domain = [userName substringFromIndex:(range.location+1)];
   } else {
      printf("not a user name.\n");
      [pool release];
      return(1);
   };

   printf("user:   %s\n", [user   UTF8String]);
   printf("domain: %s\n", [domain UTF8String]);

   [pool release];
   return(0);
}
