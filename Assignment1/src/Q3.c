/*
 *	Geoffrey Corey		Oct 7, 2011
 *	Google (for proper syntax use), C book
 *	Assignment1 Q3.c, manipulating values using pointers and sorting arrays with pointers.
 *	eclipse CDT in Linux Ubunutu
*/
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void sort(int* number, int n){
     /*Sort the given array number , of length n*/
	int i, j, temp;
	for (j = 0; j < n; j++)
	   {
	     for (i = j+1; i < n; i++)
	        {
	            if (number[j]  > number[i])
	               {
	                   temp = number[j];
	                   number[j] = number[i];
	                   number[i] = temp;
	                }
	        }
	   }
}

int main(){
    /*Declare an integer n and assign it a value of 20.*/
	int n = 20;
    
    /*Allocate memory for an array of n integers using malloc.*/
	int *ptr = (int *) malloc(n * sizeof (int));
    /*Fill this array with random numbers, using rand().*/
	srand((unsigned)time(NULL)); /* seeds random number fore pseudo randomness */
	int r, i;
	for (i = 0; i < n; i++){
		r = rand()%100+1;
		ptr[i] = r;
	}
    /*Print the contents of the array.*/
	for (i = 0; i < n; i ++){
		printf("%d\n", ptr[i]);
	}
    /*Pass this array along with n to the sort() function of part a.*/
	sort(ptr, n);
    /*Print the contents of the array.*/
	printf("\n");
	for (i = 0; i < n; i ++){

			printf("%d\n", ptr[i]);
		}
    
    return 0;
}
