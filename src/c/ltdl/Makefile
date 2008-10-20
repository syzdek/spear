#
#   Examples of using GNU Libtool's libltdl.la for loading modules.
#
#   Makefile - automate compiling on a unix platform
#

CC		= gcc
LIBTOOL		= glibtool
CFLAGS		+= -W -Wall -Werror -O2
LDFLAGS		+= -lltdl
MODFLAGS	+= -rpath /tmp/modules -module -avoid-version

all: simple-loader mod_simple.la

mod_simple.la: Makefile mod_simple.c mod_simple.sym
	$(LIBTOOL) --mode=compile --tag=CC $(CC) $(CFLAGS)   -c mod_simple.c
	$(LIBTOOL) --mode=link    --tag=CC $(CC) $(MODFLAGS) -export-symbols mod_simple.sym -o mod_simple.la mod_simple.lo

simple-loader: Makefile simple-loader.c
	$(LIBTOOL) --mode=compile --tag=CC $(CC) $(CFLAGS)  -c simple-loader.c
	$(LIBTOOL) --mode=link    --tag=CC $(CC) $(LDFLAGS) -o simple-loader simple-loader.o

clean:
	$(LIBTOOL) --mode=clean rm -f simple-loader.lo simple-loader
	$(LIBTOOL) --mode=clean rm -f mod_simple.la    mod_simple.lo
	rm -Rf .libs

distclean: clean

dist: all

install:

uninstall:

# end of Makefile
