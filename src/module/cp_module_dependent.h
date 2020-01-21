/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-08-09

Description:

**************************************************************************/

#ifndef _CP_MODULE_DEPENDENT_INCLUDE_H_
#define _CP_MODULE_DEPENDENT_INCLUDE_H_



#include "cp_module_core.h"


/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: cp_add_manager_dependent_callback_handle
*
* 函数说明: 定义添加模块后的回调函数
*
* 参    数: cp_app_t *app													[in]表示当前被处理的app信息
* 参    数: cp_module_manager_register_t* module_register					[in]表示模块管理器注册器
* 参    数: cp_uint32_t register_struct_size									[in]表示模块管理器注册器的大小
*
* 返 回 值: typedef cp_module_manager_register_t* (*
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-08-16 16:34:20
******************************************************************************************************/
typedef cp_module_manager_register_t* (*cp_add_manager_dependent_callback_handle)
	(cp_app_t *app, cp_module_manager_register_t* module_manager_register, cp_uint32_t register_struct_size);


 
 /******************************************************************************************************
 * 版权所有: fz & novigo
 *
 * 函数名称: cp_add_module_dependent_callback_handle
 *
 * 函数说明: 描述方法的功能信息
 *
 * 参    数: cp_app_t *app													[in]表示当前被处理的app信息
 * 参    数: cp_int32_t manager_type											[in]表示需要被添加的模块管理器的类型
 * 参    数: cp_module_register_t* module_register							[in]表示模块注册器
 * 参    数: cp_uint32_t register_struct_size								[in]表示模块注册器的大小
 *
 * 返 回 值: typedef cp_module_register_t* (*
 *           0  : 成功 
 *         非 0  :失败
 *
 * 备    注:其他说明内容
 *
 * 作    者：fz
 * 电子邮箱： fangzhenmu@novigo.com.cn
 * 创建日期：2016-08-16 16:45:37
 ******************************************************************************************************/
typedef cp_module_register_t* (*cp_add_module_dependent_callback_handle)
(cp_app_t *app, cp_int32_t manager_type, cp_module_register_t* module_register, cp_uint32_t register_struct_size);



/************************************************************************/
/* 定义处理根模块管理器函数的入口函数                                     */
/************************************************************************/
#define CP_ROOT_MODULE_MANAGER_DEPENDENT_FUNCTION(app_flag)										\
	cp_void_t cp_##app_flag##_root_module_manager_dependent(cp_app_t *app);						\


/************************************************************************/
/* 定义处理根模块管理器函数的入口依赖关系                                  */
/************************************************************************/
#define CP_ROOT_MODULE_MANAGER_DEPENDENT_BEGIN(app_flag)										\
	cp_void_t cp_##app_flag##_root_module_manager_dependent(cp_app_t *app){						\



/************************************************************************/
/* 定义执行处理根模块管理器函数			                                */
/************************************************************************/
#define CP_ROOT_MODULE_MANAGER_DEPENDENT(app_flag, app)											\
	cp_##app_flag##_root_module_manager_dependent((cp_app_t*)(app));							\





/************************************************************************/
/* 定义处理子模块管理器函数的入口函数                                     */
/************************************************************************/
#define CP_SUB_MODULE_MANAGER_DEPENDENT_FUNCTION(app_flag)										\
	cp_void_t cp_##app_flag##_sub_module_manager_dependent(cp_app_t *app);						\


/************************************************************************/
/* 定义处理子模块管理器函数的入口依赖关系                                  */
/************************************************************************/
#define CP_SUB_MODULE_MANAGER_DEPENDENT_BEGIN(app_flag)											\
	cp_void_t cp_##app_flag##_sub_module_manager_dependent(cp_app_t *app){						\


/************************************************************************/
/* 定义执行处理子模块管理器函数                                           */
/************************************************************************/
#define CP_SUB_MODULE_MANAGER_DEPENDENT(app_flag, app)											\
	cp_##app_flag##_sub_module_manager_dependent((cp_app_t*)(app));								\



/************************************************************************/
/* 定义处理模块函数的入口函数                                             */
/************************************************************************/
#define CP_MODULE_DEPENDENT_FUNCTION(app_flag)													\
	cp_void_t cp_##app_flag##_module_dependent(cp_app_t *app);									\



/************************************************************************/
/* 定义处理模块函数的入口依赖关系                                          */
/************************************************************************/
#define CP_MODULE_DEPENDENT_BEGIN(app_flag)														\
	cp_void_t cp_##app_flag##_module_dependent(cp_app_t *app){									\


/************************************************************************/
/* 定义执行处理模块函数													*/
/************************************************************************/
#define CP_MODULE_DEPENDENT(app_flag, app)														\
	cp_##app_flag##_module_dependent((cp_app_t*)(app));											\






/************************************************************************/
/* 添加基础模块依赖函数													*/
/* 参    数 : register_struct							[in]表示register_struct,当前注册器的数据类型				*/
/* 参    数 : add_manager_dependent_handle				[in]表示add_manager_dependent_handle,当前添加依赖执行的函数指针	*/
/* 参    数 : add_module_dependent_callback_handle		[in]表示add_module_dependent_callback_handle,当前模块添加后的回调模块注册器		*/
/* 参    数 : MODULE_REGISTER_MARCO						[in]表示模块注册器的宏	*/
/************************************************************************/
#define CP_ADD_MANAGER_BASE_DEPENDENT(register_struct, add_manager_dependent_handle,											\
			add_module_dependent_callback_handle, ...)																			\
		do{																														\
				cp_module_manager_register_t *tmp_ret_register = CP_NULL;														\
				register_struct tmp_new_register[] = {__VA_ARGS__};																\
																																\
				if ((cp_add_manager_dependent_callback_handle)add_manager_dependent_handle) {									\
						tmp_ret_register = ((cp_add_manager_dependent_callback_handle)add_manager_dependent_handle)(app,		\
						(cp_module_manager_register_t*)&tmp_new_register[0], sizeof(register_struct));							\
						if ((cp_add_manager_dependent_callback_handle)add_module_dependent_callback_handle){					\
								((cp_add_manager_dependent_callback_handle)add_module_dependent_callback_handle)				\
										(app, tmp_ret_register, sizeof(register_struct));										\
						}																										\
				}																												\
		}while(0);																												\




/************************************************************************/
/* 添加基础模块依赖函数                                                      */
/* 参    数 : register_struct							[in]表示register_struct,当前注册器的数据类型				*/
/* 参    数 : manager_type								[in]表示模块依赖的管理器的类型							*/
/* 参    数 : add_manager_dependent_handle				[in]表示add_manager_dependent_handle,当前添加依赖执行的函数指针	*/
/* 参    数 : add_module_dependent_callback_handle		[in]表示add_module_dependent_callback_handle,当前模块添加后的回调模块注册器		*/
/* 参    数 : MODULE_REGISTER_MARCO						[in]表示模块注册器的宏	*/
/************************************************************************/
#define CP_ADD_MODULE_BASE_DEPENDENT(register_struct, manager_type, add_module_dependent_handle,								\
			add_module_dependent_callback_handle, ...)																			\
		do {																													\
				cp_module_register_t *tmp_ret_register = CP_NULL;																\
				register_struct tmp_new_register[] = {__VA_ARGS__};																\
																																\
				if ((cp_add_module_dependent_callback_handle)add_module_dependent_handle) {										\
						tmp_ret_register = ((cp_add_module_dependent_callback_handle)add_module_dependent_handle)(app,			\
						manager_type, (cp_module_register_t*)&tmp_new_register[0], sizeof(register_struct));					\
						if ((cp_add_module_dependent_callback_handle)add_module_dependent_callback_handle){						\
								((cp_add_module_dependent_callback_handle)add_module_dependent_callback_handle)					\
										(app, manager_type, tmp_ret_register, sizeof(register_struct));							\
						}																										\
				}																												\
		}while(0);																												\




/************************************************************************/
/* 添加根管理器依赖函数                                                  */
/* register_struct : 表示注册器的类型*/
/************************************************************************/
#define CP_ADD_ROOT_MANAGER_DEPENDENT(register_struct, add_module_dependent_callback_handle, MODULE_REGISTER_MARCO)				\
				CP_ADD_MANAGER_BASE_DEPENDENT(register_struct, cp_add_root_manager_dependent,									\
						add_module_dependent_callback_handle, MODULE_REGISTER_MARCO)											\



/************************************************************************/
/* 添加子管理器依赖函数                                                  */
/************************************************************************/
#define CP_ADD_SUB_MANAGER_DEPENDENT(register_struct, add_module_dependent_callback_handle, MODULE_REGISTER_MARCO)				\
				CP_ADD_MANAGER_BASE_DEPENDENT(register_struct, cp_add_sub_manager_dependent,									\
						add_module_dependent_callback_handle, MODULE_REGISTER_MARCO)											\



/************************************************************************/
/* 添加模块依赖函数                                                      */
/************************************************************************/
#define CP_ADD_MODULE_DEPENDENT(register_struct, manager_type, add_module_dependent_callback_handle, MODULE_REGISTER_MARCO)		\
				CP_ADD_MODULE_BASE_DEPENDENT(register_struct, manager_type, cp_add_module_dependent,							\
						add_module_dependent_callback_handle, MODULE_REGISTER_MARCO)											\



/************************************************************************/
/* 增加模块管理器结束                                                    */
/************************************************************************/
#define CP_MODULE_MANAGER_DEPENDENT_END()												}



/************************************************************************/
/* 增加模块结束                                                         */
/************************************************************************/
#define CP_MODULE_DEPENDENT_END()														}



/************************************************************************/
/* 添加一个空的管理器注册器添加回调函数                                    */
/************************************************************************/
#define CP_MANAGER_DEPENDENT_CALLBACK_NULL			cp_add_manager_dependent_callback_null_handle

/************************************************************************/
/* 添加一个空的模块注册器添加回调函数                                     */
/************************************************************************/
#define CP_MODULE_DEPENDENT_CALLBACK_NULL			cp_add_module_dependent_callback_null_handle




/************************************************************************/
/* 根、子、侍服管理器三者关系                                             */
/* 1、根                                                                */
/*    1.1子                                                             */
/*		   1.1.1侍														*/
/*		       1.1.1...侍											    */
/************************************************************************/

/************************************************************************/
/* 处理根管理器依赖                                                      */
/************************************************************************/
cp_module_manager_register_t* cp_add_root_manager_dependent(cp_app_t *app, 
	cp_module_manager_register_t *module_manager_register, cp_uint32_t register_struct_size);

/************************************************************************/
/* 处理子管理器依赖                                                      */
/************************************************************************/
cp_module_manager_register_t* cp_add_sub_manager_dependent(cp_app_t *app, 
	cp_module_manager_register_t* module_manager_register, cp_uint32_t register_struct_size);

/************************************************************************/
/* 处理模块依赖                                                          */
/************************************************************************/
cp_module_register_t* cp_add_module_dependent(cp_app_t *app, 
	cp_int32_t manager_type, cp_module_register_t *module_register, cp_uint32_t register_struct_size);





/************************************************************************/
/* 空的管理器注册器依赖添加回调函数                                       */
/************************************************************************/
cp_module_manager_register_t* cp_add_manager_dependent_callback_null_handle(cp_app_t *app, 
	cp_module_manager_register_t *module_manager_register, cp_uint32_t register_struct_size);

/************************************************************************/
/* 空的模块注册器依赖添加回调函数                                         */
/************************************************************************/
cp_module_register_t* cp_add_module_dependent_callback_null_handle
(cp_app_t *app, cp_int32_t manager_type, cp_module_register_t *module_register, cp_uint32_t register_struct_size);


#endif