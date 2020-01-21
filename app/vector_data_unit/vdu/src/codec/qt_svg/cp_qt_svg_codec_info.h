/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/


#ifndef	_CP_QT_SVG_CODEC_INFO_INCLUDE_H_
#define _CP_QT_SVG_CODEC_INFO_INCLUDE_H_

#include "cp_qt_svg_codec_core.h"




#define		CP_QT_SVG_CODEC_NAME_MAX_LENGTH				32			//��ʾ����������




//typedef	struct cp_qt_svg_codec_info_s			cp_qt_svg_codec_info_t;
typedef void(*cp_qt_svg_codec_cb)(cp_qt_svg_codec_t* th);




#pragma pack(1)


#define CP_QT_SVG_CODEC_INFO_FIELDS														\
		CP_CODEC_INFO_FIELDS																\
		cp_char_t	av_name[CP_QT_SVG_CODEC_NAME_MAX_LENGTH];	/*��ʾ����������*/		\
		cp_int32_t	av_type;										/*��ʾ����������*/		\
		cp_int32_t	css_type;										/*��ʾcss����������*/	\



/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_qt_svg_codec_info_s {
	CP_QT_SVG_CODEC_INFO_FIELDS
};

#pragma pack()




#endif





