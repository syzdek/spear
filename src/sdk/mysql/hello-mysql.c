/* gcc hello-mysql.c `mysql_config5 --cflags` `mysql_config5 --libs` */

#include <stdio.h>
#include <mysql.h>
//#include <my_global.h>
//#include <my_sys.h>

int main(int argc, char * argv[]);
int main(int argc, char * argv[])
{
   const char * db   = NULL;
   MYSQL      * my;
   MYSQL_RES  * res;
   MYSQL_ROW    row;

   if (argc != 2)
   {
      fprintf(stderr, "Usage: %s <db>\n", argv[0]);
      return(1);
   };
   db = argv[1];

   if ((my = mysql_init(NULL)) == NULL)
   {
      fprintf(stderr, "%s: out of virtual memory\n", argv[0]);
      return(1);
   };

   if (!(mysql_real_connect(my, NULL, NULL, NULL, db, 0, NULL, 0)))
   {
      fprintf(stderr, "%s: mysql_real_connect(): %s\n", argv[0], mysql_error(my));
      mysql_close(my);
      return(1);
   };

   if ((mysql_query(my, "SELECT appSchemaUUID, appSchemaName FROM appSchema")))
   {
      fprintf(stderr, "%s: mysql_query(): %s\n", argv[0], mysql_error(my));
      mysql_close(my);
      return(1);
   };

   res = mysql_use_result(my);
   printf("found %i rows\n", mysql_num_fields(res));

   while((row = mysql_fetch_row(res)) != NULL)
   {
      printf("%s - %s\n", row[0], row[1]);
   };

   mysql_free_result(res);

   mysql_close(my);

   return(0);
}
