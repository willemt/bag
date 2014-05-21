#include <assert.h>
#include <setjmp.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CuTest.h"

#include "bag.h"

void TestBag_new(
    CuTest * tc
)
{
    bag_t *b;

    b = bag_new();
    CuAssertTrue(tc, 0 == bag_count(b));
}

void TestBag_put(
    CuTest * tc
)
{
    bag_t *b;
    int val = 10;

    b = bag_new();
    bag_put(b, &val);
    CuAssertTrue(tc, 1 == bag_count(b));
}

void TestBag_take(
    CuTest * tc
)
{
    bag_t *b;
    int val = 10;
    int *res;

    b = bag_new();
    bag_put(b, &val);
    res = bag_take(b);
    CuAssertTrue(tc, 0 == bag_count(b));
    CuAssertTrue(tc, res == &val);
}

