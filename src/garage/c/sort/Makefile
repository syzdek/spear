#
#   Examples of using GNU Libtool's libltdl.la for loading modules.
#
#   Makefile - automate compiling on a unix platform
#

CC		= gcc
LIBTOOL		= glibtool
CFLAGS		+= -W -Wall -Werror -O2
LDFLAGS		+= 
MODFLAGS	+= 

all: mergesort_struct

mergesort_struct: Makefile mergesort_struct.c
	$(LIBTOOL) --mode=compile --tag=CC $(CC) $(CFLAGS)   -c mergesort_struct.c
	$(LIBTOOL) --mode=link    --tag=CC $(CC) $(MODFLAGS) -o mergesort_struct mergesort_struct.lo

clean:
	$(LIBTOOL) --mode=clean rm -f mergesort_struct.lo mergesort_struct

distclean: clean

dist: all

install:

uninstall:

# end of Makefile
