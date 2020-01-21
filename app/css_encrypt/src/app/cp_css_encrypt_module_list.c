/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

 
#include "cp_css_encrypt_module_list.h"
#include "cp_css_encrypt_module_type.h"





/************************************************************************/
/* 添加各个基础模块管理器的支持                                           */
/************************************************************************/
CP_ROOT_MODULE_MANAGER_DEPENDENT_BEGIN(css_encrypt)

CP_ADD_ROOT_MANAGER_DEPENDENT(
	cp_module_manager_register_t,
	CP_MANAGER_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_MANAGER_REGISTER(cp_module_manager_type_pool, 1, "pool_manager", "pool manager", create_pool_manager, destroy_pool_manager));
CP_ADD_ROOT_MANAGER_DEPENDENT(
	cp_module_manager_register_t,
	CP_MANAGER_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_MANAGER_REGISTER(cp_module_manager_type_thread, 1, "thread_manager", "thread manager", create_thread_manager, destroy_thread_manager));
CP_ADD_ROOT_MANAGER_DEPENDENT(
	cp_module_manager_register_t,
	CP_MANAGER_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_MANAGER_REGISTER(cp_module_manager_type_timer, 1, "timer_manager", "timer manager", create_timer_manager, destroy_timer_manager));
CP_ADD_ROOT_MANAGER_DEPENDENT(
	cp_module_manager_register_t,
	CP_MANAGER_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_MANAGER_REGISTER(cp_module_manager_type_dev, 1, "dev_manager", "dev manager", create_dev_manager, destroy_dev_manager));

CP_MODULE_MANAGER_DEPENDENT_END()



/************************************************************************/
/* 添加各个子模块管理器的支持                                             */
/************************************************************************/
CP_SUB_MODULE_MANAGER_DEPENDENT_BEGIN(css_encrypt)

/////////////////////////////基础管理器/////////////////////////////////////////////
///////////////////////////////解码器///////////////////////////////////////////
CP_ADD_SUB_MANAGER_DEPENDENT(
	cp_module_manager_register_t,
	CP_MANAGER_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_MANAGER_REGISTER(cp_css_encrypt_manager_type_dev, 1, "css_encrypt_dev_module_manager", "css_encrypt dev module manager", create_css_encrypt_dev_manager, destroy_css_encrypt_dev_manager));

CP_MODULE_MANAGER_DEPENDENT_END()



/************************************************************************/
/* 添加模块的支持                                                        */
/************************************************************************/
CP_MODULE_DEPENDENT_BEGIN(css_encrypt)


/////////////////////////////业务处理模块/////////////////////////////////////////////

/////////////////////////////注册解码器模块/////////////////////////////////////////////

///////////////////////////播放设备模块///////////////////////////////////////////////
CP_ADD_MODULE_DEPENDENT(
	cp_module_register_t,
	cp_css_encrypt_manager_type_dev,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_REGISTER(cp_css_encrypt_module_type_hi3531_dev, 1, "hi3531_module", "hi3531 codec module", create_hi3531_dev, destroy_hi3531_dev));

CP_ADD_MODULE_DEPENDENT(
	cp_module_register_t,
	cp_css_encrypt_manager_type_dev,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_REGISTER(cp_css_encrypt_module_type_hi3536_dev, 1, "hi3536_module", "hi3536 codec module", create_hi3536_dev, destroy_hi3536_dev));

CP_MODULE_DEPENDENT_END()



