/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-07

Description:

**************************************************************************/

#ifndef _CP_MEDIA_DESCRIPTION_INCLUDE_H_
#define _CP_MEDIA_DESCRIPTION_INCLUDE_H_



//  typedef	struct cp_media_description_s					cp_media_description_t;
//  typedef	struct cp_media_packet_s						cp_media_packet_t;
//  typedef	enum cp_media_description_type_enum				cp_media_description_type_e;



#pragma pack(1)


/************************************************************************/
/* 表示数据类型                                                          */
/************************************************************************/
typedef	enum cp_media_description_type_enum
{
	cp_media_description_type_none = 0,
	cp_media_description_type_general,
	cp_media_description_type_video,
	cp_media_description_type_audio,
}cp_media_description_type_e;


#include "cp_media_core.h"


/************************************************************************/
/* 表示media description 成员内容                                            */
/************************************************************************/
#define CP_MEDIA_DESCRIPTION_FIELDS																									\
	cp_media_description_type_e				type;											/*表示描述信息类型*/						\
	cp_int32_t								desc_len;										/*媒体描述数据长度*/						\
	cp_codec_pixel_format_e					pix_fmt;										/*媒体解码类型*/							\
	cp_int32_t								channel;										/*媒体通道号*/							\
	cp_int32_t								priority;										/*通道优先级*/							\
	cp_media_type_e							encodec_type;									/*媒体编码类型编号*/						\
	cp_char_t								encodec_name[CP_APP_DEFAULT_STRING_LENGTH];		/*媒体解码器名称*/						\



/************************************************************************/
/* 媒体描述信息                                                          */
/************************************************************************/
struct cp_media_description_s
{
	CP_MEDIA_DESCRIPTION_FIELDS
};



#pragma pack()



/************************************************************************/
/* 包含                                                            */
/************************************************************************/
#include "cp_video_description.h"
#include "cp_audio_description.h"



/************************************************************************/
/* 创建描述信息                                                          */
/************************************************************************/
cp_media_description_t	*create_media_description(cp_pool_t *pool, cp_media_description_type_e type);

/************************************************************************/
/* 消毁描述信息                                                          */
/************************************************************************/
cp_int32_t destroy_media_description(cp_pool_t *pool, cp_media_description_t *md);





#endif