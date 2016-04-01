#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "bag.h"

bag_t *bag_new()
{
    bag_t *b;

    b = calloc(1, sizeof *b);
    if (! b)
      goto bad;

    b->size = 10;
    b->array = malloc(sizeof *b->array * b->size);
    if (! b->array)
      goto bad;

    b->count = 0;
    return b;

 bad:
    bag_free(b);
    return NULL;
}

static int __ensurecapacity(bag_t * b)
{
    int ii;
    void **array_n = NULL;

    if (b->count < b->size)
	return 0;

    /* double capacity */
    b->size *= 2;
    array_n = malloc(b->size * sizeof *array_n);
    if (! array_n)
        goto bad;

    /* copy old data across to new array */
    for (ii = 0; ii < b->count; ii++)
    {
	array_n[ii] = b->array[ii];
        if (! array_n[ii])
            goto bad;
    }

    /* swap arrays */
    free(b->array);
    b->array = array_n;

    return 0;

 bad:
    if (array_n)
    {
        int i;
        for (i = 0; i < ii; i++)
            free(array_n[i]);
    }

    free(array_n);
    return -1;
}

int bag_put(bag_t * b, void* item)
{
    if (__ensurecapacity(b) < 0)
        return -1;

    b->array[b->count++] = item;
    return 0;
}

void* bag_take(bag_t * b)
{
    int idx;
    void* i;

    if (0 == b->count) return NULL;

    idx = rand() % b->count;
    i = b->array[idx];
    b->array[idx] = b->array[b->count-1];
    b->count -= 1;
    return i;
}

int bag_count(bag_t * b)
{
    return b->count;
}

void bag_free(bag_t * b)
{
    if( ! b)
        return;

    free(b->array);
    free(b);
}

