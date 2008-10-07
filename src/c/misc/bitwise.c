// Example	Name		Result
// $a & $b	And		Bits that are set in both $a and $b are set.
// $a | $b	Or		Bits that are set in either $a or $b are set.
// $a ^ $b	Xor		Bits that are set in $a or $b but not both are set.
// ~ $a		Not		Bits that are set in $a are not set, and vice versa.
// $a << $b	Shift left	Shift the bits of $a $b steps to the left (each step means "multiply by two")
// $a >> $b	Shift right	Shift the bits of $a $b steps to the right (each step means "divide by two")

#include <stdio.h>

#define NUM1 0x0007
#define NUM2 0x001c
#define NUM3 0x00FF00FF

int main(void);

int main(void)
{
   printf("Value:              num1 == 0x%02X\n", NUM1);
   printf("Value:              num2 == 0x%02X\n", NUM2);
   printf("Value:              num3 == 0x%08X\n", NUM3);
   printf("numbers:            num1 == 0x%02X\n", NUM1);
   printf("And:         num1 & num2 == 0x%02X\n", NUM1 & NUM2);
   printf("Or:          num1 | num2 == 0x%02X\n", NUM1 | NUM2);
   printf("Xor:         num1 ^ num2 == 0x%02X\n", NUM1 ^ NUM2);
   printf("Not:              ~ num3 == 0x%08X\n", ~ NUM3);
   printf("Shift left:   num3 << 16 == 0x%08X\n", NUM3 << 16);
   printf("Shift right:  num3 >> 16 == 0x%08X\n", NUM3 >> 16);
   return(0);
}
