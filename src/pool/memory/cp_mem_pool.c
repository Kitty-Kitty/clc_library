/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_mem_pool.h"
#include "cp_alloc.h"




cp_mem_pool_t *cp_mem_pool_create();
/*ģ�鴴���ӿڣ���ʾ����һ��ģ��*/
cp_int32_t init_mem_pool(cp_mem_pool_t *mem_pool, const cp_mem_pool_info_t *mem_pool_info);
/*ģ������нӿڣ���ģ��init֮�󣬻ᱻ����*/
cp_int32_t open_mem_pool(cp_mem_pool_t *mem_pool, const cp_mem_pool_info_t *mem_pool_info);
/*��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t read_mem_pool(cp_mem_pool_t *mem_pool, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t write_mem_pool(cp_mem_pool_t *mem_pool, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*�ر�ģ��*/
cp_int32_t close_mem_pool(cp_mem_pool_t *mem_pool);
/*�˳�ģ��*/
cp_int32_t exit_mem_pool(cp_mem_pool_t *mem_pool);
/*����ģ�����*/
cp_int32_t set_option_mem_pool(cp_mem_pool_t *mem_pool, cp_int32_t optname, const cp_void_t* optval);
cp_int32_t get_option_mem_pool(cp_mem_pool_t *mem_pool, cp_int32_t optname, cp_void_t* optval);


cp_mem_pool_t* create_mem_pool(cp_module_register_t *register_info, cp_pool_manager_t *manager, cp_mem_pool_info_t *info)
{
	cp_mem_pool_t			*tmp_pool = NULL;


	if (!manager || !info) {
		return CP_NULL;
	}
	//����һ��ģ��
	//CP_MODULE_MALLOC(tmp_pool, manager, cp_mem_pool_t);
	tmp_pool = (cp_mem_pool_t*)cp_malloc(cp_sizeof(cp_mem_pool_t));
	if (!tmp_pool) {
		return CP_NULL;
	}

	cp_memset(tmp_pool, 0, cp_sizeof(cp_mem_pool_t));
	//Ϊ���ģ�鴴��һ��mpool
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




/*ģ�鴴���ӿڣ���ʾ����һ��ģ��*/
cp_int32_t init_mem_pool(cp_mem_pool_t *mem_pool, const cp_mem_pool_info_t *mem_pool_info)
{
	CP_MODULE_SET_HANDLERS(mem_pool, mem_pool);
	return 0;
}
/*ģ������нӿڣ���ģ��init֮�󣬻ᱻ����*/
cp_int32_t open_mem_pool(cp_mem_pool_t *mem_pool, const cp_mem_pool_info_t *mem_pool_info)
{
	return 0;
}
/*��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t read_mem_pool(cp_mem_pool_t *mem_pool, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}
/*дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t write_mem_pool(cp_mem_pool_t *mem_pool, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}
/*�ر�ģ��*/
cp_int32_t close_mem_pool(cp_mem_pool_t *mem_pool)
{
	return 0;
}
/*�˳�ģ��*/
cp_int32_t exit_mem_pool(cp_mem_pool_t *mem_pool)
{
	return 0;
}
/*����ģ�����*/
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




