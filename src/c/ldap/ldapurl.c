/*
 * Simple LDAP URL Example v0.1
 * $Source$
 * $Revision$
 * $Date$
 * $Author$
 */
/*
 * ldapsearch.c - simple ldap search
 */
/*
 * Software used in development:
 *    Sun Solaris 5.9
 *    Linux 2.4.21
 *    OpenLDAP 2.1.17
 *    GCC 2.95.3
 */
/*
 * Related Links:
 *    http://www.openldap.org
 */
/*
 * Build:
 *    gcc -g -o ldapurl.o ldapurl.c -lldap -llber -lresolv
 */

/////////////
//         //
// Headers //
//         //
/////////////

   #include <stdio.h>
   #include <stdlib.h>
   #include <string.h>
   #include <time.h>
   #include <ldap.h>
   #include "ldapconfig.h"

///////////////////
//               //
// Main Function //
//               //
///////////////////

int main(int argc, char **argv) {

   /* Declares Local Vars */
      LDAPURLDesc **ludpp;
      int rc;
      int count;
      unsigned int var;

   /* Checks for CMD args */
      if (argc != 2) {
         fprintf(stderr, "Usage: %s ldap://hostport/dn[?attrs[?scope[?filter[?exts]]]]\n", argv[0]);
         return(1);
      };

   /* Verifies that the URL is an LDAP URL */
      if (ldap_is_ldap_url(argv[1]) == 0) {
         fprintf(stderr, "Invalid LDAP URL\n");
         return(1);
      };

   /* Parses the LDAP URL */
      rc = ldap_url_parse(argv[1], ludpp);
      if (rc != 0) {
         fprintf(stderr, "Unable to parse LDAP URL\n");
         return(1);
      };

   /* Prints data from LDAP URL */
      printf("LDAP Scheme:\t%s\n", ludpp[0]->lud_scheme);
      printf("LDAP Host:\t%s\n", ludpp[0]->lud_host);
      printf("LDAP Port:\t%i\n", ludpp[0]->lud_port);
      printf("LDAP Scope:\t%i\n", ludpp[0]->lud_scope);
      printf("LDAP Base DN:\t%s\n", ludpp[0]->lud_dn);
      printf("LDAP Filter:\t%s\n", ludpp[0]->lud_filter);
      if (ludpp[0]->lud_attrs != NULL) {
         printf("LDAP Attributes:\n");
         for(count = 0; ludpp[0]->lud_attrs[count] != NULL; count++)
            printf("\t\t%s\n", ludpp[0]->lud_attrs[count]);
      };
      if (ludpp[0]->lud_exts != NULL) {
         printf("LDAP Extensions:\n");
         for(count = 0; ludpp[0]->lud_exts[count] != NULL; count++)
            printf("\t\t%s\n", ludpp[0]->lud_exts[count]);
      };

   /* Frees ludpp */
      ldap_free_urldesc(ludpp[0]);

   /* Ends program */
      return(0);

};
