/*******************************************************************************
*
*Copyright:novigo
*
*File name: cp_vdu_error.h
*
*Author:fangzhenmu@novigo.com.cn
*
*Version: 1.0
*
*Date:2018/01/26
*
*Description: create (cp_vdu_error.h)
*
*Others:
*
*History:
*******************************************************************************/

#ifndef _CP_STATUS_H_
#define _CP_STATUS_H_



#include "cp_std.h"


#ifdef __cplusplus
extern "C" {
#endif





//typedef	enum cp_status_enum									cp_status_e;
//typedef	enum cp_status_name_enum							cp_status_name_e;



/************************************************************************/
/* 定义错误编码                                                          */
/************************************************************************/
typedef	enum cp_status_enum
{
	cp_status_success = 0x000000,
	cp_status_failed = cp_std_negative_value(0x0F0000),
	cp_status_null_pointer,
	cp_status_invalid_parametes,
	cp_status_system_error,
	cp_status_module_not_ready,
	cp_status_unsupport_pixel_format,
	cp_status_not_more_buffer,
	cp_status_channel_index_existed,
	cp_status_create_source_failed,
	cp_status_operation_option_failed,
}cp_status_e;





/* Expand this list if necessary. */
/************************************************************************/
/* 定义错误说明内容                                                      */
/************************************************************************/
#define CP_STATUS_NAME_MAP(CP_STATUS)												\
	CP_STATUS(null_pointer, "null pointer error")										\
	CP_STATUS(invalid_parametes, "invalid parametes")									\
	CP_STATUS(system_error, "system error")												\
	CP_STATUS(module_not_ready, "library module not ready")								\
	CP_STATUS(unsupport_pixel_format, "system unsupport pixel format")					\
	CP_STATUS(not_more_buffer, "input not more process buffer")							\
	CP_STATUS(channel_index_existed, "this index of channel existed")					\
	CP_STATUS(create_source_failed, "create source failed")								\




typedef	enum cp_status_name_enum {
#define CP_STATUS(type, _) cp_status_name_ ## type = cp_status_ ## type,
	CP_STATUS_NAME_MAP(CP_STATUS)
#undef CP_STATUS
}cp_status_name_e;



/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: cp_strstatus
*
* 函数全名: cp_strstatus
*
* 函数访问: public 
*
* 函数说明: 获取状态码对应的字符描述
*
* 参    数: cp_status_e						[in/out]参数说明
*
* 返 回 值: const char*
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2018-2-5 17:08:10
********************************************************************************/
const char* cp_strstatus(cp_status_e status);


#ifdef __cplusplus
}
#endif


#endif //_CP_STATUS_H_

