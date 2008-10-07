/*
 *  $Id: $
 */
/*
 *  Syzdek's Silly Calculators
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
/** @file LengthObject.h  Declares the interface for LengthObject. */
#ifndef _SSC_SRC_LENGTH_CLASS_H
#define _SSC_SRC_LENGTH_CLASS_H 1

///////////////
//           //
//  Headers  //
//           //
///////////////

#include "SSCObject.h"


///////////////////////
//                   //
//  Class Definition //
//                   //
///////////////////////
/// This class is the model of a measured unit of length.
@interface LengthObject : SSCObject
{
   double meter;	///< Metric calculations use a base value in meters.
   double yard;		///< Imperial calculations use a base value in yards.
}


/********************************************************/
/*                                                      */
/*  Converts between Metric System and Imperial System  */
/*                                                      */
/********************************************************/

+ (double) footToMeter:(double)foot;
- (double) footToMeter:(double)foot;

+ (double) meterToFoot:(double)meter;
- (double) meterToFoot:(double)meter;

+ (double) meterToYard:(double)meter;
- (double) meterToYard:(double)meter;

+ (double) yardToMeter:(double)foot;
- (double) yardToMeter:(double)foot;


/******************/
/*                */
/*  Base Methods  */
/*                */
/******************/

- (id)     init;

- (double) meter;
- (void)   setMeter:(double)length;

- (double) yard;
- (void)   setYard:(double)length;


/*********************/
/*                   */
/*  Imperial System  */
/*                   */
/*********************/

- (double) thou;
- (void)   setThou:(double)length;

//- (double) mil;
//- (void)   setMil:(double)length;

- (double) inch;
- (void)   setInch:(double)length;

- (double) foot;
- (void)   setFoot:(double)length;

// yards are handled in the base methods

- (double) furlong;
- (void)   setFurlong:(double)length;

- (double) mile;
- (void)   setMile:(double)length;

- (double) league;
- (void)   setLeague:(double)length;

/* maritime units */

- (double) fathom;
- (void)   setFathom:(double)length;

- (double) cable;
- (void)   setCable:(double)length;

- (double) nauticalMile;
- (void)   setNauticalMile:(double)length;

/* Gunter's survey units */

- (double) link;
- (void)   setLink:(double)length;

- (double) pole;
- (void)   setPole:(double)length;

- (double) chain;
- (void)   setChain:(double)length;

/**************************/
/*                        */
/*  Miscellaneous System  */
/*                        */
/**************************/

- (double) digit;
- (void)   setDigit:(double)length;

- (double) palm;
- (void)   setPalm:(double)length;

- (double) hand;
- (void)   setHand:(double)length;

- (double) cubit;
- (void)   setCubit:(double)length;

/*******************/
/*                 */
/*  Metric System  */
/*                 */
/*******************/

- (double) picometer;
- (void)   setPicometer:(double)length;

- (double) nanometer;
- (void)   setNanometer:(double)length;

- (double) micrometer;
- (void)   setMicrometer:(double)length;

- (double) millimeter;
- (void)   setMillimeter:(double)length;

- (double) centimeter;
- (void)   setCentimeter:(double)length;

- (double) decimeter;
- (void)   setDecimeter:(double)length;

// meters are handled in the base methods

- (double) decameter;
- (void)   setDecameter:(double)length;

- (double) hectometer;
- (void)   setHectometer:(double)length;

- (double) kilometer;
- (void)   setKilometer:(double)length;

- (double) megameter;
- (void)   setMegameter:(double)length;

- (double) gigameter;
- (void)   setGigameter:(double)length;

- (double) terameter;
- (void)   setTerameter:(double)length;

@end

#endif /* end of header */
