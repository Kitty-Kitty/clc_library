/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_CSS_HOOK_MANAGER_INCLUDE_H_
#define _CP_CSS_HOOK_MANAGER_INCLUDE_H_

#include "cp_vdu_demo_hook_core.h"
#include "cp_rbtree.h"




//typedef struct cp_vdu_demo_hook_manager_s					cp_vdu_demo_hook_manager_t;



#pragma pack(1)


#define CP_CSS_HOOK_MANAGER_FIELDS																\
		CP_HOOK_MANAGER_FIELDS																	\
		cp_rbtree_node_t		hook_rbtree;		/*表示保存指令编码的红黑树，方便查找*/			\


struct cp_vdu_demo_hook_manager_s
{
	CP_CSS_HOOK_MANAGER_FIELDS
};

#pragma pack()




cp_vdu_demo_hook_manager_t* create_vdu_demo_hook_manager
	(cp_module_manager_register_t *register_info, cp_app_t *app, cp_vdu_demo_hook_manager_info_t *info);
cp_int32_t destroy_vdu_demo_hook_manager(cp_app_t *app, cp_vdu_demo_hook_manager_t* manager);



#endif


