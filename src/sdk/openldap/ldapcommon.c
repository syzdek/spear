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
 *  @file src/sdk/openldap/ldap_common.c shared LDAP code
 */
#include "ldapcommon.h"

///////////////
//           //
//  Headers  //
//           //
///////////////
#pragma mark -
#pragma mark Headers

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sasl/sasl.h>


/////////////////
//             //
//  Functions  //
//             //
/////////////////
#pragma mark -
#pragma mark Functions

/// initialize LDAP connection
/// @param[in]  cnfp  pointer to configuration struct
int ldapcommon_initialize(LDAPConfig * cnfp)
{
   LDAP           * ld;
   int              err;
   char           * msg;
   BerValue         cred;
   BerValue       * servercredp;

   servercredp = NULL;
   cnfp->ldapURI      = cnfp->ldapURI     ? cnfp->ldapURI      : "ldap://localhost/";
   cnfp->ldapFilter   = cnfp->ldapFilter  ? cnfp->ldapFilter   : "(objectclass=*)";
   cnfp->ldapVersion  = cnfp->ldapVersion ? cnfp->ldapVersion  : LDAP_VERSION3;
   cnfp->ldapScope    = cnfp->ldapScope   ? cnfp->ldapScope    : LDAP_SCOPE_SUB;

   // set LDAP debug level
   if (cnfp->ldapDebug)
   {
      err = ldap_set_option(NULL, LDAP_OPT_DEBUG_LEVEL, &cnfp->ldapDebug);
      if (err != LDAP_SUCCESS)
      {
         fprintf(stderr, "ldap_set_option(DEBUG_LEVEL): %s\n", ldap_err2string(err));
         return(1);
      };
   };

   // set the CA PEM file to use with TLS/SSL connections
   if (cnfp->ldapCaFile)
   {
      err = ldap_set_option(NULL, LDAP_OPT_X_TLS_CACERTFILE, (const void *)cnfp->ldapCaFile);
      if (err != LDAP_SUCCESS)
      {
         fprintf(stderr, "ldap_set_option(): %s\n", ldap_err2string(err));
         return(1);
      };
   };

   // initialize the LDAP descriptor
   err = ldap_initialize(&ld, cnfp->ldapURI);
   if (err != LDAP_SUCCESS)
   {
      fprintf(stderr, "ldap_initialize(): %s\n", ldap_err2string(err));
      return(1);
   };

   // set LDAP protocol version
   err = ldap_set_option(ld, LDAP_OPT_PROTOCOL_VERSION, &cnfp->ldapVersion);
   if (err != LDAP_SUCCESS)
   {
      fprintf(stderr, "ldap_set_option(PROTOCOL_VERSION): %s\n", ldap_err2string(err));
      ldap_unbind_ext_s(ld, NULL, NULL);
      return(1);
   };

   // set LDAP search limit
   if (cnfp->ldapSearchLimit)
   {
      err = ldap_set_option(ld, LDAP_OPT_SIZELIMIT, &cnfp->ldapSearchLimit);
      if (err != LDAP_SUCCESS)
      {
         fprintf(stderr, "ldap_set_option(SIZELIMIT): %s\n", ldap_err2string(err));
         ldap_unbind_ext_s(ld, NULL, NULL);
         return(1);
      };
   };

   // set LDAP time limit
   if (cnfp->ldapTimeLimit)
   {
      err = ldap_set_option(ld, LDAP_OPT_TIMELIMIT, &cnfp->ldapTimeLimit);
      if (err != LDAP_SUCCESS)
      {
         fprintf(stderr, "ldap_set_option(TIMELIMIT): %s\n", ldap_err2string(err));
         ldap_unbind_ext_s(ld, NULL, NULL);
         return(1);
      };
   };

   // initial TLS session
   if (cnfp->ldapUseTls)
   {
      err = ldap_start_tls_s(ld, NULL, NULL);
      if (err != LDAP_SUCCESS)
      {
         ldap_get_option(ld, LDAP_OPT_DIAGNOSTIC_MESSAGE, (void*)&msg);
         fprintf(stderr, "ldap_start_tls_s(): %s\n", ldap_err2string(err));
         fprintf(stderr, "ldap_start_tls_s(): %s\n", msg);
         ldap_memfree(msg);
         ldap_unbind_ext_s(ld, NULL, NULL);
         return(1);
      };
   };

   // bind to LDAP server using simple bind
   if (!(cnfp->ldapUseSasl))
   {
      cred.bv_val = cnfp->ldapPassword ? strdup(cnfp->ldapPassword) : NULL;
      cred.bv_len = cnfp->ldapPassword ? strlen(cnfp->ldapPassword) : 0;
      err = ldap_sasl_bind_s(ld, cnfp->ldapBindDN, LDAP_SASL_SIMPLE, &cred, NULL, NULL, &servercredp);
      if (err != LDAP_SUCCESS)
      {
         fprintf(stderr, "ldap_sasl_bind_s(): %s\n", ldap_err2string(err));
         free(cred.bv_val);
         ldap_unbind_ext_s(ld, NULL, NULL);
         return(1);
      };
      free(cred.bv_val);
   };

   // bind to LDAP server using SASL bind
   if ((cnfp->ldapUseSasl))
   {
      err = ldap_sasl_interactive_bind_s(ld, NULL, cnfp->ldapSaslMech, NULL,
               NULL, LDAP_SASL_QUIET, ldapcommon_sasl_interact, cnfp);
      if (err != LDAP_SUCCESS)
      {
         fprintf(stderr, "ldap_sasl_bind_s(): %s\n", ldap_err2string(err));
         ldap_unbind_ext_s(ld, NULL, NULL);
         return(1);
      };
   };   

   // store LDAP descriptor for later use
   cnfp->ld = ld;

   return(0);
}


// manages SASL auth interaction
int ldapcommon_sasl_interact(LDAP * ld, unsigned flags, void * defaults,
   void * sin)
{
   LDAPConfig      * cnfp = defaults;
	sasl_interact_t * interact;

   flags    = 0;
   cnfp     = (LDAPConfig *) defaults;
   interact = (sasl_interact_t *) sin;

   if (!(ld))
      return(LDAP_PARAM_ERROR);

   for(interact = sin; (interact->id != SASL_CB_LIST_END); interact++)
   {
      interact->result = NULL;
      interact->len    = 0;
      switch( interact->id )
      {
         case SASL_CB_GETREALM:
            interact->result = cnfp->ldapSaslRealm ? cnfp->ldapSaslRealm : "";
            interact->len    = strlen( interact->result );
            break;
         case SASL_CB_AUTHNAME:
            interact->result = cnfp->ldapSaslAuthUser ? cnfp->ldapSaslAuthUser : "";
            interact->len    = strlen( interact->result );
            break;
         case SASL_CB_PASS:
            interact->result = cnfp->ldapPassword ? cnfp->ldapPassword : "";
            interact->len    = strlen( interact->result );
            break;
         case SASL_CB_USER:
            interact->result = cnfp->ldapSaslUser ? cnfp->ldapSaslUser : "";
            interact->len    = strlen( interact->result );
            break;
         case SASL_CB_NOECHOPROMPT:
         case SASL_CB_ECHOPROMPT:
         default:
            break;
      };
   };

   return(LDAP_SUCCESS);
}



/* end of source */
