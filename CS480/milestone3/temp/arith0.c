/* arith0.c: simple parser -- no output
 * grammar:
 *   P ---> E '#'
 *   E ---> T {('+'|'-') T}
 *   T ---> S {('*'|'/') S}
 *   S ---> F '^' S | F
 *   F ---> char | '(' E ')'
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
char next;
void E(void);
void T(void);
void S(void);
void F(void);
void error(int);
void scan(void);
void enter(char);
void leave(char);
void spaces(int);
int level = 0;

void main(void)
{
   scan();
   E();
   if (next != '#') error(1);
   else printf("Successful parse\n");
}

void E(void)
{
   enter('E');
   T();
   while (next == '+' || next == '-') {
      scan();
      T();
   }
   leave('E');
}

void T(void)
{
   enter('T');
   S();
   while (next == '*' || next == '/') {
      scan();
      S();
   }
   leave('T');
}
void S(void)
{
   enter('S');
   F();
   if (next == '^') {
      scan();
      S();
   }
   leave('S');
}
void F(void)
{
   enter('F');
   if (isalpha(next)) {
      scan();
   }
   else if (next == '(') {
      scan();
      E();
      if (next == ')') scan();
      else error(2);
   }
   else {
      error(3);
   }
   leave('F');
}
void scan(void)
{
   while (isspace(next = getchar()))
      ;
}
void error(int n)
{
   printf("\n*** ERROR: %i\n", n);
   exit(1);
}
void enter(char name)
{
   spaces(level++);
   printf("+-%c: Enter, \t", name);
   printf("Next == %c\n", next);
}
void leave(char name)
{
   spaces(--level);
   printf("+-%c: Leave, \t", name);
   printf("Next == %c\n", next);
}

void spaces(int local_level)
{
   while (local_level-- > 0)
      printf("| ");
}
