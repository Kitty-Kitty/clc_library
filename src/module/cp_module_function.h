
/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-23

Description:css_player main include file 

**************************************************************************/


#ifndef _CP_MODULE_FUNCTION_INCLUDE_H_
#define cp__CP_MODULE_FUNCTION_INCLUDE_H_

#include <stdio.h>
#include <stdlib.h>




#include "cp_core.h"
#include "cp_module_core.h"



cp_extern cp_char_t *print_module_register_info(cp_module_register_t *module_register, cp_char_t *buf, cp_int32_t len);



/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: _malloc_module
*
* ����˵��: ����ģ����ڴ�ռ�
*
* ��    ��: cp_module_manager_t * manager						[in]����˵��
* ��    ��: cp_int32_t module_mem_size						[in]����˵��
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
cp_extern cp_module_t* _malloc_module(cp_module_manager_t *manager, cp_int32_t module_mem_size, cp_module_info_t *info);

#define cp_malloc_module(manager, type, pool_info)								\
		(type *)_malloc_module((cp_module_manager_t *)manager, cp_sizeof(type), (cp_module_info_t*) pool_info)



/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: _free_module
*
* ����˵��: �ͷ�ģ����ڴ�
*
* ��    ��: cp_module_t * module						[in]����˵��
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
cp_extern cp_int32_t _free_module(cp_module_t *module);

#define cp_free_module(module)			_free_module((cp_module_t *)module)


#define cp_print_module_register_info(module_register, buf, len)				\
		print_module_register_info((cp_module_register_t *) (module_register), (cp_char_t *) (buf), (cp_int32_t) (len))



/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: _create_module
*
* ����ȫ��: _create_module
*
* ��������: public 
*
* ����˵��: ����һ��ģ��
*
* ��    ��: cp_module_register_t * register_info					[in]ģ��ע����Ϣ
* ��    ��: cp_module_manager_t * manager						[in]ģ�������
* ��    ��: cp_module_info_t * info								[in]ģ�����Ϣ
*
* �� �� ֵ: cp_extern cp_module_t*
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2018-2-2 11:19:39
********************************************************************************/
cp_extern cp_module_t* _create_module(cp_module_register_t *register_info, cp_module_manager_t *manager, cp_module_info_t *info);

#define cp_create_module(register_info, manager, info)							\
		_create_module((cp_module_register_t *) (register_info), (cp_module_manager_t *) (manager), (cp_module_info_t *) (info))




/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: _destroy_module
*
* ����ȫ��: _destroy_module
*
* ��������: public 
*
* ����˵��: ����˵��
*
* ��    ��: cp_module_manager_t * manager						[in/out]����˵��
* ��    ��: cp_module_t * module						[in/out]����˵��
*
* �� �� ֵ: cp_extern cp_int32_t
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2018-2-2 11:20:49
********************************************************************************/
cp_extern cp_int32_t _destroy_module(cp_module_manager_t *manager, cp_module_t *module);

#define cp_destroy_module(manager, module)										\
		_destroy_module((cp_module_manager_t *) (manager), (cp_module_t *) (module))



/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: _init_module
*
* ����ȫ��: _init_module
*
* ��������: public 
*
* ����˵��: ����˵��
*
* ��    ��: cp_module_t * module						[in/out]����˵��
* ��    ��: const cp_module_info_t * info						[in/out]����˵��
*
* �� �� ֵ: cp_extern cp_int32_t
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2018-2-2 11:25:55
********************************************************************************/
cp_extern cp_int32_t _init_module(cp_module_t *module, const cp_module_info_t *info);

#define cp_init_module(module, info)											\
		_init_module((cp_module_t *) (module), (cp_module_info_t *) (info))




/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: _open_module
*
* ����ȫ��: _open_module
*
* ��������: public 
*
* ����˵��: ����˵��
*
* ��    ��: cp_module_t * module						[in/out]����˵��
* ��    ��: const cp_module_info_t * info						[in/out]����˵��
*
* �� �� ֵ: cp_extern cp_int32_t
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2018-2-2 11:25:59
********************************************************************************/
cp_extern cp_int32_t _open_module(cp_module_t *module, const cp_module_info_t *info);

#define cp_open_module(module, info)											\
		_open_module((cp_module_t *)(module), (const cp_module_info_t *)(info))




/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: _read_module
*
* ����ȫ��: _read_module
*
* ��������: public 
*
* ����˵��: ����˵��
*
* ��    ��: cp_module_t * module						[in/out]����˵��
* ��    ��: cp_uchar_t * * buf						[in/out]����˵��
* ��    ��: cp_int32_t len						[in/out]����˵��
* ��    ��: cp_int32_t flag						[in/out]����˵��
*
* �� �� ֵ: cp_extern cp_int32_t
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2018-2-2 11:26:03
********************************************************************************/
cp_extern cp_int32_t _read_module(cp_module_t *module, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);

#define cp_read_module(module, buf, len, flag)									\
		_read_module((cp_module_t *) (module), (cp_uchar_t **) (buf), (cp_int32_t) (len), (cp_int32_t) (flag))




/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: _write_module
*
* ����ȫ��: _write_module
*
* ��������: public 
*
* ����˵��: ����˵��
*
* ��    ��: cp_module_t * module						[in/out]����˵��
* ��    ��: const cp_uchar_t * * buf						[in/out]����˵��
* ��    ��: cp_int32_t len						[in/out]����˵��
* ��    ��: cp_int32_t flag						[in/out]����˵��
*
* �� �� ֵ: cp_extern cp_int32_t
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2018-2-2 11:26:04
********************************************************************************/
cp_extern cp_int32_t _write_module(cp_module_t *module, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);

#define cp_write_module(module, buf, len, flag)								\
		_write_module((cp_module_t *) (module), (const cp_uchar_t **) (buf), (cp_int32_t) (len), (cp_int32_t) (flag))




/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: _write_module
*
* ����ȫ��: _write_module
*
* ��������: 
*
* ����˵��: ����˵��
*
* ��    ��: cp_module_t * module						[in/out]����˵��
*
* �� �� ֵ: cp_extern cp_int32_t
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2018-2-2 11:26:05
********************************************************************************/
cp_extern cp_int32_t _close_module(cp_module_t *module);

#define cp_close_module(module)	_close_module((cp_module_t *) (module))






/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: _exit_module
*
* ����ȫ��: _exit_module
*
* ��������: public 
*
* ����˵��: ����˵��
*
* ��    ��: cp_module_t * module						[in/out]����˵��
*
* �� �� ֵ: cp_extern cp_int32_t
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2018-2-2 11:26:07
********************************************************************************/
cp_extern cp_int32_t _exit_module(cp_module_t *module);

#define cp_exit_module(module)		_exit_module((cp_module_t *) (module))




/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: _set_option_module
*
* ����ȫ��: _set_option_module
*
* ��������: public 
*
* ����˵��: ����˵��
*
* ��    ��: cp_module_t * module						[in/out]����˵��
* ��    ��: cp_int32_t optname						[in/out]����˵��
* ��    ��: const cp_void_t * optval						[in/out]����˵��
*
* �� �� ֵ: cp_extern cp_int32_t
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2018-2-2 11:26:09
********************************************************************************/
cp_extern cp_int32_t _set_option_module(cp_module_t *module, cp_int32_t optname, const cp_void_t* optval);

#define cp_set_option_module(module, optname, optval)							\
		_set_option_module((cp_module_t *) module, (cp_int32_t) optname, (const cp_void_t*) optval)




/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: _get_option_module
*
* ����ȫ��: _get_option_module
*
* ��������: public 
*
* ����˵��: ����˵��
*
* ��    ��: cp_module_t * module						[in/out]����˵��
* ��    ��: cp_int32_t optname						[in/out]����˵��
* ��    ��: cp_void_t * optval						[in/out]����˵��
*
* �� �� ֵ: cp_extern cp_int32_t
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2018-2-2 11:26:11
********************************************************************************/
cp_extern cp_int32_t _get_option_module(cp_module_t *module, cp_int32_t optname, cp_void_t* optval);

#define cp_get_option_module(module, optname, optval)							\
		_get_option_module((cp_module_t *)module, (cp_int32_t) optname, (cp_void_t*) optval)





/************************************************************************/
/* module��error��صĲ���                                               */
/************************************************************************/

/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: _set_module_error
*
* ����ȫ��: _set_module_error
*
* ��������: public 
*
* ����˵��: ����˵��
*
* ��    ��: cp_module_t * module						[in/out]����˵��
* ��    ��: const cp_int32_t error_no						[in/out]����˵��
* ��    ��: const cp_char_t * format						[in/out]����˵��
* ��    ��: ...						[in/out]����˵��
*
* �� �� ֵ: cp_extern cp_int32_t
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2018-2-2 11:26:13
********************************************************************************/
cp_extern cp_int32_t _set_module_error(cp_module_t *module, const cp_int32_t error_no, const cp_char_t *format, ...);
#define cp_set_module_error(module, error_no, format, ...)						\
		_set_module_error((cp_module_t *)module, (error_no), (format), ##__VA_ARGS__)

/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: _get_module_error_no
*
* ����ȫ��: _get_module_error_no
*
* ��������: public 
*
* ����˵��: ����˵��
*
* ��    ��: cp_module_t * module						[in/out]����˵��
*
* �� �� ֵ: cp_extern cp_int32_t
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2018-2-2 11:26:15
********************************************************************************/
cp_extern cp_int32_t _get_module_error_no(cp_module_t *module);
#define cp_get_module_error(module)						_get_module_error_no((cp_module_t *)module)

/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: _get_module_error_text
*
* ����ȫ��: _get_module_error_text
*
* ��������: public 
*
* ����˵��: ����˵��
*
* ��    ��: cp_module_t * module						[in/out]����˵��
*
* �� �� ֵ: cp_extern cp_char_t*
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2018-2-2 11:26:17
********************************************************************************/
cp_extern cp_char_t* _get_module_error_text(cp_module_t *module);
#define cp_get_module_error_text(module)				_get_module_error_text((cp_module_t *)module)


/************************************************************************/
/* app ��ģ�����                                                        */
/************************************************************************/

/************************************************************************/



/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: _app_create_module_by_type
*
* ����ȫ��: _app_create_module_by_type
*
* ��������: public 
*
* ����˵��: app �������ʹ���һ��ģ��
*
* ��    ��: cp_app_t * app						[in/out]����˵��
* ��    ��: cp_module_manager_type_e manager_type						[in/out]����˵��
* ��    ��: cp_module_type_e module_type						[in/out]����˵��
* ��    ��: cp_module_info_t * info						[in/out]����˵��
*
* �� �� ֵ: cp_extern cp_module_t*
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2018-2-11 15:21:45
********************************************************************************/
cp_extern cp_module_t* _app_create_module_by_type(cp_app_t *app, 
	cp_module_manager_type_e manager_type, cp_module_type_e module_type, cp_module_info_t *module_info);

#define cp_app_create_module_by_type(app, manager_type, module_type, module_info)			\
		_app_create_module_by_type((cp_app_t*) (app), (cp_module_manager_type_e) (manager_type), (cp_module_type_e) (module_type), (cp_module_info_t *) (module_info))


/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: _app_get_module_by_type
*
* ����ȫ��: _app_get_module_by_type
*
* ��������: public
*
* ����˵��: app �������ͻ�ȡһ��ģ��
*
* ��    ��: cp_app_t * app						[in/out]����˵��
* ��    ��: cp_module_manager_type_e manager_type						[in/out]����˵��
* ��    ��: cp_module_type_e module_type						[in/out]����˵��
*
* �� �� ֵ: cp_extern cp_module_t*
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2018-2-11 15:21:45
********************************************************************************/
cp_extern cp_module_t* _app_get_module_by_type(cp_app_t *app,
	cp_module_manager_type_e manager_type, cp_module_type_e module_type);

#define cp_app_get_module_by_type(app, manager_type, module_type)			\
		_app_get_module_by_type((cp_app_t*) (app), (cp_module_manager_type_e) (manager_type), (cp_module_type_e) (module_type))








#endif




