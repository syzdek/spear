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

#ifdef _EXAMPLES_C_DLL_LIBEXAMPLE_CPP
#ifdef WIN32
#define _EXAMPLES_C_DLL_EXAMPLE_H_EXPORT_DLL
#endif
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

// Windows DLL Exports
#ifdef _EXAMPLES_C_DLL_EXAMPLE_H_EXPORT_DLL
   extern "C" __declspec(dllexport) long helloworld(void);                /* Prints Hello World  */
#endif

// Everyone Else's Exports
#ifndef _EXAMPLES_C_DLL_EXAMPLE_H_EXPORT_DLL
   long helloworld(void);                                                 /* Prints Hello World  */
#endif


#endif
