/*
 * Example with corrections from:
 *
 *    Gary V. Vaughan
 *    http://sources.redhat.com/autobook/autobook/autobook_163.html#SEC163
 */  

#include <stdio.h>

int run(const char *);
int add(const int, const int);

int
run (const char *argument)
{
  printf ("Hello World, %s!\n", argument);
  return 1;
}

int
add (const int num1, const int num2)
{
   printf("%i + %i = %i\n", num1, num2, num1+num2);
   return(0);
}

