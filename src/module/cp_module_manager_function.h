
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
* 版权所有: fz & novigo
*
* 函数名称: print_manager_register_info_f
*
* 函数说明: 打印注册信息内容
*
* 参    数: cp_module_manager_register_t * manager_register		[in]需要被打印的注册信息
* 参    数: cp_char_t * buf										[in]数据缓存
* 参    数: cp_int32_t len										[in]缓存长度
*
* 返 回 值: cp_char_t *
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-06-23 10:00:46
******************************************************************************************************/
cp_extern cp_char_t *print_manager_register_info_f(cp_module_manager_register_t *manager_register, cp_char_t *buf, cp_int32_t len);



/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: _malloc_module_manager
*
* 函数说明: 创建模块的内存空间
*
* 参    数: cp_app_t *app						[in]参数说明
* 参    数: cp_int32_t manager_mem_size						[in]参数说明
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
cp_extern cp_module_manager_t* _malloc_module_manager(cp_app_t *app, cp_int32_t manager_mem_size, cp_module_info_t *info);

#define cp_malloc_module_manager(app, type, pool_info)								\
		(type *)_malloc_module_manager((cp_app_t *)app, cp_sizeof(type), (cp_module_info_t*) pool_info)



/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: _free_module
*
* 函数说明: 释放模块的内存
*
* 参    数: cp_module_manager_t *manager						[in]参数说明
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
cp_extern cp_int32_t _free_module_manager(cp_module_manager_t *manager);

#define cp_free_module_module(manager)												\
		_free_module_manager((cp_module_manager_t *)manager)



#define cp_print_manager_register_info(manager_register, buf, len)					\
		print_manager_register_info_f((cp_module_manager_register_t *) (manager_register), (cp_char_t *) (buf), (cp_int32_t) (len))


/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: create_manager_f
*
* 函数说明: 创建一个模块
*
* 参    数: cp_module_manager_register_t * register_info						[in]参数说明
* 参    数: cp_app_t * app						[in]参数说明
* 参    数: cp_module_manager_info_t * info						[in]参数说明
*
* 返 回 值: cp_module_manager_t*
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-06-23 15:45:43
******************************************************************************************************/
cp_extern cp_module_manager_t* _create_manager(cp_module_manager_register_t *register_info, cp_app_t *app, cp_module_manager_info_t *info);

#define cp_create_manager(register_info, app, info)			\
		_create_manager((cp_module_manager_register_t *) (register_info), (cp_app_t *) (app), (cp_module_manager_info_t *) (info))


/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: destroy_manager_f
*
* 函数说明: 销毁指定模块
*
* 参    数: cp_app_t * app						[in]参数说明
* 参    数: cp_module_manager_t * manager						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-06-23 15:56:14
******************************************************************************************************/
cp_extern cp_int32_t _destroy_manager(cp_app_t *app, cp_module_manager_t *manager);

#define cp_destroy_manager(app, manager)					\
		_destroy_manager((cp_app_t *) (app), (cp_module_manager_t *) (manager))


/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: init_manager_f
*
* 函数说明: 模块创建接口，表示创建一个模块
*
* 参    数: cp_module_manager_t * manager								[in]参数说明
* 参    数: const cp_module_manager_info_t * info						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-06-23 15:42:06
******************************************************************************************************/
cp_extern cp_int32_t _init_manager(cp_module_manager_t *manager, const cp_module_manager_info_t *info);

#define cp_init_manager(manager, info)						\
		_init_manager((cp_module_manager_t *) (manager), (cp_module_manager_info_t *) (info))


/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: start_manager_f
*
* 函数说明: 模块打开运行接口，在模块init之后，会被调用
*
* 参    数: cp_module_manager_t * manager						[in]参数说明
* 参    数: const cp_module_manager_info_t * info						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-06-23 15:42:25
******************************************************************************************************/
cp_extern cp_int32_t _start_manager(cp_module_manager_t *manager, const cp_module_manager_info_t *info);

#define cp_start_manager(manager, info)						\
		_start_manager((cp_module_manager_t *) (manager), (cp_module_manager_info_t *) (info))


/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: stop_manager_f
*
* 函数说明: 读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留
*
* 参    数: cp_module_manager_t * manager						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-06-23 15:42:38
******************************************************************************************************/
cp_extern cp_int32_t _stop_manager(cp_module_manager_t *manager);

#define cp_stop_manager(manager) _stop_manager((cp_module_manager_t *) (manager))


/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: ctrl_manager_f
*
* 函数说明: 设置模块参数
*
* 参    数: cp_module_manager_t * manager						[in]参数说明
* 参    数: cp_int32_t optname						[in]参数说明
* 参    数: const cp_void_t * optval						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-06-23 15:42:51
******************************************************************************************************/
cp_extern cp_int32_t _ctrl_manager(cp_module_manager_t *manager, cp_int32_t optname, const cp_void_t* optval);

#define cp_ctrl_manager(manager, optname, optval)			\
		_ctrl_manager((cp_module_manager_t *) (manager), (cp_int32_t) (optname), (cp_void_t*) (optval))


/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: get_manager_f
*
* 函数说明: 获取管理器信息
*
* 参    数: cp_app_t *app						[in]参数说明
* 参    数: const cp_module_manager_info_t * info						[in]参数说明
*
* 返 回 值: cp_module_manager_t*
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-06-23 15:42:51
******************************************************************************************************/
cp_extern cp_module_manager_t* _get_manager(const cp_app_t *app, const cp_module_manager_info_t *info);

#define cp_get_manager(app, info) _get_manager((const cp_app_t *) (app), (cp_module_manager_info_t *) (info))


/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: manager_create_module_f
*
* 函数说明: 模块创建接口，表示创建一个模块
*
* 参    数: cp_module_manager_t * manager						[in]参数说明
* 参    数: const cp_module_info_t * info						[in]参数说明
*
* 返 回 值: cp_module_t*
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-06-23 15:43:01
******************************************************************************************************/
cp_extern cp_module_t* _manager_create_module(cp_module_manager_t *manager, const cp_module_info_t *info);

#define cp_manager_create_module(manager, info)				\
		_manager_create_module((cp_module_manager_t *) (manager), (cp_module_info_t *) (info))


/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: _manager_create_module_by_register
*
* 函数说明: 通用模块创建接口，根据模块注册信息创建一个模块
*
* 参    数: cp_module_manager_t * manager						[in]参数说明
* 参    数: const cp_module_info_t * info						[in]参数说明
*
* 返 回 值: cp_extern cp_module_t*
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-04-23 15:24:08
******************************************************************************************************/
cp_extern cp_module_t* _manager_create_module_by_register(cp_module_manager_t *manager, const cp_module_info_t *info);

#define cp_manager_create_module_by_register(manager, info)	\
		_manager_create_module_by_register((cp_module_manager_t *) (manager), (cp_module_info_t *) (info))


/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: _manager_create_module_by_type
*
* 函数全名: _manager_create_module_by_type
*
* 函数访问: public 
*
* 函数说明: 通用模块创建接口，根据模块type创建一个模块
*
* 参    数: cp_module_manager_t * manager						[in/out]参数说明
* 参    数: cp_int32_t type						[in/out]参数说明
*
* 返 回 值: cp_extern cp_module_t*
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-8-21 12:04:17
********************************************************************************/
cp_extern cp_module_t* _manager_create_module_by_type(cp_module_manager_t *manager, cp_int32_t type);

#define cp_manager_create_module_by_type(manager, type)	\
		_manager_create_module_by_type((cp_module_manager_t *) (manager), (type))


/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: manager_get_module_f
*
* 函数说明: 查询一个模块
*
* 参    数: cp_module_manager_t * manager						[in]参数说明
* 参    数: const cp_module_info_t * info						[in]参数说明
*
* 返 回 值: cp_module_t*
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-07-01 17:02:11
******************************************************************************************************/
cp_extern cp_module_t* _manager_get_module(cp_module_manager_t *manager, const cp_module_info_t *info);

#define cp_manager_get_module(manager, info)				\
		_manager_get_module((cp_module_manager_t *) (manager), (cp_module_info_t *) (info))


/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: manager_register_module_f
*
* 函数说明: 写模块数据，flag为写模式的扩展标志。默认为0，其他为预留
*
* 参    数: cp_module_manager_t * manager						[in]参数说明
* 参    数: cp_module_t * module						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-06-23 15:43:12
******************************************************************************************************/
cp_extern cp_int32_t _manager_register_module(cp_module_manager_t *manager, cp_module_t *module);

#define cp_manager_register_module(manager, module)			\
		_manager_register_module((cp_module_manager_t *) (manager), (cp_module_t *) (module))


/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: manager_cancel_module_f
*
* 函数说明: 关闭模块
*
* 参    数: cp_module_manager_t * manager						[in]参数说明
* 参    数: cp_module_t * module						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-06-23 15:43:24
******************************************************************************************************/
cp_extern cp_int32_t _manager_cancel_module(cp_module_manager_t *manager, cp_module_t *module);

#define cp_manager_cancel_module(manager, module)			\
		_manager_cancel_module((cp_module_manager_t *) (manager), (cp_module_t *) (module))


/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: manager_destroy_module_f
*
* 函数说明: 退出模块
*
* 参    数: cp_module_manager_t * manager						[in]参数说明
* 参    数: cp_module_t * module						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-06-23 15:43:40
******************************************************************************************************/
cp_extern cp_int32_t _manager_destroy_module(cp_module_manager_t *manager, cp_module_t *module);

#define cp_manager_destroy_module(manager, module)			\
		_manager_destroy_module((cp_module_manager_t *) (manager), (cp_module_t *) (module))


/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: _manager_destroy_all_module
*
* 函数全名: _manager_destroy_all_module
*
* 函数访问: public 
*
* 函数说明: 表示销毁该管理器的所有已经创建的模块
*
* 参    数: cp_module_manager_t * manager						[in/out]参数说明
*
* 返 回 值: cp_extern cp_int32_t
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2018-2-9 16:32:39
********************************************************************************/
cp_extern cp_int32_t _manager_destroy_all_module(cp_module_manager_t *manager);

#define cp_manager_destroy_all_module(manager)				\
		_manager_destroy_all_module((cp_module_manager_t *) (manager))



/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: manager_ctrl_module_f
*
* 函数说明: 设置模块参数
*
* 参    数: cp_module_manager_t * manager						[in]参数说明
* 参    数: cp_module_t * module						[in]参数说明
* 参    数: cp_int32_t optname						[in]参数说明
* 参    数: const cp_void_t * optval						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-06-23 15:43:51
******************************************************************************************************/
cp_extern cp_int32_t _manager_ctrl_module(cp_module_manager_t *manager, cp_module_t *module,
	cp_int32_t optname, const cp_void_t* optval);

#define cp_manager_ctrl_module(manager, module, optname, optval)						\
		_manager_ctrl_module((cp_module_manager_t *) (manager), (cp_module_t *) module,	\
			(cp_int32_t) (optname), (cp_void_t*) (optval))









//////////////////////////////////////////////////////////////////////////
/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: _manager_get_root_manager
*
* 函数说明: 表示获取根管理器注册信息
*
* 参    数: cp_app_t * app						[in]参数说明
* 参    数: cp_int32_t type						[in]参数说明
*
* 返 回 值: cp_module_manager_t*
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-08-16 10:20:17
******************************************************************************************************/
cp_extern cp_module_manager_t* _manager_get_root_manager(cp_app_t *app, cp_int32_t type);

#define cp_manager_get_root_manager(app, type)							_manager_get_root_manager((cp_app_t *)(app), (type))


/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: _manager_set_root_manager
*
* 函数说明: 表示设备根管理器注册信息
*
* 参    数: cp_app_t * app						[in]参数说明
* 参    数: cp_int32_t type						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-08-16 11:22:16
******************************************************************************************************/
cp_extern cp_int32_t _manager_set_root_manager(cp_app_t *app, cp_int32_t type);

#define cp_manager_set_root_manager(app, type)							_manager_set_root_manager((cp_app_t *)(app), (type))

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: _manager_get_sub_manager
*
* 函数说明: 表示获取子管理器注册信息
*
* 参    数: cp_module_manager_t	*root_manager						[in]参数说明
* 参    数: cp_int32_t type											[in]参数说明
*
* 返 回 值: cp_module_manager_t*
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-08-16 10:20:17
******************************************************************************************************/
cp_extern cp_module_manager_t* _manager_get_sub_manager(cp_module_manager_t *root_manager, cp_int32_t type);

#define cp_manager_get_sub_manager(root_manager, type)					_manager_get_sub_manager((cp_module_manager_t *)(root_manager), (type))


/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: _manager_get_sub_module
*
* 函数说明: 获取指定管理下的模块
*
* 参    数: cp_app_t * app						[in]参数说明
* 参    数: cp_int32_t manager_type						[in]参数说明
* 参    数: cp_int32_t module_type						[in]参数说明
*
* 返 回 值: cp_module_t*
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-11-25 15:37:27
******************************************************************************************************/
cp_extern cp_module_t* _manager_get_sub_module(cp_app_t *app, cp_int32_t manager_type, cp_int32_t module_type);

#define cp_manager_get_sub_module(app, manager_type, module_type)		_manager_get_sub_module((cp_app_t *)(app), (manager_type), (module_type))





//////////////////////////////////////////////////////////////////////////
 /******************************************************************************************************
 * 版权所有: fz & novigo
 *
 * 函数名称: _manager_create_all_sub_manager
 *
 * 函数说明: 创建子模块管理器
 *
 * 参    数: cp_module_manager_t * root_manager						[in]参数说明
 *
 * 返 回 值: cp_int32_t
 *           0  : 成功
 *         非 0  :失败
 *
 * 备    注:其他说明内容
 *
 * 作    者：fz
 * 电子邮箱： fangzhenmu@novigo.com.cn
 * 创建日期：2017-05-09 22:05:00
 ******************************************************************************************************/
cp_extern  cp_int32_t _manager_create_all_sub_manager(cp_module_manager_t *root_manager);

#define cp_manager_create_all_sub_manager(root_manager)					_manager_create_all_sub_manager((cp_module_manager_t *)(root_manager))


/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: _manager_create_all_sub_manager
*
* 函数说明: 销毁子模块管理器
*
* 参    数: cp_module_manager_t * root_manager						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-05-09 22:05:00
******************************************************************************************************/
cp_extern  cp_int32_t _manager_destroy_all_sub_manager(cp_module_manager_t *root_manager);

#define cp_manager_destroy_all_sub_manager(root_manager)					_manager_destroy_all_sub_manager((cp_module_manager_t *)(root_manager))



/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: _manager_create_all_sub_manager
*
* 函数说明: 初始化子模块管理器
*
* 参    数: cp_module_manager_t * root_manager						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-05-09 22:05:00
******************************************************************************************************/
cp_extern  cp_int32_t _manager_init_all_sub_manager(cp_module_manager_t *root_manager);

#define cp_manager_init_all_sub_manager(root_manager)					_manager_init_all_sub_manager((cp_module_manager_t *)(root_manager))


/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: _manager_create_all_sub_manager
*
* 函数说明: 启动子模块管理器
*
* 参    数: cp_module_manager_t * root_manager						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-05-09 22:05:00
******************************************************************************************************/
cp_extern  cp_int32_t _manager_start_all_sub_manager(cp_module_manager_t *root_manager);

#define cp_manager_start_all_sub_manager(root_manager)					_manager_start_all_sub_manager((cp_module_manager_t *)(root_manager))


/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: _manager_create_all_sub_manager
*
* 函数说明: 停止子模块管理器
*
* 参    数: cp_module_manager_t * root_manager						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-05-09 22:05:00
******************************************************************************************************/
cp_extern  cp_int32_t _manager_stop_all_sub_manager(cp_module_manager_t *root_manager);

#define cp_manager_stop_all_sub_manager(root_manager)					_manager_stop_all_sub_manager((cp_module_manager_t *)(root_manager))


#endif




