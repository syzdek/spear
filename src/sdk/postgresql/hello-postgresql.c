
#include <stdio.h>
#include <libpq-fe.h>


int main(int argc, char * argv[]);
int main(int argc, char * argv[])
{
   const char * db   = NULL;
   PGconn     * pd;
   char         conninfo[1024];

   if (argc != 2)
   {
      fprintf(stderr, "Usage: %s <db>\n", argv[0]);
      return(1);
   };
   db = argv[1];

   snprintf(conninfo, 1024, "host=localhost dbname=%s", db);
   if ((pd = PQconnectdb(conninfo)) == NULL)
   {
      fprintf(stderr, "%s: PQconnectdb(): Unable to initialize database library.", argv[0]);
      return(1);
   };

   if (PQstatus(pd) != CONNECTION_OK)
   {
      fprintf(stderr, "%s: PQconnectdb(): %s\n", argv[0], PQerrorMessage(pd));
      PQfinish(pd);
      return(1);
   };

   PQfinish(pd);

   return(0);
}
