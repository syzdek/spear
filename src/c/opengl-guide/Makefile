examples = example.p6.f1-1

gcc = gcc

libpath = -L/usr/X11R6/lib

libs = -lglut

strictflags = -Wall 

flags = $(strictflags)

all: clean $(examples)

example.p6.f1-1:
	$(gcc) -o example.p6.f1-1.o example.p6.f1-1.c $(flags) $(libs) $(libpath)

clean:
	-rm -f a.out
	-rm -f *.o
