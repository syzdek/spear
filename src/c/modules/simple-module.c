/*
 * Example with corrections from:
 *
 *    Gary V. Vaughan
 *    http://sources.redhat.com/autobook/autobook/autobook_163.html#SEC163
 */  

#include <stdio.h>

int run(const char *);

int
run (const char *argument)
{
  printf ("Hello World, %s!\n", argument);
  return 0;
}

