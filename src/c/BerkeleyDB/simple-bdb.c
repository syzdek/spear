/*
 * libwrap.c - simple example of using libwrap
 * $Source$
 * $Revision$
 * $Date$
 * $Author$
 */
/*
 * Build:
 *    gcc -g -o libwrap.o libwrap.c -lwrap                              // Slackware 8.1
 *    gcc -g -o libwrap.o libwrap.c -lwrap -lwrap -lsocket -lnsl        // Solaris 5.9
 */

/////////////
//         //
// Headers //
//         //
/////////////
						/******************************************/
   #include     <stdio.h>			/* standard I/O                           */
   #include     <db.h>				/* Network include file                   */
						/******************************************/

/////////////////////
//                 //
// Global Settings //
//                 //
/////////////////////

   #define DATABASE "access.db"


///////////////////
//               //
// Main Function //
//               //
///////////////////
int main(int argc, char *argv[]) {

   /* Declare local vars */
      DB *dbp;
      int ret;

   /* Create Database handle */
      if ((ret = db_create(&dbp, NULL, 0)) != 0) {
         fprintf(stderr, "db_create: %s\n", db_strerror(ret));
         return(1);
      };

   /* Opens database */
      if ((ret = dbp->open(dbp, NULL, DATABASE, NULL, DB_TREE, DB_CREATE, 0664)) != 0) {
         dpb->err(dbp, ret, "%s", DATABASE);

   /* Exit function */
      return(0);

};

