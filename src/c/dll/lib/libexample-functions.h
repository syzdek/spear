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
#ifdef WIN32
extern "C" __declspec(dllexport) long helloworld(void) {
#else
long helloworld(void) {
#endif

      /* Prints Message */
         printf("Good Grief\n");

      /* Ends function */
         return(0);

}


/* Creates Example STRING */
#ifdef WIN32
extern "C" __declspec(dllexport) char *example_stringcreate(void) {
#else
char *example_stringcreate(void) {
#endif

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
#ifdef WIN32
extern "C" __declspec(dllexport) long example_stringdestroy(char **ptr) {
#else
long example_stringdestroy(char **ptr) {
#endif

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
#ifdef WIN32
extern "C" __declspec(dllexport) long example_sum(int num1, int num2) {
#else
long example_sum(int num1, int num2) {
#endif

   /* Declares local vars */
      long sum;

   /* Adds Numbers */
      sum = num1 + num2;

   /* Ends function */
      return(sum);

}


// Ends Prepocessor File
#endif