/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_HI3531_VPSS_INCLUDE_H_
#define _CP_HI3531_VPSS_INCLUDE_H_

#include "cp_hi3531_vpss_core.h"






#pragma pack(1)


#define CP_HI3531_VPSS_FIELDS																\
		CP_PLAYER_CODEC_FIELDS																		\



/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_hi3531_vpss_s {
	CP_HI3531_VPSS_FIELDS												/*表示时间模块信息*/

#if defined(CP_HI3531_VPSS_FILE_DEBUG)
		FILE													*file;			/*媒体文件*/
	cp_int32_t													index;
#endif

	cp_hi3531_vpss_conf_t										*av_conf;		/*表示输入配置信息*/
	cp_hi3531_vpss_configure_t							hacc;			/*表示当前的编码器配置信息*/

};


#pragma pack()



cp_hi3531_vpss_t* create_hi3531_vpss(cp_module_register_t *register_info, cp_codec_manager_t *manager, cp_hi3531_vpss_info_t *info);
cp_int32_t destroy_hi3531_vpss(cp_codec_manager_t *manager, cp_hi3531_vpss_t* hi3531_vpss);

#endif


