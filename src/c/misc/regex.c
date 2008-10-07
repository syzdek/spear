/*
 *  $Id: $
 */
/*
 *  Syzdek Coding Tools
 *  Copyright (c) 2008 David M. Syzdek <david@syzdek.net>.
 *
 *  @SYZDEK_LICENSE_HEADER_START@
 *  
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License Version 2 as
 *  published by the Free Software Foundation.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 *  
 *  @SYZDEK_LICENSE_HEADER_END@
 */
/**
 *  @file src/posixregex.c simple POSIX regex testing utility/example
 */
#define _SCT_SRC_POSIXREGEX_C 1

/////////////
//         //
//  Notes  //
//         //
/////////////

/*
 *  POSIX        ASCII           Description
 *  [:alnum:]    [A-Za-z0-9]     Alphanumeric characters
 *  [:alpha:]    [A-Za-z]        Alphabetic characters
 *  [:blank:]    [ \t]           Space and tab
 *  [:cntrl:]    [\x00-\x1F\x7F] Control characters
 *  [:digit:]    [0-9]           Digits
 *  [:graph:]    [\x21-\x7E]     Visible characters
 *  [:lower:]    [a-z]           Lowercase letters
 *  [:print:]    [\x20-\x7E]     Visible characters and spaces
 *  [:space:]    [ \t\r\n\v\f]   Whitespace characters
 *  [:upper:]    [A-Z]           Uppercase letters
 *  [:xdigit:]   [A-Fa-f0-9]     Hexadecimal digits
 *  [:punct:]    [-!"#$%&'()*+,./:;<=>?@[\\\]_`{|}~]   Punctuation characters
 */

//   Example Uses:
//      posixregex '^([[:alpha:]]+)://(([[:alnum:]]+)(:([[:alnum:]]+)){0,1}@){0,1}([-.a-z]+)(:([[:digit:]]+))*/([-/[:alnum:]]*)(\?(.*)){0,1}$'  http://jdoe:password@www.foo.org:123/path/to/file?query_string
//      posixregex '\$([[:digit:]]+)\.([[:digit:]]{2,2})' 'Your change is $7.45.'

///////////////////
//               //
//  Definitions  //
//               //
///////////////////

#undef BUFFER_SIZE
#define BUFFER_SIZE 1024

#undef MAX_MATCHES
#define MAX_MATCHES 128


///////////////
//           //
//  Headers  //
//           //
///////////////

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <regex.h>
#include <stdio.h>
#include <string.h>


//////////////////
//              //
//  Prototypes  //
//              //
//////////////////

/* main statement */
int main(int, char **);

/////////////////
//             //
//  Functions  //
//             //
/////////////////

/* main statement */
int main(int argc, char *argv[])
{
   /* declare local vars */
   int        x;
   int        y;
   int        err;
   int        strlen;
   char       arg[BUFFER_SIZE];
   char       msg[BUFFER_SIZE];
   char       str[BUFFER_SIZE];
   regex_t    regex;
   regmatch_t matches[MAX_MATCHES];

   /* check command line options */
   if (argc < 2)
   {
      printf("usage: %s regex str1 str2 ... strN\n", argv[0]);
      return(1);
   };

   /* compile regulare expression for later use */
   printf("regex: %s\n", argv[1]);
   if ((err = regcomp(&regex, argv[1], REG_EXTENDED|REG_ICASE)))
   {
      regerror(err, &regex, msg, BUFFER_SIZE-1);
      printf("%s\n", msg);
      return(1);
   };

   /*
    *  Loops through command line arguments and tests the compiled expressions
    *  against each argument.
    */
   for (x = 2; x < argc; x++)
   {
      /* copies string into buffer and prints to screen */
      strncpy(arg, argv[x], BUFFER_SIZE-1);
      printf("%3i: %s  ==> ", x, arg);

      /* tests the buffer against the regular expression */
      if ((err = regexec(&regex, arg, MAX_MATCHES, matches, 0)))
      {
         printf("not found\n");
      } else {
         printf(" found\n");
         strlen = 1;

         /* copies sub matches in buffer string */
         for(y = 0; ((y < MAX_MATCHES) && (matches[y].rm_eo > -1)); y++)
         {
            memset(str, 0, BUFFER_SIZE);
            //printf("   submatch: %2i   start: %3i   end: %3i\n", y, (int)matches[y].rm_so, (int)matches[y].rm_eo);
            if ((strlen = matches[y].rm_eo - matches[y].rm_so))
            {
               strncpy(str, &arg[matches[y].rm_so], strlen);
               printf("   submatch %i: %s\n", y, str);
            } else if (matches[y].rm_eo > 0) {
               printf("   submatch %i:\n", y);
            };
         };

         /* makes the output a little neater */
         printf("\n");
      };
   };

   /* free regular expression */
   regfree(&regex);

   /* end function */
   return(0);
}

/* end of source file */
