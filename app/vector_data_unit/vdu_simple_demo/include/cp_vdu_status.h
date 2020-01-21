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

#ifndef _CP_VDU_STATUS_H_
#define _CP_VDU_STATUS_H_



#include "cp_vdu_std.h"


#ifdef __cplusplus
extern "C" {
#endif





//typedef	enum cp_vdu_status_enum									cp_vdu_status_e;
//typedef	enum cp_vdu_status_name_enum							cp_vdu_status_name_e;



/************************************************************************/
/* 系统错误状态码                                                          */
/************************************************************************/
typedef enum cp_vdu_status_enum
{
	cp_vdu_status_success = 0x000000,
	cp_vdu_status_failed = cp_vdu_negative_value(0x0F0000),
	cp_vdu_status_null_pointer,
	cp_vdu_status_invalid_parametes,
	cp_vdu_status_system_error,
	cp_vdu_status_module_not_ready,
	cp_vdu_status_unsupport_pixel_format,
	cp_vdu_status_not_more_buffer,
	cp_vdu_status_channel_index_existed,
	cp_vdu_status_create_source_failed,
	cp_vdu_status_operation_option_failed,
}cp_vdu_status_e;





/* Expand this list if necessary. */
/************************************************************************/
/* 系统错误描述信息                                                      */
/************************************************************************/
#define CP_VDU_STATUS_NAME_MAP(CP_VDU_STATUS)												\
	CP_VDU_STATUS(null_pointer, "null pointer error")										\
	CP_VDU_STATUS(invalid_parametes, "invalid parametes")									\
	CP_VDU_STATUS(system_error, "system error")												\
	CP_VDU_STATUS(module_not_ready, "library module not ready")								\
	CP_VDU_STATUS(unsupport_pixel_format, "system unsupport pixel format")					\
	CP_VDU_STATUS(not_more_buffer, "input not more process buffer")							\
	CP_VDU_STATUS(channel_index_existed, "this index of channel existed")					\
	CP_VDU_STATUS(create_source_failed, "create source failed")								\




typedef enum cp_vdu_status_name_enum {
#define CP_VDU_STATUS(type, _) cp_vdu_status_name_ ## type = cp_vdu_status_ ## type,
	CP_VDU_STATUS_NAME_MAP(CP_VDU_STATUS)
#undef CP_VDU_STATUS
}cp_vdu_status_name_e;


/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: cp_vdu_strstatus
*
* 函数全名: cp_vdu_strstatus
*
* 函数访问: public 
*
* 函数说明: 根据错误状态码获取错误信息
*
* 参    数: cp_vdu_status_e status						[in]错误状态码数值
*
* 返 回 值: const char*
*         非空  : 错误描述信息
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2018-2-28 18:43:54
********************************************************************************/
const char* cp_vdu_strstatus(cp_vdu_status_e status);


#ifdef __cplusplus
}
#endif


#endif //_CP_VDU_STATUS_H_

