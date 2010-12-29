/*
 *  Simple Programming Examples And References
 *  Copyright (C) 2010 David M. Syzdek <david@syzdek.net>.
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
 *  @file src/sdk/openldap/ldap_common.h shared LDAP code
 */
#ifndef _SPEAR_SRC_SDK_OPENLDAP_LDAP_COMMON_H
#define _SPEAR_SRC_SDK_OPENLDAP_LDAP_COMMON_H 1

///////////////
//           //
//  Headers  //
//           //
///////////////
#pragma mark -
#pragma mark Headers

#include <ldap.h>


/////////////////
//             //
//  Datatypes  //
//             //
/////////////////
#pragma mark -
#pragma mark Datatypes

typedef struct ldap_config LDAPConfig;
struct ldap_config
{
   LDAP        * ld;
   const char  * ldapURI;
   const char  * ldapBaseDN;
   const char  * ldapFilter;
   const char  * ldapBindDN;
   const char  * ldapPassword;
   const char  * ldapCaFile;
   const char  * ldapSaslUser;
   const char  * ldapSaslAuthUser;
   const char  * ldapSaslMech;
   const char  * ldapSaslRealm;
   const char ** ldapAttributes;
   int           ldapDebug;
   int           ldapScope;
   int           ldapSearchLimit;
   int           ldapTimeLimit;
   int           ldapUseSasl;
   int           ldapUseTls;
   int           ldapVersion;
   int           silent;
   int           verbose;
   int           printConfig;
};


//////////////////
//              //
//  Prototypes  //
//              //
//////////////////
#pragma mark -
#pragma mark Prototypes

// initialize LDAP connection
int ldapcommon_initialize(LDAPConfig * cnfp);

// manages SASL auth interaction
int ldapcommon_sasl_interact(LDAP * ld, unsigned flags, void  *defaults,
   void * sin);

#endif
/* end of header */
