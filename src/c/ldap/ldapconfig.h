/*
 * Simple LDAP Config v0.1
 * $Source$
 * $Revision$
 * $Date$
 * $Author$
 */
/*
 * ldapconfig.h - simple ldap config
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
 *    N/A
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


/////////////
//         //
// Configs //
//         //
/////////////

   /* LDAP Host configs */
      #define LDAPHOST		"ldaptest01.prv.den.acsalaska.net"
      #define LDAPPORT		"13891"
      #define LDAPBINDDN	"cn=Directory Manager"
      #define LDAPBINDPW	"@dm1n_us3r"
