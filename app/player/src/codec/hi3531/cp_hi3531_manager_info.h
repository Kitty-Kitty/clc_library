/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_HI3531_MANAGER_INFO_INCLUDE_H_
#define _CP_HI3531_MANAGER_INFO_INCLUDE_H_



#include "cp_hi3531_core.h"



#pragma pack(1)



/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_hi3531_manager_info_s {
	CP_CODEC_MANAGER_INFO_FIELDS

	cp_hi3531_manager_t										*manager;
};

#pragma pack()






/************************************************************************/
/* 创建销毁info                                                          */
/************************************************************************/
cp_hi3531_manager_info_t *create_hi3531_manager_info(
	cp_hi3531_manager_t *manager, const cp_hi3531_manager_info_t *info);

cp_int32_t destroy_hi3531_manager_info(
	cp_hi3531_manager_t *manager, const cp_hi3531_manager_info_t *info);




/************************************************************************/
/* 初始化info                                                            */
/************************************************************************/
cp_int32_t init_hi3531_manager_info(
	cp_hi3531_manager_t *manager, const cp_hi3531_manager_info_t *info);


#endif




