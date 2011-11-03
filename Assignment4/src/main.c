#include<stdio.h>
#include<stdlib.h>
#include "bst.h"
#include "type.h"
#include "structs.h"

/* Example main file to begin exercising your tree */

int main(int argc, char *argv[])
{	
	struct BSTree *tree	= newBSTree();		
		
	/*Create value of the type of data that you want to store*/
	struct data myData1;
	struct data myData2;
	struct data myData3;
	struct data myData4;
		
	myData1.number = 5;
	myData1.name = "rooty";
	myData2.number = 1;
	myData2.name = "lefty";
	myData3.number = 10;
	myData3.name = "righty";
	myData4.number = 3;
	myData4.name = "righty";
	
	/*add the values to BST*/
	addBSTree(tree, &myData1);
	addBSTree(tree, &myData2);
	addBSTree(tree, &myData3);
	addBSTree(tree, &myData4);
		
	/*Print the entire tree*/	
	printTree(tree);	
	/*(( 1 ( 3 ) ) 5 ( 10 ))*/
	return 1;
}

