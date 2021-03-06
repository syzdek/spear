#
#   Simple Programming Examples And References
#   Copyright (C) 2011 David M. Syzdek <david@syzdek.net>.
#
#   @SYZDEK_BSD_LICENSE_START@
#
#   Redistribution and use in source and binary forms, with or without
#   modification, are permitted provided that the following conditions are
#   met:
#
#      * Redistributions of source code must retain the above copyright
#        notice, this list of conditions and the following disclaimer.
#      * Redistributions in binary form must reproduce the above copyright
#        notice, this list of conditions and the following disclaimer in the
#        documentation and/or other materials provided with the distribution.
#      * Neither the name of David M. Syzdek nor the
#        names of its contributors may be used to endorse or promote products
#        derived from this software without specific prior written permission.
#
#   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
#   IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
#   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
#   PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL BINDLE BINARIES BE LIABLE FOR
#   ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
#   DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
#   SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
#   CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
#   LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
#   OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
#   SUCH DAMAGE.
#
#   @SYZDEK_BSD_LICENSE_END@
#
#   @configure_input@
#
#   src/sdk/openssl/Makefile - compiles LDAP examples
#

PROGRAMS	= sha1hash peminfo servercertinfo servercainfo
HEADERS		= common.h

CFLAGS		?= -pedantic -W -Wall -Werror -O2  -Wno-deprecated
LDFLAGS		?= -lcrypto -lssl

HOST		?= www.openssl.org
PORT		?= 443
FILE		?= test.pem

all: $(PROGRAMS)

common.o: Makefile common.c $(HEADERS)
	$(CC) $(CFLAGS) -c common.c

peminfo.o: Makefile peminfo.c $(HEADERS)
	$(CC) $(CFLAGS) -c peminfo.c

peminfo: Makefile $(HEADERS) peminfo.o common.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o ${@} peminfo.o common.o

servercainfo.o: Makefile servercainfo.c $(HEADERS)
	$(CC) $(CFLAGS) -c servercainfo.c

servercainfo: Makefile $(HEADERS) servercainfo.o common.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o ${@} servercainfo.o common.o

servercertinfo.o: Makefile servercertinfo.c $(HEADERS)
	$(CC) $(CFLAGS) -c servercertinfo.c

servercertinfo: Makefile $(HEADERS) servercertinfo.o common.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o ${@} servercertinfo.o common.o

sha1hash.o: Makefile sha1hash.c $(HEADERS)
	$(CC) $(CFLAGS) -c sha1hash.c

sha1hash: Makefile $(HEADERS) sha1hash.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o ${@} sha1hash.o

.PHONY: test

test: $(PROGRAMS)
	./serverinfo "$(HOST)" "$(PORT)" "$(FILE)"
	@echo " "
	@echo " "
	./peminfo "$(FILE)"
	@echo " "
	@echo " "

clean:
	rm -f $(PROGRAMS)
	rm -f *.o
	rm -f a.out

# end of Makefile
