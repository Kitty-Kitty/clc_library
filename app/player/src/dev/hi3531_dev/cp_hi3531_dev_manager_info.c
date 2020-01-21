/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_hi3531_dev_manager_info.h"



/************************************************************************/
/* 创建销毁info                                                          */
/************************************************************************/
cp_hi3531_dev_manager_info_t *create_hi3531_dev_manager_info(
	cp_hi3531_dev_manager_t *manager, const cp_hi3531_dev_manager_info_t *info)
{
	cp_hi3531_dev_manager_info_t			*tmp_info;


	if (!manager || !info) {
		return CP_NULL;
	}

	//分配info内存
	tmp_info = cp_palloc(manager->pool, cp_sizeof(cp_hi3531_dev_manager_info_t));
	if (!tmp_info) {
		cp_manager_log(error, manager, "init_hi3531_dev_manager() error. cp_palloc() alloc info error.");
		return CP_NULL;
	}
	else {
		cp_memset(tmp_info, 0, cp_sizeof(cp_hi3531_dev_manager_info_t));
		*tmp_info = *info;
		tmp_info->manager = manager;
		manager->info = (cp_module_manager_info_t *)tmp_info;
	}
	return tmp_info;
}

cp_int32_t destroy_hi3531_dev_manager_info(
	cp_hi3531_dev_manager_t *manager, const cp_hi3531_dev_manager_info_t *info)
{
	if (!manager || !info) {
		return -1;
	}

	cp_pfree(manager->pool, info);
	manager->info = CP_NULL;

	return 0;
}

/************************************************************************/
/* 初始化info                                                            */
/************************************************************************/
cp_int32_t init_hi3531_dev_manager_info(
	cp_hi3531_dev_manager_t *manager, const cp_hi3531_dev_manager_info_t *info)
{

	return 0;
}
