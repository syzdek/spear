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
/*  libexample.cpp - C++ Wrapper for Shared Functions */
#define _EXAMPLES_C_DLL_LIBEXAMPLE_C
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
   long int _stdcall helloworld(void) {

      /* Prints Message */
         printf("Good Grief\n");

      /* Ends function */
         return(0);

   }


   /* Creates Example STRING */
   long int _stdcall example_stringcreate(struct exampledll *ptr) {

      /* Declares local vars */
         char *mystring;

      /* Allocates memory */
         mystring = ptr->message;
         if (mystring == NULL ) {
            return(1);
         };

      /* Copies Test Data */
         memcpy(mystring, EXAMPLE_STRING_DATA, EXAMPLE_STRING_SIZE-1);
         mystring[EXAMPLE_STRING_SIZE-1] = '\0';

      /* Ends Function */
         return(0);
   }


   /* Destroys Example STRING */
   long int _stdcall example_stringdestroy(struct exampledll *ptr) {

      /* Declares local vars */
         long int count;

      /* Loops through and clears string */
         for(count = 0; count < STRUCT_EXAMPLEDLL_BUFFER; count++) {
            ptr->message[count] = '\0';
         };
         
      /* Ends function */
         return(0);

   }


   /* Adds two numbers and returns the sum */
   long int _stdcall example_sum(long num1, long num2) {

      /* Declares local vars */
         long sum;

      /* Adds Numbers */
         sum = num1 + num2;

      /* Ends function */
         return(sum);

   }





