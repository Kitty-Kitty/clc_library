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



typedef cp_int32_t(*module_register_handle)(cp_module_register_t *register_info, cp_module_manager_t *manager);									/*将模块注册到模块管理器中*/
typedef cp_int32_t(*module_unregister_handle)(cp_module_register_t *register_info, cp_module_manager_t *manager);								/*将模块从模块管理器中取消注册*/
typedef cp_int32_t(*module_register_set_option_handle)(cp_module_register_t *register_info, cp_int32_t optname, const cp_void_t* optval);		/*更新模块注册信息*/
typedef cp_int32_t(*module_register_get_option_handle)(cp_module_register_t *register_info, cp_int32_t optname, cp_void_t* optval);				/*获取模块注册信息*/






cp_extern cp_int32_t cp_module_register(cp_module_register_t *register_info, cp_module_manager_t *manager);												/*将模块注册到模块管理器中*/
cp_extern cp_int32_t cp_module_unregister(cp_module_register_t *register_info, cp_module_manager_t *manager);												/*将模块从模块管理器中取消注册*/
cp_extern cp_int32_t cp_module_register_set_option(cp_module_register_t *register_info, cp_int32_t optname, const cp_void_t* optval);						/*更新模块注册信息*/
cp_extern cp_int32_t cp_module_register_get_option(cp_module_register_t *register_info, cp_int32_t optname, cp_void_t* optval);							/*获取模块注册信息*/







/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: _manager_create_register_memory
*
* 函数说明: 主要初始化各个模块的管理器内容空间大小
*
* 参    数: cp_module_manager_t * manager						[in]参数说明
* 参    数: cp_int32_t manager_register_size						[in]参数说明
* 参    数: cp_int32_t manager_size						[in]参数说明
* 参    数: cp_int32_t module_register_size						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-08-15 14:30:20
******************************************************************************************************/
cp_extern 
cp_int32_t _manager_create_register_memory(cp_module_manager_t *manager, cp_int32_t manager_register_size,
	cp_int32_t manager_size, cp_int32_t module_register_size);

#define cp_manager_create_register_memory(manager,	manager_register_size, manager_size, module_register_size)				\
	_manager_create_register_memory((cp_module_manager_t *)(manager), manager_register_size, manager_size, module_register_size);


/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: _manager_set_module_register
*
* 函数说明: 为模块管理器添加模块的注册信息
*
* 参    数: cp_module_manager_t * manager							[in]表示需要被添加的模块管理器
* 参    数: cp_module_register_t * module_register_list				[in]表示需要添加的模块注册器
* 参    数: cp_int32_t module_register_list_size						[in]表示需要添加的模块注册器数量
* 参    数: cp_int32_t size											[in]表示每个模块注册器的大小
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-08-09 17:48:23
******************************************************************************************************/
cp_extern 
cp_int32_t _manager_set_module_register(cp_module_manager_t *manager,
	cp_module_register_t *module_register_list, cp_int32_t module_register_list_size, cp_int32_t size);

#define cp_manager_set_module_register(manager,	module_register_list, module_register_list_size, size)			\
	_manager_set_module_register((cp_module_manager_t *)(manager),												\
		(cp_module_register_t *)(module_register_list), (module_register_list_size), (size));


/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: _manager_get_module_register
*
* 函数说明: 获取模块注册器信息
*
* 参    数: cp_module_manager_t * manager						[in]参数说明
* 参    数: cp_int32_t type						[in]参数说明
*
* 返 回 值: cp_module_register_t*
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-08-15 18:20:37
******************************************************************************************************/
cp_extern 
cp_module_register_t* _manager_get_module_register(cp_module_manager_t *manager, cp_int32_t type);

#define  cp_manager_get_module_register(manager, type)	_manager_get_module_register((cp_module_manager_t *)(manager), (type))

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: _manager_set_sub_manager_register
*
* 函数说明: 为模块增加子管理模块的注册信息
*
* 参    数: cp_module_manager_t * manager								[in]需要被添加了根模块地址信息
* 参    数: cp_module_manager_register_t * manager_register_list			[in]表示需要添加的注册器数组
* 参    数: cp_int32_t manager_register_list_size						[in]表示需要添加的数组大小
* 参    数: cp_int32_t size												[in]表示单个注册器的大小
*
* 返 回 值: cp_int32_t
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-08-16 15:32:06
******************************************************************************************************/
cp_extern 
cp_int32_t _manager_set_sub_manager_register(cp_module_manager_t *manager,
	cp_module_manager_register_t *manager_register_list, cp_int32_t manager_register_list_size, cp_uint32_t size);


#define cp_manager_set_sub_manager_register(manager, manager_register_list, manager_register_list_size, size)	\
	_manager_set_sub_manager_register((cp_module_manager_t *)(manager),											\
		(cp_module_manager_register_t *)(manager_register_list), (manager_register_list_size), (size));


/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: _manager_get_sub_manager_register
*
* 函数说明: 获取模块的子模块管理器信息
*
* 参    数: cp_module_manager_t * manager						[in]参数说明
* 参    数: cp_int32_t type										[in]参数说明
*
* 返 回 值: cp_module_manager_register_t*
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-08-15 18:21:44
******************************************************************************************************/
cp_extern 
cp_module_manager_register_t* _manager_get_sub_manager_register(cp_module_manager_t *manager, cp_int32_t type);

#define cp_manager_get_sub_manager_register(manager, type) _manager_get_sub_manager_register((cp_module_manager_t *)(manager), (type))




/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: _manager_set_root_manager_register
*
* 函数说明: 设置一个根模块管理器注册器信息
*
* 参    数: cp_app_t * app													[in]需要被添加应用程序地址
* 参    数: cp_module_manager_register_t * module_manager_register			[in]需要被添加的管理器注册器
* 参    数: cp_int32_t size													[in]表示注册器的大小
*
* 返 回 值: cp_int32_t
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-08-16 15:34:04
******************************************************************************************************/
cp_extern
cp_int32_t _manager_set_root_manager_register(cp_app_t *app, cp_module_manager_register_t *module_manager_register, cp_uint32_t size);

#define cp_manager_set_root_manager_register(app, module_manager_register, size)												\
		_manager_set_root_manager_register((app), (cp_module_manager_register_t*)(module_manager_register), (size))

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: _manager_get_root_manager_register
*
* 函数说明: 获取根管理器注册器
*
* 参    数: cp_app_t * app						[in]参数说明
* 参    数: cp_int32_t type						[in]参数说明
*
* 返 回 值: cp_module_manager_register_t*
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-08-16 11:30:42
******************************************************************************************************/
cp_extern
cp_module_manager_register_t* _manager_get_root_manager_register(cp_app_t *app, cp_int32_t type);

#define cp_manager_get_root_manager_register(app, type)		_manager_get_root_manager_register((cp_app_t *)(app), type)


#endif


