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
// Configs //
//         //
/////////////

   /* LDAP Host configs */
      #define LDAPHOST		"ldap01.prv.nwc.acsalaska.net"
      #define LDAPPORT		13891
      #define LDAPBINDDN	"cn=Directory Manager"
      //#define LDAPBINDDN	"uid=syzdek,ou=People,o=email,o=trapline.acsalaska.net,o=acsalaska.net"
      #define LDAPBINDPW	"Lwsu@@ps"

   /* Search Criteria */
      #define SEARCH_BASE	"o=acsalaska.net"
      #define SEARCH_FILTER	"(mail=syzdek@mosquitonet.com)"

