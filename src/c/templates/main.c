/*
 * Project Name
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
/*  main.c - Description of file */
/*
 * Build:
 *    gcc -g -o main main.c
 */
#define _PROJECT_MAIN_C

///////////////
//           //
//  Headers  //
//           //
///////////////

#include <stdio.h>		/* standard I/O functions */
#include "object.h"		/* shared functions       */


//////////////////
//              //
//  Prototypes  //
//              //
//////////////////

   int main(void);		/* Starts program */


//////////////////////
//                  //
//  Main Statement  //
//                  //
//////////////////////
int main(void) {

   /* Declares local vars */
      int rc;			/* return code of last function */

   /* Calls function */
      rc = helloworld();

   /* Ends function */
      return(rc);

}

