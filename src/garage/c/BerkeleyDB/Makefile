#
# Makefile - make file for examples of BerkeleyDB programming in C
# $Source$
# $Revision$
# $Date$
# $Author$
#

all: clean
	gcc -g -o simple-bdb.o simple-bdb.c -ldb-4
	gcc -g -o simple-bdbenv.o simple-bdbenv.c -ldb-4

clean: clean
	if [ -f a.out ];then rm a.out;fi
	-rm -f *.o
	-rm -f databases/*db.*
	-rm -f databases/log.*
	-rm -f databases/db/*.db
	-rm -f access.db
