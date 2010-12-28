
LIBTOOL	= glibtool
CC	= gcc

CFLAGS  = -W -Wall -Werror 
LDFLAGS = -framework Foundation

all: autoreleasePool

autoreleasePool: Makefile autoreleasePool.m
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) -c autoreleasePool.m
	$(LIBTOOL) --mode=link    $(CC) $(LDFLAGS) -o autoreleasePool autoreleasePool.lo

clean:
	$(LIBTOOL) --mode=clean rm -f autoreleasePool
	$(LIBTOOL) --mode=clean rm -f autoreleasePool.lo
	rm -f a.out
