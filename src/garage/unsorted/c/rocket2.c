#include <stdio.h>

#define DELAY	40000

#define CLEAR1	"    [1B[4D    [1B[4D    [1B[4D    [1B[4D    [1B[4D    "

#define ROCKET1	"[1;32m /\\ [1B[4D || [1B[4D || [1B[4D || [1B[4D    [1B[4D    [0m"
#define ROCKET2	"[1;36m _. [1B[5D / | [1B[6D / / [1B[6D / / [1B[6D   / [1B[6D     [1B[6D     [0m"
#define ROCKET3 "[1;36m ._ [1B[4D | \\ [1B[4D \\ \\ [1B[4D \\ \\ [1B[4D \\   [1B[4D     [1B[4D     [0m"

#define GROUND	"[21;0H--------------------------------------------------------------------------------\n                                                                                "
#define FLAG	"|[44m***[41m====[0m[1B[8D|[44m***[41m====[0m[1B[8D|[41m=======[0m[1B[8D|[1B[1D|[1B[1D|[1B[1D|"

#define POSXY	"[%i;%iH"
#define CLRSCR	"[2J"
#define HOME	"[22;0H"


int main(void);
int move_rocket(void);

/* moves rocket into sky */
int move_rocket(void) {

   /* declares local vars */
      int i,x,y;

   /* moves rocket */
      for (i = 0; i < 21; i ++) {

         /* rocket that shoots to right */
            if (i > 11) {
               printf("[%i;%iH", 21-((i-11)*2), 34+(2*(i-11)));
               printf(ROCKET2);
            };

         /* rochet that shoots to left */
            if ( i > 6) {
               printf("[%i;%iH", 21-i+6, 30-i+6);
               printf(ROCKET3);
            };

         /* rocket center top */
            printf("[%i;30H", 21-i);
            printf(ROCKET1);

         /* rocket slow right */
            printf("[%i;34H", 21-(i/2));
            printf(ROCKET1);

         /* rocket fast left */
            if (i > 12) {
               printf("[%i;26H", 20-((i-12)*2));
               printf(ROCKET1);
            };

         /* ground level */
            printf(GROUND);

         /* controls rate similiar to frame rate */
            usleep(DELAY);
            //sleep(1);
      };
};

int main(void) {

   printf(CLRSCR);
   printf(POSXY, 15, 3);
   printf(FLAG);
   move_rocket();
   printf(HOME);
   printf("\n");
   return(0);
}

