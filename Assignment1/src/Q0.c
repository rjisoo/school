/*
 *	Geoffrey Corey		Oct 7, 2011
 *	Google (for proper syntax use), C book
 *	Assignment1 Q0.c, manipulating values using pointers.
 *	eclipse CDT in Linux Ubunutu
*/
 
#include <stdio.h>
#include <stdlib.h>

void fooA(int* iptr){
     /*Print the value pointed to by iptr*/
	printf("%d\n", *iptr);
     /*Print the address pointed to by iptr*/
	printf("%p\n", &iptr);
     /*Print the address of iptr itself*/
	printf("%p\n", iptr);

}

int main(){
    
    /*declare an integer x*/
    int x=99;
    /*print the address of x*/
    printf("%p\n", &x);
    /*Call fooA() with the address of x*/
    fooA(&x);
    /*print the value of x*/
    printf("%d\n", x);
    /*print the value of x*/
    return 0;
}
