/*
 *	Geoffrey Corey		Oct 7, 2011
 *	Google (for proper syntax use), C book
 *	Assignment1 Q5.c, manipulating chars.
 *	eclipse CDT in Linux Ubunutu
*/
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



/*converts ch to upper case, assuming it is in lower case currently*/
char toUpperCase(char ch){
     return ch-'a'+'A';
}

/*converts ch to lower case, assuming it is in upper case currently*/
char toLowerCase(char ch){
     return ch-'A'+'a';
}

void sticky(char* word){
     /*Convert to sticky caps*/
	int i = 0;
	int l = strlen(word);
	/* printf("%d\n", l); */
	for (i = 0; i < l; i++){
	if(word[i] >= 'A') {                   /* Is is A or greater?   */
	     if (word[i] <= 'Z') {                /* and is it Z or lower? */
	                                       /* It is upper case      */
				 word[i] = toLowerCase(word[i]);     /* Convert from upper to lower case */
			 }
		}
	}
	/* printf("%s\n", word); */
	for (i = 0; i < l; i++){
		if (i % 2 == 0){
			word[i] = toUpperCase(word[i]);
	}

}
}

int main(){
    /*Read word from the keyboard using scanf*/
	char string[20];
	printf("\nPlease type 1 word and 1 word only. (Nothing past space bar will be used)\n");
	scanf("%s", string);
	printf("\nYou have entered: %4s\n", string);
    
    /*Call sticky*/
    sticky(string);
    /*Print the new word*/
    printf("%s", string);
    return 0;
}
