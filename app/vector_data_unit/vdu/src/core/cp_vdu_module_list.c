/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

 
#include "cp_vdu_module_list.h"
#include "cp_vdu_module_type.h"





/************************************************************************/
/* 添加各个基础模块管理器的支持                                           */
/************************************************************************/
CP_ROOT_MODULE_MANAGER_DEPENDENT_BEGIN(vdu_app)

CP_ADD_ROOT_MANAGER_DEPENDENT(
	cp_module_manager_register_t,
	CP_MANAGER_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_MANAGER_REGISTER(cp_module_manager_type_pool, 1, "pool_manager", "pool manager", create_pool_manager, destroy_pool_manager));
CP_ADD_ROOT_MANAGER_DEPENDENT(
	cp_module_manager_register_t,
	CP_MANAGER_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_MANAGER_REGISTER(cp_module_manager_type_thread, 1, "thread_manager", "thread manager", create_thread_manager, destroy_thread_manager));
#if 0
CP_ADD_ROOT_MANAGER_DEPENDENT(
	cp_module_manager_register_t,
	CP_MANAGER_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_MANAGER_REGISTER(cp_module_manager_type_timer, 1, "timer_manager", "timer manager", create_timer_manager, destroy_timer_manager));
#endif
CP_ADD_ROOT_MANAGER_DEPENDENT(
	cp_module_manager_register_t,
	CP_MANAGER_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_MANAGER_REGISTER(cp_module_manager_type_func, 1, "func_manager", "func manager", create_func_manager, destroy_func_manager));
CP_ADD_ROOT_MANAGER_DEPENDENT(
	cp_module_manager_register_t,
	CP_MANAGER_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_MANAGER_REGISTER(cp_module_manager_type_codec, 1, "codec_manager", "codec manager", create_codec_manager, destroy_codec_manager));

#if 0
CP_ADD_ROOT_MANAGER_DEPENDENT(
	cp_module_manager_register_t,
	CP_MANAGER_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_MANAGER_REGISTER(cp_module_manager_type_dev, 1, "dev_manager", "dev manager", create_dev_manager, destroy_dev_manager));
#endif

CP_MODULE_MANAGER_DEPENDENT_END()



/************************************************************************/
/* 添加各个子模块管理器的支持                                             */
/************************************************************************/
CP_SUB_MODULE_MANAGER_DEPENDENT_BEGIN(vdu_app)

/////////////////////////////基础管理器/////////////////////////////////////////////
CP_ADD_SUB_MANAGER_DEPENDENT(
	cp_module_manager_register_t,
	CP_MANAGER_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_MANAGER_REGISTER(cp_vdu_manager_type_func, 1, "vdu_func_module_manager", "vdu func module manager", create_vdu_func_manager, destroy_vdu_func_manager));

///////////////////////////////解码器///////////////////////////////////////////
CP_ADD_SUB_MANAGER_DEPENDENT(
	cp_module_manager_register_t,
	CP_MANAGER_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_MANAGER_REGISTER(cp_vdu_manager_type_codec, 1, "vdu_codec_module_manager", "vdu codec module manager", create_vdu_codec_manager, destroy_vdu_codec_manager));

#if 0
CP_ADD_SUB_MANAGER_DEPENDENT(
	cp_module_manager_register_t,
	CP_MANAGER_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_MANAGER_REGISTER(cp_vdu_manager_type_dev, 1, "vdu_dev_module_manager", "vdu dev module manager", create_vdu_dev_manager, destroy_vdu_dev_manager));
#endif

CP_MODULE_MANAGER_DEPENDENT_END()



/************************************************************************/
/* 添加模块的支持                                                        */
/************************************************************************/
CP_MODULE_DEPENDENT_BEGIN(vdu_app)

/////////////////////////////业务处理模块/////////////////////////////////////////////
CP_ADD_MODULE_DEPENDENT(
	cp_module_register_t,
	cp_vdu_manager_type_func,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_REGISTER(cp_vdu_module_type_func, 1, "vdu_func_module", "vdu func module", create_vdu_func, destroy_vdu_func));

/////////////////////////////注册解码器模块/////////////////////////////////////////////
CP_ADD_MODULE_DEPENDENT(
	cp_module_register_t,
	cp_vdu_manager_type_codec,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_REGISTER(cp_vdu_module_type_codec, 1, "vdu_codec_module", "vdu codec module", create_vdu_codec, destroy_vdu_codec));

#if 0
CP_ADD_MODULE_DEPENDENT(
	cp_module_register_t,
	cp_vdu_manager_type_codec,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_REGISTER(cp_vdu_module_type_hi3536_codec, 1, "hi3536_codec_module", "hi3536 codec module", create_hi3536_av_codec, destroy_hi3536_av_codec));
#endif

CP_ADD_MODULE_DEPENDENT(
	cp_module_register_t,
	cp_vdu_manager_type_codec,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_REGISTER(cp_vdu_module_type_qt_svg_codec, 1, "qt_svg_codec_module", "qt_svg codec module", create_qt_svg_codec, destroy_qt_svg_codec));

#if 0
///////////////////////////播放设备模块///////////////////////////////////////////////
CP_ADD_MODULE_DEPENDENT(
	cp_module_register_t,
	cp_vdu_manager_type_dev,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_REGISTER(cp_vdu_module_type_hi3536_dev, 1, "hi3536_module", "hi3536 codec module", create_hi3536_dev, destroy_hi3536_dev));
#endif


CP_MODULE_DEPENDENT_END()



