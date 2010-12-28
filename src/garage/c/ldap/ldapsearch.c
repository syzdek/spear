/*
 * Simple LDAP Search Example v0.1
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
 *    gcc -g -o ldapsearch.o ldapsearch.c -lldap -llber -lresolv
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

int main(int *argc, char **argv) {

   /* Declares Local Vars */
      LDAP		*ldap;
      LDAPMessage	*mesg, *entry;
      BerElement	*ber;
      char		*a, *dn;
      char		**vals;
      int		i;

   /* Connects to LDAP server */
      if ( (ldap = ldap_init(LDAPHOST, 13891)) == NULL) {
         perror("ldap_init");
         return(1);
      };
      if (ldap_simple_bind_s(ldap, LDAPBINDDN, LDAPBINDPW) != LDAP_SUCCESS) {
         ldap_perror(ldap, "ldap_simple_bind_s");
         ldap_unbind(ldap);
         return(1);
      };

   /* Searches for email */
      if ( ldap_search_s(ldap, "o=acsalaska.net", LDAP_SCOPE_SUBTREE,
         "(mail=syzdek@mosquitonet.com)", NULL, 0, &mesg ) != LDAP_SUCCESS ) {
         ldap_perror(ldap, "ldap_search_s");
         if ( mesg == NULL ) {
            ldap_unbind(ldap);
            return(1);
         };
      };

   /* Displays results */
      for (entry = ldap_first_entry(ldap, mesg); entry != NULL; entry = ldap_next_entry(ldap, entry)) {
         if ((dn = ldap_get_dn(ldap, entry)) != NULL) {
            printf( "dn: %s\n", dn );
            ldap_memfree(dn);
         };
         for (a = ldap_first_attribute(ldap, entry, &ber); a != NULL; a = ldap_next_attribute(ldap, entry, ber)) {
            if ((vals = ldap_get_values(ldap, entry, a)) != NULL ) {
               for ( i = 0; vals[i] != NULL; i++ ) {
                  printf( "%s: %s\n", a, vals[i] );
               };
               ldap_value_free( vals );
            };
            ldap_memfree( a );
         };
         if ( ber != NULL ) {
            ber_free( ber, 0 );
         };
         printf( "\n" );
      };
      ldap_msgfree(mesg);

   /* Frees Memory, Unbinds, and exits */
      ldap_unbind(ldap);
      return(0);

};
