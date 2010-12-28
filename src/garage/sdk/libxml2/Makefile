
LIBTOOL	= /Developer/usr/bin/glibtool
CC	= gcc

CFLAGS  = -W -Wall -Werror `/usr/bin/xml2-config --cflags`
LDFLAGS = -W -Wall -Werror `/usr/bin/xml2-config --libs`

PROGRAMS	= \
		  src/parse1 \
		  src/parse2 \
		  src/parse3 \
		  src/parse4 \
		  src/reader1 \
		  src/reader2 \
		  src/reader3 \
		  src/reader4 \
		  src/tree1 \
		  src/tree2 \
		  src/tree-rim \
		  src/tutorial/attribute \
		  src/tutorial/keyword \
		  src/tutorial/xpath

all: $(PROGRAMS)

src/parse1: Makefile src/parse1.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS)  -o ${@}.o -c ${@}.c
	$(LIBTOOL) --mode=link    $(CC) $(LDFLAGS) -o ${@}      ${@}.lo

src/parse2: Makefile src/parse2.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS)  -o ${@}.o -c ${@}.c
	$(LIBTOOL) --mode=link    $(CC) $(LDFLAGS) -o ${@}      ${@}.lo

src/parse3: Makefile src/parse3.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS)  -o ${@}.o -c ${@}.c
	$(LIBTOOL) --mode=link    $(CC) $(LDFLAGS) -o ${@}      ${@}.lo

src/parse4: Makefile src/parse4.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS)  -o ${@}.o -c ${@}.c
	$(LIBTOOL) --mode=link    $(CC) $(LDFLAGS) -o ${@}      ${@}.lo

src/reader1: Makefile src/reader1.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS)  -o ${@}.o -c ${@}.c
	$(LIBTOOL) --mode=link    $(CC) $(LDFLAGS) -o ${@}      ${@}.lo

src/reader2: Makefile src/reader2.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS)  -o ${@}.o -c ${@}.c
	$(LIBTOOL) --mode=link    $(CC) $(LDFLAGS) -o ${@}      ${@}.lo

src/reader3: Makefile src/reader3.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS)  -o ${@}.o -c ${@}.c
	$(LIBTOOL) --mode=link    $(CC) $(LDFLAGS) -o ${@}      ${@}.lo

src/reader4: Makefile src/reader4.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS)  -o ${@}.o -c ${@}.c
	$(LIBTOOL) --mode=link    $(CC) $(LDFLAGS) -o ${@}      ${@}.lo

src/tree1: Makefile src/tree1.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS)  -o ${@}.o -c ${@}.c
	$(LIBTOOL) --mode=link    $(CC) $(LDFLAGS) -o ${@}      ${@}.lo

src/tree2: Makefile src/tree2.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS)  -o ${@}.o -c ${@}.c
	$(LIBTOOL) --mode=link    $(CC) $(LDFLAGS) -o ${@}      ${@}.lo

src/tree-rim: Makefile src/tree-rim.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS)  -o ${@}.o -c ${@}.c
	$(LIBTOOL) --mode=link    $(CC) $(LDFLAGS) -o ${@}      ${@}.lo

src/tutorial/attribute: Makefile src/tutorial/attribute.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS)  -o ${@}.o -c ${@}.c
	$(LIBTOOL) --mode=link    $(CC) $(LDFLAGS) -o ${@}      ${@}.lo

src/tutorial/keyword: Makefile src/tutorial/keyword.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS)  -o ${@}.o -c ${@}.c
	$(LIBTOOL) --mode=link    $(CC) $(LDFLAGS) -o ${@}      ${@}.lo

src/tutorial/xpath: Makefile src/tutorial/xpath.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS)  -o ${@}.o -c ${@}.c
	$(LIBTOOL) --mode=link    $(CC) $(LDFLAGS) -o ${@}      ${@}.lo

clean:
	$(LIBTOOL) --mode=clean rm -f src/parse1    src/parse1.lo
	$(LIBTOOL) --mode=clean rm -f src/parse2    src/parse2.lo
	$(LIBTOOL) --mode=clean rm -f src/parse3    src/parse3.lo
	$(LIBTOOL) --mode=clean rm -f src/parse4    src/parse4.lo
	$(LIBTOOL) --mode=clean rm -f src/reader1   src/reader1.lo
	$(LIBTOOL) --mode=clean rm -f src/reader2   src/reader2.lo
	$(LIBTOOL) --mode=clean rm -f src/reader3   src/reader3.lo
	$(LIBTOOL) --mode=clean rm -f src/reader4   src/reader4.lo
	$(LIBTOOL) --mode=clean rm -f src/tree1     src/tree1.lo
	$(LIBTOOL) --mode=clean rm -f src/tree2     src/tree2.lo
	$(LIBTOOL) --mode=clean rm -f src/tree-rim  src/tree-rim.lo
	$(LIBTOOL) --mode=clean rm -f src/tutorial/attribute src/tutorial/attribute.lo
	$(LIBTOOL) --mode=clean rm -f src/tutorial/keyword   src/tutorial/keyword.lo
	$(LIBTOOL) --mode=clean rm -f src/tutorial/xpath     src/tutorial/xpath.lo
	rm -f a.out

rimxml:
	cp -v ~/Documents/technical/Specifications/RIM\ \(BlackBerry\ Provisioning\ System\)/RIM_XML_Examples/* \
		data/rim/
