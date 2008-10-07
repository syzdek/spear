/*
 *  $Id: $
 */
/*
 *  Simple Objective-C Object Experiment
 *  Copyright (c) 2008 David M. Syzdek <david@syzdek.net>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */
/*
 *  main.m - main program
 */

///////////////
//           //
//  Headers  //
//           //
///////////////

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "cBindings.h"

//////////////////
//              //
//  Prototypes  //
//              //
//////////////////

int main(int argc, char * argv[]);

/////////////////
//             //
//  Functions  //
//             //
/////////////////

int main(int argc, char * argv[])
{
   void * ptr;
   int    i;

   i = 0;
   if (argc > 1)
      i = atol(argv[1]);


   ptr = init();
   setNum1(ptr, 5);
   printf("number: %i\n", num1(ptr));

   sleep(i);
   release(ptr);
   ptr = NULL;

   sleep(i);

   return(0);
}

/* end of source file */
