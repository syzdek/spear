/*
 * Example DLL
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
/*  example.c - Header file */
#define _EXAMPLE_C_DLL_EXAMPLE_CPP
#include "example.h"


/////////////////
//             //
//  Functions  //
//             //
/////////////////

   /* Adds two numbers and returns the Sum */
   extern "C" int PASCAL EXPORT exampleSum(int num1, int num2) {

      /* Declares local vars */
         int sum;

      /* Adds two numbers together */
         sum = num1 + num2;

      /* Ends function */
         return(sum);
   }
         

