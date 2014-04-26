/*
 
Copyright (c) 2011, Willem-Hendrik Thiart
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * The names of its contributors may not be used to endorse or promote
      products derived from this software without specific prior written
      permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL WILLEM-HENDRIK THIART BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "bag.h"

/**
 * Init a bag and return it. Malloc space for it.
 * @return initialised bag */
bag_t *bag_new()
{
    bag_t *b;

    b = malloc(sizeof(bag_t));
    b->size = 10;
    b->array = malloc(sizeof(void *) * b->size);
    b->count = 0;
    return b;
}

static void __ensurecapacity(bag_t * b)
{
    int ii;
    void **array_n;

    if (b->count < b->size)
	return;

    /* double capacity */
    b->size *= 2;
    array_n = malloc(sizeof(void *) * b->size);

    /* copy old data across to new array */
    for (ii = 0; ii < b->count; ii++)
    {
	array_n[ii] = b->array[ii];
        assert(b->array[ii]);
    }

    /* swap arrays */
    free(b->array);
    b->array = array_n;
}

void bag_put(bag_t * b, void* item)
{
    __ensurecapacity(b);
    b->array[b->count++] = item;
}

/**
 * Remove one random item.
 * @return one random item */
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

/**
 * Free memory held by bag */
void bag_free(bag_t * b)
{
    free(b->array);
    free(b);
}

