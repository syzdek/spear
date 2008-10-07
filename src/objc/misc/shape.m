
#import <Foundation/NSObject.h>
#import <stdio.h>

@interface Quadrilateral: NSObject {
@private
   int top;
   int bottom;
   int left;
   int right;
};

-(void) setTop: (int) d;
-(void) setBottom: (int) d;
-(void) setLeft: (int) d;
-(void) setRight: (int) d;
-(void) setAll: (int) t (int) b (int) l (int) r;
@end

@implementation Quadrilateral

-(void) setTop: (int) d
{
   top = d;
   return;
}

-(void) setBottom: (int) d
{
   bottom = d;
   return;
}

-(void) setLeft: (int) d
{
   left = d;
   return;
}

-(void) setRight: (int) d
{
   right = d;
   return;
}

-(void) setAll: (int) t (int) b (int) l (int) r
{
   top = t;
   bottom = b;
   left = l;
   right = r;
   return;
}

@end
