/*
 * Author: Andrew Yang
 *
 * Date: 2/9/2023
 *
 * File: table.c (generic)
 *
 * Description: This file defines a struct "SET" and implements functions (creating, destroying the set, adding and removing elements & searching)
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "set.h"

#define FILLED 2
#define DELETED 1
#define EMPTY 0

typedef struct set{
	int count;
	int length;
	char **data;
	char *flag;
	int (*compare)();
	unsigned (*hash)();

} SET;

/*
 * Create Set Function: Creates stucture set called sp with variables length, count, and array data.
 *
 * Big O-Notation: O(1)
 */
SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)())
{
	int i;
	SET *sp = malloc(sizeof(SET));
	assert(sp != NULL);
	sp->length = maxElts;
	sp->count = 0;
	sp->data = malloc(sizeof(char *)*maxElts);
	sp->flag = malloc(sizeof(char )*maxElts);
	sp->compare = compare;
	sp->hash = hash;
	for(i = 0; i < maxElts; i++)
	{
		sp->flag[i] = 0;
	}
	return sp;
}

/*
 * Search Function: Retrieves elements and searches for elements within sp->data, if element does not exist, function returns false & returns true and the index of elements if the element does exist.
 *
 *Big O-Notation: O(m)
 */
int search(SET *sp, char *elt, bool *found)
{
	assert(elt != NULL && sp != NULL && found !=NULL);
	int idx;
	int start;
	int Bmark = 0;
	int flag = 0;
	idx = (*sp->hash)(elt) % (sp->length);
	start = idx;
	idx++;
	idx = idx % sp->length;
	while(idx != start)
	{
		if(sp ->flag[idx] == 0)
		{
			if(flag == 0)
			{
				*found = false;
				return idx;
			}
			break;
		}
		else if(sp->flag[idx] == 2)
		{
			if((sp->compare)(elt, sp->data[idx]) == 0)
			{
				*found = true;
				return idx;
			}
		}
		else //sp->flag[i] == 1
		{
			if(flag == 0)
			{
				flag = 1;
				Bmark = idx;
			}
		}
		idx++;
		idx = idx % sp->length;
	}
	*found = false;
	return Bmark;
}

/*
 * Destroy Set Function: Frees pointers in SET.
 *
 * Big O-Notation: O(1)
 */
void destroySet(SET *sp) //Frees all pointers in SET O(1)
{
	assert(sp != NULL);
	free(sp->flag);
	free(sp->data);
	free(sp);
}

/*
 * Num Elements Function: Returns number of elements.
 *
 * Big O-Notation: O(1)
 */
int numElements(SET *sp)
{
	assert(sp != NULL);
	return sp->count;
}

/*
 * Add Element Function: Adds elements to sp->data if elements is not found.
 *
 * Big O-Notation: O(m)
 */
void addElement(SET *sp, void *elt)
{
	assert(sp != NULL);
	assert(elt != NULL);
	bool found;
	int idx;
	idx = search(sp, elt, &found);
	if(found == false)
	{
		sp->data[idx] = elt;
		sp->flag[idx] = 2;
		sp->count += 1;
	}
}

/*
 * Remove Element Function: Removes element within sp->data if element is found.
 *
 * Big O-Notation: O(m)
 */
void removeElement(SET *sp, void *elt)
{
	assert(sp != NULL);
	assert(elt != NULL);
	bool found;
	int idx;
	idx = search(sp, elt, &found);
	if(found == true)
	{
		sp->flag[idx] = 1;
		sp->count -= 1;
	}
}

/*
 * Find Element Function: Takes an element and returns NULL if the element is not there and returns element if it is there.
 *
 * Big O-Notation: O(m)
 */
void *findElement(SET *sp, void *elt)
{
	assert(sp != NULL);
	assert(elt != NULL);
	bool found;
	int idx;
	idx = search(sp, elt, &found);
	if(found == false)
		return NULL;
	return sp->data[idx];
}

/*
 * Get Elements Function: Creates, copies, and returns only the filled data within sp->data.
 *
 * Big O-Notation: O(m)
 */
void *getElements(SET *sp)
{
	int i;
	int j;
	assert(sp != NULL);
	char **data = malloc(sizeof(char *)*(sp->count));
	for(i = 0, j = 0; i < sp->length; i++)
	{
		if(sp->flag[i] == 2)
		{
			data[j] = sp->data[i];
			j++;
		}
	}
	return data;
}
