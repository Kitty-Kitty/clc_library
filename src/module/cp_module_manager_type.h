/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-05-26

Description: define module information

**************************************************************************/


#ifndef	_CP_MODULE_MANAGER_TYPE_INCLUDE_H_
#define _CP_MODULE_MANAGER_TYPE_INCLUDE_H_



//����APP�����ͱ���
#define CP_LIBRARY_APP_TYPE							B32(01000000, 00000000, 00000000, 00000000)
//����ģ�����������
#define CP_LIBRARY_MODULE_MANAGER_TYPE				B32(00100000, 00000000, 00000000, 00000000)
//��ȡģ�������
#define CP_GET_LIBRARY_TYPE(type)					((type) & B32(11111111, 00000000, 00000000, 00000000))
//��ȡ��ģ�������
#define CP_GET_LIBRARY_MODULE_TYPE(type)			((type) & B32(11111111, 11111111, 00000000, 00000000))
//��ȡģ����ʵ������
#define CP_GET_LIBRARY_REAL_MODULE_TYPE(type)		(((type) & B32(00000000, 11111111, 00000000, 00000000)) >> 16)
//��ȡ��ģ����ʵ������
#define CP_GET_LIBRARY_SUB_MODULE_TYPE(type)		(((type) & B32(00000000, 00000000, 00000000, 11111111)))





//typedef enum cp_module_manager_type_enum			cp_module_manager_type_e;





/****************************************************************************************************************************************/
/* ������Ҫ����ģ������������ͣ�																											*/
/* 1����������ʹ�����˵��																												*/
/*		����B32(00000000, 00000000, 00000000, 00000000)��4�ֽڷֱ�ʹ��   																	*/
/*		����B32(xxxxxxxx, 00000000, 00000000, 00000000)��xxxxxxxxx��������ϵͳ��ģ�����ͣ�����APPģ�顢ģ���������ģ��						*/
/*		����B32(00000000, xxxxxxxx, 00000000, 00000000)��xxxxxxxxx��������ϵͳ��ģ���µ���ģ�����ͣ�����ģ��������µ�pool��timer				*/
/*		����B32(00000000, 00000000, xxxxxxxx, 00000000)��xxxxxxxxx����ΪԤ�����ݣ���ʱ��ʹ��												*/
/*		����B32(00000000, 00000000, 00000000, xxxxxxxx)��xxxxxxxxx����Ϊ��ģ���µ�����ʵ�֣�����memory_pool����pool;libuv_socket����socket	*/
/* 2����ģ������ȡֵ˵��																													*/
/*		��������ֵ��B32(01000000, 00000000, 00000000, 00000000)ָ��λ��ʹ��λ1��ʾAPPģ��   												*/
/*		��������ֵ��B32(00100000, 00000000, 00000000, 00000000)ָ��λ��ʹ��λ1��ʾģ�������												*/
/*		��������ֵ��B32(00010000, 00000000, 00000000, 00000000)ָ��λ��ʹ��λ1��ʾģ��														*/
/* 3��ģ���ϵͼ��																														*/
/*		3.1��ģ��Ĺ�ϵͼ��																												*/
/*			app->root_module_manager_register					����ģ�������ע������													*/
/*			app->root_module_manager_array						����ģ���������															*/
/*					|																													*/
/*					--->module_manager->module_manager_register				(��ģ��������µ���ģ�������ע����)							*/
/*					--->module_manager->module_managers						(��ģ��������µ���ģ�������)									*/
/*					--->module_manager->module_register						(��ģ��������µ���ģ��ע��������������ʱָ��)					*/
/*											|																							*/
/*											--->sub_module_manager->module_register		(��ģ��������µ���ģ��ע��������������ʱָ��)		*/
/*											--->sub_module_manager->modules				(��ģ��������µ���ģ��)							*/
/****************************************************************************************************************************************/

typedef enum cp_module_manager_type_enum
{
	/*�ò��ֶ������ģ������*/
	cp_module_manager_type_begin	= CP_LIBRARY_MODULE_MANAGER_TYPE,
	cp_module_manager_type_pool		= CP_LIBRARY_MODULE_MANAGER_TYPE | (B8(00000001) << 16),
	cp_module_manager_type_timer	= CP_LIBRARY_MODULE_MANAGER_TYPE | (B8(00000010) << 16),
	cp_module_manager_type_thread	= CP_LIBRARY_MODULE_MANAGER_TYPE | (B8(00000011) << 16),

	/*�ò��ֶ�����չģ������*/
	//��ģ�����Ͳ����...
	cp_module_manager_type_hook		= CP_LIBRARY_MODULE_MANAGER_TYPE | (B8(00000100) << 16),
	cp_module_manager_type_session	= CP_LIBRARY_MODULE_MANAGER_TYPE | (B8(00000101) << 16),
	cp_module_manager_type_process	= CP_LIBRARY_MODULE_MANAGER_TYPE | (B8(00000110) << 16),
	cp_module_manager_type_filter	= CP_LIBRARY_MODULE_MANAGER_TYPE | (B8(00000111) << 16),
	cp_module_manager_type_func		= CP_LIBRARY_MODULE_MANAGER_TYPE | (B8(00001000) << 16),
	cp_module_manager_type_socket	= CP_LIBRARY_MODULE_MANAGER_TYPE | (B8(00001001) << 16),
	cp_module_manager_type_codec	= CP_LIBRARY_MODULE_MANAGER_TYPE | (B8(00001010) << 16),
	cp_module_manager_type_dev		= CP_LIBRARY_MODULE_MANAGER_TYPE | (B8(00001011) << 16),


	cp_module_manager_type_extend	= CP_LIBRARY_MODULE_MANAGER_TYPE | (B8(00001100) << 16),
	//�벻Ҫ��end��������
	cp_module_manager_type_end		= CP_LIBRARY_MODULE_MANAGER_TYPE | (B8(00010000) << 16)
}cp_module_manager_type_e;



/************************************************************************/
/* ��Ӹ���ģ�����͵Ķ���                                                */
/************************************************************************/
#define CP_MODULE_MANAGER_TYPE_POOL(n)			(cp_module_manager_type_pool + n)
#define CP_MODULE_MANAGER_TYPE_TIMER(n)			(cp_module_manager_type_timer + n)
#define CP_MODULE_MANAGER_TYPE_THREAD(n)		(cp_module_manager_type_thread + n)
#define CP_MODULE_MANAGER_TYPE_HOOK(n)			(cp_module_manager_type_hook + n)
#define CP_MODULE_MANAGER_TYPE_SESSION(n)		(cp_module_manager_type_session + n)
#define CP_MODULE_MANAGER_TYPE_PROCESS(n)		(cp_module_manager_type_process + n)
#define CP_MODULE_MANAGER_TYPE_FILTER(n)		(cp_module_manager_type_filter + n)
#define CP_MODULE_MANAGER_TYPE_FUNC(n)			(cp_module_manager_type_func + n)
#define CP_MODULE_MANAGER_TYPE_SOCKET(n)		(cp_module_manager_type_socket + n)
#define CP_MODULE_MANAGER_TYPE_CODEC(n)			(cp_module_manager_type_codec + n)
#define CP_MODULE_MANAGER_TYPE_DEV(n)			(cp_module_manager_type_dev + n)
#define CP_MODULE_MANAGER_TYPE_EXTEND(n)		(cp_module_manager_type_extend + n)


#endif


