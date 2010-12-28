#
# Makefile - make file for programming examples of 
#            allocating and freeing dynamic memory in C
# $Source$
# $Revision$
# $Date$
# $Author$
#
flags = -g -O2 -Werror -Wall -pedantic -g -Wtraditional -W -Wimplicit -Wmain -Wparentheses \
        -Wreturn-type -Wunused -Wswitch -Wcomment -Wformat -Wchar-subscripts -Wshadow \
        -Wcast-qual -Wcast-align -Wwrite-strings -Wconversion -Waggregate-return \
        -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wredundant-decls \
        -Wnested-externs -Winline

objects = growing-buffer.o realloc.o

all: clean $(objects)

growing-buffer.o:
	gcc -o growing-buffer.o growing-buffer.c $(flags)

realloc.o:
	gcc -o realloc.o realloc.c $(flags)

clean:
	if [ -f a.out ];then rm a.out;fi
	-rm -f *.o
