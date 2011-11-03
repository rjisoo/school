/*
 *	Geoffrey Corey		Oct 7, 2011
 *	Google (for proper syntax use), C book
 *	Assignment1 Q2.c, manipulating values using pointers.
 *	eclipse CDT in Linux Ubunutu
*/
 
#include <stdio.h>
#include <stdlib.h>

int foo(int* a, int* b, int c){
    /*Set a to double its original value*/
    *a = 2**a;
    /*Set b to half its original value*/
    *b = *b/2;
    /*Assign a+b to c*/
    c = *a + *b;
    /*Return c*/
	return c;
}

int main(){
    /*Declare three integers x,y and z and initialize them to 5, 6, 7 respectively*/
	int x = 5;
	int y = 6;
	int z = 7;

    /*Print the values of x, y and z*/
	printf("%d %d %d\n", x, y, z);
    
    /*Call foo() appropriately, passing x,y,z as parameters*/
	int f = foo(&x, &y, z);
    
    /*Print the values of x, y and z*/
	printf("%d %d %d\n", x, y, z);
    /*Print the value returned by foo*/
	printf("%d\n", f);
    /*Is the return value different than the value of z?  Why?*/
    return 0;
}

/*
 * Answer: yes, the return value is different because foo takes the value of z and does nothing, and then c gets
 * changed to a different value.
 */
