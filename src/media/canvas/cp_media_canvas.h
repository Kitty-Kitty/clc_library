/*******************************************************************************
*
*Copyright:novigo
*
*File name: cp_media_canvas.h
*
*Author:fangzhenmu@novigo.com.cn
*
*Version: 1.0
*
*Date:2017/08/20
*
*Description: create (cp_media_canvas.h)
*
*Others:
*
*History:
*******************************************************************************/

#ifndef _CP_MEDIA_CANVAS_H_
#define _CP_MEDIA_CANVAS_H_



#include "cp_media_core.h"



//typedef		enum cp_media_canvas_type_enum				cp_media_canvas_type_e;
//typedef		struct cp_media_canvas_s					cp_media_canvas_t;




#pragma pack(1)


/************************************************************************/
/* 表示media canvas 类型信息                                            */
/************************************************************************/
typedef enum cp_media_canvas_type_enum
{
	cp_media_canvas_type_none,								//表示类型未定义
	cp_media_canvas_type_video,								//表示视频类型
	cp_media_canvas_type_audio,								//表示音频类型
}cp_media_canvas_type_e;


/************************************************************************/
/* 表示media canvas 成员内容                                            */
/************************************************************************/
#define CP_MEDIA_CANVAS_FIELDS																					\
		cp_media_canvas_type_e							type;				/*表示媒体canvas的类型信息*/			\
		cp_media_description_t							*md;				/*表示媒体基础信息*/					\



/************************************************************************/
/* 表示最终的输出数据结构                                                 */
/************************************************************************/
struct cp_media_canvas_s
{
	CP_MEDIA_CANVAS_FIELDS
};

#pragma pack()


#endif //_CP_MEDIA_CANVAS_H_


