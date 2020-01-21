/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-23

Description:css_player main include file

**************************************************************************/


#ifndef _CP_MODULE_REGISTER_FUNCTION_INCLUDE_H_
#define _CP_MODULE_REGISTER_FUNCTION_INCLUDE_H_


#include <stdio.h>
#include <stdlib.h>


#include "cp_module_core.h"



typedef cp_int32_t(*module_register_handle)(cp_module_register_t *register_info, cp_module_manager_t *manager);									/*��ģ��ע�ᵽģ���������*/
typedef cp_int32_t(*module_unregister_handle)(cp_module_register_t *register_info, cp_module_manager_t *manager);								/*��ģ���ģ���������ȡ��ע��*/
typedef cp_int32_t(*module_register_set_option_handle)(cp_module_register_t *register_info, cp_int32_t optname, const cp_void_t* optval);		/*����ģ��ע����Ϣ*/
typedef cp_int32_t(*module_register_get_option_handle)(cp_module_register_t *register_info, cp_int32_t optname, cp_void_t* optval);				/*��ȡģ��ע����Ϣ*/






cp_extern cp_int32_t cp_module_register(cp_module_register_t *register_info, cp_module_manager_t *manager);												/*��ģ��ע�ᵽģ���������*/
cp_extern cp_int32_t cp_module_unregister(cp_module_register_t *register_info, cp_module_manager_t *manager);												/*��ģ���ģ���������ȡ��ע��*/
cp_extern cp_int32_t cp_module_register_set_option(cp_module_register_t *register_info, cp_int32_t optname, const cp_void_t* optval);						/*����ģ��ע����Ϣ*/
cp_extern cp_int32_t cp_module_register_get_option(cp_module_register_t *register_info, cp_int32_t optname, cp_void_t* optval);							/*��ȡģ��ע����Ϣ*/







/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: _manager_create_register_memory
*
* ����˵��: ��Ҫ��ʼ������ģ��Ĺ��������ݿռ��С
*
* ��    ��: cp_module_manager_t * manager						[in]����˵��
* ��    ��: cp_int32_t manager_register_size						[in]����˵��
* ��    ��: cp_int32_t manager_size						[in]����˵��
* ��    ��: cp_int32_t module_register_size						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-08-15 14:30:20
******************************************************************************************************/
cp_extern 
cp_int32_t _manager_create_register_memory(cp_module_manager_t *manager, cp_int32_t manager_register_size,
	cp_int32_t manager_size, cp_int32_t module_register_size);

#define cp_manager_create_register_memory(manager,	manager_register_size, manager_size, module_register_size)				\
	_manager_create_register_memory((cp_module_manager_t *)(manager), manager_register_size, manager_size, module_register_size);


/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: _manager_set_module_register
*
* ����˵��: Ϊģ����������ģ���ע����Ϣ
*
* ��    ��: cp_module_manager_t * manager							[in]��ʾ��Ҫ����ӵ�ģ�������
* ��    ��: cp_module_register_t * module_register_list				[in]��ʾ��Ҫ��ӵ�ģ��ע����
* ��    ��: cp_int32_t module_register_list_size						[in]��ʾ��Ҫ��ӵ�ģ��ע��������
* ��    ��: cp_int32_t size											[in]��ʾÿ��ģ��ע�����Ĵ�С
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-08-09 17:48:23
******************************************************************************************************/
cp_extern 
cp_int32_t _manager_set_module_register(cp_module_manager_t *manager,
	cp_module_register_t *module_register_list, cp_int32_t module_register_list_size, cp_int32_t size);

#define cp_manager_set_module_register(manager,	module_register_list, module_register_list_size, size)			\
	_manager_set_module_register((cp_module_manager_t *)(manager),												\
		(cp_module_register_t *)(module_register_list), (module_register_list_size), (size));


/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: _manager_get_module_register
*
* ����˵��: ��ȡģ��ע������Ϣ
*
* ��    ��: cp_module_manager_t * manager						[in]����˵��
* ��    ��: cp_int32_t type						[in]����˵��
*
* �� �� ֵ: cp_module_register_t*
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-08-15 18:20:37
******************************************************************************************************/
cp_extern 
cp_module_register_t* _manager_get_module_register(cp_module_manager_t *manager, cp_int32_t type);

#define  cp_manager_get_module_register(manager, type)	_manager_get_module_register((cp_module_manager_t *)(manager), (type))

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: _manager_set_sub_manager_register
*
* ����˵��: Ϊģ�������ӹ���ģ���ע����Ϣ
*
* ��    ��: cp_module_manager_t * manager								[in]��Ҫ������˸�ģ���ַ��Ϣ
* ��    ��: cp_module_manager_register_t * manager_register_list			[in]��ʾ��Ҫ��ӵ�ע��������
* ��    ��: cp_int32_t manager_register_list_size						[in]��ʾ��Ҫ��ӵ������С
* ��    ��: cp_int32_t size												[in]��ʾ����ע�����Ĵ�С
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-08-16 15:32:06
******************************************************************************************************/
cp_extern 
cp_int32_t _manager_set_sub_manager_register(cp_module_manager_t *manager,
	cp_module_manager_register_t *manager_register_list, cp_int32_t manager_register_list_size, cp_uint32_t size);


#define cp_manager_set_sub_manager_register(manager, manager_register_list, manager_register_list_size, size)	\
	_manager_set_sub_manager_register((cp_module_manager_t *)(manager),											\
		(cp_module_manager_register_t *)(manager_register_list), (manager_register_list_size), (size));


/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: _manager_get_sub_manager_register
*
* ����˵��: ��ȡģ�����ģ���������Ϣ
*
* ��    ��: cp_module_manager_t * manager						[in]����˵��
* ��    ��: cp_int32_t type										[in]����˵��
*
* �� �� ֵ: cp_module_manager_register_t*
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-08-15 18:21:44
******************************************************************************************************/
cp_extern 
cp_module_manager_register_t* _manager_get_sub_manager_register(cp_module_manager_t *manager, cp_int32_t type);

#define cp_manager_get_sub_manager_register(manager, type) _manager_get_sub_manager_register((cp_module_manager_t *)(manager), (type))




/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: _manager_set_root_manager_register
*
* ����˵��: ����һ����ģ�������ע������Ϣ
*
* ��    ��: cp_app_t * app													[in]��Ҫ�����Ӧ�ó����ַ
* ��    ��: cp_module_manager_register_t * module_manager_register			[in]��Ҫ����ӵĹ�����ע����
* ��    ��: cp_int32_t size													[in]��ʾע�����Ĵ�С
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-08-16 15:34:04
******************************************************************************************************/
cp_extern
cp_int32_t _manager_set_root_manager_register(cp_app_t *app, cp_module_manager_register_t *module_manager_register, cp_uint32_t size);

#define cp_manager_set_root_manager_register(app, module_manager_register, size)												\
		_manager_set_root_manager_register((app), (cp_module_manager_register_t*)(module_manager_register), (size))

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: _manager_get_root_manager_register
*
* ����˵��: ��ȡ��������ע����
*
* ��    ��: cp_app_t * app						[in]����˵��
* ��    ��: cp_int32_t type						[in]����˵��
*
* �� �� ֵ: cp_module_manager_register_t*
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-08-16 11:30:42
******************************************************************************************************/
cp_extern
cp_module_manager_register_t* _manager_get_root_manager_register(cp_app_t *app, cp_int32_t type);

#define cp_manager_get_root_manager_register(app, type)		_manager_get_root_manager_register((cp_app_t *)(app), type)


#endif


