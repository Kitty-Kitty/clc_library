/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_pool_module_list.h"



cp_module_register_t  pool_module_list[] = {
	CP_MODULE_REGISTER(cp_pool_module_type_mem_pool, 1, "mem_pool_module", "memory pool module", create_mem_pool, destroy_mem_pool)
};

cp_int32_t pool_module_list_size = cp_ary_size(pool_module_list);
