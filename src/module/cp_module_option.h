/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/


#ifndef	_CP_MODULE_OPTION_INCLUDE_H_
#define _CP_MODULE_OPTION_INCLUDE_H_



#include "cp_bit.h"
#include "cp_module_core.h"





/************************************************************************/
/* 设置系统                                                              */
/************************************************************************/
//表示设置标志位
#define CP_MODULE_OPTION_SET_FLAG								(B32(00100000, 00000000, 00000000, 00000000))
//表示获取标志位
#define CP_MODULE_OPTION_GET_FLAG								(B32(01000000, 00000000, 00000000, 00000000))





//表示创建设置标志位
#define CP_MODULE_OPTION_MAKE_SET_FLAG(set_optname)				((CP_MODULE_OPTION_SET_FLAG | (set_optname)))
//表示创建获取标志位
#define CP_MODULE_OPTION_MAKE_GET_FLAG(set_optname)				((CP_MODULE_OPTION_GET_FLAG | (set_optname)))
//表示创建两者标志位
#define CP_MODULE_OPTION_MAKE_BOTH_FLAG(set_optname)			((set_optname))





//这里核验SET或者GET标志位，非零表示真；零表示假
#define CP_MODULE_OPTION_CHECK_SET_FLAG(set_optname)			((CP_MODULE_OPTION_SET_FLAG & (set_optname)))
#define CP_MODULE_OPTION_CHECK_GET_FLAG(set_optname)			((CP_MODULE_OPTION_GET_FLAG & (set_optname)))




//typedef	enum cp_module_option_enum								cp_module_option_e;
typedef struct cp_module_option_handle_s						cp_module_option_handle_t;
typedef cp_int32_t(*cp_module_set_option_handle)(cp_module_t *module, cp_int32_t optname, const cp_void_t* optval);
typedef cp_int32_t(*cp_module_get_option_handle)(cp_module_t *module, cp_int32_t optname, cp_void_t* optval);
typedef cp_int32_t(*cp_module_option_error_handle)(cp_module_t *module, cp_int32_t optname, cp_void_t* optval, cp_int32_t status);




typedef	enum cp_module_option_enum {
	cp_module_option_set_print_information = CP_MODULE_OPTION_MAKE_SET_FLAG(CP_MODULE_OPTION_SET_FLAG),

	cp_module_option_get_print_information = CP_MODULE_OPTION_MAKE_GET_FLAG(CP_MODULE_OPTION_GET_FLAG),
}cp_module_option_e;



#pragma pack(1)

/************************************************************************/
/* 表示模块选项处理结构体                                                 */
/* 主要保存各种处理函数                                                   */
/************************************************************************/
struct cp_module_option_handle_s
{
	cp_int32_t													optname;						/*表示选项名称*/
	cp_module_set_option_handle									set_option_handle;				/*表示设置选项处理函数*/
	cp_module_get_option_handle									get_option_handle;				/*表示获取选项处理函数*/
	cp_char_t													*name;							/*表示选项名称*/
	cp_char_t													*description;					/*表示选项描述*/
};


/************************************************************************/
/* 模块注册选项宏信息                                                     */
/************************************************************************/
#define CP_MODULE_OPTION_REGISTER(optname, set_option_handle, get_option_handle, name, description)			\
	{optname, (cp_module_set_option_handle) set_option_handle, (cp_module_get_option_handle) get_option_handle, name, description}



/************************************************************************/
/* 模块注册设置选项宏信息                                                 */
/************************************************************************/
#define CP_MODULE_SET_OPTION_REGISTER(optname, set_option_handle, name, description)						\
	CP_MODULE_OPTION_REGISTER(CP_MODULE_OPTION_MAKE_SET_FLAG(optname), set_option_handle, CP_NULL, name, description)


/************************************************************************/
/* 模块注册获取选项宏信息                                                 */
/************************************************************************/
#define CP_MODULE_GET_OPTION_REGISTER(optname, get_option_handle, name, description)						\
	CP_MODULE_OPTION_REGISTER(CP_MODULE_OPTION_MAKE_GET_FLAG(optname), CP_NULL, get_option_handle, name, description)


/************************************************************************/
/* 模块注册设置和获取两个选项宏信息                                                 */
/************************************************************************/
#define CP_MODULE_BOTH_OPTION_REGISTER(optname, set_option_handle, get_option_handle, name, description)	\
	CP_MODULE_SET_OPTION_REGISTER(optname, set_option_handle, name, description),							\
	CP_MODULE_GET_OPTION_REGISTER(optname, get_option_handle, name, description)							




#pragma pack()


#endif





