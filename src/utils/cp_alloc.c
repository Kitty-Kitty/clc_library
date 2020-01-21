





#include "cp_alloc.h"





void *cp_memalign(size_t alignment, size_t size)
{
	void  *p;
	



#if defined(__linux__)
	int    err;

	err = posix_memalign(&p, alignment, size);
	if (err) {
		p = NULL;
	}

#else
	p = malloc(size);
#endif

	return p;
}


void *cp_alloc(size_t size)
{
	void  *p;


	p = malloc(size);
	if (p == NULL) {
		
	}

	return p;
}


























