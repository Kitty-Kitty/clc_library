/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-11-24

Description:

**************************************************************************/

#ifndef _CP_VDU_MODULE_TYPE_INCLUDE_H_
#define _CP_VDU_MODULE_TYPE_INCLUDE_H_


#include "cp_include.h"


enum cp_vdu_manager_type_enum
{
	/////////////////////////音视频处理相关内容/////////////////////////////////////////////////
	cp_vdu_manager_type_func = CP_MODULE_MANAGER_TYPE_FUNC(1),
	//////////////////////////////////////////////////////////////////////////
	cp_vdu_manager_type_codec = CP_MODULE_MANAGER_TYPE_CODEC(1),
	cp_vdu_manager_type_dev = CP_MODULE_MANAGER_TYPE_DEV(1),
};



enum cp_vdu_module_type_enum
{
	cp_vdu_module_type_func = CP_MODULE_TYPE_FUNC(1),
	cp_vdu_module_type_codec = CP_MODULE_TYPE_CODEC(1),
	cp_vdu_module_type_hi3536_codec = CP_MODULE_TYPE_CODEC(2),
	cp_vdu_module_type_qt_svg_codec = CP_MODULE_TYPE_CODEC(3),
	cp_vdu_module_type_hi3536_dev = CP_MODULE_TYPE_DEV(1),
};



#endif