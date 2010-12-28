#import <Foundation/Foundation.h>
#import <stdio.h>

@interface HelloWorld : NSObject
{
    int num;
}

// methods
- (void)addNumber:(int)add;
- (int)getNumber;
- (void)printHello;
- (void)printVersion;
- (void)sayHello;

@end
