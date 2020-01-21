





#include "cp_mpalloc.h"




//#define			CP_MPALLOC_DEBUG				1


cp_mpool_t *cp_create_mpool(size_t size)
{
	cp_mpool_t			*p = NULL;


	p = (cp_mpool_t*)cp_memalign(CP_POOL_ALIGNMENT, size);
	if (p == NULL) {
		return NULL;
	}

	p->d.last = (unsigned char *)p + sizeof(cp_mpool_t);
	p->d.end = (unsigned char *)p + size;
	p->d.next = NULL;
	p->d.failed = 0;

	size = size - sizeof(cp_mpool_t);

	p->max = (size < CP_MAX_ALLOC_FROM_POOL) ? size : CP_MAX_ALLOC_FROM_POOL;
	p->current = p;
	p->chain = NULL;
	p->large = NULL;

	return p;
}


void cp_reset_mpool(cp_mpool_t *mpool)
{
	cp_mpool_t				*p;
	cp_mpool_large_t		*l;



	// 释放所有大块内存
	for (l = mpool->large; l; l = l->next) {
		if (l->alloc) {
			cp_free(l->alloc);
		}
	}

	// 初始化所有普通内存（所有内存池的last重新指向ngx_mpool_t结构体后面 ）
	for (p = mpool; p; p = p->d.next) {
		p->d.last = (unsigned char *)p + sizeof(cp_mpool_t);
		p->d.failed = 0;
	}

	mpool->current = mpool;
	mpool->chain = NULL;
	mpool->large = NULL;
}


void cp_destroy_mpool(cp_mpool_t *mpool)
{
	cp_mpool_t          *p, *n;
	cp_mpool_large_t    *l;


	// 释放所有的大块内存
	for (l = mpool->large; l; l = l->next) {
		if (l->alloc) {
			cp_free(l->alloc);
		}
	}

	// 释放所有普通内存
	for (p = mpool, n = mpool->d.next; /* void */; p = n, n = n->d.next) {
		cp_free(p);
		if (n == NULL) {
			break;
		}
	}
}


void *cp_mpalloc_block(cp_mpool_t *mpool, size_t size)
{
	unsigned char		*m;
	size_t				psize;
	cp_mpool_t			*p, *new_p;


	psize = (size_t)(mpool->d.end - (unsigned char *)mpool);
	m = (unsigned char*)cp_memalign(CP_POOL_ALIGNMENT, psize);
	if (m == NULL) {
		return NULL;
	}

	new_p = (cp_mpool_t *)m;
	new_p->d.end = m + psize;
	new_p->d.next = NULL;
	new_p->d.failed = 0;

	m += sizeof(cp_mpool_data_t);
	m = cp_align_ptr(m, CP_ALIGNMENT);
	new_p->d.last = m + size;

	for (p = mpool->current; p->d.next; p = p->d.next) {
		if (p->d.failed++ > 4) {
			mpool->current = p->d.next;
		}
	}
	p->d.next = new_p;

	return m;
}


void *cp_mpalloc_large(cp_mpool_t *mpool, size_t size)
{
	void				*p;
	size_t				n = 0;
	cp_mpool_large_t	*large;


	p = cp_alloc(size);
	if (p == NULL) {
		return NULL;
	}

	for (large = mpool->large; large; large = large->next) {
		if (large->alloc == NULL) {
			large->alloc = p;
			return p;
		}
		if (n++ > 3) {
			break;
		}
	}

	large = (cp_mpool_large_t*)cp_mpalloc(mpool, sizeof(cp_mpool_large_t));
	if (large == NULL) {
		cp_free(p);
		return NULL;
	}

	large->alloc = p;
	large->next = mpool->large;
	mpool->large = large;

	return p;
}


/*
从内存池分配内存，并对齐
*/
void *cp_mpalloc(cp_mpool_t *mpool, size_t size)
{
// #if 0
	unsigned char		*m;
	cp_mpool_t			*p;



	if (size <= mpool->max) {
		p = mpool->current;
		do {
			m = cp_align_ptr(p->d.last, CP_ALIGNMENT);

			if ((size_t)(p->d.end - m) >= size) {
				p->d.last = m + size;
				return m;
			}
			p = p->d.next;

		} while (p);
		return cp_mpalloc_block(mpool, size);
	}

	/*大内存尺寸则分配大块内存并添加到
	大块内存链表
	*/
	return cp_mpalloc_large(mpool, size);
// #endif
// #if defined(CP_MPALLOC_DEBUG)
// 	return  _malloc_dbg(size);
// #else
// 	return cp_malloc(size);
// #endif
}

int cp_mpfree(cp_mpool_t *mpool, void *p)
{
// #if 0
	cp_mpool_large_t  *l;


	for (l = mpool->large; l; l = l->next) {
		if (p == l->alloc) {
			cp_free(l->alloc);
			l->alloc = NULL;
			return 0;
		}
	}
// #endif	
// #if defined(CP_MPALLOC_DEBUG)
// 	_free_dbg(p);
// #else
// 	cp_free(p);
// #endif
	return -1;
}






















