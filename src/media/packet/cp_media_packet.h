/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-05

Description:

**************************************************************************/

#ifndef _CP_MEDIA_PACKET_INCLUDE_H_
#define _CP_MEDIA_PACKET_INCLUDE_H_



#include "cp_media_core.h"
#include "cp_codec_core.h"



#define		CP_MEDIA_PACKET_MAX_BUFFER_NUMBER			8		//当前最大通道数


//typedef	enum cp_media_packet_type_enum				cp_media_packet_type_e;
//typedef   enum cp_media_packet_buf_type_enum			cp_media_packet_buf_type_e;
typedef		struct cp_media_packet_buf_s				cp_media_packet_buf_t;

//typedef	struct cp_media_packet_s					cp_media_packet_t;



#pragma pack(1)

/************************************************************************/
/* 表示数据类型                                                          */
/************************************************************************/
typedef enum cp_media_packet_type_enum
{
	cp_media_packet_type_none = 0,
	cp_media_packet_type_audio,
	cp_media_packet_type_video,
	cp_media_packet_type_data_and_timestamp,
}cp_media_packet_type_e;


/* 表示数据buf类型                                                       */
/************************************************************************/
typedef enum cp_media_packet_buf_type_enum
{
	cp_media_packet_buf_type_none = 0,
	cp_media_packet_buf_type_ffmpeg,							//表示ffmpeg格式
	cp_media_packet_buf_type_hi,								//表示海狮格式
}cp_media_packet_buf_type_e;


/************************************************************************/
/* 媒体数据buf包                                                         */
/************************************************************************/
struct cp_media_packet_buf_s
{
	cp_media_packet_buf_type_e				buf_type;									//数据buf类型
	cp_buf_t								buf[CP_MEDIA_PACKET_MAX_BUFFER_NUMBER];		//媒体数据部分
	cp_void_t								*data;										//表示无法用buf表示的其他数据
};



/************************************************************************/
/* 表示media packet 成员内容                                            */
/************************************************************************/
#define CP_MEDIA_PACKET_FIELDS																				\
  	cp_pool_t								*pool;				/*表示当前内存*/								\
	cp_media_description_t					*md_p;				/*表示当前播放的媒体信息*/					\
	cp_codec_callback_info_t				*ccb_info_p;		/*表示解码器调用信息*/						\
	cp_module_t								*orgin_module;		/*表示处理的模块*/							\
	cp_void_t								*data;				/*表示其他数据*/								\
	cp_media_packet_type_e					type;				/*数据类型*/									\
	cp_timespec_t							ts;					/*媒体时间*/									\
	cp_media_packet_buf_t					mp_buf;				/*媒体数据buf部分*/							\



/************************************************************************/
/* 媒体数据包                                                            */
/************************************************************************/
struct cp_media_packet_s
{
	CP_MEDIA_PACKET_FIELDS
};

#pragma pack()




/************************************************************************/
/* 包含                                                            */
/************************************************************************/
#include "cp_video_frame_packet.h"






/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: create_media_packet
*
* 函数说明: 创建media packet
*
* 参    数: cp_pool_t * pool						[in]参数说明
* 参    数: cp_int32_t size						[in]参数说明
* 参    数: cp_media_packet_type_e type			[in]参数说明
*
* 返 回 值: cp_media_packet_t *
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-12-06 10:46:04
******************************************************************************************************/
cp_media_packet_t *create_media_packet(cp_pool_t *pool, cp_int32_t size, cp_media_packet_type_e type);

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: create_number_media_packet
*
* 函数说明: 创建多个media packet
*
* 参    数: cp_pool_t * pool						[in]参数说明
* 参    数: cp_int32_t size						[in]每个media packet大小
* 参    数: cp_int32_t number					[in]创建的个数
* 参    数: cp_media_packet_type_e type						[in]参数说明
*
* 返 回 值: cp_media_packet_t *
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-01-16 13:44:40
******************************************************************************************************/
cp_media_packet_t *create_number_media_packet(cp_pool_t *pool, cp_int32_t size, cp_int32_t number, cp_media_packet_type_e type);

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: get_media_packet_data_length
*
* 函数说明: 获取媒体包数据长度
*
* 参    数: cp_media_packet_t * mp						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-01-16 14:38:09
******************************************************************************************************/
cp_int32_t get_media_packet_data_length(cp_media_packet_t *mp);

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: clear_media_packet
*
* 函数说明: 清除media packet数据
*
* 参    数: cp_media_packet_t * mp						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-01-16 14:59:23
******************************************************************************************************/
cp_int32_t clear_media_packet(cp_media_packet_t *mp);

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: create_media_packet_channel_buffer
*
* 函数说明: 创建指定通道
*
* 参    数: cp_media_packet_t * mp						[in]参数说明
* 参    数: cp_int32_t channel_number						[in]参数说明
* 参    数: cp_int32_t size						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-12-08 13:19:37
******************************************************************************************************/
cp_int32_t create_media_packet_channel_buffer(cp_media_packet_t *mp, cp_int32_t channel_number, cp_int32_t size);

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: destroy_media_packet
*
* 函数说明: 消毁媒体数据包
*
* 参    数: cp_media_packet_t		*mp					[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-12-06 10:32:38
******************************************************************************************************/
cp_int32_t destroy_media_packet(cp_media_packet_t *mp);

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: create_media_packet_description
*
* 函数说明: 创建媒体描述信息
*
* 参    数: cp_pool_t * pool						[in]参数说明
* 参    数: cp_media_packet_t * mp				[in]参数说明
* 参    数: cp_media_description_type_e type		[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-12-07 16:43:30
******************************************************************************************************/
cp_int32_t create_media_packet_description(cp_pool_t *pool, cp_media_packet_t *mp, cp_media_description_type_e type);

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: destroy_media_packet_description
*
* 函数说明: 消毁媒体描述信息
*
* 参    数: cp_pool_t * pool						[in]参数说明
* 参    数: cp_media_packet_t * packet						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-12-07 16:47:00
******************************************************************************************************/
cp_int32_t destroy_media_packet_description(cp_pool_t *pool, cp_media_packet_t *packet);

#endif