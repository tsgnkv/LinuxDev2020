#include "buf.h"

#suite Initialization

#test capacity_init
    float *a = 0;
    ck_assert(buf_capacity(a) == 0);

#test size_init
    float *a = 0;
    ck_assert(buf_size(a) == 0);

#test size_1
    float *a = 0;
    buf_push(a, 1.3f);
    ck_assert(buf_size(a) == 1);

#test value
    float *a = 0;
    buf_push(a, 1.3f);
    ck_assert(a[0] == (float)1.3f);

#test clear
    float *a = 0;
    buf_push(a, 1.3f);
    buf_clear(a);
    ck_assert(buf_size(a) == 0);

#test clear_and_free
    float *a = 0;
    buf_push(a, 1.3f);
    buf_clear(a);
    ck_assert(buf_size(a) == 0);
    ck_assert(a != 0);
    buf_free(a);
    ck_assert(a == 0);

