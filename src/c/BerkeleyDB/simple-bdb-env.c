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
      

   /* Create Database handle */
      if ((ret = db_create(&dbp1, dbenv, 0)) != 0) {
         dbenv->err(dbenv, ret, "database create");
         dbenv->close(dbenv, 0);
         return(1);
      };

   /* Opens database */
      ret = dbp1->open(dbp1, NULL, MY_DB1_FILE, NULL, DB_BTREE, DB_CREATE, 0640);
      if (ret != 0) {
      //if ((ret = dbp1->open(dbp1, NULL, MY_DB1_FILE, NULL, DB_BTREE, DB_CREATE, 0640)) != 0) {
         dbenv->err(dbenv, ret, "DB->open: %s", MY_DB1_FILE);
         dbenv->close(dbenv, 0);
         return (ret);
      };
         

   dbenv->close(dbenv, 0);
   /* Exit function */
      return(0);

};

