#
# Makefile - make file for examples of BerkeleyDB programming in C
# $Source$
# $Revision$
# $Date$
# $Author$
#

all: clean
	gcc -g -o simple-bdb.o simple-bdb.c -ldb
	gcc -g -o simple-bdb-env.o simple-bdb-env.c -ldb

clean: clean
	if [ -f a.out ];then rm a.out;fi
	-rm -f *.o
