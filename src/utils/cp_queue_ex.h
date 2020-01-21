/* Copyright (c) 2013, Ben Noordhuis <info@bnoordhuis.nl>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef CP_QUEUE_H_
#define CP_QUEUE_H_

#include <stddef.h>

typedef void *CP_QUEUE[2];

/* Private macros. */
#define CP_QUEUE_NEXT(q)       (*(CP_QUEUE **) &((*(q))[0]))
#define CP_QUEUE_PREV(q)       (*(CP_QUEUE **) &((*(q))[1]))
#define CP_QUEUE_PREV_NEXT(q)  (CP_QUEUE_NEXT(CP_QUEUE_PREV(q)))
#define CP_QUEUE_NEXT_PREV(q)  (CP_QUEUE_PREV(CP_QUEUE_NEXT(q)))

/* Public macros. */
#define CP_QUEUE_DATA(ptr, type, field)                                          \
  ((type *) ((char *) (ptr) - offsetof(type, field)))

/* Important note: mutating the list while CP_QUEUE_FOREACH is
 * iterating over its elements results in undefined behavior.
 */
#define CP_QUEUE_FOREACH(q, h)                                                   \
  for ((q) = CP_QUEUE_NEXT(h); (q) != (h); (q) = CP_QUEUE_NEXT(q))

#define CP_QUEUE_EMPTY(q)                                                        \
  ((const CP_QUEUE *) (q) == (const CP_QUEUE *) CP_QUEUE_NEXT(q))

#define CP_QUEUE_HEAD(q)                                                         \
  (CP_QUEUE_NEXT(q))

#define CP_QUEUE_INIT(q)                                                         \
  do {                                                                        \
    CP_QUEUE_NEXT(q) = (q);                                                      \
    CP_QUEUE_PREV(q) = (q);                                                      \
  }                                                                           \
  while (0)

#define CP_QUEUE_ADD(h, n)                                                       \
  do {                                                                        \
    CP_QUEUE_PREV_NEXT(h) = CP_QUEUE_NEXT(n);                                       \
    CP_QUEUE_NEXT_PREV(n) = CP_QUEUE_PREV(h);                                       \
    CP_QUEUE_PREV(h) = CP_QUEUE_PREV(n);                                            \
    CP_QUEUE_PREV_NEXT(h) = (h);                                                 \
  }                                                                           \
  while (0)

#define CP_QUEUE_SPLIT(h, q, n)                                                  \
  do {                                                                        \
    CP_QUEUE_PREV(n) = CP_QUEUE_PREV(h);                                            \
    CP_QUEUE_PREV_NEXT(n) = (n);                                                 \
    CP_QUEUE_NEXT(n) = (q);                                                      \
    CP_QUEUE_PREV(h) = CP_QUEUE_PREV(q);                                            \
    CP_QUEUE_PREV_NEXT(h) = (h);                                                 \
    CP_QUEUE_PREV(q) = (n);                                                      \
  }                                                                           \
  while (0)

#define CP_QUEUE_MOVE(h, n)                                                      \
  do {                                                                        \
    if (CP_QUEUE_EMPTY(h))                                                       \
      CP_QUEUE_INIT(n);                                                          \
    else {                                                                    \
      CP_QUEUE* q = CP_QUEUE_HEAD(h);                                               \
      CP_QUEUE_SPLIT(h, q, n);                                                   \
    }                                                                         \
  }                                                                           \
  while (0)

#define CP_QUEUE_INSERT_HEAD(h, q)                                               \
  do {                                                                        \
    CP_QUEUE_NEXT(q) = CP_QUEUE_NEXT(h);                                            \
    CP_QUEUE_PREV(q) = (h);                                                      \
    CP_QUEUE_NEXT_PREV(q) = (q);                                                 \
    CP_QUEUE_NEXT(h) = (q);                                                      \
  }                                                                           \
  while (0)

#define CP_QUEUE_INSERT_TAIL(h, q)                                               \
  do {                                                                        \
    CP_QUEUE_NEXT(q) = (h);                                                      \
    CP_QUEUE_PREV(q) = CP_QUEUE_PREV(h);                                            \
    CP_QUEUE_PREV_NEXT(q) = (q);                                                 \
    CP_QUEUE_PREV(h) = (q);                                                      \
  }                                                                           \
  while (0)

#define CP_QUEUE_REMOVE(q)                                                       \
  do {                                                                        \
    CP_QUEUE_PREV_NEXT(q) = CP_QUEUE_NEXT(q);                                       \
    CP_QUEUE_NEXT_PREV(q) = CP_QUEUE_PREV(q);                                       \
  }                                                                           \
  while (0)

#endif /* CP_QUEUE_H_ */
