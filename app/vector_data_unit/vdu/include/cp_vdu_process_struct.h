/*******************************************************************************
*
*Copyright:novigo
*
*File name: cp_vdu_process_struct.h
*
*Author:fangzhenmu@novigo.com.cn
*
*Version: 1.0
*
*Date:2018/02/02
*
*Description: create (cp_vdu_process_struct.h)
*
*Others:
*
*History:
*******************************************************************************/

#ifndef _CP_VDU_PROCESS_STRUCT_H_
#define _CP_VDU_PROCESS_STRUCT_H_




#include "cp_module.h"
#include "cp_coordinate.h"




typedef		struct cp_vdu_process_s						cp_vdu_process_t;
typedef		struct cp_vdu_channel_process_s				cp_vdu_channel_process_t;
//typedef	enum cp_vdu_process_struct_type_enum		cp_vdu_process_struct_type_e;




/************************************************************************/
/*模块内容,子模块信息必须继承该信息                                       */
/************************************************************************/
#define CP_VDU_PROCESS_STRUCT_FIELDS																			\
			cp_void_t						*vdu;							/*表示处理单元数据地址*/				\
			cp_void_t						*channel;						/*表示处理通道数据地址*/				\
			cp_vdu_process_struct_type_e	type;							/*表示处理结构的类型*/				\
			cp_coordinate_t					coordinate;						/*表示坐标信息*/						\
			cp_rect_t						vdu_rect;						/*表示图片源矩形信息*/				\
			cp_rect_t						image_rect;						/*表示生成的图片大小，这是一种缩放的操作*/				\
			cp_uchar_t						*buf;							/*表示缓存空间*/						\
			cp_bool_t						is_debug_mode;					/*表示是否打开debug 模式*/			\
			cp_char_t						*debug_path;					/*表示debug信息保存的目录*/			\
			cp_int32_t						buf_length;						/*表示缓存空间大小*/					\
			cp_int32_t						image_length;					/*表示图片数据的长度*/				\
			cp_codec_pixel_format_e			pixel_format;					/*表示图片格式类型*/					\
			cp_module_type_e				vdu_channel_module_type;		/*表示vdu channel的类型*/			\
			CP_MODULE_ERROR_FIELDS											/*表示模块的错误信息*/				\



/************************************************************************/
/* 表示处理结构的类型                                                    */
/************************************************************************/
typedef	enum cp_vdu_process_struct_type_enum
{
	cp_vdu_process_struct_type_none = 0,
	cp_vdu_process_struct_type_process,
	cp_vdu_process_struct_type_channel,
}cp_vdu_process_struct_type_e;



/************************************************************************/
/* 表示vdu 处理相关信息结构体                                            */
/************************************************************************/
struct cp_vdu_process_s
{
	CP_VDU_PROCESS_STRUCT_FIELDS									/*表示处理结构内容*/
};



/************************************************************************/
/* 表示vdu channel处理相关信息结构体                                            */
/************************************************************************/
struct cp_vdu_channel_process_s
{
	CP_VDU_PROCESS_STRUCT_FIELDS									/*表示处理结构内容*/
	cp_int32_t							index;						/*表示通道的索引号*/
};



#endif