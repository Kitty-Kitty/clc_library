
/*
 * Copyright (C) Igor Sysoev
 * Copyright (C) Nginx, Inc.
 */


#include "cp_core.h"
#include "cp_mpalloc.h"
#include "cp_chain.h"


cp_int32_t cp_list_init(cp_list_t *list, cp_mpool_t *pool, cp_uint32_t n, size_t size)
{
	list->part.elts = cp_mpalloc(pool, n * size);
	if (list->part.elts == NULL) {
		return CP_ERROR;
	}

	list->part.nelts = 0;
	list->part.next = NULL;
	list->last = &list->part;
	list->size = size;
	list->nalloc = n;
	list->pool = pool;

	return CP_OK;
}


cp_list_t *
cp_list_create(cp_mpool_t *pool, cp_uint32_t n, size_t size)
{
	cp_list_t  *list;

	list = (cp_list_t*)cp_palloc(pool, sizeof(cp_list_t));
	if (list == NULL) {
		return NULL;
	}

	if (cp_list_init(list, pool, n, size) != CP_OK) {
		return NULL;
	}

	return list;
}

void *
cp_list_push(cp_list_t *l)
{
    void             *elt;
    cp_list_part_t  *last;

    last = l->last;

    if (last->nelts == l->nalloc) {

        /* the last part is full, allocate a new list part */

		last = (cp_list_part_t*)cp_palloc(l->pool, sizeof(cp_list_part_t));
        if (last == NULL) {
            return NULL;
        }

        last->elts = (void *)cp_palloc(l->pool, l->nalloc * l->size);
        if (last->elts == NULL) {
            return NULL;
        }

        last->nelts = 0;
        last->next = NULL;

        l->last->next = last;
        l->last = last;
    }

    elt = (char *) last->elts + l->size * last->nelts;
    last->nelts++;

    return elt;
}
