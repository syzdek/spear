/* gcc hello-mysql.c `mysql_config5 --cflags` `mysql_config5 --libs` */

#include <stdio.h>
#include <mysql.h>


int main(int argc, char * argv[]);
int main(int argc, char * argv[])
{
   MYSQL      * my;
   MYSQL_RES  * res;
   MYSQL_ROW    row;
   unsigned     y;

   if (argc < 3)
   {
      fprintf(stderr, "Usage: %s <db> <query> <param1> <param2>...<paramN>\n", argv[0]);
      fprintf(stderr, "Example:\n");
      fprintf(stderr, "    %s test.db \"SELECT * FROM tablename WHERE colid = :$ OR $2;\" 5 19\n", argv[0]);
      fprintf(stderr, "\n");
      return(1);
   };

   if ((my = mysql_init(NULL)) == NULL)
   {
      fprintf(stderr, "%s: out of virtual memory\n", argv[0]);
      return(1);
   };

   if (!(mysql_real_connect(my, "localhost", "root", NULL, argv[1], 0, NULL, 0)))
   {
      fprintf(stderr, "%s: mysql_real_connect(): %s\n", argv[0], mysql_error(my));
      mysql_close(my);
      return(1);
   };

   if ((mysql_query(my, argv[2])))
   {
      fprintf(stderr, "%s: mysql_query(): %s\n", argv[0], mysql_error(my));
      mysql_close(my);
      return(1);
   };

   res = mysql_store_result(my);
   printf("found %i columns\n", mysql_num_fields(res));

   while((row = mysql_fetch_row(res)) != NULL)
   {
      for(y = 0; y < mysql_num_fields(res); y++)
         printf("%s, ", row[y]);
      printf("\n");
   };

   mysql_free_result(res);

   mysql_close(my);

   return(0);
}
