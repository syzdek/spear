/*
 * Animated ASCII Art
 * $Source: /repos/development/blips/blips/src/blipsd/blipsd.c,v $
 * $Revision: 1.13.2.8 $
 * $Date: 2004/07/14 09:33:59 $
 * $Author: syzdek $
 */
/*
 * Copyright (c) 2004 David M. Syzdek <syzdek@mosquitonet.com>
 * All Rights Reserved.
 * COPYING RESTRICTIONS APPLY, see LICENSE.TXT file
 */
/*  pumpkin.c - header file for drawing of a pumpkin
*/
#ifndef _ANIMATED_ASCII_PUMPKIN_H
#define _ANIMATED_ASCII_PUMPKIN_H

///////////////
//           //
//  Headers  //
//           //
///////////////

//#include <opensyzler/ansimations.h>
#ifdef _ANIMATED_ASCII_PUMPKIN_C
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#endif

///////////////////
//               //
//  Definitions  //
//               //
///////////////////

#ifndef DELAY
//#define DELAY   1
#define DELAY   40000
#endif

#define PUMPKIN_COLOR_BODY	"[31m"		/* color of the pumpkin body     */
#define PUMPKIN_COLOR_STEM	"[32m"		/* color of the pumpkin stem     */
#define PUMPKIN_COLOR_CARVING	"[33m"		/* color of the pumpkin carvings */
#define PUMPKIN_COLOR_CREDITS	"[1;34m"		/* color of the pumpkin carvings */

#ifndef COLOR_RESET
#define COLOR_RESET	"[0m"			/* reset colors                  */
#endif
#ifndef POSXY
#define POSXY	"[%i;%iH"			/* positions cursor to Y X */
#endif
#ifndef CLRSCR
#define CLRSCR	"[2J"				/* clears screen */
#endif
#ifndef HOME
#define HOME	"[23;0H"			/* homes the cursor */
#endif

//////////////////
//              //
//  Prototypes  //
//              //
//////////////////

   int animate_credits_from_right(int, int, int, char *);	/* animates credits */
   int animate_mouth1(int, int);		/* animates first type of mouth */
   int animate_mouth2(int, int);		/* animates second mouth */
   int animate_pumpkin(int, int);		/* animates body of the pumpkin */
   int animate_stem(int, int);			/* animates stem of the pumpkin */
   int animate_carving1(int, int);		/* animates first type of carving */
   int animate_carving1(int, int);		/* animates second type of carving */

#ifdef _ANIMATED_ASCII_PUMPKIN_C
int main(void);
#endif

/* End Header File */
#endif

