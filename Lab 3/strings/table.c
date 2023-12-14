/*
 * Author: Andrew Yang
 *
 * Date: 2/2/2023
 *
 * File: table.c (strings)
 *
 * Description: This file defines a struct "SET" and implements it's different functions (creating and destroying sets, adding and removing elements & searching)
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

} SET;

unsigned strhash(char *s)
{
	unsigned hash = 0;
	while (*s != '\0')
	{
		hash = 31 * hash + *s ++;
	}
	return hash;
}

/*
 * Search Function: Retrieves an element and searches for the element within sp->data. If element does not exist, functions returns index & false is found. Else, returns found == true and the index of element.
 *
 * Big O-Notation: O(m)
 */
int search(SET *sp, char *elt, bool *found)
{
	assert(elt != NULL && sp != NULL && found != NULL);
	int idx, start;
	int b = 0;
	int flag = 0;
	idx = strhash(elt)%(sp->length);
	start = idx;
	idx++;
	idx = idx % sp->length;
	while(idx != start)
	{
		if(sp->flag[idx] == 0)
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
			if(strcmp(elt, sp->data[idx]) == 0)
			{
				*found = true;
				return idx;
			}
		}
		else
		{
			if (flag == 0)
			{
				flag = 1;
				b = idx;
			}
		}
		idx++;
		idx = idx % sp->length;
	}
	*found = false;
	return b;
}

/*
 * Create Set Function: Creates structure set named sp with variables length, count, and array data.
 *
 * Big O-Notation: O(1)
 */
SET *createSet(int maxElts)
{
	int i;
	SET *sp = malloc(sizeof(SET));
	assert(sp != NULL);
	sp->length = maxElts;
	sp->count = 0;
	sp->data = malloc(sizeof(char *)*maxElts);
	sp->flag = malloc(sizeof(char )*maxElts);
	for(i = 0; i < maxElts; i++)
	{
		sp->flag[i] = 0;
	}
	return sp;
}

/*
 * Destroy Set Function: Free pointers in SET.
 *
 * Big O-Notation: O(m)
 */
void destroySet(SET *sp)
{
	assert(sp != NULL);
	int i;
	for(i = 0; i < sp->length; i++)
	{
		if(sp->flag[i] == 2)
		{
			free(sp->data[i]);
		}
	}
	free(sp->flag);
	free(sp->data);
	free(sp);
}

/*
 * Num Elements Function: Returns the number of elements.
 *
 * Big O-Notation: O(1)
 */
int numElements(SET *sp)
{
	assert(sp != NULL);
	return sp->count;
}

/*
 * Add Element Function: Add elements to sp->data if the element is not found.
 *
 * Big O-Notation: O(m)
 */
void addElement(SET *sp, char *elt)
{
	assert(sp != NULL);
	assert(elt != NULL);
	bool found;
	int idx;
	idx = search(sp, elt, &found);
	if(found == false)
	{
		sp->data[idx] = strdup(elt);
		sp->flag[idx] = 2;
		sp->count += 1;
	}
}

/*
 * Remove Element Function: Removes an element within sp->data if element is found.
 *
 * Big O-Notation: O(m)
 */
void removeElement(SET *sp, char *elt)
{
	assert(sp != NULL);
	assert(elt != NULL);
	bool found;
	int idx;
	idx = search(sp, elt, &found);
	if(found == true)
	{
		free(sp->data[idx]);
		sp->flag[idx] = 1;
		sp->count -= 1;
	}
}

/*
 * Find Element Function: Takes elements and returns NULL if elements are not there & returns elements if it is there.
 *
 * Big O-Notation: O(m)
 */
char *findElement(SET *sp, char *elt)
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
 * Get Elements Function: Creates, copies & returns the filled-in data within sp->data.
 *
 *Big O-Notation: O(m)
 */
char **getElements(SET *sp)
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
