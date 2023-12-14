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
 * Search Function: Traverses and looks for elements within a SET *sp.
 *
 * Big O Complexity: O(n)
 *
 */
static int search(SET *sp, char *elt)
{
    assert(sp != NULL);
    int i;
    for(i = 0; i < sp->count; i++)
    {
        if(strcmp(elt, sp->data[i]) == 0)
        {
            return i;
        }
    }
    return -1;
}

/*
 * Create Set Function: Creates structure set named sp with length (variable), count (variable) & data (array).
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
 * Destroy Set Function: Destroys set beginning with strings of data, deleting sp->data, freeing memory & ending in SET sp.
 *
 * Big O Complexity: O(n)
 *
 */
void destroySet(SET *sp)
{
    int i;
    assert(sp != NULL);
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
 * Add Element Function: Checks to see if element is within sp->data, if not, function add element.
 *
 * Big O Complexity: O(n)
 *
 */
void addElement(SET *sp, char *elt)
{
    assert(sp != NULL);
    if(search(sp, elt) == -1)
    {
        sp->data[sp->count] = strdup(elt);
        sp->count += 1;
    }
}

/*
 * Remove Element Function: Checks to see if element is within sp->data, if so, function deletes element.
 *
 * Big O Complexity: O(n)
 *
 */
void removeElement(SET *sp, char *elt)
{
    assert(sp != NULL);
    int idx = search(sp, elt);
    if(idx != -1)
    {
        free(sp->data[idx]);
        sp->data[idx] = sp->data[sp->count -1];
        sp->count -= 1;
    }
}

/*
 * Find Element Function: Finds element within SET *sp, if that element is found it is returned and throws false if not found.
 *
 * Big O Complexity: O(n)
 *
 */
char *findElement(SET *sp, char *elt)
{
    int idx;
    assert(sp != NULL);
    idx = search(sp, elt);
    if(idx == -1)
        return NULL;
    return sp->data[idx];
}

/*
 * Get Elements Function: Copies the data in SET to **data (char) and returns **data (char).
 *
 * Big O Complexity: O(n)
 *
 */
char **getElements(SET *sp)
{
    int i;
    assert(sp != NULL);
    char **data = malloc(sizeof(char *)*(sp->count));
    for(i = 0; i < sp->count; i++)
    {
        data[i] = strdup(sp->data[i]);
    }
    return data;
}
