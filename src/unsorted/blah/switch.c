#include <stdio.h>
int main(void);
int main(void)
{
   double x;
   x = 5.2;
   switch((int)(x*10.0))
   {
      case 50:
         printf("5.0\n"); break;
      case 51:
         printf("5.1\n"); break;
      case 52:
         printf("5.2\n"); break;
      case 53:
         printf("5.3\n"); break;
      case 54:
         printf("5.4\n"); break;
      default:
         printf("I don't know\n");break;
   };
   return(0);
}
