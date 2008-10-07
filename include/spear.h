/*
 *  $Id: $
 */
/*
 *  Simple Programming Examples and References
 *  Copyright (C) 2007 David M. Syzdek <syzdek@gmail.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */
/*
 *  include/spear.h - common preprocessor macros and library headers
 */
#ifndef _SPEAR_H
#define _SPEAR_H 1

//////////////
//          //
//  Macros  //
//          //
//////////////

#undef SPEAR_ATTRIBUTE
#ifdef WIN32
#define SPEAR_ATTRIBUTE(args) /* */
#else
#define SPEAR_ATTRIBUTE(args) __attribute__ (args)
#endif

/*
 * The macros "BEGIN_C_DECLS" and "END_C_DECLS" are taken verbatim
 * from section 7.1 of the Libtool 1.5.14 manual.
 */
/* BEGIN_C_DECLS should be used at the beginning of your declarations,
   so that C++ compilers don't mangle their names. Use END_C_DECLS at
   the end of C declarations. */
#undef BEGIN_C_DECLS
#undef END_C_DECLS
#if defined(__cplusplus) || defined(c_plusplus)
# define BEGIN_C_DECLS  extern "C" {
# define END_C_DECLS    }
#else
# define BEGIN_C_DECLS  /* empty */
# define END_C_DECLS    /* empty */
#endif

/*
 * The macro "PARAMS" is taken verbatim from section 7.1 of the
 * Libtool 1.5.14 manual.
 */
/* PARAMS is a macro used to wrap function prototypes, so that
   compilers that don't understand ANSI C prototypes still work,
   and ANSI C compilers can issue warnings about type mismatches. */
#undef PARAMS
#if defined (__STDC__) || defined (_AIX) \
        || (defined (__mips) && defined (_SYSTYPE_SVR4)) \
        || defined(WIN32) || defined (__cplusplus)
# define PARAMS(protos) protos
#else
# define PARAMS(protos) ()
#endif

/* 
 * Support for DDL/SO exported functions/variables.
 */
#undef SPEAR_F
#undef SPEAR_V
#if defined(_WIN32)
#   ifdef SPEAR_SDK_LIBS_DYNAMIC
#      define SPEAR_F(type)   extern __declspec(dllexport) type
#      define SPEAR_V(type)   extern __declspec(dllexport) type
#     else
#      define SPEAR_F(type)   extern __declspec(dllimport) type
#      define SPEAR_V(type)   extern __declspec(dllimport) type
#   endif
#  else
#   define SPEAR_F(type)      extern type
#   define SPEAR_V(type)      extern type
#endif


///////////////////
//               //
//  Definitions  //
//               //
///////////////////

/* defines package information */
#ifndef PROGRAM_NAME
#define PROGRAM_NAME "spear_example"
#endif

#undef SPEAR_BUFF_LEN
#define SPEAR_BUFF_LEN	1024


///////////////
//           //
//  Headers  //
//           //
///////////////

#include <inttypes.h>


//////////////////
//              //
//  Prototypes  //
//              //
//////////////////
BEGIN_C_DECLS


END_C_DECLS

#endif /* end of header file */
