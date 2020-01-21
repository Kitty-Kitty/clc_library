/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/


#ifndef	_CP_QT_SVG_OPTION_INCLUDE_H_
#define _CP_QT_SVG_OPTION_INCLUDE_H_




#include "cp_bit.h"
#include "cp_module_option.h"




typedef enum cp_qt_svg_option_enum		cp_qt_svg_option_e;



/************************************************************************/
/* 定义module的设置属性                                                  */
/************************************************************************/
enum cp_qt_svg_option_enum
{
	cp_qt_svg_set_option_addr			= CP_MODULE_OPTION_SET_FLAG(B8(00000001)),
	cp_qt_svg_set_option_read_timeout	= CP_MODULE_OPTION_SET_FLAG(B16(00000000, 00000010)),
	cp_qt_svg_set_option_write_timeout	= CP_MODULE_OPTION_SET_FLAG(B16(00000000, 00000100)),
	cp_qt_svg_set_option_write_sync		= CP_MODULE_OPTION_SET_FLAG(B16(00000000, 00001000)),

	cp_qt_svg_set_option_membership		= CP_MODULE_OPTION_SET_FLAG(B16(10000000, 00000000)),

	cp_qt_svg_get_option_is_writable	= CP_MODULE_OPTION_GET_FLAG(B16(00000001, 00000000)),
	cp_qt_svg_get_option_is_readable	= CP_MODULE_OPTION_GET_FLAG(B16(00000010, 00000000)),
};



#endif





