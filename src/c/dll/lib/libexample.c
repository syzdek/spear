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
   long int helloworld(void) {

      /* Prints Message */
         printf("Good Grief\n");

      /* Ends function */
         return(0);

   }


   /* Creates Example STRING */
   char *example_stringcreate(void) {

      /* Declares local vars */
         char *mystring;

      /* Allocates memory */
         mystring = (char *) malloc(EXAMPLE_STRING_SIZE);
         if (mystring == NULL ) {
            return(NULL);
         };

      /* Copies Test Data */
         memcpy(mystring, EXAMPLE_STRING_DATA, EXAMPLE_STRING_SIZE-1);
         mystring[EXAMPLE_STRING_SIZE-1] = '\0';

      /* Ends Function */
         return(mystring);
   }


   /* Destroys Example STRING */
   long int example_stringdestroy(char **ptr) {

      /* Verifies String hasn't already been cleared */
      if (*ptr != NULL) {
         free(*ptr);
         *ptr = NULL;
         return(0);
      } else {
         return(1);
      };

   }


   /* Adds two numbers and returns the sum */
   long int example_sum(int num1, int num2) {

      /* Declares local vars */
         long sum;

      /* Adds Numbers */
         sum = num1 + num2;

      /* Ends function */
         return(sum);

   }




