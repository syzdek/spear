/*
 * Simple Socket Server Example
 * $Source$
 * $Revision$
 * $Date$
 * $Author$
 */
/*
 * unix-socket-server.c - simple socket server example
 */
/*
 * Source from:
 *    Network programming under Unix systems - Part II
 *    http://users.actcom.co.il/~choo/lupg/tutorials/internetworking/internet-programming.html#sockaddr
 */
/*
 * Build:
 *    gcc -g -o unix-socket-server.o unix-socket-server.c
 */



#include <stdio.h>       /* Basic I/O routines          */
#include <sys/types.h>   /* standard system types       */
#include <netinet/in.h>  /* Internet address structures */
#include <sys/socket.h>  /* socket interface functions  */
#include <netdb.h>       /* host to IP resolution       */


#define  PORT   5050           /* port of "hello world" server */
#define  LINE   "hello world"  /* what to say to our clients   */

int main()
{
    int                rc;       /* system calls return value storage  */
    int                s;        /* socket descriptor                  */
    int                cs;       /* new connection's socket descriptor */
    struct sockaddr_in sa;       /* Internet address struct            */
    struct sockaddr_in csa;      /* client's address struct            */
    int                size_csa; /* size of client's address struct    */

    /* initiate machine's Internet address structure */
    /* first clear out the struct, to avoid garbage  */
    memset(&sa, 0, sizeof(sa));
    /* Using Internet address family */
    sa.sin_family = AF_INET;
    /* copy port number in network byte order */
    sa.sin_port = htons(PORT);
    /* we will accept connections coming through any IP */
    /* address that belongs to our host, using the      */
    /* INADDR_ANY wild-card.                            */
    sa.sin_addr.s_addr = INADDR_ANY;

    /* allocate a free socket */
    /* Internet address family, Stream socket */
    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) {
        perror("socket: allocation failed");
    }

    /* bind the socket to the newly formed address */
    rc = bind(s, (struct sockaddr *)&sa, sizeof(sa));

    /* check there was no error */
    if (rc) {
        perror("bind");
    }

    /* ask the system to listen for incoming connections   */
    /* to the address we just bound. specify that up to    */
    /* 5 pending connection requests will be queued by the */
    /* system, if we are not directly awaiting them using  */
    /* the accept() system call, when they arrive.         */
    rc = listen(s, 5);

    /* check there was no error */
    if (rc) {
        perror("listen");
    }

    /* remember size for later usage */
    size_csa = sizeof(csa);

    /* enter an accept-write-close infinite loop */
    while (1) {
        /* the accept() system call will wait for a     */
        /* connection, and when one is established, a   */
        /* new socket will be created to handle it, and */
        /* the csa variable will hold the address       */
        /* of the Client that just connected to us.     */
        /* the old socket, s, will still be available   */
        /* for future accept() statements.              */
        cs = accept(s, (struct sockaddr *)&csa, &size_csa);

        /* check for errors. if any, enter accept mode again */
        if (cs < 0)
            continue;

        /* oak, we got a new connection. do the job... */
        write(cs, LINE, sizeof(LINE));

        /* now close the connection */
        close(cs);
    }
    return(0);
}
