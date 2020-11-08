#include "buf.h"

#suite Subsript

#test push_grow_trunc_subscipt
    long *ai = 0;
    for (int i = 0; i < 10000; i++)
        buf_push(ai, i);
    ck_assert(buf_size(ai) == 10000);
    int match = 0;
    for (int i = 0; i < (int)(buf_size(ai)); i++)
        match += ai[i] == i;
    ck_assert(match == 10000);
    buf_free(ai);

    /* buf_grow(), buf_trunc() */
    buf_grow(ai, 1000);
    ck_assert(buf_capacity(ai) == 1000);
    ck_assert(buf_size(ai) == 0);
    buf_trunc(ai, 100);
    ck_assert(buf_capacity(ai) == 100);
    buf_free(ai);