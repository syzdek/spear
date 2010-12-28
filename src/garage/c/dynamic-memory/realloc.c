/*
 * growing-buffer.c - simple example of realloc()   taken mostly from growing-buffer.c
 * $Source$
 * $Revision$
 * $Date$
 * $Author$
 */
/*
 * Build:
 *    Easy Build:
 *       gcc -g -o realloc.o realloc.c
 */
/*    Force Good Programming Habits (you masicist you) */
/*       gcc -g -o realloc.o realloc.c -O2 -Werror -Wall \
            -pedantic -g -Wtraditional -W -Wimplicit -Wmain -Wparentheses \
            -Wreturn-type -Wunused -Wswitch -Wcomment -Wformat \
            -Wchar-subscripts -Wshadow -Wcast-qual -Wcast-align \
            -Wwrite-strings -Wconversion -Waggregate-return \
            -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations \
            -Wredundant-decls -Wnested-externs -Winline
 */


/////////////
//         //
// Headers //
//         //
/////////////

   #include     <stdio.h>					/*  standard I/O    */
   #include     <stdlib.h>					/*  standard  libs  */


//////////////////
//              //
//  Prototypes  //
//              //
//////////////////

   int main(void);						/*  Main statement  */

///////////////////
//               //
// Main Function //
//               //
///////////////////
int main(void) {

   /* Declare local vars */
      char *ptr1;						/*  Pointer 1  points to old buffer                                    */
      char *ptr2;						/*  Pointer 2 used to alloc new buffer size                            */
      char inputchar;						/*  Used to read in one character at a time from STDIN                 */
      unsigned int  buflen;					/*  Used to keep track of the buffer size                              */
       
   /* Initialize pointers */
      ptr1 = NULL;						/*  Havn't used pointer 1 yet, so it should point to NULL              */
      ptr2 = NULL;						/*  Havn't used pointer 2 yet, so it should point to NULL              */
      buflen = 0;						/*  Start the buflen at 0                                              */

   /* Start buffer */
      ptr1 = (char *) malloc(sizeof(char));			/*  Need to start with a buffer of 1 char for the initial \0           */
      if (ptr1 == NULL) {					/*  If the pointer is NULL, malloc was unable to allocate memory       */
         printf("virtual memory exhausted\n");			/*  Let user know what's happening                                     */
         return(1);						/*  Exit with error                                                    */
      };
      ptr1[0] = '\0';						/*  If malloc did work, save NULL character in only element of buffer  */

   /* Loop until EOF, EOL, \n, \r */
      printf("Enter String: ");					/*  Give user instructions                                             */
      inputchar = (char) fgetc(stdin);				/*  Get first character of the user's input                            */
      while ((inputchar > 33) && (inputchar != EOF)) {		/*  Loop until we reach the end of the input                           */
         buflen = strlen(ptr1) + 2;				/*  Compute the size of the old buffer                                 */
         ptr2 = (char *) realloc(ptr1, buflen);			/*  Increase the size of the old buffer by one byte                    */
         if (ptr2 == NULL) {					/*  Verify that realloc was successful                                 */
           printf("Virtual Memory Exhausted\n");             	/*    If not let user know what's happening                            */
           free(ptr1);						/*    Free memory used by buffer                                       */
           return(1);						/*    Exit with an error code of 1                                     */
         };
         ptr2[buflen-2] = inputchar;				/*  Store next character from STDIN                                    */
         ptr2[buflen-1] = '\0';					/*  Add the terminating NULL character at the end of the buffer        */
         ptr1 = ptr2;						/*  The new buffer now becomes the old buffer                          */
         printf("Buffer Size:\t%i\n", strlen(ptr1));		/*  Print buffer stats (for learning purposes only)                    */
         inputchar = (char) fgetc(stdin);			/*  Fetch next character from STDIN                                    */
      };

   /* Prints password */
      printf("\nThe string is \"%s\"\n", ptr1);			/*  Print the string stored in the buffer                              */
      printf("Buffer Size:\t%i\n", strlen(ptr1));		/*  Print size of buffer                                               */
      free(ptr1);						/*  Frees memory used by buffer                                        */
            
   /* Ends function */
      return(0);						/*  And of course we have to provide an exit code                      */
}
               
