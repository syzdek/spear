
#include <Foundation/Foundation.h>
#include <stdio.h>

int main(void);

int main(void)
{
   int i;
   NSString * str    = @"test string";
   NSString * list[] = {
      @"test string",
      @"test string",
      @"another test string",
      @"TEST STRING",
      @"test",
      @"test string is short",
      @"boo hoo",
      nil
   };
   NSRange range;
   NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];

   printf("use compare use from NSString class\n");
   for(i = 0; list[i]; i++)
   {
      printf("   ");
      if ([str compare:list[i]])
         printf("No match");
      else
         printf("match   ");
      printf(" \"%s\"  === \"%s\"\n", [str UTF8String], [list[i] UTF8String]);
   };
   printf("\n");

   printf("use caseInsensitiveCompare from NSString class\n");
   for(i = 0; list[i]; i++)
   {
      printf("   ");
      if ([str caseInsensitiveCompare:list[i]])
         printf("No match");
      else
         printf("match   ");
      printf(" \"%s\"  === \"%s\"\n", [str UTF8String], [list[i] UTF8String]);
   };
   printf("\n");

   printf("use rangeOfString from NSString class\n");
   for(i = 0; list[i]; i++)
   {
      printf("   ");
      range = [str rangeOfString:list[i]];
      if (range.location == NSNotFound)
         printf("not found");
      else
         printf("found    ");
      printf(" \"%s\"  === \"%s\"\n", [str UTF8String], [list[i] UTF8String]);
   };
   printf("\n");

   printf("use rangeOfString options:NSCaseInsensitiveSearch from NSString class\n");
   for(i = 0; list[i]; i++)
   {
      printf("   ");
      range = [str rangeOfString:list[i] options:NSCaseInsensitiveSearch];
      if (range.location == NSNotFound)
         printf("not found");
      else
         printf("found    ");
      printf(" \"%s\"  === \"%s\"\n", [str UTF8String], [list[i] UTF8String]);
   };
   printf("\n");

   [pool release];
   
   return(0);
}
