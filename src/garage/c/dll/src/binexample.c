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
/*  binexample.cpp - C++ Wrapper file */
/*
 * Build:
 *    Microsoft Visual Studio 6.0
 */
#define _EXAMPLES_C_DLL_BINEXAMPLE_CPP
#include "binexample.h"


/////////////
//         //
//  Notes  //
//         //
/////////////


//////////////////////
//                  //
//  Main Statement  //
//                  //
//////////////////////
int main(void) {

   /* Declares local vars */
      long int rc;                   /* return code of last function */
      struct exampledll handle;
      
   /* Calls function */
      rc = helloworld();
      printf("\n");

   /* Adds numbers */
      printf("Calling on DLL for addition...\n");
      rc = example_sum(123, 321);
      printf("123 + 321 = %i\n\n", rc);

   /* Creates String */
      printf("Calling on DLL to create string...\n");
      rc = example_stringcreate(&handle);
      if (rc) {
         printf("There was an error creating the string\n");
         return(1);
      };

   /* Prints String */
      printf("My string is: \"%s\"\n\n", handle.message);

   /* Destroys string */
      printf("Calling on DLL to delete string...\n");
      rc = example_stringdestroy(&handle);
      if (rc) {
         printf("There was an error destroying the string\n");
         return(1);
      };

   /* Prints String */
      //rc = (int) message;
      //printf("Memory Address: %i\n", rc);
      printf("My string is: \"%s\"\n\n", handle.message);
      //printf("Backup: \"%s\"\n\n", backup);

   /* Ends function */
      return(rc);

}
