#
# Project Name
# $Source$
# $Revision$
# $Date$
# $Author$
#
# Makefile - automate compiling on a unix platform
#

#gcc = gcc
#includedir = 
#libdir = 
#libs = 

# Loads Warning flags, CFLAGS, and sets CC
include ../../.config

objects = object.o

all: $(objects) main

main: $(objects)
	$(CC) -o main $(flags) $(objects) main.c

object.o:
	$(CC) -c -o object.o $(flags) object.c

clean:
	-rm -f *.o
	-rm -f main

