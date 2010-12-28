/*
 * Example of Windows DLL and Unix Shared Library
 * $Source$
 * $Revision$
 * $Date$
 * $Author$
 */
/*
 * Copyright (c) 2003 Alaska Communications Systems <sys.admin@acsalaska.net>
 * All Rights Reserved.
 * COPYING RESTRICTIONS APPLY, see LICENSE.TXT file
 */
/*  libexample.h - Internal Prototypes */
#ifndef _EXAMPLES_C_DLL_LIBEXAMPLE_H
#define _EXAMPLES_C_DLL_LIBEXAMPLE_H

/////////////
//         //
//  Notes  //
//         //
/////////////

   /*
    * Insert notes Here
    */


////////////////////////
//                    //
//  Data Definitions  //
//                    //
////////////////////////


//////////////////////////
//                      //
//  Struct Definitions  //
//                      //
//////////////////////////


///////////////
//           //
//  Headers  //
//           //
///////////////
/* Windows Specific Headers */
#ifdef WIN32
#include <windows.h>
#endif

/* General Headers */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Exported Functions */
#include "../include/example.h"


////////////////////////
//                   //
//  Global Settings  //
//                   //
///////////////////////


//////////////////
//              //
//  Prototypes  //
//              //
//////////////////




#endif
