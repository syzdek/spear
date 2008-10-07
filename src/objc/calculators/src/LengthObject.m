/*
 *  $Id: $
 */
/*
 *  Syzdek's Silly Calculators
 *  Copyright (c) 2008 David M. Syzdek <david@syzdek.net>
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
 *  LengthObject.m - Declares the interface for LengthObject.
 */
#define _SSC_SRC_LENGTH_CLASS_M 1
#import "LengthObject.h"

/////////////
//         //
//  Class  //
//         //
/////////////
@implementation LengthObject


/********************************************************/
/*                                                      */
/*  Converts between Metric System and Imperial System  */
/*                                                      */
/********************************************************/


+ (double) footToMeter:(double)unit
{
   return(unit * 0.3048);
}


- (double) footToMeter:(double)unit
{
   return([LengthObject footToMeter:unit]);
}


+ (double) meterToFoot:(double)unit
{
   return(unit / 0.3048);
}


- (double) meterToFoot:(double)unit
{
   return([LengthObject meterToFoot:unit]);
}


+ (double) meterToYard:(double)unit
{
   return(unit / 0.9144);
}


- (double) meterToYard:(double)unit
{
   return([LengthObject meterToYard:unit]);
}


+ (double) yardToMeter:(double)unit
{
   return(unit * 0.9144);
}


- (double) yardToMeter:(double)unit
{
   return([LengthObject yardToMeter:unit]);
}


/******************/
/*                */
/*  Base Methods  */
/*                */
/******************/

/// Assume an initial value equal to 1 meter.
- (id) init
{
   [super init];
   [self setMeter:1.0];
   return(self);
}


/// A meter is 1 meter.
- (double) meter
{
   return(meter);
}


/// A meter is 1 meter.
- (void) setMeter:(double)length
{
   meter = length;
   yard  = [LengthObject meterToYard:length];
   return;
}


///  A yard is 1 yard.
- (double) yard
{
   return(yard);
}


/// A yard is 1 yard.
- (void) setYard:(double)length
{
   yard  = length;
   meter = [LengthObject footToMeter:(length * 3.0)];
   return;
}


/*********************/
/*                   */
/*  Imperial System  */
/*                   */
/*********************/

/// A yard is 36000 thous.
- (double) thou
{
   return(yard * 36000.0);
}


/// A thou is 1/36000 yards.
- (void) setThou:(double)length
{
   [self setYard:(length/36000.0)];
   return;
}


/// A yard is 36 inches.
- (double) inch
{
   return(yard * 36.0);
}


/// An inch is 1/36 yards.
- (void) setInch:(double)length
{
   [self setYard:(length/36.0)];
   return;
}


/// A yard is 3 feet.
- (double) foot
{
   return(yard * 3.0);
}


/// A foot is 1/3 yards.
- (void) setFoot:(double)length
{
   [self setYard:(length/3.0)];
   return;
}


// yards are handled in the base methods


/// A yard is 1/220 furlongs.
- (double) furlong
{
   return(yard / 220.0);
}


/// A furlong is 220 yards.
- (void) setFurlong:(double)length
{
   [self setYard:(length * 220.0)];
   return;
}


/// A yard is 1/1760 miles.
- (double) mile
{
   return(yard / 1760.0);
}


/// A mile is 1760 yards.
- (void)  setMile:(double)length
{
   [self setYard:(length * 1760.0)];
   return;
}


/// A yard is 1/5280 leagues.
- (double) league
{
   return(yard / 5280.0);
}


/// A league is 5280 yards.
- (void) setLeague:(double)length
{
   [self setYard:(length * 5280.0)];
   return;
}


/* maritime units */

/// 1 fathom == 2 yards
- (double) fathom
{
   return(yard * 2.0);
}


- (void) setFathom:(double)length
{
   [self setYard:(length / 2.0)];
   return;
}


- (double) cable
{
   return( yard / (202.0 + (2.0/3.0)) );
}


- (void)  setCable:(double)length
{
   [self setYard:(202.0 + (2.0/3.0)) * length];
   return;
}


- (double) nauticalMile
{
   return( yard / (2026.0 + (2.0/3.0)) );
}


- (void)  setNauticalMile:(double)length
{
   [self setYard:(2026.0 + (2.0/3.0)) * length];
   return;
}


/* Gunter's survey units */


- (double) link
{
   return( yard / 0.22 );
}


- (void)  setLink:(double)length
{
   [self setYard:(length * 0.22)];
   return;
}


- (double) pole
{
   return( yard / 5.5 );
}


- (void)  setPole:(double)length
{
   [self setYard:(length * 5.5)];
   return;
}


- (double) chain
{
   return( yard / 22 );
}


- (void)  setChain:(double)length
{
   [self setYard:(length * 22)];
   return;
}


/**************************/
/*                        */
/*  Miscellaneous System  */
/*                        */
/**************************/

- (double) digit
{
   return([LengthObject meterToFoot:meter] * 16.0);
}


- (void)  setDigit:(double)length
{
   meter = [LengthObject footToMeter:(length/16.0)];
   return;
}


- (double) palm
{
   return([LengthObject meterToFoot:meter] * 4.0);
}


- (void) setPalm:(double)length
{
   meter = [LengthObject footToMeter:(length/4.0)];
   return;
}


- (double) hand
{
   return([LengthObject meterToFoot:meter] * 3.0);
}


- (void) setHand:(double)length
{
   meter = [LengthObject footToMeter:(length/3.0)];
   return;
}


- (double) cubit
{
   return(yard * 2.0);
}


- (void)  setCubit:(double)length
{
   [self setYard:(length / 2.0)];
   return;
}



/*******************/
/*                 */
/*  Metric System  */
/*                 */
/*******************/

- (double) picometer
{
   return(meter * 1000000000000.0);
}


- (void)  setPicometer:(double)length
{
   [self setMeter:length / 1000000000000.0];
   return;
}


- (double) nanometer
{
   return(meter * 1000000000.0);
}


- (void)  setNanometer:(double)length
{
   [self setMeter:length / 1000000000.0];
   return;
}


- (double) micrometer
{
   return(meter * 1000000.0);
}


- (void)  setMicrometer:(double)length
{
   [self setMeter:length / 1000000.0];
   return;
}


- (double) millimeter
{
   return(meter * 1000.0);
}


- (void)  setMillimeter:(double)length
{
   [self setMeter:length / 1000.0];
   return;
}


- (double) centimeter
{
   return(meter * 100.0);
}


- (void)  setCentimeter:(double)length
{
   [self setMeter:length / 100.0];
   return;
}


- (double) decimeter
{
   return(meter * 10.0);
}


- (void)  setDecimeter:(double)length
{
   [self setMeter:length / 10.0];
   return;
}


// meters are handled in the base methods


- (double) decameter
{
   return(meter / 10.0);
}


- (void)  setDecameter:(double)length
{
   [self setMeter:length * 10.0];
   return;
}


- (double) hectometer
{
   return(meter / 100.0);
}


- (void)  setHectometer:(double)length
{
   [self setMeter:length * 100.0];
   return;
}


- (double) kilometer
{
   return(meter / 1000.0);
}


- (void)  setKilometer:(double)length
{
   [self setMeter:length * 1000.0];
   return;
}


- (double) megameter
{
   return(meter / 1000000.0);
}


- (void)  setMegameter:(double)length
{
   [self setMeter:length * 1000000.0];
   return;
}


- (double) gigameter
{
   return(meter / 1000000000.0);
}


- (void) setGigameter:(double)length
{
   [self setMeter:length * 1000000000.0];
   return;
}


- (double) terameter
{
   return(meter / 1000000000000.0);
}


- (void) setTerameter:(double)length
{
   [self setMeter:length * 1000000000000.0];
   return;
}


@end
/* end of source file */
