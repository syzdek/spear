/*
 *  $Id: $
 */
/*
 *  Syzdek's Silly Calculators
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
 *  loan.m - computes loan information
 */
/*
 *  Simple Build:
 *     gcc -Wall -c LoanCalculator.c
 *     gcc -Wall -c SSCObject.c
 *     gcc -Wall -c loan.c
 *     gcc -Wall -o loan loan.o SSCObject.o LoanCalculator.o
 *
 *  Libtool Build:
 *     libtool --mode=compile gcc -Wall -g -O2 -c loan.c
 *     libtool --mode=compile gcc -Wall -g -O2 -c SSCObject.c
 *     libtool --mode=compile gcc -Wall -g -O2 -c LoanCalculator.c
 *     libtool --mode=link    gcc -Wall -g -O2 -o loan \
 *             loan.o SSCObject.o LoanCalculator.o -lobjc
 *
 *  Libtool Install:
 *     libtool --mode=install install -c romannum /usr/local/bin/romannum
 *
 *  Libtool Clean:
 *     libtool --mode=clean rm -f romannum.lo roman_charts.lo romannum
 */
#define _SSC_SRC_LOAN_M 1

///////////////
//           //
//  Headers  //
//           //
///////////////

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <objc/Object.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "common.h"
#include "LoanCalculator.h"

//////////////////
//              //
//  Prototypes  //
//              //
//////////////////

/* main statement */
int main(int argc, char * argv[]);

/* displays usage */
void my_usage(void);

/* displays version */
void my_version(void);


/////////////////
//             //
//  Functions  //
//             //
/////////////////

/* main statement */
int main(int argc, char * argv[])
{
   int              c;
   int              idx;
   float            payment;
   float            principal;
   LoanCalculator * loan;

   static char   shortopt[] = "I:N:P:p:hV";
   static struct option longopt[] =
   {
      {"help",          no_argument, 0, 'h'},
      {"verbose",       no_argument, 0, 'v'},
      {"version",       no_argument, 0, 'V'},
      {NULL,            0,           0, 0  }
   };

   idx       = 0;
   payment   = 0;
   principal = 0;
   loan      = [[LoanCalculator alloc] init];

   while((c = getopt_long(argc, argv, shortopt, longopt, &idx)) != -1)
   {
      switch(c)
      {
         case -1:	/* no more arguments */
         case 0:	/* long option toggles */
            break;
         case 'h':
            my_usage();
            [loan release];
            return(0);
         case 'I':
            [loan setApr:strtod(optarg, NULL)];
            break;
         case 'N':
            [loan setPaymentCount:strtol(optarg, NULL, 10)];
            break;
         case 'P':
            principal = strtod(optarg, NULL);
            break;
         case 'p':
            payment = strtod(optarg, NULL);
            break;
         case 'V':
            my_version();
            [loan release];
            return(0);
         case '?':
            fprintf(stderr, "Try `%s --help' for more information.\n", PROGRAM_NAME);
            [loan release];
            return(0);
         default:
            fprintf(stderr, "%s: unrecognized option `--%c'\n", PROGRAM_NAME, c);
            fprintf(stderr, "Try `%s --help' for more information.\n", PROGRAM_NAME);
            [loan release];
            return(0);
      };
   };

   if (payment)
      [loan setPaymentAmount:payment];
   else if (principal)
      [loan setPrincipal:principal];

   printf("APR:                %10.3f %%\n", [loan apr]);
   printf("number of payments:  %11i\n",    [loan paymentCount]);
   printf("payment amount:     $%11.2f\n",  [loan paymentAmount]);
   printf("principal:          $%11.2f\n",  [loan principal]);
   printf("interest paid:      $%11.2f\n",  [loan interestPaid]);
   printf("total cost:         $%11.2f\n",  [loan totalCost]);

   [loan release];

   return(0);
}


/* displays usage */
void my_usage(void)
{
   printf("Usage: %s [OPTIONS]\n", PROGRAM_NAME);
   printf("  -I apr                    annual percentage rate of loan\n");
   printf("  -N N                      total number of payments for entire loan\n");
   printf("  -P PV                     principal of loan\n");
   printf("  -p PMT                    payment per period\n");
   printf("  -h, --help                print this help and exit\n");
   printf("  -V, --version             print version number and exit\n");
   printf("\n");
   printf("Report bugs to <%s>.\n", PACKAGE_BUGREPORT);
   return;
}


/* displays version */
void my_version(void)
{
   printf("%s (%s) %s\n", PROGRAM_NAME, PACKAGE_NAME, PACKAGE_VERSION);
   printf("Written by David M. Syzdek.\n");
   printf("\n");
   printf("%s\n", PACKAGE_COPYRIGHT);
   printf("This is free software; see the source for copying conditions.  There is NO\n");
   printf("warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n");
   return;
}

/* end of source file */
