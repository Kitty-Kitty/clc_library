/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_MEM_POOL_INCLUDE_H_
#define _CP_MEM_POOL_INCLUDE_H_



#include "cp_pool_core.h"
#include "cp_mem_pool_info.h"




#define CP_MEM_POOL_ALIGNMENT					16
#define CP_MEM_POOL_MAX_ALLOC					(16 * 1024)
#define CP_DEFAULT_MEM_POOL_SIZE				(16 * 1024)





typedef struct cp_mem_pool_s				cp_mem_pool_t;
typedef struct cp_mem_pool_data_s			cp_mem_pool_data_t;
typedef struct cp_mem_pool_large_s			cp_mem_pool_large_t;



#pragma pack(1)


struct cp_mem_pool_data_s
{
	unsigned char			*last;
	unsigned char			*end;
	cp_mem_pool_t			*next;
	int						failed;
};



struct cp_mem_pool_large_s
{
	void					*alloc;
	cp_mem_pool_large_t		*next;
};




#ifdef max
#undef max
#endif
#define CP_MEM_POOL_FIELDS							\
		CP_MODULE_FIELDS							\
		cp_mpool_t	*mpool;							\

/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_mem_pool_s {
	CP_MEM_POOL_FIELDS												/*表示时间模块信息*/
};



#pragma pack()



cp_mem_pool_t* create_mem_pool(cp_module_register_t *register_info, cp_pool_manager_t *manager, cp_mem_pool_info_t *info);
cp_int32_t destroy_mem_pool(cp_pool_manager_t *manager, cp_mem_pool_t* mem_pool);



#endif


