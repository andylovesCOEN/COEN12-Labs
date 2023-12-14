/*
 * Author: Andrew Yang
 *
 * Date: 2/23/2023
 *
 * File: set.c
 *
 * Description: This file contains the unique and parity interfaces, utilizes variety of structs and functions to search, destroy, add, and remove from a SET and SET sp.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "list.h"
#include "set.h"
#define average 20

typedef struct set{
	int count;
	int length;
	LIST **lists;
	int(*compare)();
	unsigned (*hash)();
}SET;

/*
 * Search Function: Utilize hash function to return index of element.
 *
 * Big-O Notation: O(n)
 */
int search(SET *sp, bool *found, void *elt)
{
	assert(sp != NULL && elt != NULL);
	int i = (*sp->hash)(elt) % sp->length;
	if(findItem(sp->lists[i], elt) != NULL)
	{
		*found = true;
		return i;
	}
	return -1;
}

/*
 * Create Set Function: Initializes the list.
 *
 * Big-O Notation: O(n)
 */
SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)())
{
	SET *sp = malloc(sizeof(SET));
	assert(sp != NULL);
	sp->compare = compare;
	sp->count = 0;
	sp->hash = hash;
	sp->length = maxElts / average;
	sp->lists = malloc(sizeof(LIST*)*sp->length);
	int i;
	for(i = 0; i < sp->length; i++)
		sp->lists[i] = createList(sp->compare);
	return sp;
}

/*
 * Destroy Set Function: Destroys the SET sp.
 *
 * Big-O Notation: O(1)
 */
void destroySet(SET *sp)
{
	free(sp->lists);
	free(sp);
}

/*
 * Num Elements Function: Returns the number of elements in the set.
 *
 * Big-O Notation: O(1)
 */
int numElements(SET *sp)
{
	assert(sp != NULL);
	return sp->count;
}

/*
 * Add Element Function: Adds an element to SET sp.
 *
 * Big-O Notation: O(n)
 */
void addElement(SET *sp, void *elt)
{
	int locn;
	assert(sp != NULL && elt != NULL);
	locn = (*sp->hash)(elt) % sp->length;
	if(!findItem(sp->lists[locn], elt))
	{
		addFirst(sp->lists[locn], elt);
		sp->count++;
	}
}

/*
 * Remove Element Function: Removes an element from the SET sp.
 *
 * Big-O Notation: O(n)
 */
void removeElement(SET *sp, void *elt)
{
	int locn;
	assert(sp != NULL && elt != NULL);
	locn = (*sp->hash)(elt) % sp->length;

	if(findItem(sp->lists[locn], elt))
	{
		removeItem(sp->lists[locn], elt);
		sp->count--;
	}
}

/*
 * Find Element Function: Finds the index of elt.
 *
 * Big-O Notation: O(n)
 */
void *findElement(SET *sp, void *elt)
{
	int locn;
	locn = (*sp->hash)(elt) % sp->length;
	return findItem(sp->lists[locn], elt);
}

/*
 * Get Elements Function: Returns array of the data of SET sp.
 *
 * Big-O Notation: O(n)
 */
void *getElements(SET *sp)
{
	assert(sp != NULL);
	int k = 0;
	void **data = malloc(sizeof(void *)*(sp->count));
	int i;
	for(i = 0; i < sp->length; i++)
	{
		void **items = getItems(sp->lists[i]);
		int j;
		for(j = 0; j < numItems(sp->lists[i]); j++)
		{
			data[k] = items[j];
			k++;
		}
	}
	return data;
}
