/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_FUSION_PLAYER_EXTEND_MANAGER_INCLUDE_H_
#define _CP_FUSION_PLAYER_EXTEND_MANAGER_INCLUDE_H_

#include "cp_fusion_player_extend_core.h"




//typedef struct cp_fusion_player_extend_manager_s						cp_fusion_player_extend_manager_t;



#pragma pack(1)


#define CP_FUSION_PLAYER_EXTEND_MANAGER_FIELDS																		\
		CP_FILTER_MANAGER_FIELDS																			\
		cp_int32_t						number;								/*��ʾ��ǰ�Ѿ����ŵ�����*/		\
		cp_int32_t						max_number;							/*��ʾ��ǰ�ܹ����ŵ�������*/		\


struct cp_fusion_player_extend_manager_s
{
	CP_FUSION_PLAYER_EXTEND_MANAGER_FIELDS
};

#pragma pack()




cp_fusion_player_extend_manager_t* create_player_extend_manager
	(cp_module_manager_register_t *register_info, cp_app_t *app, cp_fusion_player_extend_manager_info_t *info);
cp_int32_t destroy_player_extend_manager(cp_app_t *app, cp_fusion_player_extend_manager_t* manager);



#endif


