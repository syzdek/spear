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
      char *message;
      char *backup;
      
   /* Calls function */
      rc = helloworld();
      printf("\n");

   /* Adds numbers */
      printf("Calling on DLL for addition...\n");
      rc = example_sum(123, 321);
      printf("123 + 321 = %i\n\n", rc);

   /* Grabs String */
      printf("Calling on DLL to create string...\n");
      message = (char *) example_stringcreate();
      if (message == NULL) {
         printf("There was an error creating the string\n");
         return(1);
      };
      backup = message;

   /* Prints String */
      rc = (long int) message;
      printf("Memory Address: %i\n", rc);
      rc = (long int) &message;
      printf("Pointer Address: %i\n", rc);
      printf("My string is: \"%s\"\n\n", message);

   /* Destroys string */
      printf("Calling on DLL to delete string...\n");
      rc = example_stringdestroy((long int) &message);
      if (rc) {
         printf("There was an error destroying the string\n");
         return(1);
      };

   /* Prints String */
      rc = (int) message;
      printf("Memory Address: %i\n", rc);
    
      printf("My string is: \"%s\"\n\n", message);
      printf("Backup: \"%s\"\n\n", backup);

   /* Ends function */
      return(rc);

}
