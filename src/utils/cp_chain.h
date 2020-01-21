
/*
* Copyright (C) 2002-2016 Igor Sysoev
* Copyright (C) 2011-2016 Nginx, Inc.
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
* 1. Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
* 2. Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the distribution.
*
* THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
* OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
* LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
* OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
* SUCH DAMAGE.
*/


#ifndef _CP_LIST_H_INCLUDED_
#define _CP_LIST_H_INCLUDED_


#include "cp_core.h"
#include "cp_mpalloc.h"


typedef struct cp_list_part_s  cp_list_part_t;

struct cp_list_part_s {
    void				*elts;
    cp_uint32_t			nelts;
    cp_list_part_t		*next;
};


typedef struct {
    cp_list_part_t		*last;
    cp_list_part_t		part;
    size_t				size;
    cp_uint32_t			nalloc;
    cp_mpool_t			*pool;
} cp_list_t;


cp_list_t *cp_list_create(cp_mpool_t *pool, cp_uint32_t n, size_t size);

static cp_int32_t
cp_list_init(cp_list_t *list, cp_mpool_t *pool, cp_uint32_t n, size_t size);


/*
 *
 *  the iteration through the list:
 *
 *  part = &list.part;
 *  data = part->elts;
 *
 *  for (i = 0 ;; i++) {
 *
 *      if (i >= part->nelts) {
 *          if (part->next == NULL) {
 *              break;
 *          }
 *
 *          part = part->next;
 *          data = part->elts;
 *          i = 0;
 *      }
 *
 *      ...  data[i] ...
 *
 *  }
 */


void *cp_list_push(cp_list_t *list);


#endif /* _CP_LIST_H_INCLUDED_ */
