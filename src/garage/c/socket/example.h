/*
 * example.h - Config for examples
 * $Source$
 * $Revision$
 * $Date$
 * $Author$
 */

   /* Package Info */
      #define PACKAGE			"sockettest"

   /* Local Connections */
      #define LOCAL_PORT		5050
      #define LOCAL_INTERFACE		"127.0.0.1"	// To listen on any address set sockaddr_in.sin_addr.s_addr to INADDR_ANY

   /* Connection limits */
      #define MAX_PENDING_CONNETIONS	5
      #define MAX_ACTIVE_CONNECTIONS	10

   /* Timeout settings */
      #define LOCAL_TIMEOUT_SEC		5		// Timeout in Seconds
      #define LOCAL_TIMEOUT_USEC	100		// Timeout in Microseconds
      #define LOCAL_TIMEOUT_INTPUT	30		// Timeout in Seconds
      #define LOCAL_TIMEOUT_IDLE	10		// Timeout in Seconds

   /* Buffer Sizes */
      #define INPUT_BUFFER		1024

