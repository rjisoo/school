#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "cirListDeque.h"

/* internal functions interface */
struct DLink* _createLink (TYPE val);
void _addLinkAfter(struct cirListDeque *q, struct DLink *lnk, struct DLink *newLnk);
void _removeLink(struct cirListDeque *q, struct DLink *lnk);

/* ************************************************************************
	Deque Functions
************************************************************************ */

/* Initialize deque.

	param: 	q		pointer to the deque
	pre:	q is not null
	post:	q->Sentinel is allocated and q->size equals zero
*/
void initCirListDeque (struct cirListDeque *q) 
{

	assert (!EQ(q, 0));
	q->Sentinel = (struct DLink *)malloc(sizeof(struct DLink));
	assert (!EQ(q->Sentinel, 0));
	q->Sentinel->next = q->Sentinel;
	q->Sentinel->prev = q->Sentinel;
	q->size = 0;
}

/* Create a link for a value.

	param: 	val		the value to create a link for
	pre:	none
	post:	a link to store the value
*/
struct DLink * _createLink (TYPE val)
{

	struct DLink *newLink = (struct DLink *)malloc(sizeof(struct DLink));
	assert (!EQ(newLink, 0));
	newLink->value = val;
	return newLink;
}

/* Adds a link after another link

	param: 	q		pointer to the deque
	param: 	lnk		pointer to the existing link in the deque
	param: 	newLnk	pointer to the new link to add after the existing link
	pre:	q is not null
	pre: 	lnk and newLnk are not null
	pre:	lnk is in the deque 
	post:	the new link is added into the deque after the existing link
*/
void _addLinkAfter(struct cirListDeque *q, struct DLink *lnk, struct DLink *newLnk)
{

	assert (!EQ(q, 0));
	assert (!EQ(lnk, 0));
	assert (!EQ(newLnk, 0));
	newLnk->next = lnk;
	newLnk->prev = lnk->prev;
	lnk->prev->next = newLnk;
	lnk->prev = newLnk;
	q->size++;
}

/* Adds a link to the back of the deque

	param: 	q		pointer to the deque
	param: 	val		value for the link to be added
	pre:	q is not null
	post:	a link storing val is added to the back of the deque
*/
void addBackCirListDeque (struct cirListDeque *q, TYPE val) 
{

	assert (!EQ(q, 0));
	struct DLink *newLink = _createLink(val);
	assert (!EQ(newLink, 0));
	_addLinkAfter(q, q->Sentinel->prev, newLink);
}

/* Adds a link to the front of the deque

	param: 	q		pointer to the deque
	param: 	val		value for the link to be added
	pre:	q is not null
	post:	a link storing val is added to the front of the deque
*/
void addFrontCirListDeque(struct cirListDeque *q, TYPE val)
{

	assert (!EQ(q, 0));
	struct DLink *newLink = _createLink(val);
	assert (!EQ(newLink, 0));
	_addLinkAfter(q, q->Sentinel, newLink);
}

/* Get the value of the front of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	none
	ret: 	value of the front of the deque
*/
TYPE frontCirListDeque(struct cirListDeque *q) 
{

	assert (!EQ(q, 0));
	assert (!EQ(q->size, 0));
	return q->Sentinel->next->value;
}

/* Get the value of the back of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	none
	ret: 	value of the back of the deque
*/
TYPE backCirListDeque(struct cirListDeque *q)
{

	assert (!EQ(q, 0));
	assert (!EQ(q->size, 0));
	return q->Sentinel->prev->value;

}

/* Remove a link from the deque

	param: 	q		pointer to the deque
	param: 	lnk		pointer to the link to be removed
	pre:	q is not null and q is not empty
	pre:	lnk is in the deque 
	post:	the link is removed from the deque
*/
void _removeLink(struct cirListDeque *q, struct DLink *lnk)
{

	assert (!EQ(q, 0));
	struct DLink *temp = q->Sentinel->next;
	while (!EQ(temp, q->Sentinel)){
		if(EQ(temp,  lnk)){
			lnk->prev->next = lnk->next;
			lnk->next->prev = lnk->prev;
			free(lnk);
			q->size--;
			break;
		} else {
			temp = temp->next;
		}
	}
}

/* Remove the front of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	the front is removed from the deque
*/
void removeFrontCirListDeque (struct cirListDeque *q)
{

	assert (!EQ(q, 0));
	assert (!isEmptyCirListDeque(q));
	_removeLink(q, q->Sentinel->next);
}


/* Remove the back of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	the back is removed from the deque
*/
void removeBackCirListDeque(struct cirListDeque *q)
{

	assert (!EQ(q, 0));
	_removeLink(q, q->Sentinel->prev);
}

/* De-allocate all links of the deque

	param: 	q		pointer to the deque
	pre:	none
	post:	All links (including backSentinel) are de-allocated
*/
void freeCirListDeque(struct cirListDeque *q)
{

	while (!EQ(q->Sentinel->next, q->Sentinel)){
		removeBackCirListDeque(q);
	}
	free(q->Sentinel);
	free(q);
}

/* Check whether the deque is empty

	param: 	q		pointer to the deque
	pre:	q is not null
	ret: 	1 if the deque is empty. Otherwise, 0.
*/
int isEmptyCirListDeque(struct cirListDeque *q)
{

	assert (!EQ(q, 0));
	return (EQ(0, q->size));
}

/* Print the links in the deque from front to back

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post: 	the links in the deque are printed from front to back
*/
void printCirListDeque(struct cirListDeque *q)
{

	assert (!EQ(q, 0));
	assert (!isEmptyCirListDeque(q));
	int i;
	struct DLink *temp = q->Sentinel->next;
	printf("\n");
	for (i = 0; i < q->size; i++){
		printf("%d\n", temp->value);
		temp = temp->next;
	}
}

/* Reverse the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post: 	the deque is reversed
*/
void reverseCirListDeque(struct cirListDeque *q)
{

	assert (!EQ(q, 0));
	assert (!isEmptyCirListDeque(q));
	int i;
	int j = q->size;
	struct DLink *temp = q->Sentinel->prev;
	/* add back link to front */
	for (i = 0; i < j; i++){
		addFrontCirListDeque(q, temp->value);
		temp = temp->prev;
	}

	for (i = 0; i < j; i++){
		removeFrontCirListDeque(q);
	}
}
