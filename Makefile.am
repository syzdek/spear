#
#   Simple Programming Examples And References
#   Copyright (C) 2007, 2008, 2010 David M. Syzdek <david@syzdek.net>.
#
#   @SYZDEK_BSD_LICENSE_START@
#
#   Redistribution and use in source and binary forms, with or without
#   modification, are permitted provided that the following conditions are
#   met:
#
#      * Redistributions of source code must retain the above copyright
#        notice, this list of conditions and the following disclaimer.
#      * Redistributions in binary form must reproduce the above copyright
#        notice, this list of conditions and the following disclaimer in the
#        documentation and/or other materials provided with the distribution.
#      * Neither the name of David M. Syzdek nor the
#        names of its contributors may be used to endorse or promote products
#        derived from this software without specific prior written permission.
#
#   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
#   IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
#   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
#   PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL BINDLE BINARIES BE LIABLE FOR
#   ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
#   DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
#   SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
#   CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
#   LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
#   OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
#   SUCH DAMAGE.
#
#   @SYZDEK_BSD_LICENSE_END@
#
#   @configure_input@
#
#   Makefile.am - automate compiling on a unix platform
#

# Sub directories
SUBDIRS					=
DIST_SUBDIRS				= 

# Global flags
# Global flags
AM_LIBS					=
AM_LDFLAGS				=
AM_CFLAGS				= -O2 -W -Wall -Werror $(CFLAGS_WARNINGS)
AM_CXXFLAGS				= -O2 -W -Wall -Werror
AM_OBJCFLAGS				= -O2 -W -Wall -Werror
AM_CPPFLAGS				= -O2 -W -Wall -Werror -DHAVE_COMMON_H=1 -I$(top_builddir)/include -I$(top_srcdir)/include
ACLOCAL_AMFLAGS				= -I m4
DEFS					= -DLOCALEDIR="\"$(localedir)\"" @DEFS@


# automake targets 
check_PROGRAMS				= 
doc_DATA				= 
include_HEADERS				= 
lib_LTLIBRARIES				= 
man_MANS				=
noinst_LTLIBRARIES			= 
noinst_HEADERS				=
noinst_PROGRAMS				=


# macros for src/sdk/openldap/ldapsearch-async
if HAVE_LDAP
noinst_PROGRAMS += src/sdk/openldap/ldapsearch-async
endif
src_sdk_openldap_ldapsearch_async_DEPENDENCIES	= Makefile
src_sdk_openldap_ldapsearch_async_SOURCES	= src/sdk/openldap/ldapsearch-async.c


# macros for src/sdk/openldap/ldapsearch-sync
if HAVE_LDAP
noinst_PROGRAMS += src/sdk/openldap/ldapsearch-sync
endif
src_sdk_openldap_ldapsearch_sync_DEPENDENCIES	= Makefile
src_sdk_openldap_ldapsearch_sync_SOURCES	= src/sdk/openldap/ldapsearch-sync.c


# substitution routine
do_subst = sed \
	-e 's,[@]SHELL[@],@SHELL@,g' \
	-e 's,[@]PACKAGE_VERSION[@],@PACKAGE_VERSION@,g' \
	-e 's![@]PACKAGE_NAME[@]!@PACKAGE_NAME@!g' \
	-e 's,[@]PACKAGE_TARNAME[@],@PACKAGE_TARNAME@,g' \
	-e 's,[@]PACKAGE_BUGREPORT[@],@PACKAGE_BUGREPORT@,g' \
	-e 's,[@]RELEASE_MONTH[@],@RELEASE_MONTH@,g' \
	-e 's,[@]INSTALL[@],$(INSTALL),g' \
	-e 's,[@]INSTALL_PROGRAM[@],$(INSTALL_PROGRAM),g' \
	-e 's,[@]INSTALL_SCRIPT[@],$(INSTALL_SCRIPT),g' \
	-e 's,[@]INSTALL_DATA[@],$(INSTALL_DATA),g' \
	-e 's,[@]LIB_VERSION_CURRENT[@],@LIB_VERSION_CURRENT@,g' \
	-e 's,[@]LIB_VERSION_REVISION[@],@LIB_VERSION_REVISION@,g' \
	-e 's,[@]LIB_VERSION_AGE[@],@LIB_VERSION_AGE@,g' \
	-e 's,[@]LIB_VERSION_INFO[@],@LIB_VERSION_INFO@,g' \
	-e 's,[@]LIB_RELEASE_INFO[@],@LIB_RELEASE_INFO@,g' \
	-e 's,[@]prefix[@],$(prefix),g' \
	-e 's,[@]datadir[@],$(datadir),g' \
	-e 's,[@]sbindir[@],$(sbindir),g' \
	-e 's,[@]sysconfdir[@],$(sysconfdir),g' \
	-e 's,[@]localstatedir[@],$(localstatedir),g'
do_subst_fn = \
		echo "do_subst < ${@}.in > ${@}"; \
		mkdir -p `dirname ${@}` || exit 1; \
		${do_subst} < $(srcdir)/${@}.in > ${@} || exit 1; \
		chmod 0755 ${@}
do_subst_dt = \
		echo "do_subst < ${@}.in > ${@}"; \
		mkdir -p `dirname ${@}` || exit 1; \
		${do_subst} < $(srcdir)/${@}.in > ${@} || exit 1; \
		chmod 0644 ${@}


# lists
BUILT_SOURCES				=
TESTS					=
XFAIL_TESTS				=
EXTRA_MANS				=
EXTRA_PROGRAMS				= src/sdk/openldap/ldapsearch
EXTRA_DIST				=
CLEANFILES				= \
					  $(builddir)/a.out   $(srcdir)/a.out \
					  $(builddir)/*/a.out $(srcdir)/*/a.out \
					  config.h.in~ $(srcdir)/config.h.in~ \
					  $(man_MANS) \
					  @PACKAGE_TARNAME@-*.tar.* \
					  @PACKAGE_TARNAME@-*.zip


# custom targets
autoreconf:
	autoreconf -i -f $(ACLOCAL_AMFLAGS)

gitclean:
	$(MAKE) -f Makefile distclean
	rm -fR INSTALL
	rm -fR Makefile.in
	rm -fR aclocal.m4
	rm -fR build-aux/*
	rm -fR config.h.in
	rm -fR configure
	rm -fR m4/*


# local targets
install-exec-local:

install-data-local: 

uninstall-local:

clean-local:
	rm -fR $(srcdir)/build

distclean-local:
	rm -fR $(srcdir)/autom4te.cache

# end of automake file
