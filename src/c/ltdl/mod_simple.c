/*
 *   Notes:
 */

int mod_simple_add(int a);

// a global variable definition
int mod_simple_value = 1; 

int mod_simple_add(int a)
{
   return(mod_simple_value += a); 
} 

