/*
 *  Simple Programming Examples And References
 *  Copyright (C) 2012 David M. Syzdek <david@syzdek.net>.
 *
 *  @SYZDEK_BSD_LICENSE_START@
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are
 *  met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of David M. Syzdek nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 *  IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 *  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL DAVID M. SYZDEK BE LIABLE FOR
 *  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 *  OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 *  SUCH DAMAGE.
 *
 *  @SYZDEK_BSD_LICENSE_END@
 */
/**
 *  @file src/lang/c/pipe/pipedopen.c an example of forking a process and
 *                                      redirecting STDIN, STDOUT, and STDERR
 *                                      to pipes.
 */

///////////////
//           //
//  Headers  //
//           //
///////////////
#ifdef PMARK
#pragma mark - Headers
#endif

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <poll.h>
#include <sys/types.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/wait.h>


/////////////////
//             //
//  Datatypes  //
//             //
/////////////////
#ifdef PMARK
#pragma mark - Datatypes
#endif

struct pipedopen_fds
{
   int   pipein;
   int   pipeout;
   int   pipeerr;
   pid_t pid;
};
typedef struct pipedopen_fds PFDS;


//////////////////
//              //
//  Prototypes  //
//              //
//////////////////
#ifdef PMARK
#pragma mark - Prototypes
#endif

// forks the process with pipes to the childs STDIN, STDOUT, and STDERR
PFDS * pipedfork(void);

// closes pipes to child's process
void pipedclose(PFDS ** pfdsp);

// main loop
int main(int argc, char * argvp[]);


/////////////////
//             //
//  Functions  //
//             //
/////////////////
#ifdef PMARK
#pragma mark - Functions
#endif

/// @brief forks the process with pipes to the child's STDIN, STDOUT, and STDERR
PFDS * pipedfork(void)
{
   PFDS  * pfds;
   int     pipes[6];
   int     pos;

   // creates pipe for STDIN
   if ((pipe(&pipes[0])) == -1)
   {
      return(NULL);
   };

   // creates pipe for STDOUT
   if ((pipe(&pipes[2])) == -1)
   {
      for(pos = 0; pos < 2; pos++)
         close(pipes[pos]);
      return(NULL);
   };

   // creates pipe for STDERR
   if ((pipe(&pipes[4])) == -1)
   {
      for(pos = 0; pos < 4; pos++)
         close(pipes[pos]);
      return(NULL);
   };

   // allocates memory for pipe information
   if ((pfds = calloc(sizeof(PFDS), 1)) == NULL)
   {
      for(pos = 0; pos < 6; pos++)
         close(pipes[pos]);
      return(NULL);
   };

   // fork process
   switch(pfds->pid = fork())
   {
      // error forking process
      case -1:
      for(pos = 0; pos < 6; pos++)
         close(pipes[pos]);
      free(pfds);
      return(NULL);

      // child process
      case 0:
      if ((pfds->pipein = dup2(pipes[0], STDIN_FILENO)) == -1)
      {
         perror("dup2(STDIN_FILENO)");
         for(pos = 0; pos < 6; pos++)
            close(pipes[pos]);
         free(pfds);
         return(NULL);
      };
      if ((pfds->pipeout = dup2(pipes[3], STDOUT_FILENO)) == -1)
      {
         perror("dup2(STDOUT_FILENO)");
         for(pos = 0; pos < 6; pos++)
            close(pipes[pos]);
         free(pfds);
         return(NULL);
      };
      if ((pfds->pipeerr = dup2(pipes[5], STDERR_FILENO)) == -1)
      {
         perror("dup2(STDERR_FILENO)");
         for(pos = 0; pos < 6; pos++)
            close(pipes[pos]);
         free(pfds);
         return(NULL);
      };
      close(pipes[1]);
      close(pipes[2]);
      close(pipes[4]);
      return(pfds);

      // master process
      default:
      fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
      fcntl(pipes[2],     F_SETFL, O_NONBLOCK);
      fcntl(pipes[4],     F_SETFL, O_NONBLOCK);
      pfds->pipein  = pipes[1];
      pfds->pipeout = pipes[2];
      pfds->pipeerr = pipes[4];
      close(pipes[0]);
      close(pipes[3]);
      close(pipes[5]);
      return(pfds);
   };

   return(NULL);
}


/// @brief closes pipes to child's process
/// @param pfds       reference to struct containing pipes to child's process
void pipedclose(PFDS ** pfdsp)
{
   if (!(pfdsp))
      return;
   if (!(*pfdsp))
      return;
   close((*pfdsp)->pipein);
   close((*pfdsp)->pipeout);
   close((*pfdsp)->pipeerr);
   free(*pfdsp);
   *pfdsp = NULL;
   return;
}


/// @brief main loop
/// @param argc       number of arguments passed to program
/// @param argv       array of arguments passed to program
int main(int argc, char * argv[])
{
   int             pos;
   PFDS          * pfds;
   struct pollfd   fds[3];
   int             ret;
   char            buff[2024];
   ssize_t         len;

   if (argc < 2)
   {
      fprintf(stderr, "Usage: %s program args ...\n", argv[0]);
      return(1);
   };

   // forks process
   if (!(pfds = pipedfork()))
   {
      perror("pipedfork()");
      return(1);
   };

   // if child process, call external image
   if (pfds->pid == 0)
   {
      // execvp() is not safe for SETUID programs, use execv() instead
      if ((execvp(argv[1], &argv[1])))
         perror("execvp()");
      pipedclose(&pfds);
      return(1);
   };

   // sets up fds data
   fds[0].fd = STDIN_FILENO;
   fds[1].fd = pfds->pipeout;
   fds[2].fd = pfds->pipeerr;
   for(pos = 0; pos < 3; pos++)
      fds[pos].events = POLLIN | POLLPRI | POLLERR | POLLHUP | POLLRDBAND;

   // loops until exit or error
   while ((ret = poll(fds, 3, -1)) > 0)
   {
      // checks STDIN for data
      if (fds[0].revents & (POLLPRI|POLLIN))
         while((len = read(STDIN_FILENO, buff, 2024)) > 0)
            write(pfds->pipein, buff, len);

      // checks PIPEOUT for data
      if (fds[1].revents & (POLLPRI|POLLIN))
         while((len = read(fds[1].fd, buff, 2024)) > 0)
            write(STDOUT_FILENO, buff, len);

      // checks PIPEERR for data
      if (fds[2].revents & (POLLPRI|POLLIN))
         while((len = read(fds[2].fd, buff, 2024)) > 0)
            write(STDERR_FILENO, buff, len);

      // close pipe if STDIN is closed
      if (fds[0].revents & POLLHUP)
      {
         close(pfds->pipein);
         pfds->pipein = -1;
      };

      // exits if any of the pipes close
      if ( (fds[1].revents & POLLHUP) || (fds[2].revents & POLLHUP) )
      {
         if ((waitpid(pfds->pid, &ret, 0)) == -1)
            perror("waitid()");
         pipedclose(&pfds);

         // return with exit code of child
         return(WEXITSTATUS(ret));
      };
   };

   // reports error and kills child
   perror("poll()");
   kill(pfds->pid, SIGKILL);
   pipedclose(&pfds);

   return(1);
}


/* end of source */
