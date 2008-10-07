

#import <Foundation/Foundation.h>

@interface SecondClass : NSObject
{
   int denominator;
   int numerator;
   int sum;
}

- (int) denominator;
- (int) setDenominator:(int)number;

- (int) numerator;
- (int) setNumerator:(int)number;

@end
