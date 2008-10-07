
#import <Foundation/NSObject.h>
#import <stdio.h>
#import <stdlib.h>

@interface Fraction: NSObject {
   int numerator;
   int denominator;
}

-(void) print;
-(void) setNumerator: (int) d;
-(void) setDenominator: (int) d;
-(void) setNumerator: (int) n andDenominator: (int) d;
-(Fraction*) initWithNumerator: (int) n denominator: (int) d;
-(int) numerator;
-(int) denominator;
@end

@implementation Fraction
-(void) print {
   printf( "%i/%i", numerator, denominator );
}

-(void) setNumerator: (int) n {
   numerator = n;
}

-(void) setDenominator: (int) d {
   denominator = d;
}

-(void) setNumerator: (int) n andDenominator: (int) d {
   numerator = n;
   denominator = d;
}

-(Fraction*) initWithNumerator: (int) n denominator: (int) d {
    self = [super init];

    if ( self ) {
        [self setNumerator: n andDenominator: d];
    }

    return self;
}

-(int) denominator {
   return denominator;
}

-(int) numerator {
   return numerator;
}
@end

int main( int argc, const char *argv[] )
{
   // create a new instance
   Fraction *frac = [[Fraction alloc] init];
   Fraction *frac2 = [[Fraction alloc] init];
   Fraction *frac3 = [[Fraction alloc] initWithNumerator: 3 denominator: 10];

   if (argc < 2)
   {
      printf("usage: %s <numerator> <denominator>\n", argv[0]);
      return(1);
   };

   // set the values
   [frac setNumerator: 1];
   [frac setDenominator: 3];

   // combined set
   [frac2 setNumerator: atol(argv[1]) andDenominator: atol(argv[2])];

   // print it
   printf( "The fraction is: " );
   [frac print];
   printf( "\n" );

   // print it
   printf( "Fraction 2 is: " );
   [frac2 print];
   printf( "\n" );

    printf( "Fraction 3 is: " );
    [frac3 print];
    printf( "\n" );

   // free memory
   [frac release];
   [frac2 release];
   [frac3 release];

   return 0;
}
