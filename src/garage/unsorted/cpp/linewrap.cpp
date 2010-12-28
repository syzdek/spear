/*

  This program takes input and wraps it to 78 chars in length between 
  new lines and pads it with a space in the beginning.  This is to
  make lines on LDAP queries to conform to ldif standards.

  --David Syzdek
  
  P.S. Yes, Royce I know that perl can probably do this, it's on my list.

*/

#include <stdio.h>

int main(){

  // Sets up Vars
     char Input;
     char String[2];
       String[1]='\0';
     int Count;
     int MaxLineSize=78;
     
  // Main Loop
     Count=1;
     while ( ( Input=getchar() ) != EOF ) {	// Reads one char at a time
       String[0]=Input;
       printf(String);				// Prints char
       Count++;					// incr counter
       if ( Input == '\n' )			// resets counter if new line
          Count=1;
       if ( Count > MaxLineSize ) {		// starts new line 
         Count=2;
         printf("\n ");
       };
     };

  // And that's a wrap
     return(0);
}
      
    
