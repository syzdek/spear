
CPPFLAGS = -W -Wall -Werror

all: nsstring nsstring2

nsstring: Makefile nsstring.m
	gcc $(CPPFLAGS) -o nsstring nsstring.m -framework Foundation

nsstring2: Makefile nsstring2.m
	gcc $(CPPFLAGS) -o nsstring2 nsstring2.m -framework Foundation

clean:
	rm -f *.o
	rm -f nsstring nsstring2
