
CPPFLAGS = -W -Wall -Werror

all: hello

hello.o: Makefile hello.m HelloWorld.h
	gcc $(CPPFLAGS) -o hello.o -c hello.m

HelloWorld.o: Makefile HelloWorld.m HelloWorld.h
	gcc $(CPPFLAGS) -o HelloWorld.o -c HelloWorld.m

hello: HelloWorld.o hello.o
	gcc -W -Wall -Werror -o hello hello.o HelloWorld.o -framework Foundation

clean:
	rm -f *.o
	rm -f hello
