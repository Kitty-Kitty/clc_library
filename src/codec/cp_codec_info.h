/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/


#ifndef	_CP_CODEC_INFO_INCLUDE_H_
#define _CP_CODEC_INFO_INCLUDE_H_

#include "cp_codec_core.h"









//typedef	struct cp_codec_info_s			cp_codec_info_t;
typedef void(*cp_codec_cb)(void* arg);



#pragma pack(1)


#define CP_CODEC_INFO_FIELDS																						\
		CP_MODULE_INFO_FIELDS																						\
		cp_codec_t						*codec;							/*表示线程唯一id*/							\
		cp_codec_cb						codec_cb;						/*表示时间回调函数*/							\
		cp_void_t						*args;							/*表示参数信息*/								\
		cp_media_description_t			*md;							/*表示当前媒体描述信息*/						\


/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_codec_info_s {
	CP_CODEC_INFO_FIELDS
};

#pragma pack()


/************************************************************************/
/* 设置模块的媒体描述数据													    */
/************************************************************************/
#define CP_CODEC_INFO_SET_MEDIA_DESCRIPTION(codec_info, in_md)	do {												\
		(codec_info)->md = (in_md);																					\
	}while(0);																										\



#endif





