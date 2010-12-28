
LIBTOOL	= glibtool
CC	= gcc

CFLAGS  = -W -Wall -Werror 
LDFLAGS = -W -Wall -Werror -lcurl

PROGRAMS	= \
		  src/postit2 \
		  src/post-callback

all: $(PROGRAMS)

src/postit2: Makefile src/postit2.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS)  -o ${@}.lo -c ${@}.c
	$(LIBTOOL) --mode=link    $(CC) $(LDFLAGS) -o ${@}       ${@}.lo

src/post-callback: Makefile src/post-callback.c
	$(LIBTOOL) --mode=compile $(CC) $(CFLAGS)  -o ${@}.lo -c ${@}.c
	$(LIBTOOL) --mode=link    $(CC) $(LDFLAGS) -o ${@}       ${@}.lo

clean:
	$(LIBTOOL) --mode=clean rm -f src/postit2       src/postit2.lo
	$(LIBTOOL) --mode=clean rm -f src/post-callback src/post-callback.lo
	rm -f a.out

