/* C */
#include <string.h>
#include <stdio.h>

int main(void){
 	char str[4] = "mom",rev[4];
 	int i,j, k;

 	for(i = strlen(str)-1 , j = 0; i >= 0; i--, j++){
 		rev[j] = str[i];
 	}
	rev[j] = '\0';


 	if(strcmp(rev,str)){
 		k = 0;
 	}else{
 		k = 1;
 	}

 	return 0;
}
