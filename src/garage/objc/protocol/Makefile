
LIBTOOL	= glibtool
CC	= gcc

CFLAGS	= -W -Wall -Werror 
LDFLAGS	= -framework Foundation

all: protocolTest

FirstClass.lo: Makefile FirstClass.h FirstClass.m
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) -c FirstClass.m

SecondClass.lo: Makefile SecondClass.h SecondClass.m
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) -c SecondClass.m

protocolTest: Makefile protocolTest.m FirstClass.lo SecondClass.lo
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) -c protocolTest.m
	$(LIBTOOL) --mode=link    $(CC) $(LDFLAGS) -o protocolTest \
	   protocolTest.lo FirstClass.lo SecondClass.lo

clean:
	$(LIBTOOL) --mode=clean rm -f protocolTest
	$(LIBTOOL) --mode=clean rm -f protocolTest.lo
	$(LIBTOOL) --mode=clean rm -f FirstClass.lo
	$(LIBTOOL) --mode=clean rm -f SecondClass.lo
	rm -f a.out

