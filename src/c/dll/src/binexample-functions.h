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

   /* Calls function */
      rc = helloworld();

   /* Ends function */
      return(rc);

}
