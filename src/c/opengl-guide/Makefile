examples = example.p6.f1-1

syzdek = syzdek-001

gcc = gcc

libpath = -L/usr/X11R6/lib

libs = -lglut

strictflags = -Wall 

flags = $(strictflags)

all: $(examples) $(syzdek)

example.p6.f1-1:
	$(gcc) -o example.p6.f1-1.o example.p6.f1-1.c $(flags) $(libs) $(libpath)

syzdek-001:
	$(gcc) -o syzdek-001.o syzdek-001.c $(flags) $(libs) $(libpath)

clean:
	-rm -f a.out
	-rm -f *.o
