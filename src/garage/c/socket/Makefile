#
# Makefile - make file for examples of socket programming in C
# $Source$
# $Revision$
# $Date$
# $Author$
#

all: clean
	gcc -g -o socket-server.o socket-server.c
	gcc -g -o getpeername.o getpeername.c
	gcc -g -o libwrap.o libwrap.c -lwrap
	gcc -g -o select.o select.c
	#gcc -g -o select-timeout.o select-timeout.c

clean:
	if [ -f a.out ];then rm a.out;fi
	-rm -f *.o
