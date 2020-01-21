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





#ifndef _CP_RBTREE_H_INCLUDED_
#define _CP_RBTREE_H_INCLUDED_

#include <stdio.h>

#define cp_thread_volatile	
#define cp_uint		unsigned int

typedef unsigned int  cp_rbtree_key_t;
typedef int   cp_rbtree_key_int_t;

typedef struct cp_rbtree_node_s  cp_rbtree_node_t;

struct cp_rbtree_node_s {
	cp_rbtree_key_t       key;
	cp_rbtree_node_t     *left;
	cp_rbtree_node_t     *right;
	cp_rbtree_node_t     *parent;
	unsigned char         color;
	void				 *data;
};

#define  cp_rbtree_node_init(node)		\
			node.left = NULL;			\
			node.right = NULL;			\
			node.parent = NULL;			\
			node.key = 0;

#define	 cp_rbtree_node_is_empty(node)	\
		 node.left == NULL &&			\
		 node.right == NULL &&			\
		 node.parent == NULL &&			\
		 node.key == 0

typedef struct cp_rbtree_s  cp_rbtree_t;

typedef void (*cp_rbtree_insert_pt) (cp_rbtree_node_t *root,
    cp_rbtree_node_t *node, cp_rbtree_node_t *sentinel);

struct cp_rbtree_s {
    cp_rbtree_node_t     *root;
    cp_rbtree_node_t     *sentinel;
    cp_rbtree_insert_pt   insert;
};

#define cp_rbtree_init(tree, s, i)												\
    cp_rbtree_sentinel_init(s);													\
    (tree)->root = s;															\
    (tree)->sentinel = s;														\
    (tree)->insert = i

	void cp_rbtree_insert(cp_thread_volatile cp_rbtree_t *tree,
		cp_rbtree_node_t *node);
	void cp_rbtree_delete(cp_thread_volatile cp_rbtree_t *tree,
		cp_rbtree_node_t *node);
	void cp_rbtree_insert_value(cp_rbtree_node_t *root, cp_rbtree_node_t *node,
		cp_rbtree_node_t *sentinel);
	void cp_rbtree_insert_timer_value(cp_rbtree_node_t *root,
		cp_rbtree_node_t *node, cp_rbtree_node_t *sentinel);

#define cp_rbt_red(node)               ((node)->color = 1)
#define cp_rbt_black(node)             ((node)->color = 0)
#define cp_rbt_is_red(node)            ((node)->color)
#define cp_rbt_is_black(node)          (!cp_rbt_is_red(node))
#define cp_rbt_copy_color(n1, n2)      (n1->color = n2->color)

/* a sentinel must be black */

#define cp_rbtree_sentinel_init(node)  cp_rbt_black(node)

/*static inline*/ cp_rbtree_node_t *
cp_rbtree_min(cp_rbtree_node_t *node, cp_rbtree_node_t *sentinel);

#endif /* _CP_RBTREE_H_INCLUDED_ */




