#
# Makefile - make file for examples of encryption programming in C
# $Source$
# $Revision$
# $Date$
# $Author$
#

all: clean
	gcc -g -o crypt.o crypt.c -lcrypt
	gcc -g -o sha1.o sha1.c -lssl
	gcc -g -o sha1-base64.o sha1-base64.c -lssl

clean:
	if [ -f a.out ];then rm a.out;fi
	-rm -f *.o
