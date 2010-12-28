

#import <Foundation/Foundation.h>

#import "FirstProtocol.h"

@interface FirstClass : NSObject <FirstProtocol>
{
   int denominator;
   int numerator;
   int quotient;
}

- (int) denominator;
- (int) setDenominator:(int)number;

- (int) numerator;
- (int) setNumerator:(int)number;

@end
