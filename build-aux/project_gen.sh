#!/bin/sh
#
#   $Id: project_gen.sh,v 1.1.2.6 2007/04/18 01:16:21 syzdek Exp $
#
#   Shell Jail -- A Wrapper to Chroot a Shell
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
#   gnu/project_gen.sh - runs GNU tools and commits changes to CVS
# 

PROGRAM_NAME='project_gen.sh'
PACKAGE_VERSION='0.1.0'

GNUDIR=`dirname $0`
SRCDIR=`dirname ${GNUDIR}`

test "x${ACLOCAL}"    == "x" && ACLOCAL='aclocal -W syntax -W unsupported -W error'
test "x${AUTOCONF}"   == "x" && AUTOCONF='autoconf -W cross -W syntax -W error'
test "x${AUTOMAKE}"   == "x" && AUTOMAKE='automake -c -a --gnu -W obsolete -W override -W all -W error'
test "x${AUTOHEADER}" == "x" && AUTOHEADER='autoheader -W cross -W gnu -W obsolete -W override -W error'
test "x${LIBTOOLIZE}" == "x" && LIBTOOLIZE='libtoolize -c -f'


cd ${SRCDIR} || exit 1

for OPT in ${@};do
   if test "x${OPT}" == "x--help";then
      echo "Usage: ${PROGRAM_NAME} [OPTIONS]"
      echo "Description:"
      echo "      ${PROGRAM_NAME} runs GNU tools and commits changes to CVS"
      echo ""
      echo "Options:"
      echo "      --gen             run GNU tools without committing to CVS"
      echo "      --libtoolize      run libtoolize"
      echo "      --status          show CVS status for each file"
      echo "      --which           show which tools this script will use"
      echo "      --help            print this help and exit"
      echo "      --version         print version and exit"
      echo ""
      echo "Variables:"
      echo "      PATH              command search PATH"
      echo "      ACLOCAL           specify GNU aclocal command"
      echo "      AUTOCONF          specify GNU autoconf command"
      echo "      AUTOMAKE          specify GNU automake command"
      echo "      AUTOHEADER        specify GNU autoheader command"
      echo "      LIBTOOLIZE        specify GNU libtoolize command"
      echo ""
      echo "Use these variables to override programs found in PATH."
      echo ""
      echo "Report bugs to <bug-report@syzdek.net>."
      exit 0
   elif test "x${OPT}" == "x--version";then
      echo "${PROGRAM_NAME} (Shell Tools) ${PACKAGE_VERSION}"
      echo "Written by David M. Syzdek."
      echo ""
      echo "Copyright 2007 (C) David M. Syzdek <syzdek@gmail.com>."
      echo "This is free software; see the source for copying conditions.  There is NO"
      echo "warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE."
      exit 0
   elif test "x${OPT}" == "x--libtoolize";then
      RUN_LIBTOOLIZE=yes
   elif test "x${OPT}" == "x--which";then
      which `echo ${ACLOCAL}    |cut -d\  -f1`
      which `echo ${AUTOCONF}   |cut -d\  -f1`
      which `echo ${AUTOMAKE}   |cut -d\  -f1`
      which `echo ${AUTOHEADER} |cut -d\  -f1`
      which `echo ${LIBTOOLIZE} |cut -d\  -f1`
      exit 0
   elif test "x${OPT}" == "x--status";then
      test -d CVS && cvs status . 2>&1 |egrep '^File: |\?'
      exit 0
   elif test "x${OPT}" == "x--gen";then
      CHECK='/dev/null/'
   elif test "x${OPT}" != "x";then
      echo "${PROGRAM_NAME}: invalid option -- ${1}"
      echo "Try '${PROGRAM_NAME} --help' for more information."
      exit 1
   fi
done

echo ${ACLOCAL}
${ACLOCAL} || exit 1
test -d ${CHECK}CVS && { cvs commit -m 'ran aclocal' aclocal.m4 || exit 1; }

echo ${AUTOCONF}
${AUTOCONF} || exit 1
test -d ${CHECK}CVS && { cvs commit -m 'ran autoconf' configure || exit 1; }

echo ${AUTOMAKE}
${AUTOMAKE} || exit 1
test -d ${CHECK}CVS && { cvs commit -m 'ran automake' Makefile.in gnu || exit 1; }

echo ${AUTOHEADER}
${AUTOHEADER} || exit 1
test -d ${CHECK}CVS && { cvs commit -m 'ran autoheader' config.h.in  || exit 1; }

test "x${RUN_LIBTOOLIZE}" == "x" && exit 0
echo ${LIBTOOLIZE}
${LIBTOOLIZE} || exit 1
test -d ${CHECK}CVS && { cvs commit -m 'ran libtoolize' gnu || exit 1; }

# end of script
