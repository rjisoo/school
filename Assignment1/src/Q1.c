/*
 *	Geoffrey Corey		Oct 7, 2011
 *	Google (for proper syntax use), C book
 *	Assignment1 Q1.c, manipulating values using pointers and using structs.
 *	eclipse CDT in Linux Ubunutu
*/
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

struct student{
	int id;
	int score;
};

int contains(int values[], int want);

struct student* allocate(){
     /*Allocate memory for ten students*/
	struct student  *sptr = (struct student*)malloc(sizeof(struct student)*10);
     /*return the pointer*/
	return sptr;
}

void generate(struct student* students){
     /*Generate random ID and scores for ten students, ID being between 1 and 10, scores between 0 and 100*/
	 srand((unsigned)time(NULL));
	int randNum, randScore, i;
	int x[10];
	for (i = 0; i < 10; i++){
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
	for (i = 0; i < 10; i++){
		randScore = rand()%100;
		students[i].id = x[i];
		students[i].score = randScore;
	}
}

void output(struct student* students){
     /*Output information about the ten students in the format:
              ID1 Score1
              ID2 score2
              ID3 score3
              ...
              ID10 score10*/
	int i;
	for(i = 0; i < 10; i++){
		printf("ID %4d    Score %4d\n", students[i].id, students[i].score);
	}
}

void summary(struct student* students){
     /*Compute and print the minimum, maximum and average scores of the ten students*/
	int min, max, total, i, a;
	float avg;
	int count = 0;
	for (i = 0; i < 10; i++){
		a = students[i].score;
		if (i == 0){
			min = a;
			max = a;
			total = a;
		}else{
			total = total + a;
			if ( a < min ) min = a;
			if ( a > max ) max = a;
		}
		count++;
	}
	avg = 1.0*total/count;
	printf("\nMinimum Score: %d\nMaximum Score: %d\nAverage Score: %2.2f", min, max, avg);

     
}

void deallocate(struct student* stud){
     /*Deallocate memory from stud*/
	free(stud);
}

int contains(int values[], int want){
	int i;
	for (i = 0; i < 10; i++){
		if (values[i] == want){
			return 1;
		}
	}
	return 0;
}

int main(){
    struct student* stud = 0;
    
    /*call allocate*/
    stud = allocate();
    /*call generate*/
    generate(stud);
    /*call output*/
    output(stud);
    /*call summary*/
    summary(stud);
    /*call deallocate*/
    deallocate(stud);
    return 0;
}
