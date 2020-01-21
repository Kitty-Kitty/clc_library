/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_QT_SVG_CODEC_INCLUDE_H_
#define _CP_QT_SVG_CODEC_INCLUDE_H_

#include "cp_qt_svg_codec_core.h"



//typedef struct cp_qt_svg_codec_s					cp_qt_svg_codec_t;




#pragma pack(1)


#define CP_QT_SVG_CODEC_FIELDS																	\
		CP_VDU_CODEC_FIELDS																		\



/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_qt_svg_codec_s {
	CP_QT_SVG_CODEC_FIELDS											/*表示codec模块信息*/
	cp_qt_svg_process_t						*svg_process;			/*表示svg process内容*/
};


#pragma pack()



cp_qt_svg_codec_t* create_qt_svg_codec(cp_module_register_t *register_info, cp_codec_manager_t *manager, cp_qt_svg_codec_info_t *info);
cp_int32_t destroy_qt_svg_codec(cp_codec_manager_t *manager, cp_qt_svg_codec_t* qt_svg_codec);

#endif


