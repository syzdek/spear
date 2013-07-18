
#include <stdio.h>
#include <libpq-fe.h>


int main(int argc, char * argv[]);
int main(int argc, char * argv[])
{
   PGconn         * pd;
   PGresult       * res;
   int              x;
   int              y;
   char         conninfo[1024];

   if (argc < 3)
   {
      fprintf(stderr, "Usage: %s <db>\n", argv[0]);
      return(1);
   };

   snprintf(conninfo, 1024, "host=localhost dbname=%s", argv[1]);
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

   res = PQexec(pd, argv[2]);
   if ((!res) || ((PQresultStatus(res) != PGRES_TUPLES_OK)))
   {
      fprintf(stderr, "%s: PQexec(): %s\n", argv[0], PQerrorMessage(pd));
      PQclear(res);
      PQfinish(pd);
      return(1);
   };

   printf("%i rows found\n", PQntuples(res));
   printf("%i columns in rows\n", PQnfields(res));

   for(y = 0; y < PQnfields(res); y++)
      printf("%s, ", PQfname(res, y));
   printf("\n");

   for(x = 0; x < PQntuples(res); x++)
   {
      for(y = 0; y < PQnfields(res); y++)
      {
         if ((PQgetisnull(res, x,y)))
         {
            printf("NULL, ");
            continue;
         };
         switch(PQftype(res, y))
         {
            case 25:
            printf("text");
            break;

            case VARCHAROID:
            printf("varchar");
            break;

            default:
            break;
         };
         printf("%s, ", PQgetvalue(res, x, y));
      };
      printf("\n");
   };

   PQclear(res);

   PQfinish(pd);

   return(0);
}
