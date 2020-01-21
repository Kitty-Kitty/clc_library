/*-
 * Copyright 2002 Niels Provos <provos@citi.umich.edu>
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
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef  _CP_TREE_H_
#define  _CP_TREE_H_

#ifndef _CP__UNUSED
# if __GNUC__
#  define _CP__UNUSED __attribute__((unused))
# else
#  define _CP__UNUSED
# endif
#endif

/*
 * This file defines data structures for different types of trees:
 * splay trees and red-black trees.
 *
 * A splay tree is a self-organizing data structure.  Every operation
 * on the tree causes a splay to happen.  The splay moves the requested
 * node to the root of the tree and partly rebalances it.
 *
 * This has the benefit that request locality causes faster lookups as
 * the requested nodes move to the top of the tree.  On the other hand,
 * every lookup causes memory writes.
 *
 * The Balance Theorem bounds the total access time for m operations
 * and n inserts on an initially empty tree as O((m + n)lg n).  The
 * amortized cost for a sequence of m accesses to a splay tree is O(lg n);
 *
 * A red-black tree is a binary search tree with the node color as an
 * extra attribute.  It fulfills a set of conditions:
 *  - every search path from the root to a leaf consists of the
 *    same number of black nodes,
 *  - each red node (except for the root) has a black parent,
 *  - each leaf node is black.
 *
 * Every operation on a red-black tree is bounded as O(lg n).
 * The maximum height of a red-black tree is 2lg (n+1).
 */

#define CP_SPLAY_HEAD(name, type)                                                \
struct name {                                                                 \
  struct type *sph_root; /* root of the tree */                               \
}

#define CP_SPLAY_INITIALIZER(root)                                               \
  { NULL }

#define CP_SPLAY_INIT(root) do {                                                 \
  (root)->sph_root = NULL;                                                    \
} while (/*CONSTCOND*/ 0)

#define CP_SPLAY_ENTRY(type)                                                     \
struct {                                                                      \
  struct type *spe_left;          /* left element */                          \
  struct type *spe_right;         /* right element */                         \
}

#define CP_SPLAY_LEFT(elm, field)    (elm)->field.spe_left
#define CP_SPLAY_RIGHT(elm, field)   (elm)->field.spe_right
#define CP_SPLAY_ROOT(head)          (head)->sph_root
#define CP_SPLAY_EMPTY(head)         (CP_SPLAY_ROOT(head) == NULL)

/* CP_SPLAY_ROTATE_{LEFT,RIGHT} expect that tmp hold CP_SPLAY_{RIGHT,LEFT} */
#define CP_SPLAY_ROTATE_RIGHT(head, tmp, field) do {                             \
  CP_SPLAY_LEFT((head)->sph_root, field) = CP_SPLAY_RIGHT(tmp, field);              \
  CP_SPLAY_RIGHT(tmp, field) = (head)->sph_root;                                 \
  (head)->sph_root = tmp;                                                     \
} while (/*CONSTCOND*/ 0)

#define CP_SPLAY_ROTATE_LEFT(head, tmp, field) do {                              \
  CP_SPLAY_RIGHT((head)->sph_root, field) = CP_SPLAY_LEFT(tmp, field);              \
  CP_SPLAY_LEFT(tmp, field) = (head)->sph_root;                                  \
  (head)->sph_root = tmp;                                                     \
} while (/*CONSTCOND*/ 0)

#define CP_SPLAY_LINKLEFT(head, tmp, field) do {                                 \
  CP_SPLAY_LEFT(tmp, field) = (head)->sph_root;                                  \
  tmp = (head)->sph_root;                                                     \
  (head)->sph_root = CP_SPLAY_LEFT((head)->sph_root, field);                     \
} while (/*CONSTCOND*/ 0)

#define CP_SPLAY_LINKRIGHT(head, tmp, field) do {                                \
  CP_SPLAY_RIGHT(tmp, field) = (head)->sph_root;                                 \
  tmp = (head)->sph_root;                                                     \
  (head)->sph_root = CP_SPLAY_RIGHT((head)->sph_root, field);                    \
} while (/*CONSTCOND*/ 0)

#define CP_SPLAY_ASSEMBLE(head, node, left, right, field) do {                   \
  CP_SPLAY_RIGHT(left, field) = CP_SPLAY_LEFT((head)->sph_root, field);             \
  CP_SPLAY_LEFT(right, field) = CP_SPLAY_RIGHT((head)->sph_root, field);            \
  CP_SPLAY_LEFT((head)->sph_root, field) = CP_SPLAY_RIGHT(node, field);             \
  CP_SPLAY_RIGHT((head)->sph_root, field) = CP_SPLAY_LEFT(node, field);             \
} while (/*CONSTCOND*/ 0)

/* Generates prototypes and inline functions */

#define CP_SPLAY_PROTOTYPE(name, type, field, cmp)                               \
void name##_CP_SPLAY(struct name *, struct type *);                              \
void name##_CP_SPLAY_MINMAX(struct name *, int);                                 \
struct type *name##_CP_SPLAY_INSERT(struct name *, struct type *);               \
struct type *name##_CP_SPLAY_REMOVE(struct name *, struct type *);               \
                                                                              \
/* Finds the node with the same key as elm */                                 \
static __inline struct type *                                                 \
name##_CP_SPLAY_FIND(struct name *head, struct type *elm)                        \
{                                                                             \
  if (CP_SPLAY_EMPTY(head))                                                      \
    return(NULL);                                                             \
  name##_CP_SPLAY(head, elm);                                                    \
  if ((cmp)(elm, (head)->sph_root) == 0)                                      \
    return (head->sph_root);                                                  \
  return (NULL);                                                              \
}                                                                             \
                                                                              \
static __inline struct type *                                                 \
name##_CP_SPLAY_NEXT(struct name *head, struct type *elm)                        \
{                                                                             \
  name##_CP_SPLAY(head, elm);                                                    \
  if (CP_SPLAY_RIGHT(elm, field) != NULL) {                                      \
    elm = CP_SPLAY_RIGHT(elm, field);                                            \
    while (CP_SPLAY_LEFT(elm, field) != NULL) {                                  \
      elm = CP_SPLAY_LEFT(elm, field);                                           \
    }                                                                         \
  } else                                                                      \
    elm = NULL;                                                               \
  return (elm);                                                               \
}                                                                             \
                                                                              \
static __inline struct type *                                                 \
name##_CP_SPLAY_MIN_MAX(struct name *head, int val)                              \
{                                                                             \
  name##_CP_SPLAY_MINMAX(head, val);                                             \
  return (CP_SPLAY_ROOT(head));                                                  \
}

/* Main splay operation.
 * Moves node close to the key of elm to top
 */
#define CP_SPLAY_GENERATE(name, type, field, cmp)                                \
struct type *                                                                 \
name##_CP_SPLAY_INSERT(struct name *head, struct type *elm)                      \
{                                                                             \
    if (CP_SPLAY_EMPTY(head)) {                                                  \
      CP_SPLAY_LEFT(elm, field) = CP_SPLAY_RIGHT(elm, field) = NULL;                \
    } else {                                                                  \
      int __comp;                                                             \
      name##_CP_SPLAY(head, elm);                                                \
      __comp = (cmp)(elm, (head)->sph_root);                                  \
      if(__comp < 0) {                                                        \
        CP_SPLAY_LEFT(elm, field) = CP_SPLAY_LEFT((head)->sph_root, field);         \
        CP_SPLAY_RIGHT(elm, field) = (head)->sph_root;                           \
        CP_SPLAY_LEFT((head)->sph_root, field) = NULL;                           \
      } else if (__comp > 0) {                                                \
        CP_SPLAY_RIGHT(elm, field) = CP_SPLAY_RIGHT((head)->sph_root, field);       \
        CP_SPLAY_LEFT(elm, field) = (head)->sph_root;                            \
        CP_SPLAY_RIGHT((head)->sph_root, field) = NULL;                          \
      } else                                                                  \
        return ((head)->sph_root);                                            \
    }                                                                         \
    (head)->sph_root = (elm);                                                 \
    return (NULL);                                                            \
}                                                                             \
                                                                              \
struct type *                                                                 \
name##_CP_SPLAY_REMOVE(struct name *head, struct type *elm)                      \
{                                                                             \
  struct type *__tmp;                                                         \
  if (CP_SPLAY_EMPTY(head))                                                      \
    return (NULL);                                                            \
  name##_CP_SPLAY(head, elm);                                                    \
  if ((cmp)(elm, (head)->sph_root) == 0) {                                    \
    if (CP_SPLAY_LEFT((head)->sph_root, field) == NULL) {                        \
      (head)->sph_root = CP_SPLAY_RIGHT((head)->sph_root, field);                \
    } else {                                                                  \
      __tmp = CP_SPLAY_RIGHT((head)->sph_root, field);                           \
      (head)->sph_root = CP_SPLAY_LEFT((head)->sph_root, field);                 \
      name##_CP_SPLAY(head, elm);                                                \
      CP_SPLAY_RIGHT((head)->sph_root, field) = __tmp;                           \
    }                                                                         \
    return (elm);                                                             \
  }                                                                           \
  return (NULL);                                                              \
}                                                                             \
                                                                              \
void                                                                          \
name##_CP_SPLAY(struct name *head, struct type *elm)                             \
{                                                                             \
  struct type __node, *__left, *__right, *__tmp;                              \
  int __comp;                                                                 \
                                                                              \
  CP_SPLAY_LEFT(&__node, field) = CP_SPLAY_RIGHT(&__node, field) = NULL;            \
  __left = __right = &__node;                                                 \
                                                                              \
  while ((__comp = (cmp)(elm, (head)->sph_root)) != 0) {                      \
    if (__comp < 0) {                                                         \
      __tmp = CP_SPLAY_LEFT((head)->sph_root, field);                            \
      if (__tmp == NULL)                                                      \
        break;                                                                \
      if ((cmp)(elm, __tmp) < 0){                                             \
        CP_SPLAY_ROTATE_RIGHT(head, __tmp, field);                               \
        if (CP_SPLAY_LEFT((head)->sph_root, field) == NULL)                      \
          break;                                                              \
      }                                                                       \
      CP_SPLAY_LINKLEFT(head, __right, field);                                   \
    } else if (__comp > 0) {                                                  \
      __tmp = CP_SPLAY_RIGHT((head)->sph_root, field);                           \
      if (__tmp == NULL)                                                      \
        break;                                                                \
      if ((cmp)(elm, __tmp) > 0){                                             \
        CP_SPLAY_ROTATE_LEFT(head, __tmp, field);                                \
        if (CP_SPLAY_RIGHT((head)->sph_root, field) == NULL)                     \
          break;                                                              \
      }                                                                       \
      CP_SPLAY_LINKRIGHT(head, __left, field);                                   \
    }                                                                         \
  }                                                                           \
  CP_SPLAY_ASSEMBLE(head, &__node, __left, __right, field);                      \
}                                                                             \
                                                                              \
/* Splay with either the minimum or the maximum element                       \
 * Used to find minimum or maximum element in tree.                           \
 */                                                                           \
void name##_CP_SPLAY_MINMAX(struct name *head, int __comp)                       \
{                                                                             \
  struct type __node, *__left, *__right, *__tmp;                              \
                                                                              \
  CP_SPLAY_LEFT(&__node, field) = CP_SPLAY_RIGHT(&__node, field) = NULL;            \
  __left = __right = &__node;                                                 \
                                                                              \
  while (1) {                                                                 \
    if (__comp < 0) {                                                         \
      __tmp = CP_SPLAY_LEFT((head)->sph_root, field);                            \
      if (__tmp == NULL)                                                      \
        break;                                                                \
      if (__comp < 0){                                                        \
        CP_SPLAY_ROTATE_RIGHT(head, __tmp, field);                               \
        if (CP_SPLAY_LEFT((head)->sph_root, field) == NULL)                      \
          break;                                                              \
      }                                                                       \
      CP_SPLAY_LINKLEFT(head, __right, field);                                   \
    } else if (__comp > 0) {                                                  \
      __tmp = CP_SPLAY_RIGHT((head)->sph_root, field);                           \
      if (__tmp == NULL)                                                      \
        break;                                                                \
      if (__comp > 0) {                                                       \
        CP_SPLAY_ROTATE_LEFT(head, __tmp, field);                                \
        if (CP_SPLAY_RIGHT((head)->sph_root, field) == NULL)                     \
          break;                                                              \
      }                                                                       \
      CP_SPLAY_LINKRIGHT(head, __left, field);                                   \
    }                                                                         \
  }                                                                           \
  CP_SPLAY_ASSEMBLE(head, &__node, __left, __right, field);                      \
}

#define CP_SPLAY_NEGINF  -1
#define CP_SPLAY_INF     1

#define CP_SPLAY_INSERT(name, x, y)  name##_CP_SPLAY_INSERT(x, y)
#define CP_SPLAY_REMOVE(name, x, y)  name##_CP_SPLAY_REMOVE(x, y)
#define CP_SPLAY_FIND(name, x, y)    name##_CP_SPLAY_FIND(x, y)
#define CP_SPLAY_NEXT(name, x, y)    name##_CP_SPLAY_NEXT(x, y)
#define CP_SPLAY_MIN(name, x)        (CP_SPLAY_EMPTY(x) ? NULL                      \
                                  : name##_CP_SPLAY_MIN_MAX(x, CP_SPLAY_NEGINF))
#define CP_SPLAY_MAX(name, x)        (CP_SPLAY_EMPTY(x) ? NULL                      \
                                  : name##_CP_SPLAY_MIN_MAX(x, CP_SPLAY_INF))

#define CP_SPLAY_FOREACH(x, name, head)                                          \
  for ((x) = CP_SPLAY_MIN(name, head);                                           \
       (x) != NULL;                                                           \
       (x) = CP_SPLAY_NEXT(name, head, x))

/* Macros that define a red-black tree */
#define CP_RB_HEAD(name, type)                                                   \
struct name {                                                                 \
  struct type *rbh_root; /* root of the tree */                               \
}

#define CP_RB_INITIALIZER(root)                                                  \
  { NULL }

#define CP_RB_INIT(root) do {                                                    \
  (root)->rbh_root = NULL;                                                    \
} while (/*CONSTCOND*/ 0)

#define CP_RB_BLACK  0
#define CP_RB_RED    1
#define CP_RB_ENTRY(type)                                                        \
struct {                                                                      \
  struct type *rbe_left;        /* left element */                            \
  struct type *rbe_right;       /* right element */                           \
  struct type *rbe_parent;      /* parent element */                          \
  int rbe_color;                /* node color */                              \
}

#define CP_RB_LEFT(elm, field)     (elm)->field.rbe_left
#define CP_RB_RIGHT(elm, field)    (elm)->field.rbe_right
#define CP_RB_PARENT(elm, field)   (elm)->field.rbe_parent
#define CP_RB_COLOR(elm, field)    (elm)->field.rbe_color
#define CP_RB_ROOT(head)           (head)->rbh_root
#define CP_RB_EMPTY(head)          (CP_RB_ROOT(head) == NULL)

#define CP_RB_SET(elm, parent, field) do {                                       \
  CP_RB_PARENT(elm, field) = parent;                                             \
  CP_RB_LEFT(elm, field) = CP_RB_RIGHT(elm, field) = NULL;                          \
  CP_RB_COLOR(elm, field) = CP_RB_RED;                                              \
} while (/*CONSTCOND*/ 0)

#define CP_RB_SET_BLACKRED(black, red, field) do {                               \
  CP_RB_COLOR(black, field) = CP_RB_BLACK;                                          \
  CP_RB_COLOR(red, field) = CP_RB_RED;                                              \
} while (/*CONSTCOND*/ 0)

#ifndef CP_RB_AUGMENT
#define CP_RB_AUGMENT(x)  do {} while (0)
#endif

#define CP_RB_ROTATE_LEFT(head, elm, tmp, field) do {                            \
  (tmp) = CP_RB_RIGHT(elm, field);                                               \
  if ((CP_RB_RIGHT(elm, field) = CP_RB_LEFT(tmp, field)) != NULL) {                 \
    CP_RB_PARENT(CP_RB_LEFT(tmp, field), field) = (elm);                            \
  }                                                                           \
  CP_RB_AUGMENT(elm);                                                            \
  if ((CP_RB_PARENT(tmp, field) = CP_RB_PARENT(elm, field)) != NULL) {              \
    if ((elm) == CP_RB_LEFT(CP_RB_PARENT(elm, field), field))                       \
      CP_RB_LEFT(CP_RB_PARENT(elm, field), field) = (tmp);                          \
    else                                                                      \
      CP_RB_RIGHT(CP_RB_PARENT(elm, field), field) = (tmp);                         \
  } else                                                                      \
    (head)->rbh_root = (tmp);                                                 \
  CP_RB_LEFT(tmp, field) = (elm);                                                \
  CP_RB_PARENT(elm, field) = (tmp);                                              \
  CP_RB_AUGMENT(tmp);                                                            \
  if ((CP_RB_PARENT(tmp, field)))                                                \
    CP_RB_AUGMENT(CP_RB_PARENT(tmp, field));                                        \
} while (/*CONSTCOND*/ 0)

#define CP_RB_ROTATE_RIGHT(head, elm, tmp, field) do {                           \
  (tmp) = CP_RB_LEFT(elm, field);                                                \
  if ((CP_RB_LEFT(elm, field) = CP_RB_RIGHT(tmp, field)) != NULL) {                 \
    CP_RB_PARENT(CP_RB_RIGHT(tmp, field), field) = (elm);                           \
  }                                                                           \
  CP_RB_AUGMENT(elm);                                                            \
  if ((CP_RB_PARENT(tmp, field) = CP_RB_PARENT(elm, field)) != NULL) {              \
    if ((elm) == CP_RB_LEFT(CP_RB_PARENT(elm, field), field))                       \
      CP_RB_LEFT(CP_RB_PARENT(elm, field), field) = (tmp);                          \
    else                                                                      \
      CP_RB_RIGHT(CP_RB_PARENT(elm, field), field) = (tmp);                         \
  } else                                                                      \
    (head)->rbh_root = (tmp);                                                 \
  CP_RB_RIGHT(tmp, field) = (elm);                                               \
  CP_RB_PARENT(elm, field) = (tmp);                                              \
  CP_RB_AUGMENT(tmp);                                                            \
  if ((CP_RB_PARENT(tmp, field)))                                                \
    CP_RB_AUGMENT(CP_RB_PARENT(tmp, field));                                        \
} while (/*CONSTCOND*/ 0)

/* Generates prototypes and inline functions */
#define  CP_RB_PROTOTYPE(name, type, field, cmp)                                 \
  CP_RB_PROTOTYPE_INTERNAL(name, type, field, cmp,)
#define  CP_RB_PROTOTYPE_STATIC(name, type, field, cmp)                          \
  CP_RB_PROTOTYPE_INTERNAL(name, type, field, cmp, _CP__UNUSED static)
#define CP_RB_PROTOTYPE_INTERNAL(name, type, field, cmp, attr)                   \
attr void name##_CP_RB_INSERT_COLOR(struct name *, struct type *);               \
attr void name##_CP_RB_REMOVE_COLOR(struct name *, struct type *, struct type *);\
attr struct type *name##_CP_RB_REMOVE(struct name *, struct type *);             \
attr struct type *name##_CP_RB_INSERT(struct name *, struct type *);             \
attr struct type *name##_CP_RB_FIND(struct name *, struct type *);               \
attr struct type *name##_CP_RB_NFIND(struct name *, struct type *);              \
attr struct type *name##_CP_RB_NEXT(struct type *);                              \
attr struct type *name##_CP_RB_PREV(struct type *);                              \
attr struct type *name##_CP_RB_MINMAX(struct name *, int);                       \
                                                                              \

/* Main rb operation.
 * Moves node close to the key of elm to top
 */
#define  CP_RB_GENERATE(name, type, field, cmp)                                  \
  CP_RB_GENERATE_INTERNAL(name, type, field, cmp,)
#define  CP_RB_GENERATE_STATIC(name, type, field, cmp)                           \
  CP_RB_GENERATE_INTERNAL(name, type, field, cmp, _CP__UNUSED static)
#define CP_RB_GENERATE_INTERNAL(name, type, field, cmp, attr)                    \
attr void                                                                     \
name##_CP_RB_INSERT_COLOR(struct name *head, struct type *elm)                   \
{                                                                             \
  struct type *parent, *gparent, *tmp;                                        \
  while ((parent = CP_RB_PARENT(elm, field)) != NULL &&                          \
      CP_RB_COLOR(parent, field) == CP_RB_RED) {                                    \
    gparent = CP_RB_PARENT(parent, field);                                       \
    if (parent == CP_RB_LEFT(gparent, field)) {                                  \
      tmp = CP_RB_RIGHT(gparent, field);                                         \
      if (tmp && CP_RB_COLOR(tmp, field) == CP_RB_RED) {                            \
        CP_RB_COLOR(tmp, field) = CP_RB_BLACK;                                      \
        CP_RB_SET_BLACKRED(parent, gparent, field);                              \
        elm = gparent;                                                        \
        continue;                                                             \
      }                                                                       \
      if (CP_RB_RIGHT(parent, field) == elm) {                                   \
        CP_RB_ROTATE_LEFT(head, parent, tmp, field);                             \
        tmp = parent;                                                         \
        parent = elm;                                                         \
        elm = tmp;                                                            \
      }                                                                       \
      CP_RB_SET_BLACKRED(parent, gparent, field);                                \
      CP_RB_ROTATE_RIGHT(head, gparent, tmp, field);                             \
    } else {                                                                  \
      tmp = CP_RB_LEFT(gparent, field);                                          \
      if (tmp && CP_RB_COLOR(tmp, field) == CP_RB_RED) {                            \
        CP_RB_COLOR(tmp, field) = CP_RB_BLACK;                                      \
        CP_RB_SET_BLACKRED(parent, gparent, field);                              \
        elm = gparent;                                                        \
        continue;                                                             \
      }                                                                       \
      if (CP_RB_LEFT(parent, field) == elm) {                                    \
        CP_RB_ROTATE_RIGHT(head, parent, tmp, field);                            \
        tmp = parent;                                                         \
        parent = elm;                                                         \
        elm = tmp;                                                            \
      }                                                                       \
      CP_RB_SET_BLACKRED(parent, gparent, field);                                \
      CP_RB_ROTATE_LEFT(head, gparent, tmp, field);                              \
    }                                                                         \
  }                                                                           \
  CP_RB_COLOR(head->rbh_root, field) = CP_RB_BLACK;                                 \
}                                                                             \
                                                                              \
attr void                                                                     \
name##_CP_RB_REMOVE_COLOR(struct name *head, struct type *parent,                \
    struct type *elm)                                                         \
{                                                                             \
  struct type *tmp;                                                           \
  while ((elm == NULL || CP_RB_COLOR(elm, field) == CP_RB_BLACK) &&                 \
      elm != CP_RB_ROOT(head)) {                                                 \
    if (CP_RB_LEFT(parent, field) == elm) {                                      \
      tmp = CP_RB_RIGHT(parent, field);                                          \
      if (CP_RB_COLOR(tmp, field) == CP_RB_RED) {                                   \
        CP_RB_SET_BLACKRED(tmp, parent, field);                                  \
        CP_RB_ROTATE_LEFT(head, parent, tmp, field);                             \
        tmp = CP_RB_RIGHT(parent, field);                                        \
      }                                                                       \
      if ((CP_RB_LEFT(tmp, field) == NULL ||                                     \
          CP_RB_COLOR(CP_RB_LEFT(tmp, field), field) == CP_RB_BLACK) &&                \
          (CP_RB_RIGHT(tmp, field) == NULL ||                                    \
          CP_RB_COLOR(CP_RB_RIGHT(tmp, field), field) == CP_RB_BLACK)) {               \
        CP_RB_COLOR(tmp, field) = CP_RB_RED;                                        \
        elm = parent;                                                         \
        parent = CP_RB_PARENT(elm, field);                                       \
      } else {                                                                \
        if (CP_RB_RIGHT(tmp, field) == NULL ||                                   \
            CP_RB_COLOR(CP_RB_RIGHT(tmp, field), field) == CP_RB_BLACK) {              \
          struct type *oleft;                                                 \
          if ((oleft = CP_RB_LEFT(tmp, field))                                   \
              != NULL)                                                        \
            CP_RB_COLOR(oleft, field) = CP_RB_BLACK;                                \
          CP_RB_COLOR(tmp, field) = CP_RB_RED;                                      \
          CP_RB_ROTATE_RIGHT(head, tmp, oleft, field);                           \
          tmp = CP_RB_RIGHT(parent, field);                                      \
        }                                                                     \
        CP_RB_COLOR(tmp, field) = CP_RB_COLOR(parent, field);                       \
        CP_RB_COLOR(parent, field) = CP_RB_BLACK;                                   \
        if (CP_RB_RIGHT(tmp, field))                                             \
          CP_RB_COLOR(CP_RB_RIGHT(tmp, field), field) = CP_RB_BLACK;                   \
        CP_RB_ROTATE_LEFT(head, parent, tmp, field);                             \
        elm = CP_RB_ROOT(head);                                                  \
        break;                                                                \
      }                                                                       \
    } else {                                                                  \
      tmp = CP_RB_LEFT(parent, field);                                           \
      if (CP_RB_COLOR(tmp, field) == CP_RB_RED) {                                   \
        CP_RB_SET_BLACKRED(tmp, parent, field);                                  \
        CP_RB_ROTATE_RIGHT(head, parent, tmp, field);                            \
        tmp = CP_RB_LEFT(parent, field);                                         \
      }                                                                       \
      if ((CP_RB_LEFT(tmp, field) == NULL ||                                     \
          CP_RB_COLOR(CP_RB_LEFT(tmp, field), field) == CP_RB_BLACK) &&                \
          (CP_RB_RIGHT(tmp, field) == NULL ||                                    \
          CP_RB_COLOR(CP_RB_RIGHT(tmp, field), field) == CP_RB_BLACK)) {               \
        CP_RB_COLOR(tmp, field) = CP_RB_RED;                                        \
        elm = parent;                                                         \
        parent = CP_RB_PARENT(elm, field);                                       \
      } else {                                                                \
        if (CP_RB_LEFT(tmp, field) == NULL ||                                    \
            CP_RB_COLOR(CP_RB_LEFT(tmp, field), field) == CP_RB_BLACK) {               \
          struct type *oright;                                                \
          if ((oright = CP_RB_RIGHT(tmp, field))                                 \
              != NULL)                                                        \
            CP_RB_COLOR(oright, field) = CP_RB_BLACK;                               \
          CP_RB_COLOR(tmp, field) = CP_RB_RED;                                      \
          CP_RB_ROTATE_LEFT(head, tmp, oright, field);                           \
          tmp = CP_RB_LEFT(parent, field);                                       \
        }                                                                     \
        CP_RB_COLOR(tmp, field) = CP_RB_COLOR(parent, field);                       \
        CP_RB_COLOR(parent, field) = CP_RB_BLACK;                                   \
        if (CP_RB_LEFT(tmp, field))                                              \
          CP_RB_COLOR(CP_RB_LEFT(tmp, field), field) = CP_RB_BLACK;                    \
        CP_RB_ROTATE_RIGHT(head, parent, tmp, field);                            \
        elm = CP_RB_ROOT(head);                                                  \
        break;                                                                \
      }                                                                       \
    }                                                                         \
  }                                                                           \
  if (elm)                                                                    \
    CP_RB_COLOR(elm, field) = CP_RB_BLACK;                                          \
}                                                                             \
                                                                              \
attr struct type *                                                            \
name##_CP_RB_REMOVE(struct name *head, struct type *elm)                         \
{                                                                             \
  struct type *child, *parent, *old = elm;                                    \
  int color;                                                                  \
  if (CP_RB_LEFT(elm, field) == NULL)                                            \
    child = CP_RB_RIGHT(elm, field);                                             \
  else if (CP_RB_RIGHT(elm, field) == NULL)                                      \
    child = CP_RB_LEFT(elm, field);                                              \
  else {                                                                      \
    struct type *left;                                                        \
    elm = CP_RB_RIGHT(elm, field);                                               \
    while ((left = CP_RB_LEFT(elm, field)) != NULL)                              \
      elm = left;                                                             \
    child = CP_RB_RIGHT(elm, field);                                             \
    parent = CP_RB_PARENT(elm, field);                                           \
    color = CP_RB_COLOR(elm, field);                                             \
    if (child)                                                                \
      CP_RB_PARENT(child, field) = parent;                                       \
    if (parent) {                                                             \
      if (CP_RB_LEFT(parent, field) == elm)                                      \
        CP_RB_LEFT(parent, field) = child;                                       \
      else                                                                    \
        CP_RB_RIGHT(parent, field) = child;                                      \
      CP_RB_AUGMENT(parent);                                                     \
    } else                                                                    \
      CP_RB_ROOT(head) = child;                                                  \
    if (CP_RB_PARENT(elm, field) == old)                                         \
      parent = elm;                                                           \
    (elm)->field = (old)->field;                                              \
    if (CP_RB_PARENT(old, field)) {                                              \
      if (CP_RB_LEFT(CP_RB_PARENT(old, field), field) == old)                       \
        CP_RB_LEFT(CP_RB_PARENT(old, field), field) = elm;                          \
      else                                                                    \
        CP_RB_RIGHT(CP_RB_PARENT(old, field), field) = elm;                         \
      CP_RB_AUGMENT(CP_RB_PARENT(old, field));                                      \
    } else                                                                    \
      CP_RB_ROOT(head) = elm;                                                    \
    CP_RB_PARENT(CP_RB_LEFT(old, field), field) = elm;                              \
    if (CP_RB_RIGHT(old, field))                                                 \
      CP_RB_PARENT(CP_RB_RIGHT(old, field), field) = elm;                           \
    if (parent) {                                                             \
      left = parent;                                                          \
      do {                                                                    \
        CP_RB_AUGMENT(left);                                                     \
      } while ((left = CP_RB_PARENT(left, field)) != NULL);                      \
    }                                                                         \
    goto color;                                                               \
  }                                                                           \
  parent = CP_RB_PARENT(elm, field);                                             \
  color = CP_RB_COLOR(elm, field);                                               \
  if (child)                                                                  \
    CP_RB_PARENT(child, field) = parent;                                         \
  if (parent) {                                                               \
    if (CP_RB_LEFT(parent, field) == elm)                                        \
      CP_RB_LEFT(parent, field) = child;                                         \
    else                                                                      \
      CP_RB_RIGHT(parent, field) = child;                                        \
    CP_RB_AUGMENT(parent);                                                       \
  } else                                                                      \
    CP_RB_ROOT(head) = child;                                                    \
color:                                                                        \
  if (color == CP_RB_BLACK)                                                      \
    name##_CP_RB_REMOVE_COLOR(head, parent, child);                              \
  return (old);                                                               \
}                                                                             \
                                                                              \
/* Inserts a node into the RB tree */                                         \
attr struct type *                                                            \
name##_CP_RB_INSERT(struct name *head, struct type *elm)                         \
{                                                                             \
  struct type *tmp;                                                           \
  struct type *parent = NULL;                                                 \
  int comp = 0;                                                               \
  tmp = CP_RB_ROOT(head);                                                        \
  while (tmp) {                                                               \
    parent = tmp;                                                             \
    comp = (cmp)(elm, parent);                                                \
    if (comp < 0)                                                             \
      tmp = CP_RB_LEFT(tmp, field);                                              \
    else if (comp > 0)                                                        \
      tmp = CP_RB_RIGHT(tmp, field);                                             \
    else                                                                      \
      return (tmp);                                                           \
  }                                                                           \
  CP_RB_SET(elm, parent, field);                                                 \
  if (parent != NULL) {                                                       \
    if (comp < 0)                                                             \
      CP_RB_LEFT(parent, field) = elm;                                           \
    else                                                                      \
      CP_RB_RIGHT(parent, field) = elm;                                          \
    CP_RB_AUGMENT(parent);                                                       \
  } else                                                                      \
    CP_RB_ROOT(head) = elm;                                                      \
  name##_CP_RB_INSERT_COLOR(head, elm);                                          \
  return (NULL);                                                              \
}                                                                             \
                                                                              \
/* Finds the node with the same key as elm */                                 \
attr struct type *                                                            \
name##_CP_RB_FIND(struct name *head, struct type *elm)                           \
{                                                                             \
  struct type *tmp = CP_RB_ROOT(head);                                           \
  int comp;                                                                   \
  while (tmp) {                                                               \
    comp = cmp(elm, tmp);                                                     \
    if (comp < 0)                                                             \
      tmp = CP_RB_LEFT(tmp, field);                                              \
    else if (comp > 0)                                                        \
      tmp = CP_RB_RIGHT(tmp, field);                                             \
    else                                                                      \
      return (tmp);                                                           \
  }                                                                           \
  return (NULL);                                                              \
}                                                                             \
                                                                              \
/* Finds the first node greater than or equal to the search key */            \
attr struct type *                                                            \
name##_CP_RB_NFIND(struct name *head, struct type *elm)                          \
{                                                                             \
  struct type *tmp = CP_RB_ROOT(head);                                           \
  struct type *res = NULL;                                                    \
  int comp;                                                                   \
  while (tmp) {                                                               \
    comp = cmp(elm, tmp);                                                     \
    if (comp < 0) {                                                           \
      res = tmp;                                                              \
      tmp = CP_RB_LEFT(tmp, field);                                              \
    }                                                                         \
    else if (comp > 0)                                                        \
      tmp = CP_RB_RIGHT(tmp, field);                                             \
    else                                                                      \
      return (tmp);                                                           \
  }                                                                           \
  return (res);                                                               \
}                                                                             \
                                                                              \
/* ARGSUSED */                                                                \
attr struct type *                                                            \
name##_CP_RB_NEXT(struct type *elm)                                              \
{                                                                             \
  if (CP_RB_RIGHT(elm, field)) {                                                 \
    elm = CP_RB_RIGHT(elm, field);                                               \
    while (CP_RB_LEFT(elm, field))                                               \
      elm = CP_RB_LEFT(elm, field);                                              \
  } else {                                                                    \
    if (CP_RB_PARENT(elm, field) &&                                              \
        (elm == CP_RB_LEFT(CP_RB_PARENT(elm, field), field)))                       \
      elm = CP_RB_PARENT(elm, field);                                            \
    else {                                                                    \
      while (CP_RB_PARENT(elm, field) &&                                         \
          (elm == CP_RB_RIGHT(CP_RB_PARENT(elm, field), field)))                    \
        elm = CP_RB_PARENT(elm, field);                                          \
      elm = CP_RB_PARENT(elm, field);                                            \
    }                                                                         \
  }                                                                           \
  return (elm);                                                               \
}                                                                             \
                                                                              \
/* ARGSUSED */                                                                \
attr struct type *                                                            \
name##_CP_RB_PREV(struct type *elm)                                              \
{                                                                             \
  if (CP_RB_LEFT(elm, field)) {                                                  \
    elm = CP_RB_LEFT(elm, field);                                                \
    while (CP_RB_RIGHT(elm, field))                                              \
      elm = CP_RB_RIGHT(elm, field);                                             \
  } else {                                                                    \
    if (CP_RB_PARENT(elm, field) &&                                              \
        (elm == CP_RB_RIGHT(CP_RB_PARENT(elm, field), field)))                      \
      elm = CP_RB_PARENT(elm, field);                                            \
    else {                                                                    \
      while (CP_RB_PARENT(elm, field) &&                                         \
          (elm == CP_RB_LEFT(CP_RB_PARENT(elm, field), field)))                     \
        elm = CP_RB_PARENT(elm, field);                                          \
      elm = CP_RB_PARENT(elm, field);                                            \
    }                                                                         \
  }                                                                           \
  return (elm);                                                               \
}                                                                             \
                                                                              \
attr struct type *                                                            \
name##_CP_RB_MINMAX(struct name *head, int val)                                  \
{                                                                             \
  struct type *tmp = CP_RB_ROOT(head);                                           \
  struct type *parent = NULL;                                                 \
  while (tmp) {                                                               \
    parent = tmp;                                                             \
    if (val < 0)                                                              \
      tmp = CP_RB_LEFT(tmp, field);                                              \
    else                                                                      \
      tmp = CP_RB_RIGHT(tmp, field);                                             \
  }                                                                           \
  return (parent);                                                            \
}

#define CP_RB_NEGINF   -1
#define CP_RB_INF      1

#define CP_RB_INSERT(name, x, y)   name##_CP_RB_INSERT(x, y)
#define CP_RB_REMOVE(name, x, y)   name##_CP_RB_REMOVE(x, y)
#define CP_RB_FIND(name, x, y)     name##_CP_RB_FIND(x, y)
#define CP_RB_NFIND(name, x, y)    name##_CP_RB_NFIND(x, y)
#define CP_RB_NEXT(name, x, y)     name##_CP_RB_NEXT(y)
#define CP_RB_PREV(name, x, y)     name##_CP_RB_PREV(y)
#define CP_RB_MIN(name, x)         name##_CP_RB_MINMAX(x, CP_RB_NEGINF)
#define CP_RB_MAX(name, x)         name##_CP_RB_MINMAX(x, CP_RB_INF)

#define CP_RB_FOREACH(x, name, head)                                             \
  for ((x) = CP_RB_MIN(name, head);                                              \
       (x) != NULL;                                                           \
       (x) = name##_CP_RB_NEXT(x))

#define CP_RB_FOREACH_FROM(x, name, y)                                           \
  for ((x) = (y);                                                             \
      ((x) != NULL) && ((y) = name##_CP_RB_NEXT(x), (x) != NULL);                \
       (x) = (y))

#define CP_RB_FOREACH_SAFE(x, name, head, y)                                     \
  for ((x) = CP_RB_MIN(name, head);                                              \
      ((x) != NULL) && ((y) = name##_CP_RB_NEXT(x), (x) != NULL);                \
       (x) = (y))

#define CP_RB_FOREACH_REVERSE(x, name, head)                                     \
  for ((x) = CP_RB_MAX(name, head);                                              \
       (x) != NULL;                                                           \
       (x) = name##_CP_RB_PREV(x))

#define CP_RB_FOREACH_REVERSE_FROM(x, name, y)                                   \
  for ((x) = (y);                                                             \
      ((x) != NULL) && ((y) = name##_CP_RB_PREV(x), (x) != NULL);                \
       (x) = (y))

#define CP_RB_FOREACH_REVERSE_SAFE(x, name, head, y)                             \
  for ((x) = CP_RB_MAX(name, head);                                              \
      ((x) != NULL) && ((y) = name##_CP_RB_PREV(x), (x) != NULL);                \
       (x) = (y))

#endif  /* _CP_TREE_H_ */
