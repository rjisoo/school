/*
	Geoffrey Corey		10-14-2011
	<collaborators, description of help>
	Assignment2 Using a Dynamic Array to track characters
	Eclipse CDT in Ubuntu
*/

/*	stack.c: Stack application. */
#include <stdio.h>
#include <stdlib.h>
#include "dynArray.h"


/* ***************************************************************
Using stack to check for unbalanced parentheses.
***************************************************************** */

/* Returns the next character of the string, once reaches end return '0' (zero)
	param: 	s pointer to a string 	
	pre: s is not null		
*/
char nextChar(char* s)
{
	static int i = -1;	
	char c;
	++i;	
	c = *(s+i);			
	if ( c == '\0' )
		return '\0';	
	else 
		return c;
}

/* Checks whether the (), {}, and [] are balanced or not
	param: 	s pointer to a string 	
	pre: s is not null	
	post:	
*/
int isBalanced(char* s)
{

	/*
	 * if '{' || '[' || '(' -> push
	 * if ']' || '}' || ')' -> check size, if size  > 0 -> top, match then pop else not balanced.
	 * if size > 0 at end -> unbalanced.
	 */
	char t;
	struct DynArr* l = newDynArr(2);
	do {
		t = nextChar(s);
		if (EQ(t, '{') || EQ(t, '[') || EQ(t, '(')){ /* Checks if char is '{',  '(', or '[' and pushes */
			pushDynArr(l, t);
			/* printf("\n%c\n",topDynArr(l)); */
		}

		if (EQ(t, '}') || EQ(t, ']') || EQ(t, ')')){
			if (sizeDynArr(l) == 0){ /* Checks if list is 0, because then automatic non-balanced */
				return 0;
			} else {
				if (EQ(t, '}')){ /* Checks for a matching '{' in stack */
					if (EQ(topDynArr(l), '{')){
						popDynArr(l);
					}
				}

				if (EQ(t, ']')){ /* Checks for a matching '[' in stack */
					if (EQ(topDynArr(l), '[')){
						popDynArr(l);
					}
				}

				if (EQ(t, ')')){ /* Checks for a matching '(' in stack */
					if (EQ(topDynArr(l), '(')){
						popDynArr(l);
					}
				}
			}
		}
	} while (t != 0);

	if(sizeDynArr(l) == 0){ /* Checks for values left in stack not caught in previous checks */
		return 1;
	}
	return 0;
}

int main(int argc, char* argv[]){

	printf("Assignment 2\n");
	
	char* s=argv[1];	
	int res;
	
	res = isBalanced(s);

	if (res)
		printf("The string %s is balanced\n", s);
	else 
		printf("The string %s is not balanced\n", s);
	
	return 0;	
}

