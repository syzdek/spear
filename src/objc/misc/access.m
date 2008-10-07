

#import <Foundation/NSObject.h>
#import <stdio.h>

@interface Access: NSObject {
@public
    int publicVar;
@private
    int privateVar;
    int privateVar2;
@protected
    int protectedVar;
}
@end


@implementation Access
@end

int main( int argc, const char *argv[] ) {
    Access *a = [[Access alloc] init];

    // works
    a->publicVar = 5;
    printf( "public var: %i\n", a->publicVar );

    // doesn't compile
    //a->privateVar = 10;
    //printf( "private var: %i\n", a->privateVar );

    [a release];
    return 0;
}
