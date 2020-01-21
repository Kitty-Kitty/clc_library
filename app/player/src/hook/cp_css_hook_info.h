/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/


#ifndef	_CP_CSS_HOOK_INFO_INCLUDE_H_
#define _CP_CSS_HOOK_INFO_INCLUDE_H_




#include "cp_css_hook_core.h"




//typedef	struct cp_css_hook_info_s			cp_css_hook_info_t;




#pragma pack(1)


#define CP_CSS_HOOK_INFO_FIELDS																					\
		CP_HOOK_INFO_FIELDS																						\
		cp_int32_t				command;			/*表示当前的指令编码*/										\



/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_css_hook_info_s {
	CP_CSS_HOOK_INFO_FIELDS
};


#pragma pack()



#endif





