/*
 * growing-buffer.c - simple example of reading input from stdin and growing the buffer
 * $Source$
 * $Revision$
 * $Date$
 * $Author$
 */
/*
 * Build:
 *    Easy Build:
 *       gcc -g -o growing-buffer.o growing-buffer.c
 */
/*    Force Good Programming Habits (you masicist you) */
/*       gcc -g -o growing-buffer.o growing-buffer.c -O2 -Werror -Wall \
            -pedantic -g -Wtraditional -W -Wimplicit -Wmain -Wparentheses \
            -Wreturn-type -Wunused -Wswitch -Wcomment -Wformat \
            -Wchar-subscripts -Wshadow -Wcast-qual -Wcast-align \
            -Wwrite-strings -Wconversion -Waggregate-return \
            -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations \
            -Wredundant-decls -Wnested-externs -Winline
 */


/////////////
//         //
//  Notes  //
//         //
/////////////

   /* 
    * Pretty much the idea is to snowball the buffer. Meaning
    * as the buffer is tossed from pointer to pointer it grows
    * by one character.  The buffer will continue to get tossed
    * back and forth between the two pointers until there is no
    * more input from STDIN. IE, it snowballs until there isn't
    * any thing left to read.
    *
    * I am using one char variable to read STDIN via fgetc(stdin).
    * I am using one int variable to keep track of which pointer is
    * tossing the buffer, and which pointer is catching the buffer.
    *
    * And no I did not read about this algorithim, my simplistic
    * mind thought it up all by it's lonesome at 1:00am.
    *
    * Note to self, realloc() would probably be more efficient, but
    * I didn't think of it until after I wrote this example.
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
      char *ptr1;						/*  Pointer 1 to play hot patato with                   */		
      char *ptr2;						/*  Pointer 2 to play hot patato with                   */
      char inputchar;						/*  Used to read in one character at a time from STDIN  */
      int  toggle;						/*  Refers first to pointer one then to pointer two     */
       

   /* Initialize pointers */
      ptr1 = NULL;						/*  Havn't used pointer 1 yet, so it should point to NULL               */
      ptr2 = NULL;						/*  Havn't used pointer 2 yet, so it should point to NULL               */
      toggle = 0;						/*  Start the toggle at 0, so we'll copy ptr1 to ptr2 first             */

   /* Start buffer */
      ptr1 = (char *) malloc(sizeof(char));			/*  Need to start with a buffer of 1 char for the initial \0            */
      if (ptr1 == NULL) {					/*  If the pointer is NULL, malloc was unable to allocate memory        */
         printf("virtual memory exhausted\n");			/*  Let user know what's happening                                      */
         return(1);						/*  Exit with error                                                     */
      };
      ptr1[0] = '\0';						/*  If malloc did work, save NULL characters in only element of buffer  */

   /* Loop until EOF, EOL, \n, \r */
      printf("Enter String: ");					/*  Give user instructions                                              */
      inputchar = (char) fgetc(stdin);				/*  Get first character of the user's input                             */
      while ((inputchar > 33) && (inputchar != EOF)) {		/*  Loop until we reach the end of the input                            */
         if (toggle) {						/*  If toggle is set to one                                             */
            free(ptr1);						/*     1) free memory used by pointer 1                                 */
            ptr1 = (char *) malloc(strlen(ptr2)+2);		/*     2) Allocate memory that is 1 byte larger than pointer 2          */
            if (ptr1 == NULL) {					/*        a) verify that malloc allocated the memory                    */
              printf("Virtual Memory Exhausted\n");             /*           if not let user know what's happening                      */
              free(ptr2);                                       /*           exit with error                                            */
            };
            memcpy(ptr1, ptr2, strlen(ptr2));			/*     3) Copy data from memory at pointer 2 to pointer 1               */
            ptr1[strlen(ptr2)] = inputchar;                     /*     4) Append the latest character from STDIN                        */
            ptr1[strlen(ptr2)+1] = '\0';			/*     5) Add the trailing NULL character at the end                    */
            toggle = 0;						/*     6) Set toggle to zero                                            */
            printf(						/*     7) Print                                                         */
               "Current Buffer Size: %i\tData: \"%s\"\n",       /*           Description of data                                        */
               strlen(ptr1), 					/*           Size of Buffer                                             */
               ptr1                                             /*           Contents of Buffer                                         */
            );
           } else {						/*  Otherwise, assume toggle is set to zero                             */
            free(ptr2);						/*     1) free memory used by pointer 2                                 */
            ptr2 = (char *) malloc(strlen(ptr1)+2);             /*     2) Allocate memory that is 1 byte larger than pointer 1          */
            if (ptr2 == NULL) {					/*        a) verify that malloc allocated the memory                    */
              printf("Virtual Memory Exhausted\n");		/*           if not let user know what's happening                      */
              free(ptr1);					/*           exit with error                                            */
            };
            memcpy(ptr2, ptr1, strlen(ptr1));			/*     3) Copy data from memory at pointer 1 to pointer 2               */
            ptr2[strlen(ptr1)] = inputchar;			/*     4) Append the latest character from STDIN                        */
            ptr2[strlen(ptr1)+1] = '\0';			/*     5) Add the trailing NULL character at the end                    */
            toggle = 1;						/*     6) Set toggle to zero                                            */
            printf(						/*     7) Print                                                         */
               "Current Buffer Size: %i\tData: \"%s\"\n", 	/*           Description of data                                        */
               strlen(ptr2), 					/*           Size of Buffer                                             */
               ptr2						/*           Contents of Buffer                                         */
            );
         };
         inputchar = (char) fgetc(stdin);			/*  Fetch next character from STDIN                                     */
      };

   /* Prints password */
      if (toggle) {						/*  Determine which pointer the buffer was last handed to               */
         printf("\nThe string is \"%s\"\n", ptr2);		/*  If it was poitner 2, print contents of buffer at pointer 2          */
         printf("Buffer Size:\t%i\n", strlen(ptr2));		/*  Print size of buffer at pointer 2                                   */
        } else {						
         printf("\nThe string is \"%s\"\n", ptr1);		/*  If it was pointer 1, print contents of buffer at pointer 2          */
         printf("Buffer Size:\t%i\n", strlen(ptr1));		/*  Print size of buffer at pointer 1                                   */
      };
            
   /* Cleans up Memory */
      free(ptr1);						/*  Free memory pointed to by pointer 1                                 */
      free(ptr2);						/*  Free memory pointed to by pointer 1                                 */

   /* Ends function */
      return(0);						/*  And of course we have to provide an exit code                       */
}
               
