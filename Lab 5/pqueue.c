/*
 * Author: Andrew Yang
 *
 * File: pqueue.c
 *
 * Date: 2/2/2023
 *
 * Description: This file contains the source code of pqueue.c; featuring functions which creates, destroys, and returns number of queues, & adding and removing entries.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "pqueue.h"
#define elements 10;

typedef struct pqueue{
	int count;
	int length;
	void **data;
	int (*compare)();
}PQ;

int parent(int x)
{
	return (x-1)/2;
}

int left(int x)
{
	return (x*2)+1;
}

int right(int x)
{
	return (x*2)+2;
}

/*
 * Create Queue Function: Creates the queue.
 *
 * Big-O Notation: O(1)
 */
PQ *createQueue(int (*compare)())
{
	PQ *pq = malloc(sizeof(PQ));
	assert(pq != NULL);
	pq->compare = compare;
	pq->count = 0;
	pq->length = elements;
	pq->data = malloc(sizeof(void*)*pq->length);
	return pq;
}

/*
 * Destroy Queue Function: Destroys the queue.
 *
 * Big-O Notation: O(n)
 */
void destroyQueue(PQ *pq)
{
	assert(pq != NULL);
	int i;
	for(i = 0; i < pq->count; i++)
	{
		free(pq->data[i]);
	}
	free(pq->data);
	free(pq);	
	return;
}

/*
 * Num Entries Function: Returns the count of the queue.
 *
 * Big-O Notation: O(1)
 */
int numEntries(PQ *pq)
{
	assert(pq != NULL);
	return pq->count;
}

/*
 * Add Entry Function: Adds entry to the priority queue.
 *
 * Big-O Notation: O(log(n))
 */
void addEntry(PQ *pq, void *entry)
{
	assert(pq!=NULL && entry!=NULL);
	if (pq->count == pq->length)
	{
		pq->data = realloc(pq->data,sizeof(void*)*pq->length*2);
		pq->length = pq->length * 2;
	}
	pq->data[pq->count] = entry;
	int index = pq->count;
	while (pq->compare(pq->data[index], pq->data[parent(index)])<0)
	{
		void *temp = pq->data[parent(index)];
		pq->data[parent(index)] = pq->data[index];
		pq->data[index] = temp;
		
		index=parent(index);
	}
	pq->count++;
}

/*
 * Remove Entry Function: Removes the aforementioned priority entry from the queue.
 *
 * Big-O Notation: O(log(n))
 */
void *removeEntry(PQ *pq)
{
	void *root = pq->data[0];
	int index = 0, smallestIndex = 0;
	pq->data[index]=pq->data[pq->count-1];

	while (left(index)<pq->count - 1)
	{
		smallestIndex = left(index);
		if (right(index)<pq->count - 1)
		{
			if (pq->compare(pq->data[left(index)],pq->data[right(index)])<0)
			{
				smallestIndex=left(index);
			} else 
			{
				smallestIndex=right(index);
			}
		}
		
		if (pq->compare(pq->data[smallestIndex],pq->data[index])<0)
		{
			void *temp = pq->data[smallestIndex];
			pq->data[smallestIndex] = pq->data[index];
			pq->data[index] = temp;
			index = smallestIndex;
		}
		else
		{
			break;
		}
	}
	pq->count--;
	return root;
}
