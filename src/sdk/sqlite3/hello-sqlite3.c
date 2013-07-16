
#include <stdio.h>
#include <sqlite3.h>
#include <stdlib.h>


int main(int argc, char * argv[]);
int main(int argc, char * argv[])
{
   sqlite3 * db;
   char    * errmsg = 0;
   int       rc;

   if (argc != 2)
   {
      fprintf(stderr, "Usage: %s <db>\n", argv[0]);
      return(1);
   };

   rc = sqlite3_open(argv[1], &db);
   if ((rc))
   {
      fprintf(stderr, "%s sqlite3_open(): %s\n", argv[0], sqlite3_errmsg(db));
      return(1);
   };

   sqlite3_close(db);

   return(0);
}
