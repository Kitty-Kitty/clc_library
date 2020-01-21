/**************************************************************************

* Copyright: novigo

* Author: tianhuiming@novigo.com.cn

* Date£º2016-5-10
        
* Description:

**************************************************************************/

/*
* Copyright (C) Igor Sysoev
* Copyright (C) Nginx, Inc.
*/



#include "cp_queue.h"



/*
* find the middle queue element if the queue has odd number of elements
* or the first element of the queue's second part otherwise
*/

cp_queue_t *cp_queue_middle(cp_queue_t *queue)
{
	cp_queue_t  *middle, *next;

	middle = cp_queue_head(queue);

	if (middle == cp_queue_last(queue)) {
		return middle;
	}

	next = cp_queue_head(queue);

	for (;;) {
		middle = cp_queue_next(middle);

		next = cp_queue_next(next);

		if (next == cp_queue_last(queue)) {
			return middle;
		}

		next = cp_queue_next(next);

		if (next == cp_queue_last(queue)) {
			return middle;
		}
	}
}


/* the stable insertion sort */

void cp_queue_sort(cp_queue_t *queue,
int(*cmp)(const cp_queue_t *, const cp_queue_t *))
{
	cp_queue_t  *q, *prev, *next;

	q = cp_queue_head(queue);

	if (q == cp_queue_last(queue)) {
		return;
	}

	for (q = cp_queue_next(q); q != cp_queue_sentinel(queue); q = next) {

		prev = cp_queue_prev(q);
		next = cp_queue_next(q);

		cp_queue_remove(q);

		do {
			if (cmp(prev, q) <= 0) {
				break;
			}

			prev = cp_queue_prev(prev);

		} while (prev != cp_queue_sentinel(queue));

		cp_queue_insert_after(prev, q);
	}
}


