#examples = example.p6.f1-1

syzdek = syzdek-001 syzdek-002 glx

gcc = gcc

libpath = -L/usr/X11R6/lib

libs = -lglut

#strictflags = -O2 -Werror -Wall -pedantic -g -Wtraditional -W -Wimplicit -Wmain -Wparentheses -Wreturn-type -Wunused -Wswitch -Wcomment -Wformat -Wchar-subscripts -Wuninitialized -Wshadow -Wpointer-arith -Wcast-qual -Wcast-align -Wwrite-strings -Wconversion -Waggregate-return -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wredundant-decls -Wnested-externs -Winline

strictflags = -O2 -Werror -W

flags = $(strictflags)

all: $(syzdek)

example.p6.f1-1:
	$(gcc) -o example.p6.f1-1.o example.p6.f1-1.c $(flags) $(libs) $(libpath)

syzdek-001:
	$(gcc) -o syzdek-001.o syzdek-001.c $(flags) $(libs) $(libpath)

syzdek-002:
	$(gcc) -o syzdek-002.o syzdek-002.c $(flags) $(libs) $(libpath)

glx:
	gcc -o glx.o glx.c -O2 -Werror -W -lGL -L/usr/X11R6/lib

clean:
	-rm -f a.out
	-rm -f *.o
