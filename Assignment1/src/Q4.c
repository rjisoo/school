/*
 *	Geoffrey Corey		Oct 7, 2011
 *	Google (for proper syntax use), C book
 *	Assignment1 Q4.c, manipulating values using pointers and structs.
 *	eclipse CDT in Linux Ubunutu
*/
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct student{
	int id;
	int score;
};

int contains(int values[], int want){
	int i;
	for (i = 0; i < 10; i++){
		if (values[i] == want){
			return 1;
		}
	}
	return 0;
}

void sort(struct student* students, int n){
     /*Sort the n students based on their score*/
	int i, j;
	struct student temp;
		for (j = 0; j < n; j++)
		   {
		     for (i = j+1; i < n; i++)
		        {
		            if (students[j].id  > students[i].id)
		               {
		                   temp = students[j];
		                   students[j] = students[i];
		                   students[i] = temp;
		                }
		        }
		   }
}

int main(){
    /*Declare an integer n and assign it a value.*/
	int n = 100;
    
    /*Allocate memory for n students using malloc.*/
	struct student  *sptr = (struct student*)malloc(sizeof(struct student)*n);
    
    /*Generate random IDs and scores for the n students, using rand().*/
	srand((unsigned)time(NULL));
		int randNum, randScore, i;
		int x[n];
		for (i = 0; i < n; i++){
			randNum = rand()%100000+100000;
			if (i != 0){
				if (contains(x, randNum) == 1){
					i--;
				} else {
					x[i] = randNum;
				}
			}
			x[i] = randNum;
		}
		for (i = 0; i < n; i++){
			randScore = rand()%100;
			sptr[i].id = x[i];
			sptr[i].score = randScore;
		}
    
    /*Print the contents of the array of n students.*/
			for(i = 0; i < n; i++){
				if(i < 9){
					printf("ID00%d %4d    Score00%d %4d\n", i+1, sptr[i].id, i+1, sptr[i].score);
				} else if (i > 1 && i < 99) {
					printf("ID0%d %4d    Score0%d %4d\n", i+1, sptr[i].id, i+1, sptr[i].score);
				} else {
					printf("ID%d %4d    Score%d %4d\n", i+1, sptr[i].id, i+1, sptr[i].score);
				}
			}
		printf("\n\n");
    /*Pass this array along with n to the sort() function*/
			sort(sptr, n);
    
    /*Print the contents of the array of n students.*/
			for(i = 0; i < n; i++){
				if(i < 9){
					printf("ID00%d %4d    Score00%d %4d\n", i+1, sptr[i].id, i+1, sptr[i].score);
				} else if (i > 1 && i < 99) {
					printf("ID0%d %4d    Score0%d %4d\n", i+1, sptr[i].id, i+1, sptr[i].score);
				} else {
					printf("ID%d %4d    Score%d %4d\n", i+1, sptr[i].id, i+1, sptr[i].score);
				}
			}
		printf("\n");
    
    return 0;
}
