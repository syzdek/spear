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
/*  binexamples-functions.h - Shared Functions */
/*
 * Build:
 *    Microsoft Visual Studio 6.0
 */
#define _EXAMPLE_C_DLL_BINEXAMPLE_FUNCTIONS_H
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
      int rc;                   /* return code of last function */
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
      message = example_stringcreate();
      if (message == NULL) {
         fprintf(stderr, "There was an error creating the string\n");
         return(1);
      };
      backup = message;

   /* Prints String */
      rc = (int) message;
      printf("Memory Address: %i\n", rc);
      printf("My string is: \"%s\"\n\n", message);

   /* Destroys string */
      printf("Calling on DLL to delete string...\n");
      rc = example_stringdestroy(&message);
      if (rc) {
         fprintf(stderr, "There was an error destroying the string\n");
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
