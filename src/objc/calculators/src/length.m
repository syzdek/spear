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
 *  testLength.m - tests length calculations
 */
/*
 *  Simple Build:
 *     gcc -Wall -c LengthObject.m
 *     gcc -Wall -c SSCObject.m
 *     gcc -Wall -c testLength.m
 *     gcc -Wall -o testLength testLength.o SSCObject.o LoanCalculator.o
 *
 *  Libtool Build:
 *     libtool --mode=compile gcc -Wall -g -O2 -c testLength.m
 *     libtool --mode=compile gcc -Wall -g -O2 -c SSCObject.c
 *     libtool --mode=compile gcc -Wall -g -O2 -c LengthObject.c
 *     libtool --mode=link    gcc -Wall -g -O2 -o testLength \
 *             testLength.o SSCObject.o LengthObject.o -lobjc
 */
#define _SSC_SRC_TEST_LENGTH_M 1

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
#include "LengthObject.h"

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
   int            c;
   int            idx;
   LengthObject * length;

   static char   shortopt[] = "hVT:I:F:Y:f:M:L:A:C:N:l:P:c:";
   static struct option longopt[] =
   {
      {"help",		no_argument,		0, 'h'},
      {"version",	no_argument,		0, 'V'},
      // imperial system
      {"thou",		required_argument,	0, 'T'},
      {"inch",		required_argument,	0, 'I'},
      {"foot",		required_argument,	0, 'F'},
      {"yard",		required_argument,	0, 'Y'},
      {"furlong",	required_argument,	0, 'f'},
      {"mile",		required_argument,	0, 'M'},
      {"league",	required_argument,	0, 'L'},
      {"fathom",	required_argument,	0, 'A'},
      {"cable",		required_argument,	0, 'C'},
      {"nautical",	required_argument,	0, 'N'},
      {"link",		required_argument,	0, 'l'},
      {"pole",		required_argument,	0, 'P'},
      {"chain",		required_argument,	0, 'c'},
      {NULL,		0,			0, 0  }
   };

   idx    = 0;
   length = [[LengthObject alloc] init];
   [length setMeter:100];

   while((c = getopt_long(argc, argv, shortopt, longopt, &idx)) != -1)
   {
      switch(c)
      {
         case -1:       /* no more arguments */
         case 0:        /* long option toggles */
            break;
         case 'h':
            my_usage();
            [length release];
            return(0);
         case 'V':
            my_version();
            [length release];
            return(0);

         /* imperial system */
         case 'T':
            [length setThou:strtod(optarg, NULL)];
            break;
         case 'I':
            [length setInch:strtod(optarg, NULL)];
            break;
         case 'F':
            [length setFoot:strtod(optarg, NULL)];
            break;
         case 'Y':
            [length setYard:strtod(optarg, NULL)];
            break;
         case 'f':
            [length setFurlong:strtod(optarg, NULL)];
            break;
         case 'M':
            [length setMile:strtod(optarg, NULL)];
            break;
         case 'L':
            [length setLeague:strtod(optarg, NULL)];
            break;
         case 'A':
            [length setFathom:strtod(optarg, NULL)];
            break;
         case 'C':
            [length setCable:strtod(optarg, NULL)];
            break;
         case 'N':
            [length setNauticalMile:strtod(optarg, NULL)];
            break;
         case 'l':
            [length setLink:strtod(optarg, NULL)];
            break;
         case 'P':
            [length setPole:strtod(optarg, NULL)];
            break;
         case 'c':
            [length setChain:strtod(optarg, NULL)];
            break;

         case '?':
            fprintf(stderr, "Try `%s --help' for more information.\n", PROGRAM_NAME);
            [length release];
            return(0);
         default:
            fprintf(stderr, "%s: unrecognized option `--%c'\n", PROGRAM_NAME, c);
            fprintf(stderr, "Try `%s --help' for more information.\n", PROGRAM_NAME);
            [length release];
            return(0);
      };
   };

   printf("Imperial Units:\n");
   printf("   thou/mil:        %30.8f\n",  [length thou]);
   printf("   inch:            %30.8f\n",  [length inch]);
   printf("   foot:            %30.8f\n",  [length foot]);
   printf("   yard:            %30.8f\n",  [length yard]);
   printf("   furlong:         %30.8f\n",  [length furlong]);
   printf("   mile:            %30.8f\n",  [length mile]);
   printf("   league:          %30.8f\n",  [length league]);
   printf("\n");

   printf("Imperial Units (maritime):\n");
   printf("   fathom:          %30.8f\n",  [length fathom]);
   printf("   cable:           %30.8f\n",  [length cable]);
   printf("   mile (nautical): %30.8f\n",  [length nauticalMile]);
   printf("\n");

   printf("Imperial Units (survey):\n");
   printf("   link:            %30.8f\n",  [length link]);
   printf("   pole/rod/perch:  %30.8f\n",  [length pole]);
   printf("   chain:           %30.8f\n",  [length chain]);
   printf("\n");

   printf("Miscellaneous Units:\n");
   printf("   digit:           %30.8f\n",  [length digit]);
   printf("   palm:            %30.8f\n",  [length palm]);
   printf("   hand:            %30.8f\n",  [length hand]);
   printf("   cubit:           %30.8f\n",  [length cubit]);
   printf("\n");

   printf("Metric Units\n");
   printf("   picometer:       %30.8f\n",  [length picometer]);
   printf("   nanometer:       %30.8f\n",  [length nanometer]);
   printf("   micrometer:      %30.8f\n",  [length micrometer]);
   printf("   millimeter:      %30.8f\n",  [length millimeter]);
   printf("   centimeter:      %30.8f\n",  [length centimeter]);
   printf("   decimeter:       %30.8f\n",  [length decimeter]);
   printf("   meters:          %30.8f\n",  [length meter]);
   printf("   decameter:       %30.8f\n",  [length decameter]);
   printf("   hectometer:      %30.8f\n",  [length hectometer]);
   printf("   kilometer:       %30.8f\n",  [length kilometer]);
   printf("   megameter:       %30.8f\n",  [length megameter]);
   printf("   gigameter:       %30.8f\n",  [length gigameter]);
   printf("   terameter:       %30.8f\n",  [length terameter]);

   [length release];

   return(0);
}


/* displays usage */
void my_usage(void)
{
   printf("Usage: %s [OPTIONS]\n", PROGRAM_NAME);
   printf("Imperial Options:\n");
   printf("  --thou=units              calculates from thous (also known as mil)\n");
   printf("  --inch=units              calculates from inches\n");
   printf("  --foot=units              calculates from feet\n");
   printf("  --yard=units              calculates from yards\n");
   printf("  --furlong=units           calculates from furlongs\n");
   printf("  --mile=units              calculates from miles\n");
   printf("  --league=units            calculates from leagues\n");
   printf("  --fathom=units            calculates from fathoms\n");
   printf("  --cable=units             calculates from cables\n");
   printf("  --nautical=units          calculates from nautical miles\n");
   printf("  --pole=units              calculates from poles (also known as rod or perch\n");
   printf("  --chain=units             calculates from chains\n");
   printf("Miscellaneous Options:\n");
   printf("  --digit=units             calculates from digits\n");
   printf("  --palm=units              calculates from palms\n");
   printf("  --hand=units              calculates from hands\n");
   printf("  --cubit=units             calculates from cubits\n");
   printf("Metric Options:\n");
   printf("  --picometer=units         calculates from picometers\n");
   printf("  --nanometer=units         calculates from nanometers\n");
   printf("  --micrometer=units        calculates from micrometers\n");
   printf("  --millimeter=units        calculates from millimeters\n");
   printf("  --centimeter=units        calculates from centimeters\n");
   printf("  --decimeter=units         calculates from decimeters\n");
   printf("  --meter=units             calculates from meters\n");
   printf("  --decameter=units         calculates from decameters\n");
   printf("  --hectometer=units        calculates from hectometers\n");
   printf("  --kilometer=units         calculates from kilometers\n");
   printf("  --megameter=units         calculates from megameters\n");
   printf("  --gigameter=units         calculates from gigameters\n");
   printf("  --terameter=units         calculates from terameters\n");
   printf("Common Options:\n");
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
