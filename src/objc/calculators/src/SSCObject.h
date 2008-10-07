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
/** @file SSCObject.h   basic object stuff.  */
#ifndef _SSC_SRC_SSCOBJECT_H
#define _SSC_SRC_SSCOBJECT_H 1

///////////////
//           //
//  Headers  //
//           //
///////////////

#include <objc/Object.h>
#include <stdlib.h>


///////////////////////
//                   //
//  Class Definition //
//                   //
///////////////////////
/**
 *  This class provides a subset of the functionality from NSObject. The
 *  purpose is to allow a subset of the features available in NSObject to be
 *  used on systems which do not have a Foundation framework from either
 *  OPENstep, GNUstep, Cocoa, or libFoundation.
 */
@interface SSCObject : Object
{
   int retainCount;
}

- (void)         dealloc;
- (void)         release;
- (void)         retain;
- (unsigned int) retainCount;

@end

#endif /* end of header */
