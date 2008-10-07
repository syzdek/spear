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
/** @file TemperatureObject.h  Declares the interface for TemperatureObject. */
#ifndef _SSC_SRC_TEMPERATURE_CLASS_H
#define _SSC_SRC_TEMPERATURE_CLASS_H 1

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
/// This class is the model of a measured unit of temperature.
@interface TemperatureObject : SSCObject
{
   float kelvin;	///< All calculations use a base value in Kelvins.
}

- (float) celsius;
- (void)  setCelsius:(float)degree;

- (float) fahrenheit;
- (void)  setFahrenheit:(float)degree;

- (id)    init;

- (float) kelvin;
- (void)  setKelvin:(float)degree;

- (float) rankine;
- (void)  setRankine:(float)degree;

@end

#endif /* end of header */
