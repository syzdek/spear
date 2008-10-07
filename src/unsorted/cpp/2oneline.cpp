#include <stdio.h>

int main() {

  char Input;
  char String[2];
  String[1]='\0';
  bool Space=0;
  bool LineEnd=0;
  while ( ( Input=getchar() ) != EOF ) {
    String[0]=Input;
    if ( (Input=='\t') || (Input=='\n') )
      String[0]=' ';
    if ( (LineEnd==1) && (Input=='z') )
        {
          String[0]='\n';
          printf(String);
          String[0]='z';
         }
    if (String[0]!=' ')
      {
        printf(String);
        Space=0;
      }
     else
      { 
        if (Space==0)
          printf(String);
        Space=1;
      }
    LineEnd=0;
    if (Input=='\n')
      LineEnd=1;
  }
  String[0]='\n';
  printf(String);
  return(0);
}
      
    
