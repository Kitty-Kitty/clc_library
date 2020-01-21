
/*
 * Copyright (C) Igor Sysoev
 * Copyright (C) Nginx, Inc.
 */


#ifndef _CP_ARRAY_H_INCLUDED_
#define _CP_ARRAY_H_INCLUDED_


#include "cp_core.h"
#include "cp_mpalloc.h"



typedef struct {
    void					*elts;
    cp_uint32_t				nelts;
    size_t					size;
    cp_uint32_t				nalloc;
    cp_mpool_t				*pool;
} cp_array_pool_t;


cp_array_pool_t *cp_array_pool_create(cp_mpool_t *p, cp_uint32_t n, size_t size);
void cp_array_pool_destroy(cp_array_pool_t *a);
void *cp_array_pool_push(cp_array_pool_t *a);
void *cp_array_pool_push_n(cp_array_pool_t *a, cp_uint32_t n);


static cp_int32_t
cp_array_pool_init(cp_array_pool_t *array, cp_mpool_t *pool, cp_uint32_t n, size_t size)
{
    /*
     * set "array->nelts" before "array->elts", otherwise MSVC thinks
     * that "array->nelts" may be used without having been initialized
     */

    array->nelts = 0;
    array->size = size;
    array->nalloc = n;
    array->pool = pool;

    array->elts = (void*)cp_palloc(pool, n * size);
    if (array->elts == NULL) {
        return CP_ERROR;
    }

    return CP_OK;
}


#endif /* _CP_ARRAY_H_INCLUDED_ */
