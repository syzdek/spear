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


////////////////////////
//                    //
//  Data Definitions  //
//                    //
////////////////////////

/* Defines buffer sizes */
#define STRUCT_EXAMPLEDLL_BUFFER 1024

/* String Test Data */
#define EXAMPLE_STRING_SIZE   12
#define EXAMPLE_STRING_DATA   "Hello Riley"

/* _stdcall is needed by Win DLLs but not C */
#ifndef WIN32
#ifdef _stdcall
#undef _stdcall
#define _stdcall
#endif
#endif


//////////////////////////
//                      //
//  Struct Definitions  //
//                      //
//////////////////////////

/* Example Struct */
struct exampledll {
   long int socket;
   long int sum;
   char message[STRUCT_EXAMPLEDLL_BUFFER];
};


//////////////////
//              //
//  Prototypes  //
//              //
//////////////////

   long int _stdcall helloworld(void);
   long int _stdcall example_stringcreate(struct exampledll *);
   long int _stdcall example_stringdestroy(struct exampledll *);
   long int _stdcall example_sum(long int, long int);


#endif
