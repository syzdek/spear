#
#   $Id: $
#
#   Simple Programming Examples and References
#   Copyright (C) 2007 David M. Syzdek <syzdek@gmail.com>
#
#   This program is free software; you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation; either version 2 of the License, or
#   (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with this program; if not, write to the Free Software
#   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
#
#   @configure_input@
#
#   Makefile.am - automate compiling on a unix platform
#

# Sub directories
SUBDIRS					=  
DIST_SUBDIRS				= 

# Global flags
AM_LIBS					=
AM_LDFLAGS				= 
AM_CFLAGS				= \
					  @CFLAGS_WARNINGS@ \
					  -I$(top_srcdir)/include \
					  -I$(top_builddir)/include

# automake targets 
noinst_LTLIBRARIES			= 
noinst_HEADERS				= include/spear.h
bin_PROGRAMS				= src/c/socket/tcp_client src/c/socket/tcp_server
#bin_PROGRAMS				= 
check_PROGRAMS				= 
lib_LTLIBRARIES				= 
include_HEADERS				= 
doc_DATA				= 
man_MANS				=


# macros for src/c/socket/tcp_client
src_c_socket_tcp_client_DEPENDENCIES	=
src_c_socket_tcp_client_CFLAGS		= $(AM_CFLAGS)
src_c_socket_tcp_client_CPPFLAGS	= $(AM_CPPFLAGS) -DPROGRAM_NAME=\"tcp_client\"
src_c_socket_tcp_client_CXXFLAGS	= $(AM_CXXFLAGS)
src_c_socket_tcp_client_LDFLAGS		= $(AM_LDFLAGS)
src_c_socket_tcp_client_LDADD		= $(AM_LIBS)
src_c_socket_tcp_client_SOURCES		= \
					  src/c/socket/socket_functions.c \
					  src/c/socket/socket_functions.h \
					  src/c/socket/tcp_client.c \
					  src/c/socket/tcp_client.h

# macros for src/c/socket/tcp_servert
src_c_socket_tcp_server_DEPENDENCIES	=
src_c_socket_tcp_server_CFLAGS		= $(AM_CFLAGS)
src_c_socket_tcp_server_CPPFLAGS	= $(AM_CPPFLAGS)
src_c_socket_tcp_server_CXXFLAGS	= $(AM_CXXFLAGS) -DPROGRAM_NAME=\"tcp_server\"
src_c_socket_tcp_server_LDFLAGS		= $(AM_LDFLAGS)
src_c_socket_tcp_server_LDADD		= $(AM_LIBS)
src_c_socket_tcp_server_SOURCES		= \
					  src/c/socket/socket_functions.c \
					  src/c/socket/socket_functions.h \
					  src/c/socket/tcp_server.c \
					  src/c/socket/tcp_server.h

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
	-e 's,[@]prefix[@],$(prefix),g' \
	-e 's,[@]datadir[@],$(datadir),g' \
	-e 's,[@]sbindir[@],$(sbindir),g' \
	-e 's,[@]sysconfdir[@],$(sysconfdir),g' \
	-e 's,[@]localstatedir[@],$(localstatedir),g'

TESTS					=
XFAIL_TESTS				=
EXTRA_MANS				=
EXTRA_PROGRAMS				=
EXTRA_DIST				=
CLEANFILES				= \
					  a.out \
					  $(srcdir)/a.out \
					  config.h.in~ \
					  $(srcdir)/config.h.in~ \
					  stamp-h1 \
					  stamp-vti \
					  $(srcdir)/stamp-vti \
					  @PACKAGE_TARNAME@-*.tar.* \
					  @PACKAGE_TARNAME@-*.zip

# custom targets

# local targets
install-exec-local:

install-data-local: 

uninstall-local:
	rm -fR $(DESTDIR)/$(docdir)

distclean-local:
	rm -fR $(srcdir)/autom4te.cache

# end of automake file
