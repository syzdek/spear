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
/*  example.h - contains exported functions and datatypes */
#ifndef _EXAMPLES_C_DLL_EXAMPLE_H
#define _EXAMPLES_C_DLL_EXAMPLE_H

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

/* String Test Data */
#define EXAMPLE_STRING_SIZE   12
#define EXAMPLE_STRING_DATA   "Hello Riley"

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

   long int helloworld(void);
   char *example_stringcreate(void);
   long int example_stringdestroy(char **);
   long int example_sum(int, int);

#endif
