/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-08-09

Description:

**************************************************************************/

#ifndef _CP_MODULE_DEPENDENT_INCLUDE_H_
#define _CP_MODULE_DEPENDENT_INCLUDE_H_




#include "cp_register.h"



/************************************************************************/
/* 定义各种处理函数的入口依赖关系                                         */
/************************************************************************/
#define CP_MAIN_MODULE_DEPENDENT_BEGIN(app)											\
	void cp_##app##_main_module_dependent(){									\



/************************************************************************/
/* 定义正确返回的依赖关系                                                */
/************************************************************************/
#define CP_SUB_MODULE_DEPENDENT_BEGIN(app)											\
	void cp_##app##_sub_dependent(){											\




/************************************************************************/
/* 定义各种处理函数的入口依赖关系                                         */
/************************************************************************/
#define CP_MAIN_MODULE_DEPENDENT(app)											\
	cp_##app##_main_module_dependent();											\



/************************************************************************/
/* 添加入口依赖函数                                                      */
/************************************************************************/
#define CP_ADD_MODULE_DEPENDENT(register_type, MODULE_REGISTER_MARCO)				\
		{																			\
				register_type tmp_new_register[] = {MODULE_REGISTER_MARCO};			\
				cp_add_module_dependent(sizeof(register_type), (cp_test_register*)&tmp_new_register[0]);	\
																					\
		}																			\


/************************************************************************/
/* 帧加模块结束                                                         */
/************************************************************************/
#define CP_MODULE_DEPENDENT_END														}				



int cp_add_module_dependent(int register_type_size, cp_test_register* module_register);



#endif