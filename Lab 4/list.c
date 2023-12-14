/*
 * Author: Andrew Yang
 *
 * Date: 2/16/2023
 *
 * File: list.c
 *
 * Description: Contains maze and radix interfaces, utilizes struct LIST, nodes, and compound functions to create, destroy, add, remove, and find elements in said list.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "list.h"

typedef struct node
{
	void *data;
	struct node *next;
	struct node *prev;
}NODE;

typedef struct list
{
	int count;
	struct node *head;
	int(*compare)();
}LIST;

/*
 * Create List Function: Initializes the list.
 *
 * Big-O Notation: O(1)
 */
LIST *createList(int (*compare)())
{
	LIST *lp = malloc(sizeof(LIST));
	assert(lp != NULL);
	lp->head = malloc(sizeof(NODE));
	lp->compare = compare;
	lp->count = 0;
	lp->head->next = lp->head;
	lp->head->prev = lp->head;
	return lp;
}

/*
 * Destroy List Function: Destroys the list.
 *
 * Big-O Notation: O(n)
 */
void destroyList(LIST *lp)
{
	assert(lp != NULL);
	NODE *pDelete, *pNext;
	pDelete = lp->head;

	do{
		pNext = pDelete->next;
		free(pDelete);
		pDelete = pNext;
	}while(pDelete != lp->head);
	
	free(lp);
}

/*
 * Num Items Function: Returns the count of the list.
 *
 * Big-O Notation: O(1)
 */
int numItems(LIST *lp)
{
	assert(lp != NULL);
	return lp->count;
}

/*
 * Add First Function: Adds an item to the beginning of list.
 *
 * Big-O Notation: O(1)
 */
void addFirst(LIST *lp, void *item)
{
	assert(lp != NULL);
	NODE *temp = malloc(sizeof(NODE));
	assert(temp != NULL);
	temp->data = item;

	lp->head->next->prev = temp;
	temp->next = lp->head->next;
	temp->prev = lp->head;
	lp->head->next = temp;

	lp->count++;
	return;
}

/*
 * Add Last Function: Adds an item to the end of the list.
 *
 * Big-O Notation: O(1)
 */
void addLast(LIST *lp, void *item)
{
	assert(lp != NULL && item != NULL);
	NODE *temp = malloc(sizeof(NODE));
	temp->data = item;

	lp->head->prev->next = temp;
	temp->next = lp->head;
	temp->prev = lp->head->prev;
	lp->head->prev = temp;

	lp->count++;
	return;
}

/*
 * Remove First Function: Removes the first element from the list.
 *
 * Big-O Notation: O(1)
 */
void *removeFirst(LIST *lp)
{
	assert(lp != NULL && lp->count > 0);
	void *item;
	NODE *pDelete = lp->head->next;
	item = pDelete->data;
	lp->head->next = pDelete->next;
	pDelete->next->prev = lp->head;
	lp->count--;
	free(pDelete);
	return item;
}

/*
 * Remove Last Function: Removes the last element from the list.
 *
 * Big-O Notation: O(1)
 */
void *removeLast(LIST *lp)
{
	assert(lp->head->next != lp->head);
	void *item;
	NODE *pDelete = lp->head->prev;
	item = pDelete->data;

	lp->head->prev = pDelete->prev;
	pDelete->prev->next = lp->head;

	lp->count--;
	free(pDelete);
	return item;
}

/*
 * Get First Function: Retrieves the first element and returns said first element.
 *
 * Big-O Notation: O(1)
 */
void *getFirst(LIST *lp)
{
	assert(lp->head->next != lp->head);
	return lp->head->next->data;
}

/*
 * Get Last Function: Retrieves the last element and returns said last element.
 *
 * Big-O Notation: O(1)
 */
void *getLast(LIST *lp)
{
	assert(lp->head->next != lp->head);
	return lp->head->prev->data;
}

/*
 * Remove Item Function: Removes an item from list.
 *
 * Big-O Notation: O(n)
 */
void removeItem(LIST *lp, void *item)
{
	assert(lp != NULL);
	NODE *pSearch = lp->head->next;
	int i;
	for(i = 0; i < lp->count; i++)
	{
		if(lp->compare(pSearch->data, item) == 0)
		{
			pSearch->prev->next = pSearch->next;
			pSearch->next->prev = pSearch->prev;
			free(pSearch);
			lp->count--;
			break;
		}
		else
		{
			pSearch = pSearch->next;
		}
	}
	return;
}

/*
 * Find Item Function: Traverses the list, returns and item if that is in the list and NULL if it is not in the list.
 *
 * Big-O Notation: O(n)
 */
void *findItem(LIST *lp, void *item)
{
	assert(lp != NULL);
	if(lp->count > 0)
	{
		NODE *pSearch;
		pSearch = lp->head->next;
		while(pSearch != lp->head)
		{
			if((*lp->compare)(pSearch->data, item) == 0)
			{
				return pSearch->data;
			}
			pSearch = pSearch->next;
		}
	}	
	return NULL;
}

/*
 * Get Items Function: Creates array of elements and returns the array.
 *
 * Big-O Notation: O(n)
 */
void *getItems(LIST *lp)
{
	void **data = malloc(sizeof(void *)*(lp->count));
	int i = 0;
	NODE *pSearch = lp->head->next;
	
	while(i < lp->count)
	{
		data[i] = pSearch->data;
		pSearch = pSearch->next;
		i++;
	}
	return data;
}
