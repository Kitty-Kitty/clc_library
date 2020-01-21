/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef _CP_VDU_INFO_INCLUDE_H_
#define _CP_VDU_INFO_INCLUDE_H_




#include "cp_vdu_core.h"




//typedef struct cp_vdu_app_info_s					cp_vdu_app_info_t;




#pragma pack(1)

/************************************************************************/
/* ǰ���豸������Ϣ                                                     */
/************************************************************************/
struct cp_vdu_app_info_s
{
	CP_APP_INFO_FIELDS
	cp_channel_manager_t			channel_manager;															//��ʾͨ����������Ϣ

};

#pragma pack()

cp_bool_t init_vdu_info(cp_vdu_app_t *vdu, cp_vdu_app_info_t *info);


#endif