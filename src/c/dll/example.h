/*
 * Example DLL
 * $Source$
 * $Revision$
 * $Date$
 * $Author$
 */
/*  example.h - Header file for example DLL */
#ifndef _EXAMPLE_C_DLL_EXAMPLE_H
#define _EXAMPLE_C_DLL_EXAMPLE_H

/////////////
//         //
//  Notes  //
//         //
/////////////


///////////////////
//               //
//  Definitions  //
//               //
///////////////////


///////////////
//           //
//  Headers  //
//           //
///////////////

#include <stdio.h>


//////////////////
//              //
//  Prototypes  //
//              //
//////////////////

   extern "C" char PASCAL EXPORT *exampleString();			/*  Returns a pointer to a string          */
   extern "C" int PASCAL EXPORT exampleSum(int, int);		/*  Adds two numbers and returns the Sums  */	

#endif