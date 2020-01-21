

/*******************************************************************************
*
*Copyright:novigo
*
*File name: cp_vdu.h
*
*Author:fangzhenmu@novigo.com.cn
*
*Version: 1.0
*
*Date:2018/01/01
*
*Description: create (cp_vdu.h)
*1、这个模块主要用于矢量类数据的处理需求，通过模块方式可以支持多种类型
*2、模块主要处置思想为：对cp_app的一种整体封装，将app封装为一个codec类模块
*3、模块的使用方法有两种：
*			1）外部使用。加载cp_vdu.h头文件，调用其中的接口函数
*			2）内部使用。即可以使用1）方法，也可以直接加载其中的模块
*Others:
*
*History:
*******************************************************************************/

#ifndef _CP_VDU_H_
#define _CP_VDU_H_



#include <stdio.h>
#include <stdlib.h>
#include "cp_vdu_type.h"
#include "cp_vdu_vector_stream_type.h"
#include "cp_vdu_rect.h"
#include "cp_vdu_pixel.h"



//定义接口的导出方式
#ifndef cp_extern
#define cp_extern
#endif



//表示默认的缓冲区大小
#define CP_VDU_DEFAULT_BUFFER_LENGTH			32




typedef  struct cp_vdu_s						cp_vdu_t;
typedef  struct cp_vdu_channel_s				cp_vdu_channel_t;
typedef  struct cp_vdu_info_s					cp_vdu_info_t;
typedef	 struct cp_vdu_version_s				cp_vdu_version_t;
typedef  struct cp_vdu_image_info_s				cp_vdu_image_info_t;




#pragma pack(1)


/************************************************************************/
/*定义一个vdu内容															*/
/************************************************************************/
struct cp_vdu_s {
	void										*app;					/*用于描述app信息结构信息，用于兼容cp_app内容*/
	void										*process;				/*表示处理单元地址*/
	cp_vdu_type_e								type;					/*表示vdu类型*/

};


/************************************************************************/
/*定义一个vdu channel内容													*/
/************************************************************************/
struct cp_vdu_channel_s {
	void										*app;					/*用于描述app信息结构信息，用于兼容cp_app内容*/
	cp_vdu_t									*vdu;					/*表示其发展的vdu对象*/
	void										*channel;				/*表示保存channel的信息内容*/
	cp_vdu_channel_type_e						type;					/*表示vdu channel通道的类型*/
	int											index;					/*表示通道的索引号*/
};



/************************************************************************/
/*定义一个vdu内容															*/
/************************************************************************/
struct cp_vdu_info_s {
	int											type;					/*表示类型信息*/
};



/************************************************************************/
/*定义一个vdu内容															*/
/************************************************************************/
struct cp_vdu_version_s {
	char										name[CP_VDU_DEFAULT_BUFFER_LENGTH];					/*表示程序名称,例如:"cp_vdu"*/
	int											version;											/*表示版本号,例如:100*/
	char										str_version[CP_VDU_DEFAULT_BUFFER_LENGTH];			/*表示版本字符串,例如:"V0.1.0"*/
	char										description[CP_VDU_DEFAULT_BUFFER_LENGTH];			/*表示其他描述信息,例如:"cp_vdu/V0.1.0"*/
};


/************************************************************************/
/*定义一个vdu 图片信息内容													*/
/************************************************************************/
struct cp_vdu_image_info_s {
	char										*buf;												/*表示输出的图片位图保存的内存位置*/
	int											buf_length;											/*表示输出的图片位图保存的内存长度*/
	cp_vdu_pixel_format_e						vpf;												/*表示图片的格式*/
	cp_vdu_rect_t								vdu_rect;											/*表示vdu的图片区域*/
	cp_vdu_rect_t								image_rect;											/*表示vdu图片导出后的目标图片大小，也存在缩放的操作*/
	int											image_length;										/*表示图片位图数据实际长度*/
};



#pragma pack()



#include "cp_vdu_api.h"




#endif //_CP_VDU_H_


