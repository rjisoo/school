/*
 File: bst.c
 Implementation of the binary search tree data structure.
 
 */
#include <stdlib.h>
#include <stdio.h>
#include "assert.h"
#include "type.h"
#include "bst.h"


struct Node {
	TYPE         val;
	struct Node *left;
	struct Node *right;
};

struct BSTree {
	struct Node *root;
	int          cnt;
};

/*----------------------------------------------------------------------------*/
/*
 function to initialize the binary search tree.
 param tree
 pre: tree is not null
 post:	tree size is 0
		root is null
 */

void initBSTree(struct BSTree *tree)
{	

	tree->cnt  = 0; 
	tree->root = 0;	
}

/*
 function to create a binary search tree.
 param: none
 pre: none
 post: tree->count = 0
		tree->root = 0;
 */
 
struct BSTree*  newBSTree()
{

	struct BSTree *tree = (struct BSTree *)malloc(sizeof(struct BSTree));
	assert(tree != 0);
	
	initBSTree(tree);
	return tree;
}

/*----------------------------------------------------------------------------*/
/*
function to free the nodes of a binary search tree
param: node  the root node of the tree to be freed
 pre: none
 post: node and all descendants are deallocated
*/
 
void _freeBST(struct Node *node)
{

	if (node != 0) {
		_freeBST(node->left);
		_freeBST(node->right);		
		free(node);
	}
}

/* 
 function to clear the nodes of a binary search tree 
 param: tree    a binary search tree
 pre: tree ! = null
 post: the nodes of the tree are deallocated
		tree->root = 0;
		tree->cnt = 0
 */
void clearBSTree(struct BSTree *tree)
{

	_freeBST(tree->root);
	tree->root = 0;
	tree->cnt  = 0;
}

/*
 function to deallocate a dynamically allocated binary search tree
 param: tree   the binary search tree
 pre: tree != null;
 post: all nodes and the tree structure itself are deallocated.
 */
void deleteBSTree(struct BSTree *tree)
{

	clearBSTree(tree);
	free(tree);
}

/*----------------------------------------------------------------------------*/
/*
 function to determine if  a binary search tree is empty.
 
 param: tree    the binary search tree
 pre:  tree is not null
 */
int isEmptyBSTree(struct BSTree *tree)
{

	return (tree->cnt == 0);
}

/*
 function to determine the size of a binary search tree

param: tree    the binary search tree
pre:  tree is not null
*/
int sizeBSTree(struct BSTree *tree)
{

	return tree->cnt;
}

/*----------------------------------------------------------------------------*/
/*
 recursive helper function to add a node to the binary search tree.
 param:  cur	the current root node
		 val	the value to be added to the binary search tree
 pre:	val is not null
 */
struct Node *_addNode(struct Node *cur, TYPE val)
{

	struct Node *new;
	int c;
	if (cur == NULL){
		printf("We are adding data here.\n");
		/* case: cur is where we are to add the value to the tree */
		new = (struct Node *)malloc(sizeof(struct Node));
		assert (new != NULL);
		new->val = val;
		new->left = new->right = NULL;
		return new;
	} else {
		printf("cur isn't where we are adding the data.\n");
		/* case: cur is not where we are to add to the tree */
		c = compare(val, cur->val);
		if (c == 0 || c == -1){
			printf("We are adding data to the left.\n");
			/* case: value to add is less than or equal to current val */
			cur->left = _addNode(cur->left, val);
			return cur;
		} else {
			printf("We are adding data to the right.\n");
			/* case: value is greater than current value */
			cur->right = _addNode(cur->right, val);
			return cur;
		}

	}
	printf("something really weird happened in _addNode and it made it this far.\n");
}

/*
 function to add a value to the binary search tree
 param: tree   the binary search tree
		val		the value to be added to the tree
 
 pre:	tree is not null
		val is not null
 pose:  tree size increased by 1
		tree now contains the value, val
 */
void addBSTree(struct BSTree *tree, TYPE val)
{

	tree->root = _addNode(tree->root, val);	
	tree->cnt++;
}


/*
function to determine if the binary search tree contains a particular element
 param:	tree	the binary search tree
		val		the value to search for in the tree
 pre:	tree is not null
		val is not null
 post:	none
 */

/*----------------------------------------------------------------------------*/
int containsBSTree(struct BSTree *tree, TYPE val)
{

	assert (tree != NULL);
	assert (val != NULL);
	/*
	 *  struct Node *cur = tree->root
	 *
	 *  	case: cur->val == val
	 *  			return 1;
	 *
	 *  	case: cur->val > val
	 *  			cur = cur->left
	 *
	 *  	case: cur->val < val
	 *  			cur = cur->right
	 */

	struct Node *cur;
	cur = tree->root;
	int c;

	while (cur != NULL){
		c = compare(val, cur->val);
		if (c == 0){
			/* case: cur contains value */
			printf("cur contains the value.\n");
			return 1;
		} else {
			printf("cur doesn't contain the value. ");
			if (c == 1){
				printf("checking right.\n");
				cur = cur->right;
			} else {

				printf("checking left.\n");
				cur = cur->left;
			}
		}
	}
	printf("The value is not contained.\n");
	return 0;
}

/*
 helper function to find the left most child of a node
 param: cur		the current node
 pre:	cur is not null
 post: none
 */

/*----------------------------------------------------------------------------*/
TYPE _leftMost(struct Node *cur)
{

	assert (cur != NULL);
	printf("running _leftMost.\n");

	/*
	 *  if cur is left most, return cur->value
	 *
	 *  else return _leftMost(cur->left);
	 */
	if (cur->left == NULL){
		printf("We have found the left most value.\n");
		print_type(cur->val);
		printf("\n");
		return cur->val;
	} else {
		printf("This isn't left most val, finding next left.\n");
		return _leftMost(cur->left);
	}

}
/*
 helper function to remove the left most child of a node
 param: cur	the current node
 pre:	cur is not null
 post:	the left most node of cur is not in the tree
 */
/*----------------------------------------------------------------------------*/
struct Node *_removeLeftMost(struct Node *cur)
{
	/* FIXME write remove left most function */
	assert (cur != NULL);
	struct Node *temp;
	if (cur->left == NULL){
		/* We are left most node */
		temp = cur->right;
		/* cur-> either contains a node, or is null, so it updates the node pointing to cur so we can remove cur */
		free (cur->val); /* not sure if needed, but seems safe */
		free (cur);
		return temp;
	} else {
		/* cur is not left most node */
		cur->left = _removeLeftMost(cur->left);
		return cur;
	}
}
/*
 recursive helper function to remove a node from the tree
 param:	cur	the current node
		val	the value to be removed from the tree
 pre:	val is in the tree
		cur is not null
		val is not null
 */
/*----------------------------------------------------------------------------*/
struct Node *_removeNode(struct Node *cur, TYPE val)
{
	/* FIXME Still need to fix remove function */
	assert (cur != NULL);
	assert (val != NULL);
	printf("Running _removeNode.\n");

	/*
	 * case: 		val == cur->val (== 0)
	 * 					print "It's equal!"
	 *
	 * case: 		val < cur->val (== -1)
	 * 					print "It's less than!"
	 *
	 * case: 		val > cur->val (== 1)
	 * 					print "It's greater than!"
	 */
	int c = compare(val, cur->val);
	printf("compare returns %d.\n", c);

	if (c == -1){
		cur->left = _removeNode(cur->left, val);
		return cur;
	} else if (c == 1){
		cur->right = _removeNode(cur->right, val);
		return cur;
	} else {
		printf("They're equal!\n");
		print_type(cur->val);
		printf("\n");
		print_type(val);
		printf("\n");
		print_type(_leftMost(cur->right));
		/* remove cur */
		return cur;
	}



}
/*
 function to remove a value from the binary search tree
 param: tree   the binary search tree
		val		the value to be removed from the tree
 pre:	tree is not null
		val is not null
		val is in the tree
 pose:	tree size is reduced by 1
 */
void removeBSTree(struct BSTree *tree, TYPE val)
{

	if (containsBSTree(tree, val)) {
		print_type(val);
		printf("\n");
		tree->root = _removeNode(tree->root, val);
		tree->cnt--;
	}
}


/*----------------------------------------------------------------------------*/

/* The following is used only for debugging, set to "#if 0" when used 
  in other applications */
#if 1
#include <stdio.h>

/*----------------------------------------------------------------------------*/
void printNode(struct Node *cur) {
	 if (cur == 0) return;
	 printf("(");
	 printNode(cur->left);	 
	 /*print_type prints the value of the TYPE*/
	 print_type(cur->val);
	 printNode(cur->right);
	 printf(")");
}

void printTree(struct BSTree *tree) {
	 if (tree == 0) return;	 
	 printNode(tree->root);	 
}
/*----------------------------------------------------------------------------*/

#endif
