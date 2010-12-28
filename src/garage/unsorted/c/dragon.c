
#include <stdio.h>

#define DELAY   40000

#define POSXY	"[%i;%iH"
#define CLRSCR	"[2J"
#define HOME	"[23;0H"

/* Dragon */
#define DRAGON_01 "[36m                    ___====-_  _-====___[0m"
#define DRAGON_02 "[36m              _--~~~[35m#####[36m//      [36m\\\\[35m#####[36m~~~--_[0m"
#define DRAGON_03 "[36m           _-~[35m##########[36m// [31m(    ) [36m\\\\[35m##########[36m~-_[0m"
#define DRAGON_04 "[36m          -[35m############[36m//  [31m:\\^^/:  [36m\\\\[35m############[36m-[0m"
#define DRAGON_05 "[36m        _~[35m############[36m//   [31m([37m@[31m::[37m@[31m)   [36m\\\\[35m############[36m~_[0m"
#define DRAGON_06 "[36m       ~[35m#############[36m((     [31m\\\\//     [36m))[35m#############[36m~[0m"
#define DRAGON_07 "[36m      -[35m###############[36m\\\\    [31m(^^)    [36m//[35m###############[36m-[0m"
#define DRAGON_08 "[36m     -[35m#################[36m\\\\  [31m/ [33m   [31m\\  [36m//[35m#################[36m-[0m"
#define DRAGON_09 "[36m    -[35m###################[36m\\\\[31m/      \\[36m//[35m###################[36m-[0m"
#define DRAGON_10 "[36m   _[35m#[36m/:[35m##########/\\[35m######[31m(   /\\   )[35m######/\\[35m##########[36m:\\[35m#[36m_[0m"
#define DRAGON_11 "[36m   :/ :[35m#[36m/\\[35m#[36m/\\[35m#[36m/\\/  \\[35m#[36m/\\[35m##[31m\\  :  :  /[35m##[36m/\\[35m#[36m/  \\/\\[35m#[36m/\\[35m#[36m/\\[35m#[36m: \\:[0m"
#define DRAGON_12 "[36m      :/  V  V      V  \\[35m#[31m\\: :  : :/[35m#[36m/  V      V  V  \\:   [0m"
#define DRAGON_13 "[36m                        \\ [31m: :  : : [36m/                  [0m"
#define DRAGON_14 "[0m"

/* cubes */
const char *cubes[] = { "                 [1;33m___          [1;36m______[0m",
                        "                [1;33m/__/\\     [1;32m___[1;36m/[1;32m_____[1;36m/\\[0m",
                        "                [1;33m\\  \\ \\   [1;32m/         /\\[1;36m\\[0m",
                        "                 [1;33m\\  \\ \\[1;34m_[1;32m/[1;34m__       [1;32m/  \\[0m",
                        "                 [0;35m_[1;33m\\  \\ \\  [1;34m/\\[0;35m_____[1;32m/[0;35m___ [1;32m\\[0m",
                        "                [0;35m/[1;34m/ [1;33m\\__\\/ [1;34m/  \\       [0;35m/\\ [1;32m\\[0m",
                        "        [0;32m_______[0;35m/[1;34m/_______/    \\     [0;35m/ [0;32m_[0;35m\\[1;32m/[0;32m______[0m",
                        "       [0;32m/      [0;35m/ [1;34m\\       \\    /    [0;35m/ [0;32m/        /\\[0m",
                        "    [0;36m__[0;32m/      [0;35m/   [1;34m\\       \\  /    [0;35m/ [0;32m/        / [0;36m_[0;32m\\[0;36m__[0m",
                        "   [0;36m/ [0;32m/      [0;35m/     [1;34m\\_______\\/    [0;35m/ [0;32m/        / [0;36m/   /\\[0m",
                        "  [0;36m/_[0;32m/______[0;35m/___________________/ [0;32m/________/ [0;36m/___/  \\[0m",
                        "  [0;36m\\ [0;32m\\      \\    [1;32m___________    [0;35m\\ [0;32m\\        \\ [0;36m\\   \\  /[0m",
                        "   [0;36m\\_[0;32m\\      \\  [1;32m/          /\\    [0;35m\\ [0;32m\\        \\ [0;36m\\___\\/[0m",
                        "      [0;32m\\      \\[1;32m/          /  \\    [0;35m\\ [0;32m\\        \\  /[0m",
                        "       [0;32m\\_____[1;32m/          /    \\    [0;35m\\ [0;32m\\________\\/[0m",
                        "            [1;32m/__________/      \\    [0;35m\\  /[0m",
                        "            [1;32m\\   [1;36m_____  [1;32m\\      /[0;35m_____\\/[0m",
                        "             [1;32m\\ [1;36m/    /\\  [1;32m\\    / [1;33m\\  \\ \\[0m",
                        "              [1;36m/____/  \\  [1;32m\\  /   [1;33m\\  \\ \\[0m",
                        "              [1;36m\\    \\  /[1;32m___\\/     [1;33m\\  \\ \\[0m",
                        "               [1;36m\\____\\/            [1;33m\\__\\/[0m",
};
      
/* Misc Pictures */
#define VLINE " [1B[1D [1B[1D [1B[1D [1B[1D [1B[1D [1B[1D [1B[1D [1B[1D [1B[1D [1B[1D [1B[1D [1B[1D [1B[1D [1B[1D"
#define CLEARING	"Clearing old picture..."
#define DRAWING		"Drawing new image...   "

int main(void);

int main(void) {

   int c,i;

   /* clear screen */
      printf(CLRSCR);
      printf(POSXY, 0, 0);

   /* print dragon */
      printf(POSXY, 0, 15);
      printf("%s\n", CLEARING);
      printf("%s\n", DRAGON_01);
      printf("%s\n", DRAGON_02);
      printf("%s\n", DRAGON_03);
      printf("%s\n", DRAGON_04);
      printf("%s\n", DRAGON_05);
      printf("%s\n", DRAGON_06);
      printf("%s\n", DRAGON_07);
      printf("%s\n", DRAGON_08);
      printf("%s\n", DRAGON_10);
      printf("%s\n", DRAGON_11);
      printf("%s\n", DRAGON_12);
      printf("%s\n", DRAGON_13);
      printf("%s\n", DRAGON_14);

   /* Flush screen */
      fflush(stdout);

   /* Clear dragon */
      for (i = 0; i < 79; i ++) {
         printf(POSXY, 2, i);
         printf(VLINE);
         printf(HOME);
         fflush(stdout);
         usleep(DELAY);
      };

   /* Draws cubes */
      printf(POSXY, 0, 15);
      printf("%s\n", DRAWING);
      for (i = 21; i > 0; i--) {
         printf(POSXY, i, 0);
         printf("%s", cubes[i-1]);      
         printf(HOME);
         fflush(stdout);
         usleep(DELAY);
      };


   /* Home cursor */
      printf(HOME);
      fflush(stdout);

   return(0);
}
