/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-05-26

Description: define module

**************************************************************************/


#ifndef	_CP_CSS_HOOK_BLOCK_INCLUDE_H_
#define _CP_CSS_HOOK_BLOCK_INCLUDE_H_


#include "cp_css_hook_core.h"



typedef struct cp_css_hook_block_s			cp_css_hook_block_t;




/************************************************************************/
/* ģ��hook����Ϣ	                                                    */
/************************************************************************/
struct cp_css_hook_block_s
{
	cp_css_semh_hook_type_e		type;
	cp_css_hook_t				*hook;
	cp_queue_t					queue;
};






#endif


