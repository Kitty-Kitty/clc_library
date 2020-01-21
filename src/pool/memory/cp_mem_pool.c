/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_mem_pool.h"
#include "cp_alloc.h"




cp_mem_pool_t *cp_mem_pool_create();
/*模块创建接口，表示创建一个模块*/
cp_int32_t init_mem_pool(cp_mem_pool_t *mem_pool, const cp_mem_pool_info_t *mem_pool_info);
/*模块打开运行接口，在模块init之后，会被调用*/
cp_int32_t open_mem_pool(cp_mem_pool_t *mem_pool, const cp_mem_pool_info_t *mem_pool_info);
/*读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留*/
cp_int32_t read_mem_pool(cp_mem_pool_t *mem_pool, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*写模块数据，flag为写模式的扩展标志。默认为0，其他为预留*/
cp_int32_t write_mem_pool(cp_mem_pool_t *mem_pool, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*关闭模块*/
cp_int32_t close_mem_pool(cp_mem_pool_t *mem_pool);
/*退出模块*/
cp_int32_t exit_mem_pool(cp_mem_pool_t *mem_pool);
/*设置模块参数*/
cp_int32_t set_option_mem_pool(cp_mem_pool_t *mem_pool, cp_int32_t optname, const cp_void_t* optval);
cp_int32_t get_option_mem_pool(cp_mem_pool_t *mem_pool, cp_int32_t optname, cp_void_t* optval);


cp_mem_pool_t* create_mem_pool(cp_module_register_t *register_info, cp_pool_manager_t *manager, cp_mem_pool_info_t *info)
{
	cp_mem_pool_t			*tmp_pool = NULL;


	if (!manager || !info) {
		return CP_NULL;
	}
	//创建一个模块
	//CP_MODULE_MALLOC(tmp_pool, manager, cp_mem_pool_t);
	tmp_pool = (cp_mem_pool_t*)cp_malloc(cp_sizeof(cp_mem_pool_t));
	if (!tmp_pool) {
		return CP_NULL;
	}

	cp_memset(tmp_pool, 0, cp_sizeof(cp_mem_pool_t));
	//为这个模块创建一个mpool
	tmp_pool->mpool = cp_create_mpool(CP_APP_DEFAULT_BUFFER_LENGTH);
	if (!tmp_pool->mpool) {
		cp_free(tmp_pool);
		return CP_NULL;
	}
	CP_MODULE_SET_HANDLERS(tmp_pool, mem_pool);
	return tmp_pool;
}

cp_int32_t destroy_mem_pool(cp_pool_manager_t *manager, cp_mem_pool_t* mem_pool)
{
	if (!mem_pool) {
		return -1;
	}

	if (mem_pool->mpool) {
		cp_destroy_mpool(mem_pool->mpool);
		mem_pool->mpool = CP_NULL;
	}

	cp_free(mem_pool);
	return 0;
}




/*模块创建接口，表示创建一个模块*/
cp_int32_t init_mem_pool(cp_mem_pool_t *mem_pool, const cp_mem_pool_info_t *mem_pool_info)
{
	CP_MODULE_SET_HANDLERS(mem_pool, mem_pool);
	return 0;
}
/*模块打开运行接口，在模块init之后，会被调用*/
cp_int32_t open_mem_pool(cp_mem_pool_t *mem_pool, const cp_mem_pool_info_t *mem_pool_info)
{
	return 0;
}
/*读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留*/
cp_int32_t read_mem_pool(cp_mem_pool_t *mem_pool, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}
/*写模块数据，flag为写模式的扩展标志。默认为0，其他为预留*/
cp_int32_t write_mem_pool(cp_mem_pool_t *mem_pool, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}
/*关闭模块*/
cp_int32_t close_mem_pool(cp_mem_pool_t *mem_pool)
{
	return 0;
}
/*退出模块*/
cp_int32_t exit_mem_pool(cp_mem_pool_t *mem_pool)
{
	return 0;
}
/*设置模块参数*/
cp_int32_t set_option_mem_pool(cp_mem_pool_t *mem_pool, cp_int32_t optname, const cp_void_t* optval)
{
	cp_mem_pool_info_t				*tmp_info = (cp_mem_pool_info_t *)optval;


	if (!optval) {
		return -1;
	}

	switch (optname)
	{
		case CP_POOL_OPTION_ALLOC:
		{
			tmp_info->buf = cp_mpalloc(mem_pool->mpool, tmp_info->size);
			if (!tmp_info->buf) {
				return -1;
			}
		}
		break;
		case CP_POOL_OPTION_FREE:
		{
			return cp_mpfree(mem_pool->mpool, tmp_info->buf);
		}
		break;
		default:
		{
			return -1;
		}
		break;
	}
	return 0;
}
cp_int32_t get_option_mem_pool(cp_mem_pool_t *mem_pool, cp_int32_t optname, cp_void_t* optval)
{
	return 0;
}




