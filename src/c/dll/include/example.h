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

/* DLL Definitions */
#ifndef EXAMPLE_FUNCTION_PREFIX
#ifdef WIN32
#define EXAMPLE_FUNCTION_PREFIX extern "C" __declspec(dllexport)
#else 
#define EXAMPLE_FUNCTION_PREFIX
#endif
#endif

/* Needed by Windows DLL */
#ifndef PASCAL
#define PASCAL
#endif
#ifndef EXPORT
#define EXPORT
#endif


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

   EXAMPLE_FUNCTION_PREFIX long helloworld(void);
   EXAMPLE_FUNCTION_PREFIX char *example_stringcreate(void);
   EXAMPLE_FUNCTION_PREFIX long example_stringdestroy(char **);
   EXAMPLE_FUNCTION_PREFIX long example_sum(int, int);

#endif
