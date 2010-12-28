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
 *  TemperatureObject.m - Declares the interface for TemperatureObject.
 */
#define _SSC_SRC_TEMPERATURE_CLASS_M 1
#import "TemperatureObject.h"

/////////////
//         //
//  Class  //
//         //
/////////////
@implementation TemperatureObject


/// f(celsius) = kelvin - 273.15
- (float) celsius
{
   return(kelvin - 273.15);
}


/// f(kelvin) = celsius + 273.15
- (void) setCelsius:(float)degree
{
   kelvin = degree + 273.15;
   return;
}


/// f(fahrenheit) = (kelvin * 9/5) - 459.67
- (float) fahrenheit
{
   return((kelvin * (9.0/5.0)) - 459.67);
}


/// f(kelvin) = (5/9)(fahrenheit + 459.67)
- (void) setFahrenheit:(float)degree
{
   kelvin = (5.0/9.0) * (degree + 459.67);
   return;
}


/// Assume an initial value equal to melting point of water.
- (id) init
{
   [super init];
   kelvin = 273.15;
   return(self);
}


/// f(kelvin) = kelvin.
- (float) kelvin
{
   return(kelvin);
}


/// f(kelvin) = kelvin.
- (void)  setKelvin:(float)degree
{
   kelvin = degree;
   return;
}


/// f(rankine) = (kelvin)(9/5)
- (float) rankine
{
   return(kelvin * (9.0/5.0));
}


/// f(kelvin) = (rankine)(5/9)
- (void)  setRankine:(float)degree
{
   kelvin = degree * (5.0/9.0);
   return;
}

@end
/* end of source file */
