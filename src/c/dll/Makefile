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

#strictflags = -Wimplicit -Wmain -Wparentheses -Wreturn-type -Wunused -Wswitch\
# -Wcomment -Wformat -Wchar-subscripts -Wuninitialized -Wshadow -Wpointer-arith\
# -Wcast-qual -Wcast-align -Wwrite-strings -Wconversion -Waggregate-return\
# -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations\
# -Wredundant-decls -Wnested-externs -Winline

flags = $(generalflags) $(warningflags) $(strictflags)

cpp-objects = lib/libexample-cpp.o

c-objects = lib/libexample-c.o

shared-objects = lib/libexample.so lib/libexamplecpp.so

objects = $(cpp-objects) $(c-objects) $(shared-objects)

all: mainc 

mainc: lib/libexamplec.so
	$(gcc) -o Debug/binexample-c $(flags) -lexamplec -L./Debug src/binexample.c

maincpp: lib/libexamplecpp.so
	$(gcc) -o Debug/binexample-cpp $(flags) -lexamplecpp -L./Debug src/binexample.cpp -lc

lib/libexamplec.so: $(c-objects)
	$(gcc) -shared -o Debug/libexamplec.so $(c-objects)

lib/libexamplecpp.so: $(cpp-objects)
	$(gcc) -shared -o Debug/libexamplecpp.so $(cpp-objects)

lib/libexample-cpp.o:
	$(gcc) -c -fPIC -o lib/libexample-cpp.o $(flags) lib/libexample.cpp

lib/libexample-c.o:
	$(gcc) -c -fPIC -o lib/libexample-c.o $(flags) lib/libexample.c

clean:
	-rm -f lib/*.o
	-rm -f Debug/binexample-c
	-rm -f Debug/binexample-cpp
	-rm -f Debug/*.so

