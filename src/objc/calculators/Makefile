
LIBTOOL = glibtool
CC	= gcc

CFLAGS	= -W -Wall -Werror -DPROGRAM_NAME="\"${@}\""
LDFLAGS	= -lobjc

OBJECTS	= src/LengthObject.lo \
	  src/LoanCalculator.lo \
	  src/SSCObject.lo \
	  src/TemperatureObject.lo

all: loan length temperature

src/LengthObject.lo: Makefile src/LengthObject.m src/LengthObject.h src/SSCObject.h
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) -o src/LengthObject.o -c src/LengthObject.m

src/LoanCalculator.lo: Makefile src/LoanCalculator.m src/LoanCalculator.h src/SSCObject.h
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) -o src/LoanCalculator.o -c src/LoanCalculator.m

src/SSCObject.lo: Makefile src/SSCObject.m src/SSCObject.h
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) -o src/SSCObject.o -c src/SSCObject.m

src/TemperatureObject.lo: Makefile src/TemperatureObject.m src/TemperatureObject.h src/SSCObject.h
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS) -o src/TemperatureObject.o -c src/TemperatureObject.m

loan: Makefile src/loan.m src/common.h $(OBJECTS)
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS)  -o src/loan.o -c src/loan.m 
	$(LIBTOOL) --mode=link    $(CC) $(LDFLAGS) -o loan \
		src/loan.lo src/LoanCalculator.lo src/SSCObject.lo

length: Makefile src/length.m $(OBJECTS)
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS)  -o src/length.o -c src/length.m
	$(LIBTOOL) --mode=link    $(CC) $(LDFLAGS) -o length \
		src/length.lo src/LengthObject.lo src/SSCObject.lo

temperature: Makefile src/temperature.m $(OBJECTS)
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS)  -o src/temperature.o -c src/temperature.m
	$(LIBTOOL) --mode=link    $(CC) $(LDFLAGS) -o temperature \
		src/temperature.lo src/TemperatureObject.lo src/SSCObject.lo

install: length loan temperature
	$(LIBTOOL) --mode=install install length      /usr/local/bin
	$(LIBTOOL) --mode=install install loan        /usr/local/bin
	$(LIBTOOL) --mode=install install temperature /usr/local/bin

uninstall:
	$(LIBTOOL) --mode=uninstall rm -f /usr/local/bin/length
	$(LIBTOOL) --mode=uninstall rm -f /usr/local/bin/loan
	$(LIBTOOL) --mode=uninstall rm -f /usr/local/bin/temperature

clean:
	$(LIBTOOL) --mode=clean rm -f length      src/length.lo
	$(LIBTOOL) --mode=clean rm -f loan        src/loan.lo
	$(LIBTOOL) --mode=clean rm -f temperature src/temperature.lo
	$(LIBTOOL) --mode=clean rm -f $(OBJECTS)
	rm -f a.out

