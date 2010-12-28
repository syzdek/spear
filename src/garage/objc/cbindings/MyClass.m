/*
 *  $Id: $
 */
/*
 *  Simple Objective-C Object Experiment
 *  Copyright (C) 2008 David M. Syzdek <david@syzdek.net>.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */
/*
 *  MyClass.h - simple object
 */
#define _MYCLASS_M 1
#include "MyClass.h"


/////////////
//         //
//  Class  //
//         //
/////////////
@implementation MyClass

- (void) retain
{
   owners++;
   return;
}


- (void) release
{
   if (owners)
      owners--;
   else
      [self free];
   return;
}


- (int) var1
{
   return(var1);
}


- (void) setVar1:(int)anInt
{
   var1 = anInt;
   return;
}


- (int)  var2
{
   return(var2);
}


- (void) setVar2:(int)anInt
{
   var2 = anInt;
   return;
}


- (int)  var3
{
   return(var3);
}


- (void) setVar3:(int)anInt
{
   var3 = anInt;
   return;
}

@end
/* end of source file */
