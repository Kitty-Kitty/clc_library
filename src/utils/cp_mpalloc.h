

/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2014-2-11

Description:palloc defined

**************************************************************************/



#ifndef _CP_PALLOC_H_
#define _CP_PALLOC_H_




#include <stddef.h>
#include "cp_queue.h"
#include "cp_alloc.h"




#define CP_POOL_ALIGNMENT				16
#define CP_MAX_ALLOC_FROM_POOL			(16 * 1024)
#define CP_DEFAULT_POOL_SIZE			(16 * 1024)




typedef struct cp_mpool_s				cp_mpool_t;
typedef	struct cp_mpool_data_s			cp_mpool_data_t;
typedef	struct cp_mpool_large_s			cp_mpool_large_t;




#pragma pack(1)

struct cp_mpool_data_s
{
	unsigned char					*last;
	unsigned char					*end;
	cp_mpool_t						*next;
	int								failed;
};




struct cp_mpool_large_s
{
	cp_mpool_large_t				*next;
	void							*alloc;
};




struct cp_mpool_s
{
	cp_mpool_data_t					d;
	size_t							max;
	cp_mpool_t						*current;
	cp_queue_t						*chain;
	cp_mpool_large_t				*large;
};
#pragma pack()




#if defined(__cplusplus)
extern "C"{
#endif


	cp_mpool_t *cp_create_mpool(size_t size);
	void cp_destroy_mpool(cp_mpool_t *mpool);
	void cp_reset_mpool(cp_mpool_t *mpool);



	void *cp_mpalloc_block(cp_mpool_t *mpool, size_t size);
	void *cp_mpalloc_large(cp_mpool_t *mpool, size_t size);
	void *cp_mpalloc(cp_mpool_t *mpool, size_t size);
	int cp_mpfree(cp_mpool_t *mpool, void *p);

#if defined(__cplusplus)
};
#endif





#endif /* _CP_PALLOC_H_ */










