/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_CODEC_INCLUDE_H_
#define _CP_CODEC_INCLUDE_H_




#include "cp_codec_core.h"




//typedef struct cp_codec_s				cp_codec_t;
typedef	struct cp_codec_callback_handle_s				cp_codec_callback_handle_t;



#pragma pack(1)



typedef cp_int32_t(*cp_codec_general_cb_handle)(cp_module_t *module,
	cp_codec_callback_info_t *ccb_info_p, cp_media_packet_t *mp);				/*常规回调函数*/



#define CP_CODEC_FIELDS																						\
		CP_MODULE_FIELDS																					\


/************************************************************************/
/*解码器信息                                                             */
/************************************************************************/
struct cp_codec_s {
	CP_CODEC_FIELDS																/*表示时间模块信息*/
};


/************************************************************************/
/* 解码器异常信息                                                        */
/************************************************************************/
struct cp_codec_status_info_s
{
	cp_int32_t					status;
};


/************************************************************************/
/* 解码器回调，主要用于数据处理后同步回调。是一种同步处理                   */
/************************************************************************/
struct cp_codec_callback_handle_s
{
	cp_codec_general_cb_handle		read_cb;							//表示解码器读处理回调函数
	cp_codec_general_cb_handle		write_cb;							//表示解码器写处理回调函数
	cp_codec_general_cb_handle		error_cb;							//表示解码器错误处理回调函数
};


/************************************************************************/
/* 解码器调用信息，解码器通过这个结构判断是否同步回调                      */
/************************************************************************/
struct cp_codec_callback_info_s
{
	cp_codec_callback_handle_t		handle;							//表示回调句柄
	cp_codec_status_info_t			status_info;					//表示解码器状态信息
	cp_module_t						*module;
	cp_uchar_t						**buf;
	cp_int32_t						len;
	cp_int32_t						flag;
};


#pragma pack()



#endif


