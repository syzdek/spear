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
/*  libexample-functions.h - Contains shared code */
#ifndef _EXAMPLES_C_DLL_LIBEXAMPLE_FUNCTIONS_H
#define _EXAMPLES_C_DLL_LIBEXAMPLE_FUNCTIONS_H
#include "libexample.h"


/////////////
//         //
//  Notes  //
//         //
/////////////


/////////////////
//             //
//  Functions  //
//             //
/////////////////

/* Prints Hello World */
#ifdef _EAMPLES_C_DLL_EXAMPLE_H_EXPORT_DLL
extern "C" __declspec(dllexport) long helloworld(void) {
#else
long helloworld(void) {
#endif

      /* Prints Message */
         printf("Hello World\n");

      /* Ends function */
         return(0);

   }


#endif