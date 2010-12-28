objects = chroot.o

strictflags = -O2 -Werror -Wall -pedantic -g -Wtraditional -W -Wimplicit -Wmain -Wparentheses -Wreturn-type -Wunused -Wswitch -Wcomment -Wformat -Wchar-subscripts -Wuninitialized -Wshadow -Wpointer-arith -Wcast-qual -Wcast-align -Wwrite-strings -Wconversion -Waggregate-return -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wredundant-decls -Wnested-externs -Winline

#generalflags = -O2 -Werror -Wall -pedantic -g -Wtraditional -W

flags = $(strictflags)

gcc = gcc

g++ = g++

all: clean $(objects)  

chroot.o: $(objects) $(alpined-o)
	$(gcc) $(flags) -o chroot.o chroot.c

clean:
	-rm -f a.out
	-rm -f *.o
