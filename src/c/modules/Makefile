#
# Examples: Dynamic module loading
# $Source$
# $Revision$
# $Date$
# $Author$
#
# Makefile - automate compiling on a unix platform
#

OBJECTLEN := 4097

include ../../.config

examples = simple-module.so simple-loader

all: $(examples)

simple-module.so: simple-module.o
	gcc $(SOFLAGS) -o simple-module.so simple-module.o $(flags)
simple-module.o: simple-module.c
	gcc $(SOFLAGS) -c simple-module.c $(flags)
simple-loader: simple-loader.c
	gcc -o simple-loader simple-loader.c -ldl $(flags)

clean:
	-rm -f simple-loader
	-rm -f *.o
	-rm -f *.so
