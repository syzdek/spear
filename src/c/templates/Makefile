#
# Project Name
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

objects = object.o

all: $(objects) main

main: $(objects)
	$(gcc) -o main $(flags) $(objects) main.c

object.o:
	$(gcc) -c -o object.o $(flags) object.c

clean:
	-rm -f *.o
	-rm -f main

