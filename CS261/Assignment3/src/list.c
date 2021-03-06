/*
	Geoffrey Corey		10-27-2011
	linked list data structure implementation
*/
#include "listbag.h"
#include "type.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

/*
	function to initialize the list, set the sentinels and set the size
	param lst the list
	pre: lst is not null
	post: lst size is 0
*/

void initList (struct list *lst) {

	assert (!EQ(lst, 0));
	lst->head = (struct DLink *)malloc(sizeof(struct DLink));
	assert (!EQ(lst->head, 0));
	lst->tail = (struct DLink *)malloc(sizeof(struct DLink));
	assert (!EQ(lst->tail, 0));
	lst->head->next = lst->tail;
	lst->tail->prev = lst->head;
	lst->size = 0;
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

	assert (!EQ(lst, 0));
	assert (!EQ(lnk, 0));
	struct DLink *newLink = (struct DLink *)malloc(sizeof(struct DLink));
	assert (!EQ(newLink, 0));
	newLink->value = v;
	newLink->next = lnk;
	newLink->prev = lnk->prev;
	lnk->prev->next = newLink;
	lnk->prev = newLink;
	lst->size++;
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

	assert (!EQ(lst, 0));
	_addLink(lst, lst->head->next, e);
}

/*
	addBackList
	Function to add a value to the back of the list, can use _addlink()
	param: lst the list
	pre: lst is not null
	post: lst is not empty
*/

void addBackList(struct list *lst, TYPE e)
{

	assert (!EQ(lst, 0));
	_addLink(lst, lst->tail, e);
}

/*
	frontList
	function to return the element in the front of the  list
	param: lst the list
	pre: lst is not null
	pre: lst is not empty
	post: none
*/

TYPE frontList (struct list *lst)
{

	assert (!EQ(lst, 0));
	assert (isEmptyList(lst));
	return lst->head->next->value;
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
	assert (!EQ(lst, 0));
	assert (!isEmptyList(lst));
	return lst->tail->prev->value;
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

	assert (!EQ(lst, 0));
	assert (!EQ(lnk, 0));
	lnk->prev->next = lnk->next;
	lnk->next->prev = lnk->prev;
	free(lnk);
	lst->size--;
}

/*
	removeFrontList
	Function to remove element from front of list, can use _removelink()
	param: lst the list
	pre:lst is not null
	pre: lst is not empty
	post: size is reduced by 1
*/

void removeFrontList(struct list *lst)
{

	assert (!EQ(lst, 0));
	assert (!isEmptyList(lst));
	_removeLink(lst, lst->head->next);
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

	assert (!EQ(lst, 0));
	assert (!isEmptyList(lst));
	_removeLink(lst, lst->tail);
}

/*
	isEmptyList
	param: q the list
	pre: q is not null
	post: none
*/

int isEmptyList(struct list *lst)
{

	assert (!EQ(lst, 0));
	return (!EQ(lst->size, 0));
}

/* Function to print list
   Pre: lst is not null
*/
void _printList(struct list* lst)
{

	assert (!EQ(lst, 0));
	struct DLink *temp = lst->head->next;
	while (!EQ(lst->tail, temp)){
		printf("%d\n", temp->value);
		temp = temp->next;
	}
}

/* Iterative implementation of contains() 
	Function to find if a given value belongs in the list
   Pre: lst is not null
*/
int listContains (struct list *lst, TYPE e)
{

	assert (!EQ(lst, 0));
	struct DLink* temp = lst->head->next;
	while (!EQ(temp, lst->tail)){
		if(EQ(temp->value, e)){
			return 1;
		} else {
			temp = temp->next;
		}
	}
	return 0;
}

/* Iterative implementation of remove() 
	Function to remove a given value from the list
   Pre: lst is not null
*/
void listRemove (struct list *lst, TYPE e)
{

	assert (!EQ(lst, 0));
	struct DLink *temp = lst->head->next;
	if(listContains(lst, e)){
		while (!EQ(lst->tail, temp)){
			if(EQ(temp->value, e)){
				_removeLink(lst, temp);
				break;
			} else {
				temp = temp->next;
			}
		}
	}
}
