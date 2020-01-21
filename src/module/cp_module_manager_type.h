/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-05-26

Description: define module information

**************************************************************************/


#ifndef	_CP_MODULE_MANAGER_TYPE_INCLUDE_H_
#define _CP_MODULE_MANAGER_TYPE_INCLUDE_H_



//定义APP的类型编码
#define CP_LIBRARY_APP_TYPE							B32(01000000, 00000000, 00000000, 00000000)
//定义模块管理器类型
#define CP_LIBRARY_MODULE_MANAGER_TYPE				B32(00100000, 00000000, 00000000, 00000000)
//获取模块的类型
#define CP_GET_LIBRARY_TYPE(type)					((type) & B32(11111111, 00000000, 00000000, 00000000))
//获取子模块的类型
#define CP_GET_LIBRARY_MODULE_TYPE(type)			((type) & B32(11111111, 11111111, 00000000, 00000000))
//获取模块真实的类型
#define CP_GET_LIBRARY_REAL_MODULE_TYPE(type)		(((type) & B32(00000000, 11111111, 00000000, 00000000)) >> 16)
//获取子模块真实的类型
#define CP_GET_LIBRARY_SUB_MODULE_TYPE(type)		(((type) & B32(00000000, 00000000, 00000000, 11111111)))





//typedef enum cp_module_manager_type_enum			cp_module_manager_type_e;





/****************************************************************************************************************************************/
/* 这里主要描述模块管理器的类型：																											*/
/* 1、其中类型使用情况说明																												*/
/*		其中B32(00000000, 00000000, 00000000, 00000000)的4字节分别使用   																	*/
/*		其中B32(xxxxxxxx, 00000000, 00000000, 00000000)的xxxxxxxxx部分描述系统主模块类型，例如APP模块、模块管理器、模块						*/
/*		其中B32(00000000, xxxxxxxx, 00000000, 00000000)的xxxxxxxxx部分描述系统主模块下的子模块类型，例如模块管理器下的pool、timer				*/
/*		其中B32(00000000, 00000000, xxxxxxxx, 00000000)的xxxxxxxxx部分为预留内容，暂时不使用												*/
/*		其中B32(00000000, 00000000, 00000000, xxxxxxxx)的xxxxxxxxx部分为子模块下的重载实现，类似memory_pool属于pool;libuv_socket属于socket	*/
/* 2、主模块类型取值说明																													*/
/*		在类型数值中B32(01000000, 00000000, 00000000, 00000000)指定位置使能位1表示APP模块   												*/
/*		在类型数值中B32(00100000, 00000000, 00000000, 00000000)指定位置使能位1表示模块管理器												*/
/*		在类型数值中B32(00010000, 00000000, 00000000, 00000000)指定位置使能位1表示模块														*/
/* 3、模块关系图：																														*/
/*		3.1、模块的关系图：																												*/
/*			app->root_module_manager_register					（根模块管理器注册器）													*/
/*			app->root_module_manager_array						（根模块管理器）															*/
/*					|																													*/
/*					--->module_manager->module_manager_register				(根模块管理器下的子模块管理器注册器)							*/
/*					--->module_manager->module_managers						(根模块管理器下的子模块管理器)									*/
/*					--->module_manager->module_register						(根模块管理器下的子模块注册器，根据配置时指定)					*/
/*											|																							*/
/*											--->sub_module_manager->module_register		(子模块管理器下的子模块注册器，根据配置时指定)		*/
/*											--->sub_module_manager->modules				(子模块管理器下的子模块)							*/
/****************************************************************************************************************************************/

typedef enum cp_module_manager_type_enum
{
	/*该部分定义基础模块类型*/
	cp_module_manager_type_begin	= CP_LIBRARY_MODULE_MANAGER_TYPE,
	cp_module_manager_type_pool		= CP_LIBRARY_MODULE_MANAGER_TYPE | (B8(00000001) << 16),
	cp_module_manager_type_timer	= CP_LIBRARY_MODULE_MANAGER_TYPE | (B8(00000010) << 16),
	cp_module_manager_type_thread	= CP_LIBRARY_MODULE_MANAGER_TYPE | (B8(00000011) << 16),

	/*该部分定义扩展模块类型*/
	//新模块类型插入点...
	cp_module_manager_type_hook		= CP_LIBRARY_MODULE_MANAGER_TYPE | (B8(00000100) << 16),
	cp_module_manager_type_session	= CP_LIBRARY_MODULE_MANAGER_TYPE | (B8(00000101) << 16),
	cp_module_manager_type_process	= CP_LIBRARY_MODULE_MANAGER_TYPE | (B8(00000110) << 16),
	cp_module_manager_type_filter	= CP_LIBRARY_MODULE_MANAGER_TYPE | (B8(00000111) << 16),
	cp_module_manager_type_func		= CP_LIBRARY_MODULE_MANAGER_TYPE | (B8(00001000) << 16),
	cp_module_manager_type_socket	= CP_LIBRARY_MODULE_MANAGER_TYPE | (B8(00001001) << 16),
	cp_module_manager_type_codec	= CP_LIBRARY_MODULE_MANAGER_TYPE | (B8(00001010) << 16),
	cp_module_manager_type_dev		= CP_LIBRARY_MODULE_MANAGER_TYPE | (B8(00001011) << 16),


	cp_module_manager_type_extend	= CP_LIBRARY_MODULE_MANAGER_TYPE | (B8(00001100) << 16),
	//请不要在end后定义内容
	cp_module_manager_type_end		= CP_LIBRARY_MODULE_MANAGER_TYPE | (B8(00010000) << 16)
}cp_module_manager_type_e;



/************************************************************************/
/* 添加各个模块类型的定义                                                */
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


