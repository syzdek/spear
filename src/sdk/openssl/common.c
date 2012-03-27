/*
 *  Simple Programming Examples And References
 *  Copyright (C) 2012 David M. Syzdek <david@syzdek.net>.
 *
 *  @SYZDEK_BSD_LICENSE_START@
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are
 *  met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of David M. Syzdek nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 *  IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 *  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL BINDLE BINARIES BE LIABLE FOR
 *  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 *  OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 *  SUCH DAMAGE.
 *
 *  @SYZDEK_BSD_LICENSE_END@
 */
/**
 *  @file src/sdk/openssl/common.c common functions for openssl examples
 */
#include "common.h"

///////////////
//           //
//  Headers  //
//           //
///////////////
#pragma mark Headers

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <openssl/x509.h>


/////////////////
//             //
//  Functions  //
//             //
/////////////////
#pragma mark - Functions

// parses ASN1_TIME into struct tm
int parse_asn1_time(const ASN1_TIME * atp, struct tm * tsp)
{
   const char * str;
   unsigned     offset;
   int          val;
   char         buff[5];

   if ((atp->type != V_ASN1_GENERALIZEDTIME) && (atp->type != V_ASN1_UTCTIME))
      return(1);

   memset(tsp, 0, sizeof(struct tm));
   str    = (const char *)atp->data;
   offset = 0;

   // Date format:
   //    YYMMDDHHMMSSZ   - before year 2050
   //    YYYYMMDDHHMMSSZ - after year 2049

   // parses year
   switch(atp->type)
   {
      case V_ASN1_GENERALIZEDTIME:
      sscanf(&str[offset], "%04i", &val);
      val -= 1900;
      tsp->tm_year  = val;
      offset += 4;
      break;

      case V_ASN1_UTCTIME:
      sscanf(&str[offset], "%02i", &val);
      if (val < 50)
         val += 2000 - 1900;
      tsp->tm_year  = val;
      offset += 2;
      break;

      default:
      return(1);
   };

   // parses month
   sscanf(&str[offset], "%02s", buff);
   buff[2]       = '\0';
   val           = strtol(buff, NULL, 10) - 1;
   tsp->tm_mon   = val;
   offset       += 2;

   // parses day of month
   sscanf(&str[offset], "%02s", buff);
   buff[2]       = '\0';
   val           = strtol(buff, NULL, 10);
   tsp->tm_mday  = val;
   offset       += 2;

   // parses hour
   sscanf(&str[offset], "%02s", buff);
   buff[2]       = '\0';
   val           = strtol(buff, NULL, 10);
   tsp->tm_hour  = val;
   offset       += 2;

   // parses minute
   sscanf(&str[offset], "%02s", buff);
   buff[2]       = '\0';
   val           = strtol(buff, NULL, 10);
   tsp->tm_min   = val;
   offset       += 2;

   // parses second
   sscanf(&str[offset], "%02s", buff);
   buff[2]       = '\0';
   val           = strtol(buff, NULL, 10);
   tsp->tm_sec   = val;
   offset       += 2;

   return(0);
}


// parses DN into componets
void parse_dn(char * dn, MY_X509_NAME * namep)
{
   char                * bol;
   char                * eol;

   memset(namep, 0, sizeof(MY_X509_NAME));
   bol = &dn[1];
   while((bol))
   {
      eol    = index(bol, '/');
      if ((eol))
         eol[0] = '\0';
      if      (!(strncasecmp(bol, "C=", 2)))
         namep->c = &bol[2];
      else if (!(strncasecmp(bol, "st=", 3)))
         namep->st = &bol[3];
      else if (!(strncasecmp(bol, "l=", 2)))
         namep->l = &bol[2];
      else if (!(strncasecmp(bol, "o=", 2)))
         namep->o = &bol[2];
      else if (!(strncasecmp(bol, "ou=", 3)))
         namep->ou = &bol[3];
      else if (!(strncasecmp(bol, "cn=", 3)))
         namep->cn = &bol[3];
      else if (!(strncasecmp(bol, "emailAddress=", 13)))
         namep->email = &bol[13];
      else if (!(strncasecmp(bol, "description=", 13)))
         namep->description = &bol[13];
      bol    = ((eol)) ? &eol[1] : NULL;
   };
   return;
}


// prints dn
void print_dn(const char * prefix, MY_X509_NAME * namep)
{
   if (!(prefix))
      prefix = "";

   if ((namep->cn))
      printf("%sCommon Name:  %s\n", prefix, namep->cn);
   if ((namep->o))
      printf("%sOrganization: %s\n", prefix, namep->o);
   if ((namep->ou))
      printf("%sDepartment:   %s\n", prefix, namep->ou);
   if ((namep->l))
      printf("%sCity:         %s\n", prefix, namep->l);
   if ((namep->st))
      printf("%sState:        %s\n", prefix, namep->st);
   if ((namep->c))
      printf("%sCountry:      %s\n", prefix, namep->c);
   if ((namep->email))
      printf("%sE-mail:       %s\n", prefix, namep->email);
   if ((namep->description))
      printf("%sDescription:  %s\n", prefix, namep->description);

   return;
}


/* end of source */
