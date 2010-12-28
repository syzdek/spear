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
   #include     <stdio.h>			/* standard I/O                           */
   #include     <db.h>				/* Network include file                   */
   #include	"example.h"			/* Configurations for example programs    */
						/******************************************/

///////////////////
//               //
// Main Function //
//               //
///////////////////
int main(int argc, char *argv[]) {

   /* Declare local vars */			/***********************************/
      DB_ENV *dbenv;				/* pointer to database environment */
      DB *dbp1;					/* pointer to 1st database         */
      DB *dbp2;					/* pointer to 2nd database         */
      DBT key1, data1;				/* Database key and data variables */
      DBT key2, data2;				/* Database key and data variables */
      int ret;					/* return code/message             */

   /* Creates the DB environment */
      if ((ret = db_env_create(&dbenv, 0)) != 0) {
         fprintf(stderr, "%s: %s\n", argv[0], db_strerror(ret));
         return(1);
      };
      dbenv->set_errfile(dbenv, stderr);
      dbenv->set_errpfx(dbenv, argv[0]);

   /* Set shared memory buffer pool cachesize: 5MB.            */
   /* Databases are in a subdirectory of the environment home. */
      if ((ret = dbenv->set_cachesize(dbenv, 0, 5 * 1024 * 1024, 0)) != 0) {
         dbenv->err(dbenv, ret, "set_cachesize");
         dbenv->close(dbenv, 0);
         return(1);
      };
      if ((ret = dbenv->set_data_dir(dbenv, MY_DBENV_DIR_DATA)) != 0) {
         dbenv->err(dbenv, ret, "set_data_dir: %s", MY_DBENV_DIR_DATA);
         dbenv->close(dbenv, 0);
         return(1);
      };

   /* Open the environment with full transactional support. */
      dbenv->open(
         dbenv, 
         MY_DBENV_DIR_HOME, 
         DB_CREATE 
         | DB_INIT_LOG 
         | DB_INIT_LOCK 
         | DB_INIT_MPOOL 
         | DB_INIT_TXN, 
         0
      );
      if (ret != 0) {
         dbenv->err(dbenv, ret, "environment open: %s", MY_DBENV_DIR_HOME);
         dbenv->close(dbenv, 0);
         return(1);
      };
      

   /* Create first Database handle */
      if ((ret = db_create(&dbp1, dbenv, 0)) != 0) {
         dbenv->err(dbenv, ret, "database create");
         dbenv->close(dbenv, 0);
         return(1);
      };

   /* Opens first database */
      if ((ret = dbp1->open(dbp1, NULL, MY_DB1_FILE, NULL, DB_BTREE, DB_CREATE, 0640)) != 0) {
         dbenv->err(dbenv, ret, "DB->open: %s", MY_DB1_FILE);
         dbp1->close(dbp1, 0);
         dbenv->close(dbenv, 0);
         return (ret);
      };

   /* Create second Database handle */
      if ((ret = db_create(&dbp2, dbenv, 0)) != 0) {
         dbenv->err(dbenv, ret, "database create");
         dbp1->close(dbp1, 0);
         dbenv->close(dbenv, 0);
         return(1);
      };

   /* Opens second database */
      if ((ret = dbp2->open(dbp2, NULL, MY_DB2_FILE, NULL, DB_BTREE, DB_CREATE, 0640)) != 0) {
         dbenv->err(dbenv, ret, "DB->open: %s", MY_DB2_FILE);
         dbp1->close(dbp1, 0);
         dbp2->close(dbp1, 0);
         dbenv->close(dbenv, 0);
         return (ret);
      };

   /* Clears variables to avoid garbage */
      memset(&key1, 0, sizeof(key1));
      memset(&data1, 0, sizeof(data1));
      memset(&key2, 0, sizeof(key2));
      memset(&data2, 0, sizeof(data2));

   /* Preps data to be added to first database */
      key1.data = "fruit";
      key1.size = sizeof("fruit");
      data1.data = "apple";
      data1.size = sizeof("apple");

   /* pushes data into first database */
      if ((ret = dbp1->put(dbp1, NULL, &key1, &data1, 0)) == 0) {
         printf("db: %s: key stored.\n", (char *)key1.data);
        } else {
         dbp1->err(dbp1, ret, "DB->put");
         dbp1->close(dbp1, 0);
         dbp2->close(dbp2, 0);
         dbenv->close(dbenv, 0);
         return(1);
      };

   /* Preps data for second database */
      key2 = data1;
      data2.data = "red";
      data2.size = sizeof("red");

   /* pushes data into second database */
      if ((ret = dbp2->put(dbp2, NULL, &key2, &data2, 0)) == 0) {
         printf("db: %s: key stored.\n", (char *)key2.data);
        } else {
         dbp1->err(dbp2, ret, "DB->put");
         dbp1->close(dbp1, 0);
         dbp2->close(dbp2, 0);
         dbenv->close(dbenv, 0);
         return(1);
      };

   /* Pulls data from database */
      if ((ret = dbp1->get(dbp1, NULL, &key1, &data1, 0)) == 0) {
         printf("db: %s: key retrieved: data was %s.\n", (char *)key1.data, (char *)data1.data);
         if ((ret = dbp1->get(dbp2, NULL, &data1, &data2, 0)) == 0) {
            printf("db: %s: key retrieved: data was %s.\n", (char *)data1.data, (char *)data2.data);
           } else {
            dbp1->err(dbp2, ret, "DB->get");
            dbp1->close(dbp1, 0);
            dbp2->close(dbp2, 0);
            dbenv->close(dbenv, 0);
            return(1);
         };
        } else {
         dbp1->err(dbp2, ret, "DB->get");
         dbp1->close(dbp1, 0);
         dbp2->close(dbp2, 0);
         dbenv->close(dbenv, 0);
         return(1);
      };

   /* Exit function */
      dbp1->close(dbp1, 0);
      dbp2->close(dbp2, 0);
      dbenv->close(dbenv, 0);
      return(0);

};

