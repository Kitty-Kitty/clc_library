/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2017-03-26

Description:

**************************************************************************/

#ifndef _CP_POOL_FUNCTION_INCLUDE_H_
#define _CP_POOL_FUNCTION_INCLUDE_H_


typedef struct cp_pool_info_s					cp_pool_info_t;
//typedef	struct cp_pool_s						cp_pool_t;
typedef	struct cp_pool_handles_s				cp_pool_handles_t;
typedef	struct cp_pool_manager_handles_s		cp_pool_manager_handles_t;



//创建一个内存池，默认是使用标准内存的内存池，即mem_pool
cp_pool_t* cp_create_pool(const cp_app_t *app);
//创建指定类型的内存池，即根据info中的type类型来选择需要创建的内存池
cp_pool_t* cp_create_pool_ex(const cp_app_t *app, const cp_pool_info_t *info);
//销毁指定的内存池
cp_void_t cp_destroy_pool(const cp_pool_t *pool);
//重置内存池，主要是实现部分内存的释放
cp_void_t cp_reset_pool(const cp_pool_t *pool);

//内存申请（对齐）
cp_void_t* cp_palloc(const cp_pool_t *pool, const size_t size);
//内存申请（不对齐）
// cp_void_t *cp_pnalloc(cp_pool_t *pool, size_t size);
//内存申请（清空）
cp_void_t* cp_pcalloc(const cp_pool_t *pool, const size_t size);
// cp_void_t *cp_pmemalign(cp_pool_t *pool, size_t size, size_t alignment);
cp_int32_t cp_pfree(const cp_pool_t *pool, const cp_void_t *p);



#endif