#
# Makefile - make file for examples of BerkeleyDB programming in C
# $Source$
# $Revision$
# $Date$
# $Author$
#

all:
	gcc -g -o simple-bdb.o simple-bdb.c -ldb

clean: clean
	if [ -f a.out ];then rm a.out;fi
	-rm -f *.o
