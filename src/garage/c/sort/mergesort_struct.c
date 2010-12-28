/*
 *  LDAP Utilities
 *  Copyright (c) 2008 David M. Syzdek <david@syzdek.net>.
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
/**
 *  @file src/c/sort/mergesort_struct.c Example of mergesort() using array of 
 *                                      structs
 */
/*
 *  Simple Build:
 *     export CFLAGS='-Wall -I../include'
 *     gcc ${CFLAGS} -c mergesort_struct.c
 *     gcc ${CFLAGS} -o mergesort_struct mergesort_struct.o
 *
 *  Libtool Build:
 *     export CFLAGS='-Wall -I../include'
 *     libtool --mode=compile --tag=CC gcc ${CFLAGS} -c mergesort_struct.c
 *     libtool --mode=link    --tag=CC gcc ${CFLAGS} -o mergesort_struct \
 *             mergesort_struct.lo
 *
 *  Libtool Clean:
 *     libtool --mode=clean rm -f mergesort_struct.lo mergesort_struct
 */


///////////////
//           //
//  Headers  //
//           //
///////////////

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>


/////////////////
//             //
//  Datatypes  //
//             //
/////////////////

/// super secret daata struct
struct my_data
{
   char     str[64];
   int      num;
};


//////////////////
//              //
//  Prototypes  //
//              //
//////////////////

// entry point to program
int main(void);

// custom comparision function used for sorting
int my_sort(const void * ptr1, const void * ptr2);


/////////////////
//             //
//  Functions  //
//             //
/////////////////

/// entry point to program
int main(void)
{
   unsigned         u;
   size_t           len;
   struct my_data   data[] =
   {
      {"hola",         31},
      {"ciao",         83},
      {"hello",        11},
      {"hallo",         4},
      {"bonjour",      41},
      {"salutations",  73}
   };

   len = sizeof(data)/sizeof(struct my_data);

   printf("Unsorted:\n");
   for(u = 0; u < len; u++)
      printf("%5i %s\n", data[u].num, data[u].str);
   printf("\n");

   mergesort(data, len, sizeof(struct my_data), my_sort);

   printf("Sorted:\n");
   for(u = 0; u < len; u++)
      printf("%5i %s\n", data[u].num, data[u].str);

   return(0);
}


/// custom comparision function used for sorting
/// @param[in] ptr1   pointer to first data item to compare
/// @param[in] ptr2   pointer to second data item to compare
int my_sort(const void * ptr1, const void * ptr2)
{
   int                    res;

   if ( (!(ptr1)) && (!(ptr2)) )
      return(0);
   if (!(ptr1))
      return(-1);
   if (!(ptr2))
      return(1);
   if ( ((struct my_data *)ptr1)->num < ((struct my_data *)ptr2)->num )
      return(-1);
   if ( ((struct my_data *)ptr1)->num > ((struct my_data *)ptr2)->num )
      return(1);
   if ((res = strcasecmp(((struct my_data *)ptr1)->str, ((struct my_data *)ptr2)->str)))
      return(res);
   return(strcmp(((struct my_data *)ptr1)->str, ((struct my_data *)ptr2)->str));
}

/* end of source */
