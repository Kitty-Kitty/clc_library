/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_ECAM_CODEC_INCLUDE_H_
#define _CP_ECAM_CODEC_INCLUDE_H_

#include <stddef.h>
#include "uv.h"
#include "cp_ecam_codec_core.h"



//typedef struct cp_ecam_codec_s				cp_ecam_codec_t;





#pragma pack(1)


#define CP_ECAM_CODEC_FIELDS											\
		CP_CODEC_FIELDS													\
		cp_int32_t						css_av_type;	/*css 媒体类型*/	\
		cp_media_channel_info_t			*mci;		/*媒体通道信息*/		\


/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_ecam_codec_s {
	CP_ECAM_CODEC_FIELDS												/*表示时间模块信息*/
};

#pragma pack()




cp_ecam_codec_t* create_ecam_codec(cp_module_register_t *register_info, cp_codec_manager_t *manager, cp_ecam_codec_info_t *info);
cp_int32_t destroy_ecam_codec(cp_codec_manager_t *manager, cp_ecam_codec_t* ecam_codec);



/************************************************************************/
/* 设置解码的数据													    */
/************************************************************************/
#define CP_ECAM_CODEC_SET_MEDIA_CHANNEL_INFO(codec, in_mci)	do {	\
		(codec)->mci = (cp_media_channel_info_t*)(in_mci);				\
	}while(0);															\


#endif


