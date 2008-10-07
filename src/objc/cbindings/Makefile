
LIBTOOL	= glibtool
CC	= gcc

CFLAGS  = -W -Wall -Werror 
LDFLAGS = -lobjc

all: cbindings 

cBindings.lo: Makefile cBindings.h cBindings.m MyClass.h
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) -c cBindings.m

main.lo: Makefile main.c cBindings.h
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) -c main.c

MyClass.lo: Makefile MyClass.h MyClass.m
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) -c MyClass.m

cbindings: Makefile cBindings.lo main.lo MyClass.lo
	$(LIBTOOL) --mode=link    $(CC) $(LDFLAGS) -o cbindings \
			cBindings.lo MyClass.lo main.lo

clean:
	$(LIBTOOL) --mode=clean rm -f cbindings
	$(LIBTOOL) --mode=clean rm -f cBindings.lo
	$(LIBTOOL) --mode=clean rm -f MyClass.lo
	$(LIBTOOL) --mode=clean rm -f main.lo
	rm -f a.out
