all: clean
	gcc -g -o unix-socket-server.o unix-socket-server.c
	gcc -g -o unix-socket-client.o unix-socket-client.c
	gcc -g -o unix-socket-server-poll.o unix-socket-server-poll.c
	gcc -g -o getpeername.o getpeername.c
	gcc -g -o libwrap.o libwrap.c -lwrap

clean:
	if [ -f a.out ];then rm a.out;fi
	-rm -f *.o
