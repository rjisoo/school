#include "listbag.h"
#include <assert.h>
#include "type.h"
#include <stdlib.h>

/*Bag interface*/
/* Function to initialize bag:
	Pre: b is not null
	Post: list implementing the bag is initialized, size = 0
*/
void initBag(struct bag* b){
	assert( b != NULL);
	b->lst = (struct list*)malloc(sizeof(struct list));/*Allocate for the list implementing the bag*/
	initList(b->lst);/*Initialize list*/
}

/* Function to add an element to the bag:
	Pre: b is not null
	Post: val is added to the bag ie the list implementing the bag*/
void addToBag(struct bag* b, TYPE val){
 	/*FIX ME //TODO get add from paper*/
	assert (!EQ(b, 0));
}

/* Function to remove an element from the bag:
	Pre: b is not null
	Post: Element (if found) removed from bag/list
*/
void removeFromBag(struct bag* b, TYPE val){
	/*FIX ME //TODO get remove from paper */
	assert (!EQ(b, 0));
}

/*Function to test if an element exists in the bag
	Pre: b is not null
*/
int bagContains(struct bag* b, TYPE val){

	assert (!EQ(b, 0));
	int i = 0;
	struct DLink *temp = b->lst->head;
	while (LT(i, b->lst->size)){
		temp = temp->next;
		if(EQ(temp->value, val)){
			return 1;
		}
		i++;
	}
	return 0;
}

/*Function to test if the bag is empty
	Pre: b is not null
*/

int isEmptyBag(struct bag* b){

	assert (!EQ(b, 0));
	return (EQ(b->lst->size, 0));
}
