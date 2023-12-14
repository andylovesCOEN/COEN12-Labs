#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "set.h"

typedef struct set{
    int count;
    int length;
    char **data;

} SET;

/*
 * Search Function (Private): Searches for elements in a sequantial fashion within a SET *sp.
 *
 * Big O Complexity: O(log n)
 *
 */
static int search(SET *sp, char *elt, bool *found)
{
    assert(sp != NULL);
    int lo = 0;
    int hi = sp->count -1;
    int mi;
    int x;
    while(lo <= hi)
    {
        mi = (lo + hi)/2;
        x = strcmp(elt, sp->data[mi]);
        if(x < 0)
            hi = mi -1;
        else if(x > 0)
            lo = mi + 1;
        else
        {
            *found = true;
            return mi;
        }    
    }
    *found = false;
    return lo;
}

/*
 * Create Set Function: Creates structure set sp with length (variable), count (variable) & data (array).
 *
 * Big O Complexity: O(1)
 *
 */
SET *createSet(int maxElts)
{
    SET *sp = malloc(sizeof(SET));
    assert(sp != NULL);
    sp->length = maxElts;
    sp->count = 0;
    sp->data = malloc(sizeof(char *)*maxElts);
    return sp;
}

/*
 * Destroy Set Function: Destroys a set beginning with strings, deleting so->data, freeing memory & ending with SET sp. 
 *
 * Big O Complexity: O(n)
 *
 */
void destroySet(SET *sp)
{
    assert(sp != NULL);
    int i;
    for(i = 0; i < sp->count; i++)
        free(sp->data[i]);
    free(sp->data);
    free(sp);
}

/*
 * Number of Elements Function: Returns sp->count.
 *
 * Big O Complexity: O(1)
 *
 */
int numElements(SET *sp)
{
    assert(sp != NULL);
    return sp->count;
}

/*
 * Add Element Function: Checks if element is within sp->data, if not, function adds element.
 *
 * Big O Complexity: O(n)
 *
 */
void addElement(SET *sp, char *elt)
{
    assert(sp != NULL);
    bool found;
    int idx = 0;
    
    idx = search(sp, elt, &found);
    if(found == false)
    {
	int i;
        for(i = sp->count; i > idx; i--)
        {
            sp->data[i] = sp->data[i-1];
        }
        sp->data[idx] = strdup(elt);
        sp->count += 1;
    }
}

/*
 * Remove Element Function: Checks if element is within sp->data, if so, function removes element.
 *
 * Big O Complexity: O(n)
 *
 */
void removeElement(SET *sp, char *elt)
{
    assert(sp != NULL);
    bool found;
    int idx = search(sp, elt, &found);
    if(found == true)
    {
        free(sp->data[idx]);
        int i;
        for(i = idx + 1; i < sp->count; i ++)
        {
            sp->data[i-1] = sp->data[i];
        }
        sp->count -= 1;
    }
}

/*
 * Find Element Function: Finds element within SET *sp, the element is returned if it is found & throws false if not found.
 *
 * Big O Complexity: O(n)
 *
 */
char *findElement(SET *sp, char *elt)
{
    assert(sp != NULL);
    bool found;
    int idx;
    idx = search(sp, elt, & found);
    if(found == false)
        return NULL;
    return sp->data[idx];
}

/*
 * Get Elements Function: Copies the data in SET to **data (char) & returns **data (char).
 *
 * Big O Complexity: O(n)
 *
 */
char **getElements(SET *sp)
{
    assert(sp != NULL);
    int i;
    char **data = malloc(sizeof(char *)*(sp->count));
    for(i = 0; i < sp->count; i++)
    {
        data[i] = strdup(sp->data[i]);
    }
    return data;
}
