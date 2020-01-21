
/*
 * Copyright (C) Igor Sysoev
 * Copyright (C) Nginx, Inc.
 */


#include "cp_array_pool.h"


cp_array_pool_t *
cp_array_pool_create(cp_mpool_t *p, cp_uint32_t n, size_t size)
{
    cp_array_pool_t *a;

	a = (cp_array_pool_t*)cp_palloc(p, sizeof(cp_array_pool_t));
    if (a == NULL) {
        return NULL;
    }

    if (cp_array_pool_init(a, p, n, size) != CP_OK) {
        return NULL;
    }

    return a;
}


void
cp_array_pool_destroy(cp_array_pool_t *a)
{
    cp_mpool_t  *p;

    p = a->pool;

    if ((unsigned char *) a->elts + a->size * a->nalloc == p->d.last) {
        p->d.last -= a->size * a->nalloc;
    }

    if ((unsigned char *) a + sizeof(cp_array_pool_t) == p->d.last) {
        p->d.last = (unsigned char *) a;
    }
}


void *
cp_array_pool_push(cp_array_pool_t *a)
{
    void        *elt, *new;
    size_t       size;
    cp_mpool_t  *p;

    if (a->nelts == a->nalloc) {

        /* the array is full */

        size = a->size * a->nalloc;

        p = a->pool;

        if ((unsigned char *) a->elts + size == p->d.last
            && p->d.last + a->size <= p->d.end)
        {
            /*
             * the array allocation is the last in the pool
             * and there is space for new allocation
             */

            p->d.last += a->size;
            a->nalloc++;

        } else {
            /* allocate a new array */

            new = (void*)cp_palloc(p, 2 * size);
            if (new == NULL) {
                return NULL;
            }

            cp_memcpy(new, a->elts, size);
            a->elts = new;
            a->nalloc *= 2;
        }
    }

    elt = (unsigned char *) a->elts + a->size * a->nelts;
    a->nelts++;

    return elt;
}


void *
cp_array_pool_push_n(cp_array_pool_t *a, cp_uint32_t n)
{
    void        *elt, *new;
    size_t       size;
    cp_uint32_t   nalloc;
    cp_mpool_t  *p;

    size = n * a->size;

    if (a->nelts + n > a->nalloc) {

        /* the array is full */

        p = a->pool;

        if ((unsigned char *) a->elts + a->size * a->nalloc == p->d.last
            && p->d.last + size <= p->d.end)
        {
            /*
             * the array allocation is the last in the pool
             * and there is space for new allocation
             */

            p->d.last += size;
            a->nalloc += n;

        } else {
            /* allocate a new array */

            nalloc = 2 * ((n >= a->nalloc) ? n : a->nalloc);

			new = (void*)cp_palloc(p, nalloc * a->size);
            if (new == NULL) {
                return NULL;
            }

            cp_memcpy(new, a->elts, a->nelts * a->size);
            a->elts = new;
            a->nalloc = nalloc;
        }
    }

    elt = (unsigned char *) a->elts + a->size * a->nelts;
    a->nelts += n;

    return elt;
}
