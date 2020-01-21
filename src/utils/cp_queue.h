/**************************************************************************

* Copyright: novigo

* Author: tianhuiming@novigo.com.cn

* Date£º2016-5-10
        
* Description:

**************************************************************************/


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




#ifndef _CP_QUEUE_INCLUDE_H_
#define _CP_QUEUE_INCLUDE_H_



typedef struct cp_queue_s  cp_queue_t;


struct cp_queue_s {
	cp_queue_t  *prev;
	cp_queue_t  *next;
};


#define cp_queue_init(q)                                                     \
    (q)->prev = q;                                                           \
    (q)->next = q


#define cp_queue_empty(h)                                                    \
    (h == (h)->prev)


#define cp_queue_insert_head(h, x)                                           \
    (x)->next = (h)->next;                                                   \
    (x)->next->prev = x;                                                     \
    (x)->prev = h;                                                           \
    (h)->next = x


#define cp_queue_insert_after   cp_queue_insert_head


#define cp_queue_insert_tail(h, x)                                           \
    (x)->prev = (h)->prev;                                                   \
    (x)->prev->next = x;                                                     \
	(x)->next = h;                                                           \
    (h)->prev = x


#define cp_queue_head(h)                                                     \
    (h)->next


#define cp_queue_last(h)                                                     \
    (h)->prev


#define cp_queue_sentinel(h)                                                 \
    (h)


#define cp_queue_next(q)                                                     \
    (q)->next


#define cp_queue_prev(q)                                                     \
    (q)->prev


#if (NGX_DEBUG)

#define cp_queue_remove(x)                                                   \
    (x)->next->prev = (x)->prev;                                             \
    (x)->prev->next = (x)->next;                                             \
    (x)->prev = NULL;                                                        \
    (x)->next = NULL

#else

#define cp_queue_remove(x)                                                  \
    (x)->next->prev = (x)->prev;                                            \
    (x)->prev->next = (x)->next

#endif


#define cp_queue_split(h, q, n)                                             \
    (n)->prev = (h)->prev;                                                  \
    (n)->prev->next = n;                                                    \
    (n)->next = q;                                                          \
    (h)->prev = (q)->prev;                                                  \
    (h)->prev->next = h;                                                    \
    (q)->prev = n;


#define cp_queue_add(h, n)                                                  \
    (h)->prev->next = (n)->next;                                            \
    (n)->next->prev = (h)->prev;                                            \
    (h)->prev = (n)->prev;                                                  \
    (h)->prev->next = h;


#define cp_queue_data(q, type, link)                                        \
    (type *) ((u_char *) q - offsetof(type, link))


cp_queue_t *cp_queue_middle(cp_queue_t *queue);
void cp_queue_sort(cp_queue_t *queue,
	int(*cmp)(const cp_queue_t *, const cp_queue_t *));




#endif /* _CP_QUEUE_INCLUDE_H_ */



