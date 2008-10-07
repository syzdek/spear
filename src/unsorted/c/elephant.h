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
/*  elephant.c - header file for drawing of a elephant
*/
#ifndef _ANIMATED_ASCII_ELEPHANT_H
#define _ANIMATED_ASCII_ELEPHANT_H

///////////////
//           //
//  Headers  //
//           //
///////////////

//#include <opensyzler/ansimations.h>
#ifdef _ANIMATED_ASCII_ELEPHANT_C
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

#define COLOR_CREDITS   "[1;35m"
#define COLOR_ELEPHANT   "[1;34m"
#define COLOR_FLAG   "[1;31m"

#ifndef COLOR_RESET
#define COLOR_RESET     "[0m"	/* reset colors */
#endif
#ifndef POSXY
#define POSXY   "[%i;%iH"                    /* positions cursor to Y X */
#endif
#ifndef CLRSCR
#define CLRSCR  "[2J"                                /* clears screen */
#endif
#ifndef HOME
#define HOME    "[23;0H"                     /* homes the cursor */
#endif


//////////////////
//              //
//  Prototypes  //
//              //
//////////////////

#ifdef _ANIMATED_ASCII_ELEPHANT_C
int main(void);
#endif

/* End Header File */
#endif
