#include "listbag.h"
#include "type.h"
#include <assert.h>
#include <stdlib.h>

/*
	function to initialize the list, set the sentinels and set the size
	param lst the list
	pre: lst is not null
	post: lst size is 0
*/

void initList (struct list *lst) {
	/* FIX ME*/
}


/*
	_addLink
	Funtion to add a value v to the list before the link l
	param: lst the list
	param: lnk the  link to add before
	param: v the value to add
	pre: lst is not null
	pre: lnk is not null
	post: lst is not empty
*/

void _addLink(struct list *lst, struct DLink *lnk, TYPE v)
{
	/* FIX ME*/
}


/*
	addFrontList
	Function to add a value to the front of the list, can use _addLink()
	param: lst the list
	param: e the element to be added
	pre: lst is not null
	post: lst is not empty, increased size by 1
*/

void addFrontList(struct list *lst, TYPE e)
{
	/* FIX ME*/
}

/*
	addBackList
	Function to add a value to the back of the list, can use _addlink()
	param: lst the list
	pre: lst is not null
	post: lst is not empty
*/

void addBackList(struct list *lst, TYPE e) {
	/* FIX ME*/
}

/*
	frontList
	function to return the element in the front of the  list
	param: lst the list
	pre: lst is not null
	pre: lst is not empty
	post: none
*/

TYPE frontList (struct list *lst) {
	/* FIX ME*/
}

/*
	backList
	function to return the element in the back of the  list
	param: lst the list
	pre: lst is not null
	pre: lst is not empty
	post: lst is not empty
*/

TYPE backList(struct list *lst)
{
	/* FIX ME*/
}

/*
	_removeLink
	Function to remove a given link
	param: lst the list
	param: lnk the linke to be removed
	pre: lst is not null
	pre: lnk is not null
	post: lst size is reduced by 1
*/

void _removeLink(struct list *lst, struct DLink *lnk)
{
	/* FIX ME*/
}

/*
	removeFrontList
	Function to remove element from front of list, can use _removelink()
	param: lst the list
	pre:lst is not null
	pre: lst is not empty
	post: size is reduced by 1
*/

void removeFrontList(struct list *lst) {
	/* FIX ME*/
}

/*
	removeBackList
	Function to remove element from back of list, can use _removelink()
	param: lst the list
	pre: lst is not null
	pre:lst is not empty
	post: size reduced by 1
*/

void removeBackList(struct list *lst)
{
	/* FIX ME*/
}

/*
	isEmptyList
	param: q the list
	pre: q is not null
	post: none
*/

int isEmptyList(struct list *lst) {
	/* FIX ME*/
}

/* Function to print list
   Pre: lst is not null
*/
void _printList(struct list* lst)
{
	/* FIX ME*/
}

/* Iterative implementation of contains() 
	Function to find if a given value belongs in the list
   Pre: lst is not null
*/
int listContains (struct list *lst, TYPE e) {
	/* FIX ME*/
}

/* Iterative implementation of remove() 
	Function to remove a given value from the list
   Pre: lst is not null
*/
void listRemove (struct list *lst, TYPE e) {
	/* FIX ME*/
}
