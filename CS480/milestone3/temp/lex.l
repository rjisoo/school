%{
  #define DIGIT 2
  #define INT 3
  #define FLOAT 4
  #define L_BRACKET 5
  #define R_BRACKET 6
  #define BINOP 7
  #define IF 8
  #define OR 9
  #define ID 10 
  int yyint;
  double yyflt;
%}

ws  [ \t\n]+
digit [0-9]
int {digit}+
float   ({digit}+)?(\.{digit}+)?([eE][+-]?{digit}+)? 
l_brac  \[
r_brac  \]
op      [+^%>]|>=|<=
if      if
letters [a-zA-Z_]
id      {letters}+({digit}|{letters})*

%% 
{ws}     { }  // ignore whitespace
{int}    { yyint=atoi(yytext); return(INT); }   // match integer numbers 
{float}    { yyflt=atof(yytext); return(FLOAT); } // match on float
{l_brac}   { return(L_BRACKET); }
{r_brac}   { return(R_BRACKET); }
{op}       { return(BINOP); }
{if}       { return(IF); }    //match if before id or it will be id
{id}       { return(ID); }
.    { yyerror(); }     //error on anything else
%% 

int yyerror(void)  // default action in case of error in yylex()
{  printf(" error\n");  
   exit(0); 
}

int yywrap(void) 
{ return 1; }   // won't compile on Linux w/o it
