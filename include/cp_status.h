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
/* ����������                                                          */
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
/* �������˵������                                                      */
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
* ��Ȩ����: fz & novigo
*
* ��������: cp_strstatus
*
* ����ȫ��: cp_strstatus
*
* ��������: public 
*
* ����˵��: ��ȡ״̬���Ӧ���ַ�����
*
* ��    ��: cp_status_e						[in/out]����˵��
*
* �� �� ֵ: const char*
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2018-2-5 17:08:10
********************************************************************************/
const char* cp_strstatus(cp_status_e status);


#ifdef __cplusplus
}
#endif


#endif //_CP_STATUS_H_

