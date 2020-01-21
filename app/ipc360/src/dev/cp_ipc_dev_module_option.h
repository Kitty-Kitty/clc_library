/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-08

Description:

**************************************************************************/

#ifndef _CP_IPC_DEV_MODULE_OPTION_INCLUDE_H_
#define _CP_IPC_DEV_MODULE_OPTION_INCLUDE_H_


#include "cp_module_option.h"
#include "cp_bit.h"




typedef enum cp_ipc_dev_option_enum		cp_ipc_dev_option_e;



/************************************************************************/
/* 定义module的设置属性                                                  */
/************************************************************************/
enum cp_ipc_dev_option_enum
{
	cp_ipc_dev_set_option_media_info			= CP_MODULE_OPTION_MAKE_SET_FLAG(B16(00000001, 00000000)),
	cp_ipc_dev_set_option_audio_buffer_size	= CP_MODULE_OPTION_MAKE_SET_FLAG(B16(00000000, 10000000)),

	cp_ipc_dev_get_option_media_info			= CP_MODULE_OPTION_MAKE_GET_FLAG(B16(00000001, 00000000)),
};

#endif
