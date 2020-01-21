/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/


#ifndef	_CP_CODEC_OPTION_INCLUDE_H_
#define _CP_CODEC_OPTION_INCLUDE_H_




//typedef enum cp_codec_option_enum		cp_codec_option_e;



/************************************************************************/
/* 定义module的设置属性                                                  */
/************************************************************************/
typedef enum cp_codec_option_enum
{
	cp_codec_set_option_join = CP_MODULE_OPTION_MAKE_SET_FLAG(0x01),
	cp_codec_get_option_self = CP_MODULE_OPTION_MAKE_GET_FLAG(0x02),
}cp_codec_option_e;



#endif





