#
#   $Id: $
#
#   Simple Programming Examples and References
#   Copyright (C) 2007, 2008 David M. Syzdek <syzdek@gmail.com>
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
#   configure.in - automate compiling on a unix platform
#

# +-=-=-=-=-=-=-=-=-+
# |                 |
# |  Autoconf Init  |
# |                 |
# +-=-=-=-=-=-=-=-=-+

AC_PREREQ(2.61)

AC_COPYRIGHT([Copyright (c) 2007 David M. Syzdek <spear-project@syzdek.net>.])
AC_REVISION($Revision: 1.1.2.1 $)

AC_INIT([Simple Programming Examples and References],[0.0.0-0.0.1],[syzdek@gmail.com],[spear])
AC_SUBST([RELEASE_MONTH],["September 2007"])

# Version Info:
#    Current    -- the current version number of this API
#    Revision   -- the revision of the implementation of the API version
#    Age        -- How many seqential past API versions is supported by
#                  this implementation
# Format => Current:Revision:Age
AC_SUBST(LIB_VERSION_INFO, 0:0:0)

AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_SRCDIR([.])
AC_CONFIG_LIBOBJ_DIR(compat)
AC_CONFIG_HEADERS([config.h])

# determines host type
AC_CANONICAL_BUILD
AC_CANONICAL_HOST
AC_CANONICAL_TARGET

# configures for automake
AM_INIT_AUTOMAKE(1.10 gnu std-options subdir-objects)

# Compilers                                                       
AC_PROG_CC 
AM_PROG_CC_C_O

# binary locations
AC_PROG_INSTALL
AC_PATH_PROG([SHELL],   sh bash,        [AC_MSG_ERROR([missing "sh"])], [$PATH])
AC_CHECK_TOOLS(AR,      ar gar,         [AC_MSG_ERROR([missing binutil "ar"])])
AC_CHECK_TOOLS(LD,      ld gld,         [AC_MSG_ERROR([missing binutil "ld"])])
AC_CHECK_TOOLS(NM,      nm gnm,         [AC_MSG_ERROR([missing binutil "nm"])])
AC_CHECK_TOOLS(RANLIB,  ranlib granlib, [AC_MSG_ERROR([missing binutil "ranlib"])])
AC_CHECK_TOOLS(STRIP,   strip gstrip,   [AC_MSG_ERROR([missing binutil "strip"])])

# checks for Unix Variants
AC_AIX
AC_GNU_SOURCE
AC_MINIX
AC_C_BIGENDIAN

# shell programs
AC_PROG_AWK
AC_PROG_EGREP
AC_PROG_FGREP
AM_PROG_LEX
AC_PROG_LN_S

# GNU Libtool Support
AC_LIBTOOL_DLOPEN
AC_DISABLE_FAST_INSTALL
AC_PROG_LIBTOOL

# +-=-=-=-=-=-+
# |           |
# |  Options  |
# |           |
# +-=-=-=-=-=-+

AC_SPEAR_ENABLE_WARNINGS

# +-=-=-=-=-=-=-=-=-+
# |                 |
# |  Shared Checks  |
# |                 |
# +-=-=-=-=-=-=-=-=-+

# enables getopt_long if header and functions were found
AC_CHECK_HEADERS([getopt.h], [AC_DEFINE_UNQUOTED(USE_GETOPT_LONG, 1, [Use GNU getopt_long])])

# checks for cross compile (need to verify the following checks)
test "x$host" == "x$build"  && COMPILE_MODE='native compile';
test "x$host" != "x$build"  && COMPILE_MODE='cross compile';
test "x$host" != "x$target" && COMPILE_MODE='Canadian cross compile';

# checks for build variants in order to include system specific source files
case $host in
   *cygwin*)  COMPILE_CYGWIN=true;;
   *darwin*)  COMPILE_DARWIN=true;;
   *freebsd*) COMPILE_FREEBSD=true;;
   *linux*)   COMPILE_LINUX=true;;
   *mingw*)   COMPILE_MINGW=true;;
   *solaris*) COMPILE_SOLARIS=true;;
esac
AM_CONDITIONAL([COMPILE_CYGWIN],  [test "x$COMPILE_CYGWIN" == "xtrue"])
AM_CONDITIONAL([COMPILE_DARWIN],  [test "x$COMPILE_DARWIN" == "xtrue"])
AM_CONDITIONAL([COMPILE_FREEBSD], [test "x$COMPILE_FREEBSD" == "xtrue"])
AM_CONDITIONAL([COMPILE_LINUX],   [test "x$COMPILE_LINUX" == "xtrue"])
AM_CONDITIONAL([COMPILE_MINGW],   [test "x$COMPILE_MINGW" == "xtrue"])
AM_CONDITIONAL([COMPILE_SOLARIS], [test "x$COMPILE_SOLARIS" == "xtrue"])

# +-=-=-=-=-=-=-=-=+
# |                |
# |  Create files  |
# |                |
# +-=-=-=-=-=-=-=-=+

AC_CONFIG_FILES([Makefile])

AC_OUTPUT

# +-=-=-=-=-=-=-=-=-=-+
# |                   |
# |  Show Local Conf  |
# |                   |
# +-=-=-=-=-=-=-=-=-=-+

AC_MSG_NOTICE([ ])
AC_MSG_NOTICE([   Simple Programming Examples and References])
AC_MSG_NOTICE([ ])
AC_MSG_NOTICE([   Compile Mode                  $COMPILE_MODE])
AC_MSG_NOTICE([ ])
AC_MSG_NOTICE([   Debug Mode                    $USE_DEBUG])
AC_MSG_NOTICE([   Use Warnings                  $USE_WARNINGS])
AC_MSG_NOTICE([   Use Strict Warnings           $USE_STRICTWARNINGS])
AC_MSG_NOTICE([ ])
AC_MSG_NOTICE([   GCC Flags:                    ${CFLAGS} ${LDFLAGS} ${LIBS}])
AC_MSG_NOTICE([ ])

# end of configure.ac
