/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-05-26

Description: define module information

**************************************************************************/


#ifndef	_CP_MODULE_TYPE_INCLUDE_H_
#define _CP_MODULE_TYPE_INCLUDE_H_



#include "cp_bit.h"




/************************************************************************/
/* �����cp_module_type.h �����͵Ķ���                           */
/************************************************************************/
#define CP_LIBRARY_MODULE_TYPE				B32(00010000, 00000000, 00000000, 00000000)




//typedef enum cp_module_type_enum			cp_module_type_e;




typedef enum cp_module_type_enum
{
	cp_module_type_begin	= CP_LIBRARY_MODULE_TYPE,

	/*�ò��ֶ������ģ������*/
	cp_module_type_pool		= CP_LIBRARY_MODULE_TYPE | (B8(00000001) << 16),
	cp_module_type_timer	= CP_LIBRARY_MODULE_TYPE | (B8(00000010) << 16),
	cp_module_type_thread	= CP_LIBRARY_MODULE_TYPE | (B8(00000011) << 16),

	/*�ò��ֶ�����չģ������*/
	//��ģ�����Ͳ����...
	cp_module_type_hook		= CP_LIBRARY_MODULE_TYPE | (B8(00000100) << 16),
	cp_module_type_session	= CP_LIBRARY_MODULE_TYPE | (B8(00000101) << 16),
	cp_module_type_process	= CP_LIBRARY_MODULE_TYPE | (B8(00000110) << 16),
	cp_module_type_filter	= CP_LIBRARY_MODULE_TYPE | (B8(00000111) << 16),
	cp_module_type_func		= CP_LIBRARY_MODULE_TYPE | (B8(00001000) << 16),
	cp_module_type_socket	= CP_LIBRARY_MODULE_TYPE | (B8(00001001) << 16),
	cp_module_type_codec	= CP_LIBRARY_MODULE_TYPE | (B8(00001010) << 16),
	cp_module_type_dev		= CP_LIBRARY_MODULE_TYPE | (B8(00001011) << 16),
	cp_module_type_extend	= CP_LIBRARY_MODULE_TYPE | (B8(00001100) << 16),

	/*�ò��ֶ�����չģ������*/
	//��ģ�����Ͳ����...

	//�벻Ҫ��end��������
	cp_module_type_end = CP_LIBRARY_MODULE_TYPE | (B8(00001011) << 16)
}cp_module_type_e;




/************************************************************************/
/* ��Ӹ���ģ�����͵Ķ���                                                */
/************************************************************************/
#define CP_MODULE_TYPE_POOL(n)			(cp_module_type_pool + n)
#define CP_MODULE_TYPE_TIMER(n)			(cp_module_type_timer + n)
#define CP_MODULE_TYPE_THREAD(n)		(cp_module_type_thread + n)
#define CP_MODULE_TYPE_HOOK(n)			(cp_module_type_hook + n)
#define CP_MODULE_TYPE_SESSION(n)		(cp_module_type_session + n)
#define CP_MODULE_TYPE_PROCESS(n)		(cp_module_type_process + n)
#define CP_MODULE_TYPE_FILTER(n)		(cp_module_type_filter + n)
#define CP_MODULE_TYPE_FUNC(n)			(cp_module_type_func + n)
#define CP_MODULE_TYPE_SOCKET(n)		(cp_module_type_socket + n)
#define CP_MODULE_TYPE_CODEC(n)			(cp_module_type_codec + n)
#define CP_MODULE_TYPE_DEV(n)			(cp_module_type_dev + n)
#define CP_MODULE_TYPE_EXTEND(n)		(cp_module_type_extend + n)

#endif


