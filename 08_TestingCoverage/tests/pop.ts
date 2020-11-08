#include "buf.h"

#suite Pop

#test pop
    float *a = 0;
    buf_push(a, 1.1);
    buf_push(a, 1.2);
    buf_push(a, 1.3);
    buf_push(a, 1.4);
    ck_assert(buf_size(a) == 4);
    ck_assert(buf_pop(a) == (float)1.4f);
    buf_trunc(a, 3);
    ck_assert(buf_size(a) == 3);
    ck_assert(buf_pop(a) == (float)1.3f);
    ck_assert(buf_pop(a) == (float)1.2f);
    ck_assert(buf_pop(a) == (float)1.1f);
    ck_assert(buf_size(a) == 0);
    buf_free(a);
