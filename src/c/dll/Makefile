#
# Example of Windows DLL and Unix Shared Library
# $Source$
# $Revision$
# $Date$
# $Author$
#
# Makefile - automate compiling on a unix platform
#

gcc = gcc

includedir = 

libdir = 

libs = 

generalflags = -O2 -g -std=gnu99

warningflags = -Werror -Wall -pedantic -Wtraditional -W

strictflags = -Wimplicit -Wmain -Wparentheses -Wreturn-type -Wunused -Wswitch\
 -Wcomment -Wformat -Wchar-subscripts -Wuninitialized -Wshadow -Wpointer-arith\
 -Wcast-qual -Wcast-align -Wwrite-strings -Wconversion -Waggregate-return\
 -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations\
 -Wredundant-decls -Wnested-externs -Winline

flags = $(generalflags) $(warningflags) $(strictflags)

objects = lib/libexample.o

shared-objects = lib/libexample.so

all: main

main: lib/libexamplec.so
	$(gcc) -o Debug/binexample $(flags) -lexample -L./Debug src/binexample.c

lib/libexamplec.so: $(objects)
	$(gcc) -shared -o Debug/libexample.so $(objects)

lib/libexample.o:
	$(gcc) -c -fPIC -o lib/libexample.o $(flags) lib/libexample.c

clean:
	-rm -f lib/*.o
	-rm -f Debug/binexample
	-rm -f Debug/*.so

