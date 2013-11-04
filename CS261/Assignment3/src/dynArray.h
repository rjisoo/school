/* 	dynArr.h : Dynamic Array implementation. */
#ifndef DYNAMIC_ARRAY_INCLUDED
#define DYNAMIC_ARRAY_INCLUDED 1

#include "type.h"
struct DynArr
{
	TYPE *data;		/* pointer to the data array */
	int size;		/* Number of elements in the array */
	int capacity;	/* capacity ofthe array */
};

struct bag {
	struct DynArr *lst;
};

typedef struct DynArr DynArr;


/* Dynamic Array Functions */
void initDynArr(DynArr *v, int capacity);	
DynArr *newDynArr(int cap);

void freeDynArr(DynArr *v);
void deleteDynArr(DynArr *v);

void _dynArrSetCapacity(DynArr *v, int newCap);
int sizeDynArr(DynArr *v);

void addDynArr(DynArr *v, TYPE val);
TYPE getDynArr(DynArr *v, int pos);
void putDynArr(DynArr *v, int pos, TYPE val);
void swapDynArr(DynArr *v, int i, int  j);
void removeAtDynArr(DynArr *v, int idx);
void removeDynArr(DynArr *v, TYPE val);
int containsDynArr(DynArr *v, TYPE val);

/* Stack interface. */
int isEmptyDynArr(DynArr *v);
void pushDynArr(DynArr *v, TYPE val);
TYPE topDynArr(DynArr *v);
void popDynArr(DynArr *v);


/*Bag interface*/
void initBag(struct bag* b);
void addToBag(struct bag* b, TYPE val);
void removeFromBag(struct bag* b, TYPE val);
int bagContains(struct bag* b, TYPE val);
int isEmptyBag(struct bag* b);
void printBag(struct bag* b);
#endif

