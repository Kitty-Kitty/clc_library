/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-08-09

Description:

**************************************************************************/


#include "cp_include.h"
#include "cp_module_dependent.h"





/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: cp_add_root_manager_dependent
*
* 函数说明: 处理根管理器依赖
*
* 参    数: cp_module_manager_t * app						[in]参数说明
* 参    数: cp_uint32_t register_struct_size						[in]参数说明
* 参    数: cp_module_manager_register_t * module_manager_register						[in]参数说明
*
* 返 回 值: cp_module_manager_register_t*
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-08-16 14:52:29
******************************************************************************************************/
cp_module_manager_register_t* cp_add_root_manager_dependent
	(cp_app_t *app, cp_module_manager_register_t* module_manager_register, cp_uint32_t register_struct_size) {
	cp_int32_t										ret_int = 0;
	cp_module_manager_register_t					*tmp_mmr = CP_NULL;




	//判断数据合法性
	if (!app || !register_struct_size || !module_manager_register) {
		return CP_NULL;
	}
	//设置一个根管理器注册器
	ret_int = cp_manager_set_root_manager_register(app, module_manager_register, register_struct_size);
	if (ret_int) {
		return CP_NULL;
	}
	return (cp_module_manager_register_t*)cp_manager_get_root_manager_register(app, module_manager_register->type);
}


/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: cp_add_sub_manager_dependent
*
* 函数说明: 处理子管理器依赖
*
* 参    数: cp_module_manager_t * app						[in]参数说明
* 参    数: cp_uint32_t register_struct_size						[in]参数说明
* 参    数: cp_module_manager_register_t * module_manager_register						[in]参数说明
*
* 返 回 值: cp_module_manager_register_t*
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-08-16 14:52:44
******************************************************************************************************/
cp_module_manager_register_t* cp_add_sub_manager_dependent
	(cp_app_t *app, cp_module_manager_register_t* module_manager_register, cp_uint32_t register_struct_size) {
	cp_int32_t										ret_int = 0;
	cp_module_manager_t								*tmp_root_manager = CP_NULL;
	cp_module_manager_register_t					*tmp_mmr = CP_NULL;
	cp_char_t										tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };




	//判断数据合法性
	if (!app || !register_struct_size || !module_manager_register) {
		return CP_NULL;
	}
	tmp_root_manager = cp_manager_get_root_manager(app, module_manager_register->type);
	if (!tmp_root_manager) {
		cp_app_log(error, app, "cp_add_sub_manager_dependent() error. not found root manager of [%s] register_struct_size[%d].",
			cp_print_manager_register_info(module_manager_register, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH),
			register_struct_size);
		return CP_NULL;
	}
	//设置一个根管理器注册器
	ret_int = cp_manager_set_sub_manager_register(tmp_root_manager, module_manager_register, 1, register_struct_size);
	if (ret_int) {
		cp_app_log(error, app, "cp_add_sub_manager_dependent() error. set_sub_manager_register() error of [%s] register_struct_size[%d].",
			cp_print_manager_register_info(module_manager_register, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH),
			register_struct_size);
		return CP_NULL;
	}
	return (cp_module_manager_register_t*)cp_manager_get_sub_manager_register(tmp_root_manager, module_manager_register->type);
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: cp_add_module_dependent
*
* 函数说明: 添加模块依赖信息
*
* 参    数: cp_module_manager_t * app						[in]表示需要添加的模块管理器
* 参    数: cp_uint32_t register_struct_size						[in]表示注册器的大小
* 参    数: cp_module_manager_register_t * module_manager_register				[in]表示需要添加的注册器
*
* 返 回 值: cp_module_manager_register_t*
*           0  : 失败
*         非 0  :成功 
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-08-09 15:45:57
******************************************************************************************************/
cp_module_register_t* cp_add_module_dependent(cp_app_t *app, 
	cp_int32_t manager_type, cp_module_register_t* module_register, cp_uint32_t register_struct_size) {
	cp_int32_t										ret_int = 0;
	cp_module_manager_info_t						tmp_module_manager_info;
	cp_module_manager_t								*tmp_module_manager = CP_NULL;




	//判断数据合法性
	if (!app || !register_struct_size || !module_register) {
		return CP_NULL;
	}
	//获取模块管理器
	CP_MODULE_MANAGER_INFO_SET_TYPE(&tmp_module_manager_info, manager_type);
	tmp_module_manager = cp_get_manager(app, &tmp_module_manager_info);
	if (!tmp_module_manager) {
		return CP_NULL;
	}
	//设置一个模块注册器
	ret_int = cp_manager_set_module_register(tmp_module_manager, module_register, 1, register_struct_size);
	if (ret_int) {
		return CP_NULL;
	}
	return (cp_module_register_t*)cp_manager_get_module_register(tmp_module_manager, module_register->type);
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: cp_add_manager_dependent_callback_null_handle
*
* 函数说明: 一个空的依赖回调函数
*
* 参    数: cp_module_manager_t * app												[in]参数说明
* 参    数: cp_uint32_t register_struct_size											[in]参数说明
* 参    数: cp_module_manager_register_t * module_manager_register					[in]参数说明
*
* 返 回 值: cp_module_manager_register_t*
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-08-16 15:30:17
******************************************************************************************************/
cp_module_manager_register_t* cp_add_manager_dependent_callback_null_handle(cp_app_t *app, 
	cp_module_manager_register_t* module_manager_register, cp_uint32_t register_struct_size) {
	return module_manager_register;
}


/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: cp_add_module_dependent_callback_null_handle
*
* 函数说明: 描述方法的功能信息
*
* 参    数: cp_app_t * app										[in]需要被处理的app
* 参    数: cp_int32_t manager_type								[in]参数说明
* 参    数: cp_module_register_t * module_register				[in]参数说明
* 参    数: cp_uint32_t register_struct_size						[in]参数说明
*
* 返 回 值: cp_module_register_t*
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-08-16 17:00:50
******************************************************************************************************/
cp_module_register_t* cp_add_module_dependent_callback_null_handle
(cp_app_t *app, cp_int32_t manager_type, cp_module_register_t* module_register, cp_uint32_t register_struct_size) {
	return module_register;
}