/*
 * Simple Socket Client Example
 * $Source$
 * $Revision$
 * $Date$
 * $Author$
 */
/*
 * unix-socket-client.c - simple socket client example
 */
/*
 * Source from:
 *    Network programming under Unix systems - Part II
 *    http://users.actcom.co.il/~choo/lupg/tutorials/internetworking/internet-programming.html#sockaddr
 */
/*
 * Build:
 *    gcc -g -o unix-socket-client.o unix-socket-client.c
 */

#include <stdio.h>         /* Basic I/O routines          */
#include <sys/types.h>     /* standard system types       */
#include <netinet/in.h>    /* Internet address structures */
#include <sys/socket.h>    /* socket interface functions  */
#include <netdb.h>         /* host to IP resolution       */

#define  HOSTNAMELEN   40   /* maximal host name length */
#define  BUFLEN        1024   /* maximum response size  */
#define  PORT          13   /* port of daytime server   */

int main(int argc, char *argv[])
{
    int                 rc;            /* system calls return value storage */
    int                 s;             /* socket descriptor                 */
    char                buf[BUFLEN+1]; /* buffer server answer              */
    char*               pc;            /* pointer into the buffer           */
    struct sockaddr_in  sa;            /* Internet address struct           */
    struct hostent*     hen;           /* host-to-IP translation            */

    /* check there are enough parameters */
    if (argc < 2) {
        fprintf(stderr, "Missing host name\n");
        exit (1);
    }

    /* Address resolution stage */
    hen = gethostbyname(argv[1]);
    if (!hen) {
        perror("couldn't resolve host name");
    }

    /* initiate machine's Internet address structure */
    /* first clear out the struct, to avoid garbage  */
    memset(&sa, 0, sizeof(sa));

    /* Using Internet address family */
    sa.sin_family = AF_INET;
    /* copy port number in network byte order */
    sa.sin_port = htons(PORT);
    /* copy IP address into address struct */
    memcpy(&sa.sin_addr.s_addr, hen->h_addr_list[0], hen->h_length);

    /* allocate a free socket                 */
    /* Internet address family, Stream socket */
    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) {
        perror("socket: allocation failed");
    }

    /* now connect to the remote server. the system will */
    /* use the 4th binding method (see section 3)        */
    /* note the cast to a struct sockaddr pointer of the */
    /* address of variable sa.                           */
    rc = connect(s, (struct sockaddr *)&sa, sizeof(sa));

    /* check there was no error */
    if (rc) {
        perror("connect");
    }

    /* now that we are connected, start reading the socket */
    /* till read() returns 0, meaning the server closed    */
    /* the connection.                                     */
    pc = buf;

    while (rc = read(s, pc, BUFLEN - (pc-buf))) {
        pc += rc;
    }

    /* close the socket */
    close(s);

    /* pad a null character to the end of the result */
    *pc = ' ';

    /* print the result */
    printf("Time: %s\n", buf);

     /* and terminate */
    return 0;
}
