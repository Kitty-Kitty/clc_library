
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
* 版权所有: fz & novigo
*
* 函数名称: _malloc_module
*
* 函数说明: 创建模块的内存空间
*
* 参    数: cp_module_manager_t * manager						[in]参数说明
* 参    数: cp_int32_t module_mem_size						[in]参数说明
* 参    数: cp_module_info_t * info						[in]参数说明
*
* 返 回 值: cp_extern cp_module_t *
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-03-26 14:04:55
******************************************************************************************************/
cp_extern cp_module_t* _malloc_module(cp_module_manager_t *manager, cp_int32_t module_mem_size, cp_module_info_t *info);

#define cp_malloc_module(manager, type, pool_info)								\
		(type *)_malloc_module((cp_module_manager_t *)manager, cp_sizeof(type), (cp_module_info_t*) pool_info)



/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: _free_module
*
* 函数说明: 释放模块的内存
*
* 参    数: cp_module_t * module						[in]参数说明
*
* 返 回 值: cp_extern cp_int32_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-03-26 14:07:54
******************************************************************************************************/
cp_extern cp_int32_t _free_module(cp_module_t *module);

#define cp_free_module(module)			_free_module((cp_module_t *)module)


#define cp_print_module_register_info(module_register, buf, len)				\
		print_module_register_info((cp_module_register_t *) (module_register), (cp_char_t *) (buf), (cp_int32_t) (len))



/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: _create_module
*
* 函数全名: _create_module
*
* 函数访问: public 
*
* 函数说明: 创建一个模块
*
* 参    数: cp_module_register_t * register_info					[in]模块注册信息
* 参    数: cp_module_manager_t * manager						[in]模块管理器
* 参    数: cp_module_info_t * info								[in]模块的信息
*
* 返 回 值: cp_extern cp_module_t*
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2018-2-2 11:19:39
********************************************************************************/
cp_extern cp_module_t* _create_module(cp_module_register_t *register_info, cp_module_manager_t *manager, cp_module_info_t *info);

#define cp_create_module(register_info, manager, info)							\
		_create_module((cp_module_register_t *) (register_info), (cp_module_manager_t *) (manager), (cp_module_info_t *) (info))




/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: _destroy_module
*
* 函数全名: _destroy_module
*
* 函数访问: public 
*
* 函数说明: 函数说明
*
* 参    数: cp_module_manager_t * manager						[in/out]参数说明
* 参    数: cp_module_t * module						[in/out]参数说明
*
* 返 回 值: cp_extern cp_int32_t
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2018-2-2 11:20:49
********************************************************************************/
cp_extern cp_int32_t _destroy_module(cp_module_manager_t *manager, cp_module_t *module);

#define cp_destroy_module(manager, module)										\
		_destroy_module((cp_module_manager_t *) (manager), (cp_module_t *) (module))



/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: _init_module
*
* 函数全名: _init_module
*
* 函数访问: public 
*
* 函数说明: 函数说明
*
* 参    数: cp_module_t * module						[in/out]参数说明
* 参    数: const cp_module_info_t * info						[in/out]参数说明
*
* 返 回 值: cp_extern cp_int32_t
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2018-2-2 11:25:55
********************************************************************************/
cp_extern cp_int32_t _init_module(cp_module_t *module, const cp_module_info_t *info);

#define cp_init_module(module, info)											\
		_init_module((cp_module_t *) (module), (cp_module_info_t *) (info))




/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: _open_module
*
* 函数全名: _open_module
*
* 函数访问: public 
*
* 函数说明: 函数说明
*
* 参    数: cp_module_t * module						[in/out]参数说明
* 参    数: const cp_module_info_t * info						[in/out]参数说明
*
* 返 回 值: cp_extern cp_int32_t
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2018-2-2 11:25:59
********************************************************************************/
cp_extern cp_int32_t _open_module(cp_module_t *module, const cp_module_info_t *info);

#define cp_open_module(module, info)											\
		_open_module((cp_module_t *)(module), (const cp_module_info_t *)(info))




/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: _read_module
*
* 函数全名: _read_module
*
* 函数访问: public 
*
* 函数说明: 函数说明
*
* 参    数: cp_module_t * module						[in/out]参数说明
* 参    数: cp_uchar_t * * buf						[in/out]参数说明
* 参    数: cp_int32_t len						[in/out]参数说明
* 参    数: cp_int32_t flag						[in/out]参数说明
*
* 返 回 值: cp_extern cp_int32_t
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2018-2-2 11:26:03
********************************************************************************/
cp_extern cp_int32_t _read_module(cp_module_t *module, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);

#define cp_read_module(module, buf, len, flag)									\
		_read_module((cp_module_t *) (module), (cp_uchar_t **) (buf), (cp_int32_t) (len), (cp_int32_t) (flag))




/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: _write_module
*
* 函数全名: _write_module
*
* 函数访问: public 
*
* 函数说明: 函数说明
*
* 参    数: cp_module_t * module						[in/out]参数说明
* 参    数: const cp_uchar_t * * buf						[in/out]参数说明
* 参    数: cp_int32_t len						[in/out]参数说明
* 参    数: cp_int32_t flag						[in/out]参数说明
*
* 返 回 值: cp_extern cp_int32_t
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2018-2-2 11:26:04
********************************************************************************/
cp_extern cp_int32_t _write_module(cp_module_t *module, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);

#define cp_write_module(module, buf, len, flag)								\
		_write_module((cp_module_t *) (module), (const cp_uchar_t **) (buf), (cp_int32_t) (len), (cp_int32_t) (flag))




/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: _write_module
*
* 函数全名: _write_module
*
* 函数访问: 
*
* 函数说明: 函数说明
*
* 参    数: cp_module_t * module						[in/out]参数说明
*
* 返 回 值: cp_extern cp_int32_t
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2018-2-2 11:26:05
********************************************************************************/
cp_extern cp_int32_t _close_module(cp_module_t *module);

#define cp_close_module(module)	_close_module((cp_module_t *) (module))






/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: _exit_module
*
* 函数全名: _exit_module
*
* 函数访问: public 
*
* 函数说明: 函数说明
*
* 参    数: cp_module_t * module						[in/out]参数说明
*
* 返 回 值: cp_extern cp_int32_t
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2018-2-2 11:26:07
********************************************************************************/
cp_extern cp_int32_t _exit_module(cp_module_t *module);

#define cp_exit_module(module)		_exit_module((cp_module_t *) (module))




/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: _set_option_module
*
* 函数全名: _set_option_module
*
* 函数访问: public 
*
* 函数说明: 函数说明
*
* 参    数: cp_module_t * module						[in/out]参数说明
* 参    数: cp_int32_t optname						[in/out]参数说明
* 参    数: const cp_void_t * optval						[in/out]参数说明
*
* 返 回 值: cp_extern cp_int32_t
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2018-2-2 11:26:09
********************************************************************************/
cp_extern cp_int32_t _set_option_module(cp_module_t *module, cp_int32_t optname, const cp_void_t* optval);

#define cp_set_option_module(module, optname, optval)							\
		_set_option_module((cp_module_t *) module, (cp_int32_t) optname, (const cp_void_t*) optval)




/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: _get_option_module
*
* 函数全名: _get_option_module
*
* 函数访问: public 
*
* 函数说明: 函数说明
*
* 参    数: cp_module_t * module						[in/out]参数说明
* 参    数: cp_int32_t optname						[in/out]参数说明
* 参    数: cp_void_t * optval						[in/out]参数说明
*
* 返 回 值: cp_extern cp_int32_t
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2018-2-2 11:26:11
********************************************************************************/
cp_extern cp_int32_t _get_option_module(cp_module_t *module, cp_int32_t optname, cp_void_t* optval);

#define cp_get_option_module(module, optname, optval)							\
		_get_option_module((cp_module_t *)module, (cp_int32_t) optname, (cp_void_t*) optval)





/************************************************************************/
/* module中error相关的操作                                               */
/************************************************************************/

/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: _set_module_error
*
* 函数全名: _set_module_error
*
* 函数访问: public 
*
* 函数说明: 函数说明
*
* 参    数: cp_module_t * module						[in/out]参数说明
* 参    数: const cp_int32_t error_no						[in/out]参数说明
* 参    数: const cp_char_t * format						[in/out]参数说明
* 参    数: ...						[in/out]参数说明
*
* 返 回 值: cp_extern cp_int32_t
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2018-2-2 11:26:13
********************************************************************************/
cp_extern cp_int32_t _set_module_error(cp_module_t *module, const cp_int32_t error_no, const cp_char_t *format, ...);
#define cp_set_module_error(module, error_no, format, ...)						\
		_set_module_error((cp_module_t *)module, (error_no), (format), ##__VA_ARGS__)

/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: _get_module_error_no
*
* 函数全名: _get_module_error_no
*
* 函数访问: public 
*
* 函数说明: 函数说明
*
* 参    数: cp_module_t * module						[in/out]参数说明
*
* 返 回 值: cp_extern cp_int32_t
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2018-2-2 11:26:15
********************************************************************************/
cp_extern cp_int32_t _get_module_error_no(cp_module_t *module);
#define cp_get_module_error(module)						_get_module_error_no((cp_module_t *)module)

/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: _get_module_error_text
*
* 函数全名: _get_module_error_text
*
* 函数访问: public 
*
* 函数说明: 函数说明
*
* 参    数: cp_module_t * module						[in/out]参数说明
*
* 返 回 值: cp_extern cp_char_t*
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2018-2-2 11:26:17
********************************************************************************/
cp_extern cp_char_t* _get_module_error_text(cp_module_t *module);
#define cp_get_module_error_text(module)				_get_module_error_text((cp_module_t *)module)


/************************************************************************/
/* app 的模块操作                                                        */
/************************************************************************/

/************************************************************************/



/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: _app_create_module_by_type
*
* 函数全名: _app_create_module_by_type
*
* 函数访问: public 
*
* 函数说明: app 根据类型创建一个模块
*
* 参    数: cp_app_t * app						[in/out]参数说明
* 参    数: cp_module_manager_type_e manager_type						[in/out]参数说明
* 参    数: cp_module_type_e module_type						[in/out]参数说明
* 参    数: cp_module_info_t * info						[in/out]参数说明
*
* 返 回 值: cp_extern cp_module_t*
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2018-2-11 15:21:45
********************************************************************************/
cp_extern cp_module_t* _app_create_module_by_type(cp_app_t *app, 
	cp_module_manager_type_e manager_type, cp_module_type_e module_type, cp_module_info_t *module_info);

#define cp_app_create_module_by_type(app, manager_type, module_type, module_info)			\
		_app_create_module_by_type((cp_app_t*) (app), (cp_module_manager_type_e) (manager_type), (cp_module_type_e) (module_type), (cp_module_info_t *) (module_info))


/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: _app_get_module_by_type
*
* 函数全名: _app_get_module_by_type
*
* 函数访问: public
*
* 函数说明: app 根据类型获取一个模块
*
* 参    数: cp_app_t * app						[in/out]参数说明
* 参    数: cp_module_manager_type_e manager_type						[in/out]参数说明
* 参    数: cp_module_type_e module_type						[in/out]参数说明
*
* 返 回 值: cp_extern cp_module_t*
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2018-2-11 15:21:45
********************************************************************************/
cp_extern cp_module_t* _app_get_module_by_type(cp_app_t *app,
	cp_module_manager_type_e manager_type, cp_module_type_e module_type);

#define cp_app_get_module_by_type(app, manager_type, module_type)			\
		_app_get_module_by_type((cp_app_t*) (app), (cp_module_manager_type_e) (manager_type), (cp_module_type_e) (module_type))








#endif




