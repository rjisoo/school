#ifndef __LIST_H
#define __LIST_H

#include "type.h"

struct DLink{ /* structure of a link/node*/
	TYPE value;/*Value of a link*/
	struct DLink* next;/*Ptr to next link*/
	struct DLink* prev;/*Ptr to prev link*/
};

struct list{ /*Structure of a list*/
	struct DLink* head;/*Head sentinel*/
	struct DLink* tail;/*Tail sentinel*/
	int size;/*Size of list*/
};

struct bag{/*Wrapper for bag*/
	struct list* lst;/*List implementing the bag*/
};

/*Linked list with 2 sentinels*/
void   initList(struct list *lst);
int 	isEmptyList(struct list *lst);
void  addBackList(struct list *lst, TYPE val);
void 	addFrontList(struct list *lst, TYPE val);
TYPE  frontList(struct list *lst);
TYPE 	backList(struct list *lst);
void  removeFrontList(struct list *lst);
void 	removeBackList(struct list *lst);
int listContains(struct list *lst, TYPE e);
void listRemove (struct list *lst, TYPE e);

/*Bag interface*/
void initBag(struct bag* b);
void addToBag(struct bag* b, TYPE val);
void removeFromBag(struct bag* b, TYPE val);
int bagContains(struct bag* b, TYPE val);
int isEmptyBag(struct bag* b);

#endif
