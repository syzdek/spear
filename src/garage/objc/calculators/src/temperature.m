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
 *  temperature.m - tests temperature calculations
 */
/*
 *  Simple Build:
 *     gcc -Wall -c TemperatureObject.m
 *     gcc -Wall -c SSCObject.m
 *     gcc -Wall -c temperature.m
 *     gcc -Wall -o temperature temperature.o SSCObject.o TemperatureObject.o
 *
 *  Libtool Build:
 *     libtool --mode=compile gcc -Wall -g -O2 -c temperature.m
 *     libtool --mode=compile gcc -Wall -g -O2 -c SSCObject.c
 *     libtool --mode=compile gcc -Wall -g -O2 -c TemperatureObject.c
 *     libtool --mode=link    gcc -Wall -g -O2 -o temperature \
 *             temperature.o SSCObject.o TemperatureObject.o -lobjc
 */
#define _SSC_SRC_TEMPERATURE_M 1

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
#include <getopt.h>

#include "common.h"
#include "TemperatureObject.h"

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
   int                 c;
   int                 idx;
   TemperatureObject * temperature;

   static char   shortopt[] = "hVC:F:K:R:";
   static struct option longopt[] =
   {
      {"help",		no_argument,		0, 'h'},
      {"version",	no_argument,		0, 'V'},
      {"celsius",	required_argument,	0, 'C'},
      {"fahrenheit",	required_argument,	0, 'F'},
      {"kelvin",	required_argument,	0, 'K'},
      {"rankine",	required_argument,	0, 'R'},
      {NULL,		0,			0, 0  }
   };

   idx    = 0;
   temperature = [[TemperatureObject alloc] init];

   while((c = getopt_long(argc, argv, shortopt, longopt, &idx)) != -1)
   {
      switch(c)
      {
         case -1:       /* no more arguments */
         case 0:        /* long option toggles */
            break;
         case 'h':
            my_usage();
            [temperature release];
            return(0);
         case 'V':
            my_version();
            [temperature release];
            return(0);

         case 'C':
            [temperature setCelsius:strtod(optarg, NULL)];
            break;
         case 'F':
            [temperature setFahrenheit:strtod(optarg, NULL)];
            break;
         case 'K':
            [temperature setKelvin:strtod(optarg, NULL)];
            break;
         case 'R':
            [temperature setRankine:strtod(optarg, NULL)];
            break;

         case '?':
            fprintf(stderr, "Try `%s --help' for more information.\n", PROGRAM_NAME);
            [temperature release];
            return(0);
         default:
            fprintf(stderr, "%s: unrecognized option `--%c'\n", PROGRAM_NAME, c);
            fprintf(stderr, "Try `%s --help' for more information.\n", PROGRAM_NAME);
            [temperature release];
            return(0);
      };
   };

   printf("Celsius:    %10.2f\n",  [temperature celsius]);
   printf("Fahrenheit: %10.2f\n",  [temperature fahrenheit]);
   printf("Kelvin:     %10.2f\n",  [temperature kelvin]);
   printf("Rankine:    %10.2f\n",  [temperature rankine]);

   [temperature release];

   return(0);
}


/* displays usage */
void my_usage(void)
{
   printf("Usage: %s [OPTIONS]\n", PROGRAM_NAME);
   printf("  -C, --celsius=NUMBER       calculates from kilometers\n");
   printf("  -F, --fahrenheit=NUMBER    calculates from megameters\n");
   printf("  -h, --help                 print this help and exit\n");
   printf("  -K, --kelvin=NUMBER        calculates from gigameters\n");
   printf("  -R, --rankine=NUMBER       calculates from terameters\n");
   printf("  -V, --version              print version number and exit\n");
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
