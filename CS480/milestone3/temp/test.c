#include <stdio.h>

int yylex ();  // scanner prototype
extern int yyleng;
extern char *yytext;
extern int yyint;
extern double yyflt;

int main(void) 
{  int n;
   while ( n = yylex() )  { // call scanner until it returns 0 for EOF
      if(n==3)
    // output the lexeme as a decimal value
         printf ("Code:%d  Lexeme:%d  Length:%d\n", n, yyint, yyleng);
      else if(n==4)
    // output the lexeme as a float
         printf ("Code:%d  Lexeme:%f  Length:%d\n", n, yyflt, yyleng);
      else
         // output the token code, lexeme string, length
         printf ("Code:%d  Lexeme:%s  Length:%d\n", n, yytext, yyleng);
   }
   return 0;
}

