
/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-23

Description:css_player main include file 

**************************************************************************/


#ifndef _CP_MODULE_MANAGER_FUNCTION_INCLUDE_H_
#define _CP_MODULE_MANAGER_FUNCTION_INCLUDE_H_


#include <stdio.h>
#include <stdlib.h>




#include "cp_core.h"
#include "cp_module_core.h"



/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: print_manager_register_info_f
*
* ����˵��: ��ӡע����Ϣ����
*
* ��    ��: cp_module_manager_register_t * manager_register		[in]��Ҫ����ӡ��ע����Ϣ
* ��    ��: cp_char_t * buf										[in]���ݻ���
* ��    ��: cp_int32_t len										[in]���泤��
*
* �� �� ֵ: cp_char_t *
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-06-23 10:00:46
******************************************************************************************************/
cp_extern cp_char_t *print_manager_register_info_f(cp_module_manager_register_t *manager_register, cp_char_t *buf, cp_int32_t len);



/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: _malloc_module_manager
*
* ����˵��: ����ģ����ڴ�ռ�
*
* ��    ��: cp_app_t *app						[in]����˵��
* ��    ��: cp_int32_t manager_mem_size						[in]����˵��
* ��    ��: cp_module_info_t * info						[in]����˵��
*
* �� �� ֵ: cp_extern cp_module_t *
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-03-26 14:04:55
******************************************************************************************************/
cp_extern cp_module_manager_t* _malloc_module_manager(cp_app_t *app, cp_int32_t manager_mem_size, cp_module_info_t *info);

#define cp_malloc_module_manager(app, type, pool_info)								\
		(type *)_malloc_module_manager((cp_app_t *)app, cp_sizeof(type), (cp_module_info_t*) pool_info)



/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: _free_module
*
* ����˵��: �ͷ�ģ����ڴ�
*
* ��    ��: cp_module_manager_t *manager						[in]����˵��
*
* �� �� ֵ: cp_extern cp_int32_t
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-03-26 14:07:54
******************************************************************************************************/
cp_extern cp_int32_t _free_module_manager(cp_module_manager_t *manager);

#define cp_free_module_module(manager)												\
		_free_module_manager((cp_module_manager_t *)manager)



#define cp_print_manager_register_info(manager_register, buf, len)					\
		print_manager_register_info_f((cp_module_manager_register_t *) (manager_register), (cp_char_t *) (buf), (cp_int32_t) (len))


/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: create_manager_f
*
* ����˵��: ����һ��ģ��
*
* ��    ��: cp_module_manager_register_t * register_info						[in]����˵��
* ��    ��: cp_app_t * app						[in]����˵��
* ��    ��: cp_module_manager_info_t * info						[in]����˵��
*
* �� �� ֵ: cp_module_manager_t*
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-06-23 15:45:43
******************************************************************************************************/
cp_extern cp_module_manager_t* _create_manager(cp_module_manager_register_t *register_info, cp_app_t *app, cp_module_manager_info_t *info);

#define cp_create_manager(register_info, app, info)			\
		_create_manager((cp_module_manager_register_t *) (register_info), (cp_app_t *) (app), (cp_module_manager_info_t *) (info))


/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: destroy_manager_f
*
* ����˵��: ����ָ��ģ��
*
* ��    ��: cp_app_t * app						[in]����˵��
* ��    ��: cp_module_manager_t * manager						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-06-23 15:56:14
******************************************************************************************************/
cp_extern cp_int32_t _destroy_manager(cp_app_t *app, cp_module_manager_t *manager);

#define cp_destroy_manager(app, manager)					\
		_destroy_manager((cp_app_t *) (app), (cp_module_manager_t *) (manager))


/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: init_manager_f
*
* ����˵��: ģ�鴴���ӿڣ���ʾ����һ��ģ��
*
* ��    ��: cp_module_manager_t * manager								[in]����˵��
* ��    ��: const cp_module_manager_info_t * info						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-06-23 15:42:06
******************************************************************************************************/
cp_extern cp_int32_t _init_manager(cp_module_manager_t *manager, const cp_module_manager_info_t *info);

#define cp_init_manager(manager, info)						\
		_init_manager((cp_module_manager_t *) (manager), (cp_module_manager_info_t *) (info))


/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: start_manager_f
*
* ����˵��: ģ������нӿڣ���ģ��init֮�󣬻ᱻ����
*
* ��    ��: cp_module_manager_t * manager						[in]����˵��
* ��    ��: const cp_module_manager_info_t * info						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-06-23 15:42:25
******************************************************************************************************/
cp_extern cp_int32_t _start_manager(cp_module_manager_t *manager, const cp_module_manager_info_t *info);

#define cp_start_manager(manager, info)						\
		_start_manager((cp_module_manager_t *) (manager), (cp_module_manager_info_t *) (info))


/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: stop_manager_f
*
* ����˵��: ��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��
*
* ��    ��: cp_module_manager_t * manager						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-06-23 15:42:38
******************************************************************************************************/
cp_extern cp_int32_t _stop_manager(cp_module_manager_t *manager);

#define cp_stop_manager(manager) _stop_manager((cp_module_manager_t *) (manager))


/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: ctrl_manager_f
*
* ����˵��: ����ģ�����
*
* ��    ��: cp_module_manager_t * manager						[in]����˵��
* ��    ��: cp_int32_t optname						[in]����˵��
* ��    ��: const cp_void_t * optval						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-06-23 15:42:51
******************************************************************************************************/
cp_extern cp_int32_t _ctrl_manager(cp_module_manager_t *manager, cp_int32_t optname, const cp_void_t* optval);

#define cp_ctrl_manager(manager, optname, optval)			\
		_ctrl_manager((cp_module_manager_t *) (manager), (cp_int32_t) (optname), (cp_void_t*) (optval))


/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: get_manager_f
*
* ����˵��: ��ȡ��������Ϣ
*
* ��    ��: cp_app_t *app						[in]����˵��
* ��    ��: const cp_module_manager_info_t * info						[in]����˵��
*
* �� �� ֵ: cp_module_manager_t*
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-06-23 15:42:51
******************************************************************************************************/
cp_extern cp_module_manager_t* _get_manager(const cp_app_t *app, const cp_module_manager_info_t *info);

#define cp_get_manager(app, info) _get_manager((const cp_app_t *) (app), (cp_module_manager_info_t *) (info))


/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: manager_create_module_f
*
* ����˵��: ģ�鴴���ӿڣ���ʾ����һ��ģ��
*
* ��    ��: cp_module_manager_t * manager						[in]����˵��
* ��    ��: const cp_module_info_t * info						[in]����˵��
*
* �� �� ֵ: cp_module_t*
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-06-23 15:43:01
******************************************************************************************************/
cp_extern cp_module_t* _manager_create_module(cp_module_manager_t *manager, const cp_module_info_t *info);

#define cp_manager_create_module(manager, info)				\
		_manager_create_module((cp_module_manager_t *) (manager), (cp_module_info_t *) (info))


/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: _manager_create_module_by_register
*
* ����˵��: ͨ��ģ�鴴���ӿڣ�����ģ��ע����Ϣ����һ��ģ��
*
* ��    ��: cp_module_manager_t * manager						[in]����˵��
* ��    ��: const cp_module_info_t * info						[in]����˵��
*
* �� �� ֵ: cp_extern cp_module_t*
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-04-23 15:24:08
******************************************************************************************************/
cp_extern cp_module_t* _manager_create_module_by_register(cp_module_manager_t *manager, const cp_module_info_t *info);

#define cp_manager_create_module_by_register(manager, info)	\
		_manager_create_module_by_register((cp_module_manager_t *) (manager), (cp_module_info_t *) (info))


/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: _manager_create_module_by_type
*
* ����ȫ��: _manager_create_module_by_type
*
* ��������: public 
*
* ����˵��: ͨ��ģ�鴴���ӿڣ�����ģ��type����һ��ģ��
*
* ��    ��: cp_module_manager_t * manager						[in/out]����˵��
* ��    ��: cp_int32_t type						[in/out]����˵��
*
* �� �� ֵ: cp_extern cp_module_t*
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-8-21 12:04:17
********************************************************************************/
cp_extern cp_module_t* _manager_create_module_by_type(cp_module_manager_t *manager, cp_int32_t type);

#define cp_manager_create_module_by_type(manager, type)	\
		_manager_create_module_by_type((cp_module_manager_t *) (manager), (type))


/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: manager_get_module_f
*
* ����˵��: ��ѯһ��ģ��
*
* ��    ��: cp_module_manager_t * manager						[in]����˵��
* ��    ��: const cp_module_info_t * info						[in]����˵��
*
* �� �� ֵ: cp_module_t*
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-07-01 17:02:11
******************************************************************************************************/
cp_extern cp_module_t* _manager_get_module(cp_module_manager_t *manager, const cp_module_info_t *info);

#define cp_manager_get_module(manager, info)				\
		_manager_get_module((cp_module_manager_t *) (manager), (cp_module_info_t *) (info))


/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: manager_register_module_f
*
* ����˵��: дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��
*
* ��    ��: cp_module_manager_t * manager						[in]����˵��
* ��    ��: cp_module_t * module						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-06-23 15:43:12
******************************************************************************************************/
cp_extern cp_int32_t _manager_register_module(cp_module_manager_t *manager, cp_module_t *module);

#define cp_manager_register_module(manager, module)			\
		_manager_register_module((cp_module_manager_t *) (manager), (cp_module_t *) (module))


/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: manager_cancel_module_f
*
* ����˵��: �ر�ģ��
*
* ��    ��: cp_module_manager_t * manager						[in]����˵��
* ��    ��: cp_module_t * module						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-06-23 15:43:24
******************************************************************************************************/
cp_extern cp_int32_t _manager_cancel_module(cp_module_manager_t *manager, cp_module_t *module);

#define cp_manager_cancel_module(manager, module)			\
		_manager_cancel_module((cp_module_manager_t *) (manager), (cp_module_t *) (module))


/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: manager_destroy_module_f
*
* ����˵��: �˳�ģ��
*
* ��    ��: cp_module_manager_t * manager						[in]����˵��
* ��    ��: cp_module_t * module						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-06-23 15:43:40
******************************************************************************************************/
cp_extern cp_int32_t _manager_destroy_module(cp_module_manager_t *manager, cp_module_t *module);

#define cp_manager_destroy_module(manager, module)			\
		_manager_destroy_module((cp_module_manager_t *) (manager), (cp_module_t *) (module))


/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: _manager_destroy_all_module
*
* ����ȫ��: _manager_destroy_all_module
*
* ��������: public 
*
* ����˵��: ��ʾ���ٸù������������Ѿ�������ģ��
*
* ��    ��: cp_module_manager_t * manager						[in/out]����˵��
*
* �� �� ֵ: cp_extern cp_int32_t
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2018-2-9 16:32:39
********************************************************************************/
cp_extern cp_int32_t _manager_destroy_all_module(cp_module_manager_t *manager);

#define cp_manager_destroy_all_module(manager)				\
		_manager_destroy_all_module((cp_module_manager_t *) (manager))



/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: manager_ctrl_module_f
*
* ����˵��: ����ģ�����
*
* ��    ��: cp_module_manager_t * manager						[in]����˵��
* ��    ��: cp_module_t * module						[in]����˵��
* ��    ��: cp_int32_t optname						[in]����˵��
* ��    ��: const cp_void_t * optval						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-06-23 15:43:51
******************************************************************************************************/
cp_extern cp_int32_t _manager_ctrl_module(cp_module_manager_t *manager, cp_module_t *module,
	cp_int32_t optname, const cp_void_t* optval);

#define cp_manager_ctrl_module(manager, module, optname, optval)						\
		_manager_ctrl_module((cp_module_manager_t *) (manager), (cp_module_t *) module,	\
			(cp_int32_t) (optname), (cp_void_t*) (optval))









//////////////////////////////////////////////////////////////////////////
/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: _manager_get_root_manager
*
* ����˵��: ��ʾ��ȡ��������ע����Ϣ
*
* ��    ��: cp_app_t * app						[in]����˵��
* ��    ��: cp_int32_t type						[in]����˵��
*
* �� �� ֵ: cp_module_manager_t*
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-08-16 10:20:17
******************************************************************************************************/
cp_extern cp_module_manager_t* _manager_get_root_manager(cp_app_t *app, cp_int32_t type);

#define cp_manager_get_root_manager(app, type)							_manager_get_root_manager((cp_app_t *)(app), (type))


/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: _manager_set_root_manager
*
* ����˵��: ��ʾ�豸��������ע����Ϣ
*
* ��    ��: cp_app_t * app						[in]����˵��
* ��    ��: cp_int32_t type						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-08-16 11:22:16
******************************************************************************************************/
cp_extern cp_int32_t _manager_set_root_manager(cp_app_t *app, cp_int32_t type);

#define cp_manager_set_root_manager(app, type)							_manager_set_root_manager((cp_app_t *)(app), (type))

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: _manager_get_sub_manager
*
* ����˵��: ��ʾ��ȡ�ӹ�����ע����Ϣ
*
* ��    ��: cp_module_manager_t	*root_manager						[in]����˵��
* ��    ��: cp_int32_t type											[in]����˵��
*
* �� �� ֵ: cp_module_manager_t*
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-08-16 10:20:17
******************************************************************************************************/
cp_extern cp_module_manager_t* _manager_get_sub_manager(cp_module_manager_t *root_manager, cp_int32_t type);

#define cp_manager_get_sub_manager(root_manager, type)					_manager_get_sub_manager((cp_module_manager_t *)(root_manager), (type))


/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: _manager_get_sub_module
*
* ����˵��: ��ȡָ�������µ�ģ��
*
* ��    ��: cp_app_t * app						[in]����˵��
* ��    ��: cp_int32_t manager_type						[in]����˵��
* ��    ��: cp_int32_t module_type						[in]����˵��
*
* �� �� ֵ: cp_module_t*
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-11-25 15:37:27
******************************************************************************************************/
cp_extern cp_module_t* _manager_get_sub_module(cp_app_t *app, cp_int32_t manager_type, cp_int32_t module_type);

#define cp_manager_get_sub_module(app, manager_type, module_type)		_manager_get_sub_module((cp_app_t *)(app), (manager_type), (module_type))





//////////////////////////////////////////////////////////////////////////
 /******************************************************************************************************
 * ��Ȩ����: fz & novigo
 *
 * ��������: _manager_create_all_sub_manager
 *
 * ����˵��: ������ģ�������
 *
 * ��    ��: cp_module_manager_t * root_manager						[in]����˵��
 *
 * �� �� ֵ: cp_int32_t
 *           0  : �ɹ�
 *         �� 0  :ʧ��
 *
 * ��    ע:����˵������
 *
 * ��    �ߣ�fz
 * �������䣺 fangzhenmu@novigo.com.cn
 * �������ڣ�2017-05-09 22:05:00
 ******************************************************************************************************/
cp_extern  cp_int32_t _manager_create_all_sub_manager(cp_module_manager_t *root_manager);

#define cp_manager_create_all_sub_manager(root_manager)					_manager_create_all_sub_manager((cp_module_manager_t *)(root_manager))


/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: _manager_create_all_sub_manager
*
* ����˵��: ������ģ�������
*
* ��    ��: cp_module_manager_t * root_manager						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-05-09 22:05:00
******************************************************************************************************/
cp_extern  cp_int32_t _manager_destroy_all_sub_manager(cp_module_manager_t *root_manager);

#define cp_manager_destroy_all_sub_manager(root_manager)					_manager_destroy_all_sub_manager((cp_module_manager_t *)(root_manager))



/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: _manager_create_all_sub_manager
*
* ����˵��: ��ʼ����ģ�������
*
* ��    ��: cp_module_manager_t * root_manager						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-05-09 22:05:00
******************************************************************************************************/
cp_extern  cp_int32_t _manager_init_all_sub_manager(cp_module_manager_t *root_manager);

#define cp_manager_init_all_sub_manager(root_manager)					_manager_init_all_sub_manager((cp_module_manager_t *)(root_manager))


/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: _manager_create_all_sub_manager
*
* ����˵��: ������ģ�������
*
* ��    ��: cp_module_manager_t * root_manager						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-05-09 22:05:00
******************************************************************************************************/
cp_extern  cp_int32_t _manager_start_all_sub_manager(cp_module_manager_t *root_manager);

#define cp_manager_start_all_sub_manager(root_manager)					_manager_start_all_sub_manager((cp_module_manager_t *)(root_manager))


/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: _manager_create_all_sub_manager
*
* ����˵��: ֹͣ��ģ�������
*
* ��    ��: cp_module_manager_t * root_manager						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-05-09 22:05:00
******************************************************************************************************/
cp_extern  cp_int32_t _manager_stop_all_sub_manager(cp_module_manager_t *root_manager);

#define cp_manager_stop_all_sub_manager(root_manager)					_manager_stop_all_sub_manager((cp_module_manager_t *)(root_manager))


#endif




