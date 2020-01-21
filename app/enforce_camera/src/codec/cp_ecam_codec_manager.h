/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_ECAM_CODEC_MANAGER_INCLUDE_H_
#define _CP_ECAM_CODEC_MANAGER_INCLUDE_H_



#include "cp_ecam_codec_core.h"



typedef struct cp_ecam_codec_manager_s					cp_ecam_codec_manager_t;



#pragma pack(1)

struct cp_ecam_codec_manager_s
{
	CP_CODEC_MANAGER_FIELDS
};

#pragma pack()




cp_ecam_codec_manager_t* create_ecam_codec_manager(cp_module_manager_register_t *register_info, cp_app_t *app, cp_ecam_codec_manager_info_t *info);
cp_int32_t destroy_ecam_codec_manager(cp_app_t *app, cp_ecam_codec_manager_t* manager);

#endif


