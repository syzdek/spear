#/* 

# Prints Hellow World in Perl and bash
   printf "Hello World\n";
   exit 0;

# Next we stop the perl preprocessor
1;
__END__

Now we can end our C/C++ comments
#*/

// Needed for printf function in both C and C++
#include <stdio.h>

// Our Prototype
int main(void);

// Our main function
int main(void) {
   /* Prints in C and C++ */ 
   printf("Hello World\n");

   /* End function */
   return(0);
}

