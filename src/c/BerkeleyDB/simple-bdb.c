/*
 * libwrap.c - simple example of using libwrap
 * $Source$
 * $Revision$
 * $Date$
 * $Author$
 */
/*
 * Build:
 *    gcc -g -o simple-bdb.o simple-bdb.c -ldb   // Slackware 8.1
 */

/////////////
//         //
// Headers //
//         //
/////////////
						/******************************************/
   #include	<sys/types.h>
   #include     <stdio.h>			/* standard I/O                           */
   #include     <db.h>				/* Network include file                   */
//   #include	"example.h"			/* Configurations for example programs    */
						/******************************************/

///////////////////
//               //
// Main Function //
//               //
///////////////////
int main(int argc, char *argv[]) {

   /* Declare local vars */			/***********************************/
      DB *dbp;					/* pointer to database             */
      int ret;					/* return code/message             */
      DBT key, data;				/* Database key and data variables */

   /* Create Database handle */
      if ((ret = db_create(&dbp, NULL, 0)) != 0) {
         fprintf(stderr, "db_create: %s\n", db_strerror(ret));
         return(1);
      };

   /* Opens database */
      ret = dbp->open(dbp, NULL, "/tmp/access.db", NULL, DB_BTREE, DB_CREATE, 0664);
      if (ret != 0) {
         dbp->err(dbp, ret, "%s", "/tmp/access.db");
         dbp->close(dbp, 0);
         return(1);
      };

   /* Clear variables to avoid garbage */
      memset(&key, 0, sizeof(key));
      memset(&data, 0, sizeof(data));

   /* Preps data to be added */
      key.data = "fruit";
      key.size = sizeof("fruit");
      data.data = "apple";
      data.size = sizeof("apple");

   /* pushes data into database */
      if ((ret = dbp->put(dbp, NULL, &key, &data, 0)) == 0) {
         printf("db: %s: key stored.\n", (char *)key.data);
	} else {
         dbp->err(dbp, ret, "DB->put");
         //goto err;
      };

   /* Close Database and exit */
      dbp->close(dbp, 0);
      return(1);

};


