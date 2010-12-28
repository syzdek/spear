
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct test_data   TestData;
typedef struct test_data * TestDataRef;

int main(int argc, char * argv[]);
int test_function(TestDataRef data, int argc, char * argv[]);

struct test_data
{
   int x;
   int y;
   int (*funcptr)(TestDataRef data, int argc, char * argv[]);
};


int main(int argc, char * argv[])
{
   TestDataRef data;

   if (!(data = (TestDataRef) malloc(sizeof(TestData))))
   {
      fprintf(stderr, "out of virtual memory\n");
      return(1);
   };
   memset(data, 0, sizeof(TestData));

   data->x       = 1;
   data->y       = 2;
   data->funcptr = &test_function;

   data->funcptr(data, argc, argv);

   free(data);

   return(0);
}



int test_function(TestDataRef data, int argc, char * argv[])
{
   int i;
   printf("x: %i\n", data->x);
   printf("y: %i\n", data->y);
   for(i = 1; i < argc; i++)
      printf("arg %i: %s\n", i, argv[i]);
   return(0);
}

