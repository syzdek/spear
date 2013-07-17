
#include <stdio.h>
#include <sqlite3.h>
#include <stdlib.h>


int main(int argc, char * argv[]);
int main(int argc, char * argv[])
{
   sqlite3       * db;
   sqlite3_stmt  * pstmt;
   int             err;
   int             x;
   int             count;

   if (argc < 3)
   {
      fprintf(stderr, "Usage: %s <db> <query> <param1> <param2>...<paramN>\n", argv[0]);
      fprintf(stderr, "Example:\n");
      fprintf(stderr, "    %s test.db \"SELECT * FROM tablename WHERE colid = :$ OR $2;\" 5 19\n", argv[0]);
      fprintf(stderr, "\n");
      return(1);
   };

   if ((err = sqlite3_open(argv[1], &db)))
   {
      fprintf(stderr, "%s sqlite3_open(): %s\n", argv[0], sqlite3_errmsg(db));
      return(1);
   };

   if ((err = sqlite3_prepare_v2(db, argv[2], 1024, &pstmt, NULL)))
   {
      fprintf(stderr, "%s sqlite3_prepare_v2(): %s\n", argv[0], sqlite3_errmsg(db));
      sqlite3_close(db);
      return(1);
   };

   for(x = 3; x < argc; x++)
   {
      if ((err = sqlite3_bind_text(pstmt, x-2, argv[x], -1, SQLITE_STATIC)) != 0)
      {
         fprintf(stderr, "%s sqlite3_bind_text(): %s\n", argv[0], sqlite3_errmsg(db));
         sqlite3_close(db);
         return(1);
      };
   };

   err = sqlite3_step(pstmt);

   count = sqlite3_column_count(pstmt);

   for(x = 0; x < count; x++)
      printf("%s, ", sqlite3_column_name(pstmt, x));
   printf("\n");

   while(err != SQLITE_DONE)
   {
      switch(err)
      {
         case SQLITE_ROW:
         for(x = 0; x < count; x++)
         {
            switch(sqlite3_column_type(pstmt, x))
            {
               case SQLITE_BLOB:
               printf("%s, ", sqlite3_column_blob(pstmt, x));
               break;

               case SQLITE_FLOAT:
               printf("%f, ", sqlite3_column_double(pstmt, x));
               break;

               case SQLITE_INTEGER:
               printf("%i, ", sqlite3_column_int(pstmt, x));
               break;

               case SQLITE_NULL:
               printf("%s, ", "NULL");
               break;

               case SQLITE_TEXT:
               default:
               printf("%s, ", sqlite3_column_text(pstmt, x));
            };
         };
         printf("\n");
         break;

         case SQLITE_ERROR:
         fprintf(stderr, "%s sqlite3_step(): %s\n", argv[0], sqlite3_errmsg(db));
         break;

         default:
         fprintf(stderr, "%s: %i: unknown response\n", argv[0], err);
      };
      err = sqlite3_step(pstmt);
   };

   sqlite3_finalize(pstmt);

   sqlite3_close(db);

   return(0);
}
