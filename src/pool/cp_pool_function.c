/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2017-03-26

Description:

**************************************************************************/
#include "cp_pool_core.h"
#include "cp_pool_function.h"


extern cp_module_register_t  pool_module_list[];
extern cp_int32_t pool_module_list_size;



cp_pool_t *cp_create_pool(const cp_app_t *app)
{
	cp_pool_manager_t				*tmp_manager = CP_NULL;
	cp_pool_t						*tmp_pool = CP_NULL;
	cp_module_manager_info_t		tmp_module_manager_info = { 0, };
	cp_pool_info_t					tmp_pool_info = { 0, };


	CP_MODULE_MANAGER_INFO_SET_TYPE(&tmp_module_manager_info, cp_module_manager_type_pool);
	tmp_manager = (cp_pool_manager_t*)cp_get_manager(app, &tmp_module_manager_info);
	if (!tmp_manager) {
		return CP_NULL;
	}

	tmp_pool_info.size = CP_APP_DEFAULT_BUFFER_LENGTH;

	tmp_pool = (cp_pool_t*)cp_create_module(&pool_module_list[0], tmp_manager, &tmp_pool_info);
	if (tmp_pool) {
		if (!cp_init_module(tmp_pool, &tmp_pool_info)) {
			return tmp_pool;
		}
		else {
			cp_destroy_pool(tmp_pool);
		}
	}
	return CP_NULL;
}
cp_pool_t *cp_create_pool_ex(const cp_app_t *app, const cp_pool_info_t *info)
{
	cp_pool_manager_t				*tmp_manager = CP_NULL;
	cp_module_manager_info_t		tmp_module_manager_info;


	CP_MODULE_MANAGER_INFO_SET_TYPE(&tmp_module_manager_info, cp_module_manager_type_pool);
	tmp_manager = (cp_pool_manager_t*)cp_get_manager(app, &tmp_module_manager_info);
	if (!tmp_manager) {
		return CP_NULL;
	}

	return (cp_pool_t*)cp_create_module(&pool_module_list[0], tmp_manager, info);
}
cp_void_t cp_destroy_pool(const cp_pool_t *pool)
{
	if (pool) {
		cp_destroy_module(pool->manager, pool);
	}
}
cp_void_t cp_reset_pool(const cp_pool_t *pool)
{

}

cp_void_t *cp_palloc(const cp_pool_t *pool, const size_t size)
{
	cp_int32_t					ret_int = 0;
	cp_pool_info_t				tmp_info = { 0, };


	tmp_info.size = size;
	ret_int = cp_set_option_module(pool, CP_POOL_OPTION_ALLOC, &tmp_info);
	if (ret_int) {
		return CP_NULL;
	}

	return tmp_info.buf;
}
// cp_void_t *cp_pnalloc(cp_pool_t *pool, size_t size)
// {
// 	return 0;
// }
cp_void_t *cp_pcalloc(const cp_pool_t *pool, const size_t size)
{
	cp_void_t					*tmp_buf = CP_NULL;



	tmp_buf = cp_palloc(pool, size);
	if (!tmp_buf) {
		return CP_NULL;
	}

	cp_memset(tmp_buf, 0, size);
	return tmp_buf;
}
// cp_void_t *cp_pmemalign(cp_pool_t *pool, size_t size, size_t alignment)
// {
// 	return 0;
// }
cp_int32_t cp_pfree(const cp_pool_t *pool, const cp_void_t *p)
{
	cp_pool_info_t				tmp_info;



	tmp_info.buf = (cp_void_t*)p;
	return cp_set_option_module(pool, CP_POOL_OPTION_FREE, &tmp_info);
}
