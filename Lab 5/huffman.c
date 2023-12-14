/*
 * Author: Andrew Yang
 *
 * Date: 2/9/2023
 *
 * File: huffman.c
 *
 * Description: This file contains the interface of the huffman.c, including the Main, Compare Nodes, Depth, and Make Node statics.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "pack.h"
#include "pqueue.h"
#include <ctype.h>

# define END 256

typedef struct node NODE;

static NODE* makeNode(int data, NODE* left, NODE* right);
static int depth(NODE* np);
static int nodeCompare(NODE* np1, NODE* np2);

int ascii[257];
NODE *global[257];

/*
 * Main Function: Contains statics of huffman.c 
 *
 * Big-O Notation: O(n)
 */
int main(int argc, char *argv[])
{
	if(argc == 2)
	{
		printf("File missing or required file count not met!\n");
		return 0;
	}
	else
	{
		FILE* fp = fopen(argv[1], "r");
		if(fp == NULL)
		{
			printf("File cannot be opened!\n");
			return 0;
		}
		int x = getc(fp);
		while(x != EOF)
		{
			ascii[x]++;
			x = getc(fp);
		}
		fclose(fp);
	}
	PQ *pq = createQueue(nodeCompare);
	int i;
	for(i = 0; i < 256; i++)
	{
		if(ascii[i] > 0)
		{
			global[i] = makeNode(ascii[i], NULL, NULL);
			addEntry(pq, global[i]);
		}
	}
	global[256] = makeNode(0, NULL, NULL);
	addEntry(pq, global[256]);
	while(numEntries(pq) > 1)
	{
		NODE* leftNode = removeEntry(pq);
		NODE* rightNode = removeEntry(pq);
		NODE* parentNode = makeNode(leftNode->count + rightNode->count, leftNode, rightNode);
		addEntry(pq, parentNode);
	}
	for(i = 0; i < 256; i++)
	{
		if(global[i] != NULL)
		{
			printf(isprint(i) ? "%c" : "%03o", i);
			printf(": %d x %d bits = %d bits\n", ascii[i], depth(global[i]), ascii[i]*depth(global[i]));
		}
	}
	pack(argv[1], argv[2], global);
	destroyQueue(pq);
	return 0;
}

/*
 * Node Compare: Compares two node, returns the larger between the two. 
 *
 * Big-O Notation: O(1)
 */
static int nodeCompare(NODE* node1, NODE* node2)
{
	assert(node1 != NULL && node2 != NULL);
	if(node1->count < node2->count)
		return -1;
	else if(node1->count > node2->count)
		return 1;
	else
	{
		return 0;
	}
}

/*
 * Depth: Returns depth of the node.
 *
 * Big-O Notation: O(h)
 */
static int depth(NODE* np)
{
	assert(np != NULL);
	if(np->parent == NULL)
		return 0;
	return depth(np->parent) + 1;
}

/*
 * Make Node: 
 *
 *Big-O Notation: O(1)
 */
static NODE* makeNode(int data, NODE* left, NODE* right)
{
	NODE* root = malloc(sizeof(NODE));
	assert(root != NULL);
	root->count = data;
	root->parent = NULL;

	if(left != NULL)
		left->parent = root;
	
	if(right != NULL)
		right->parent = root;
	
return root;
}
