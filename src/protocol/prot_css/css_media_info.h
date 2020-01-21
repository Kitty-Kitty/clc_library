/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#ifndef _CSS_MEDIA_INFO_INCLUDE_H_
#define _CSS_MEDIA_INFO_INCLUDE_H_

#include "cp_typedef.h"
#include "cp_default.h"
#include "prot_gmp_core.h"
#include "css_device_info.h"




typedef struct cp_timestamp_s						cp_timestamp_t;
// typedef struct cp_rect_s							cp_rect_t;
typedef struct cp_play_position_s					cp_play_position_t;
typedef struct cp_play_channel_info_s				cp_play_channel_info_t;




#pragma pack(1)

typedef enum cp_media_process_type_enum
{
	cp_media_process_type_none = 0,
	cp_media_process_type_audio,
	cp_media_process_type_video,
	cp_media_process_type_all
}cp_media_process_type_e;


/************************************************************************/
/* 时间戳数据                                                            */
/************************************************************************/
struct cp_timestamp_s
{
	cp_uint32_t						a_sec;								//表示时间戳中的绝对时间（absolutely time）秒 部分
	gm_std_uint						a_nsec;								//表示时间戳中的绝对时间（absolutely time）纳秒 部分
	gm_std_uint						r_sec;								//表示时间戳中的相对时间（relatives time）秒 部分
	gm_std_uint						r_nsec;								//表示时间戳中的相对时间（relatives time）秒 部分
};


/************************************************************************/
/* 描述图形矩形信息                                                      */
/************************************************************************/
struct cp_play_position_s
{
	cp_rect_t						source;								//表示媒体源坐标信息
	cp_rect_t						dest;								//表示媒体源目标位置信息
};

/************************************************************************/
/* 异常上报                                                             */
/************************************************************************/
typedef struct cp_exception_info
{
	cp_uint64_t						time;
	cp_int32_t						media_exception_type;
	cp_int32_t						index;
	cp_int32_t						status;
	cp_int32_t						private_status;
	cp_char_t						description[CP_APP_DEFAULT_BUFFER_LENGTH];
	cp_char_t						meidia_id[CP_APP_DEFAULT_ID_LENGTH];
	cp_char_t						play_session[CP_APP_DEFAULT_SESSION_ID_LENGTH];
}cp_exception_info_t;

typedef struct cp_jpeg_info
{
	cp_int32_t						w;												//第一个矩形描述图片大小
	cp_int32_t						h;
	cp_uint32_t						iobuflen;
	cp_char_t						id[CP_APP_DEFAULT_ID_LENGTH];					//图片唯一编号
	cp_char_t						*iobuf;											//图片数据
	cp_uint32_t						channelID;										//设备数字ID
	cp_uchar_t						bfps;
	cp_uchar_t						type;											//图片类型
}cp_jpeg_info_t;

typedef struct cp_checkcolor_info_s
{
	cp_uchar_t						source_color[CP_APP_DEFAULT_LENGTH];			//表示源颜色数值
	cp_uchar_t						dest_color[CP_APP_DEFAULT_LENGTH];				//表示目的颜色数值
}cp_checkcolor_info_t;

typedef struct cp_video_source_info_s
{
	cp_int32_t						height;											//媒体高度
	cp_int32_t						width;											//媒体宽度
	cp_int32_t						fps;											//媒体帧率
	cp_int32_t						bps;											//媒体流的码率信息
	cp_int32_t						encodec_type;									//媒体编码类型编号
	cp_char_t						encodec_name[CP_APP_DEFAULT_STRING_LENGTH];		//媒体解码器名称
}cp_video_source_info_t;

typedef struct cp_audio_source_info_s
{

	cp_int32_t						volume;											//音频音量
	cp_int32_t						bit_rate;										//音频输出码率
	cp_int32_t						sample_rate;									//采样频率，单位（Hz）
	cp_int32_t						encodec_type;									//媒体编码类型编号
	cp_int32_t						sound_channel_type;								//描述声道类型，和sound channel name 二选一
	cp_char_t						sound_channel_name[CP_APP_DEFAULT_STRING_LENGTH];			//描述声道名称
	cp_char_t						encodec_name[CP_APP_DEFAULT_STRING_LENGTH];		//媒体解码器名称
}cp_audio_source_info_t;


typedef struct cp_media_info_s
{
	cp_uchar_t						type;											//媒体类型

	cp_video_source_info_t			video_source;									//表示视频信息
	cp_audio_source_info_t			audio_source;									//表示音频信息

	cp_char_t						id[CP_APP_DEFAULT_ID_LENGTH];					//媒体唯一编号ID
	cp_char_t						name[CP_APP_DEFAULT_STRING_LENGTH];				//媒体名称
	cp_char_t						addr[CP_APP_DEFAULT_BUFFER_LENGTH];				//媒体地址
}cp_media_info_t;

typedef struct cp_stream_description_s
{
	cp_int32_t						transport_type;									//表示该通道媒体的传输方式
	cp_int32_t						distribution_type;								//表示通道媒体流分发的类型	
}cp_stream_description_t;

typedef struct cp_cmd_info_s
{
	cp_uint32_t						time_s;											//表示指令时间秒
	cp_uint32_t						time_ns;										//表示指令时间纳秒
	cp_int32_t						sequence;										//表示指令序号
}cp_cmd_info_t;

typedef struct cp_channel_stop_info_s
{
	cp_char_t						play_session[CP_APP_DEFAULT_SESSION_ID_LENGTH];	//保存当前通道的唯一会话ID
	cp_char_t						id[CP_APP_DEFAULT_ID_LENGTH];					//媒体唯一编号ID
	cp_uint32_t						index;										//媒体唯一编号ID
	cp_uchar_t						type;											//媒体类型
	cp_char_t						encode_type;									//媒体编码类型
	cp_int32_t						status;
}cp_channel_stop_info_t;

typedef struct cp_channel_info_s
{
	cp_int32_t						layer;											//媒体层次
	cp_uint32_t						index;											//媒体唯一编号ID
	cp_int32_t						mode;											//媒体播放类型
	cp_stream_description_t			stream_description;								//通道中媒体流情况描述
	cp_play_addr_t					play_addr_info;									//保存当前通道接收通道请求的IP地址
	cp_multicast_addr_t				multicast_info;									//表示组播的地址
	cp_char_t						play_session[CP_APP_DEFAULT_SESSION_ID_LENGTH];	//保存当前通道的唯一会话ID
	cp_play_position_t				position;										//媒体播放的大屏位置
}cp_channel_info_t;

typedef struct cp_channel_rect_info_s
{
	cp_uint32_t						index;											//表示媒体通道编
	gmdt_rect_t						rect_pair[CP_APP_DEFAULT_RECT_PARE_NUMBER];		//表示矩形框信息
}cp_channel_rect_info_t;

typedef struct cp_media_group_info_s
{
	cp_int32_t						no;												//表示设备编号
	cp_int32_t						group_id;										//表示组编号
	list_node						chan_rect_list;									//表示通道信息
}cp_media_group_info_t;

typedef struct cp_media_channel_info_s
{
	cp_int32_t						group_id;										//表示组编号id数据
	cp_channel_info_t				channel_info;									//表示通道信息
	cp_media_info_t					media_info;										//表示媒体信息
}cp_media_channel_info_t;


struct cp_play_channel_info_s
{
	cp_media_process_type_e			mpy;											//媒体处理类型
	cp_timestamp_t					command_time;									//表示指令执行时间
	cp_uint64_t						sequence_number;								//表示指令序号
	cp_array_t						mci_array;										//表示媒体通道列表cp_media_channel_info_t数组
};


typedef struct cp_background_media_info_s
{
	cp_uchar_t						layer;											//表示表示图片的图层关系
	cp_uchar_t						type;											//媒体类型，设置图片表示图片类型，设置字幕则可以不使用
	cp_char_t						id[CP_APP_DEFAULT_ID_LENGTH];					//媒体唯一编号ID
	cp_uchar_t						back_color[CP_APP_DEFAULT_DOUBLE_LENGTH];		//表示纯色背景图片颜色
	cp_uchar_t						*picture_p;										//表示媒体图片内容
	gmdt_rectpair_t					size;											//表示矩形块信息

	gmdt_rectpair_t					position;										//媒体播放的大屏位置
	gmdt_rectpair_t					back_size;										//表示背景框大小
	cp_float_t						ruler_height;									//描述屏幕高度的像素与毫米的转化比例
	cp_float_t						ruler_width;									//描述屏幕宽度的像素与毫米的转化比例
	cp_int32_t						rows;											//表示需要被设置的行数
	cp_int32_t						columns;										//表示需要被设置的列数
	cp_int32_t						content_font_size;								//表示文本的字号大小
	cp_int32_t						content_space;									//表示文本的间隔大小
	cp_char_t						content[CP_APP_DEFAULT_DEFAULT_WORDS_LENGTH];	//表示文本框的内容
	cp_char_t						content_font[CP_APP_DEFAULT_STRING_LENGTH];		//表示文本的字体名称
	gmdt_rectpair_t					border;											//第一个矩形用来表示屏幕边框上下左右四个方向尺寸信息，第二个矩形预留
	cp_uchar_t						op_type;										//操作类型，主要分为设置背景图片和设置字幕背景
	cp_uchar_t						content_style;									//表示文本的对齐方式
	cp_uchar_t						content_encode;									//表示文本的编码方式
	cp_uchar_t						content_diaphanity;								//表示文本的透明度
	cp_uchar_t						back_diaphanity;								//表示背景的透明度
	cp_uchar_t						content_color[CP_APP_DEFAULT_DOUBLE_LENGTH];	//表示字幕背景颜色
}cp_background_media_info_t;

typedef struct cp_background_reflesh_info_s
{
	cp_char_t						type;											//表示刷新的方式
	cp_char_t						background[CP_APP_DEFAULT_ID_LENGTH];			//表示图片的唯一编码id
	gmdt_rectpair_t					size;											//设备的屏幕信息
	gmdt_rectpair_t					reflesh_time;									//表示刷新时间信息
}cp_background_reflesh_info_t;

typedef struct cp_player_background_info_s
{
	cp_uchar_t						is_set;											//表示是否将处理后的图片设置到设备,0表示不需要；1表示需要
	gmdt_rectpair_t					size;											//设备的屏幕信息
	gmdt_rectpair_t					border;											//设备的屏幕边框信息
	cp_char_t						backcolor[CP_APP_DEFAULT_DOUBLE_LENGTH];		//表示设备的默认背景色
	cp_host_t						host_info;										//表示传递过来的设备信息
	cp_background_media_info_t		media_info;										//表示设备媒体列表
	cp_background_reflesh_info_t	reflesh_info;									//表示设备刷新信息
}cp_player_background_info_t;

typedef struct cp_play_task_s
{
	cp_char_t						id[CP_APP_DEFAULT_ID_LENGTH];					//表示任务的编码ID
	cp_char_t						name[CP_APP_DEFAULT_LENGTH];					//表示任务的名称
	cp_int32_t						serial_number;									//表示任务执行编码
	cp_int32_t						status;											//表示状态码
	gmdt_rectpair_t					begin_time;										//表示任务开始时间
	gmdt_rectpair_t					end_time;										//表示任务结束时间
	gmdt_rectpair_t					interval_time;									//表示任务重复间隔时间
	cp_char_t						type;											//表示任务类型
	cp_int32_t						loop_times;										//表示任务循环次数
}cp_play_task_t;



#pragma pack()

#endif