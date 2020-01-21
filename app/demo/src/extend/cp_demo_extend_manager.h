/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_DEMO_EXTEND_MANAGER_INCLUDE_H_
#define _CP_DEMO_EXTEND_MANAGER_INCLUDE_H_

#include "cp_demo_extend_core.h"




//typedef struct cp_demo_extend_manager_s						cp_demo_extend_manager_t;



#pragma pack(1)


#define CP_DEMO_EXTEND_MANAGER_FIELDS																		\
		CP_FILTER_MANAGER_FIELDS																			\
		cp_int32_t						number;								/*��ʾ��ǰ�Ѿ����ŵ�����*/		\
		cp_int32_t						max_number;							/*��ʾ��ǰ�ܹ����ŵ�������*/		\


struct cp_demo_extend_manager_s
{
	CP_DEMO_EXTEND_MANAGER_FIELDS
};

#pragma pack()




cp_demo_extend_manager_t* create_demo_extend_manager
	(cp_module_manager_register_t *register_info, cp_app_t *app, cp_demo_extend_manager_info_t *info);
cp_int32_t destroy_demo_extend_manager(cp_app_t *app, cp_demo_extend_manager_t* manager);



#endif


