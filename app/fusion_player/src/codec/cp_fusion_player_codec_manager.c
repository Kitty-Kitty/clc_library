/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/


/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_fusion_player_codec_manager.h"
#include "cp_include.h"




extern cp_module_register_t  player_codec_module_manager_list[];
extern cp_int32_t player_codec_module_manager_list_size;



//模块创建接口，表示创建一个模块
cp_int32_t init_player_codec_manager(cp_fusion_player_codec_manager_t *manager, const cp_fusion_player_codec_manager_info_t *info);
//模块打开运行接口，在模块init之后，会被调用
cp_int32_t start_player_codec_manager(cp_fusion_player_codec_manager_t *manager, const cp_fusion_player_codec_manager_info_t *info);
//读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留
cp_int32_t stop_player_codec_manager(cp_fusion_player_codec_manager_t *manager);
//设置模块参数
cp_int32_t ctrl_player_codec_manager(cp_fusion_player_codec_manager_t *manager, cp_int32_t optname, const cp_void_t* optval);
//模块创建接口，表示创建一个模块
cp_codec_t* create_player_codec_module(cp_fusion_player_codec_manager_t *manager, const cp_codec_info_t *info);
//模块查询接口，表示从管理器中查询一个模块
cp_codec_t* get_player_codec_module(cp_fusion_player_codec_manager_t *manager, const cp_codec_info_t *info);
//写模块数据，flag为写模式的扩展标志。默认为0，其他为预留
cp_int32_t register_player_codec_module(cp_fusion_player_codec_manager_t *manager, cp_codec_t *codec);
//关闭模块
cp_int32_t cancel_player_codec_module(cp_fusion_player_codec_manager_t *manager, cp_codec_t *codec);
//退出模块
cp_int32_t destroy_player_codec_module(cp_fusion_player_codec_manager_t *manager, cp_codec_t *codec);
//设置模块参数
cp_int32_t ctrl_player_codec_module(cp_fusion_player_codec_manager_t *manager, cp_codec_t *codec, cp_int32_t optname, const cp_void_t* optval);




cp_fusion_player_codec_manager_t* create_player_codec_manager(cp_module_manager_register_t *register_info, cp_app_t *app, cp_fusion_player_codec_manager_info_t *info)
{
	cp_fusion_player_codec_manager_t			*tmp_manager = CP_NULL;


	if (!app || !info) {
		return tmp_manager;
	}

	//配置一个manager 内存空间
	CP_MODULE_MANAGER_MALLOC(tmp_manager, app, cp_fusion_player_codec_manager_t);

	if (tmp_manager) {
		//配置manager信息
		tmp_manager->register_info = *register_info;
		//为设备分配空间
		tmp_manager->pool = cp_create_pool(app);
		//设置各种操作句柄
		CP_MODULE_MANAGER_SET_HANDLERS(tmp_manager, player_codec);
		//初始化模块中的所有队列
		cp_manager_create_register_memory(tmp_manager, CP_LIBRARY_MODULE_MANAGER_MAX_SIZE,
			CP_LIBRARY_MODULE_MANAGER_MAX_SIZE, CP_LIBRARY_MODULE_MAX_SIZE);
	}

	return tmp_manager;
}

cp_int32_t destroy_player_codec_manager(cp_app_t *app, cp_fusion_player_codec_manager_t* manager)
{
	if (!manager) {
		return 0;
	}

	if (manager->pool) {
		cp_destroy_pool(manager->pool);
	}

	CP_MODULE_MANAGER_FREE(manager);

	return 0;
}



//模块创建接口，表示创建一个模块
cp_int32_t init_player_codec_manager(cp_fusion_player_codec_manager_t *manager, const cp_fusion_player_codec_manager_info_t *info)
{
	cp_int32_t										i = 0;
	cp_int32_t										tmp_ret_int = 0;
	cp_char_t										tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };




	for (i = 0; i < player_codec_module_manager_list_size; i++) {
		//设置一个根管理器注册器
		tmp_ret_int = cp_manager_set_sub_manager_register(manager, &player_codec_module_manager_list[i], 1, cp_sizeof(cp_module_register_t));
		if (tmp_ret_int) {
			cp_manager_log(error, manager,
				"init_player_codec_manager() error. set_sub_manager_register() error of [%s] register_struct_size[%d].",
				cp_print_manager_register_info(&player_codec_module_manager_list[i], tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH),
				cp_sizeof(cp_module_register_t));
			return -1;
		}
	}

	return 0;
}
//模块打开运行接口，在模块init之后，会被调用
cp_int32_t start_player_codec_manager(cp_fusion_player_codec_manager_t *manager, const cp_fusion_player_codec_manager_info_t *info)
{
	cp_int32_t										tmp_ret_int = 0;



	//创建管理器注册器
	tmp_ret_int = cp_manager_create_all_sub_manager(manager);
	if (tmp_ret_int) {
		cp_manager_log(error, manager,
			"cp_manager_create_all_sub_manager() error. return [%d]",
			tmp_ret_int);
		return -1;
	}

	//初始化管理器注册器
	tmp_ret_int = cp_manager_init_all_sub_manager(manager);
	if (tmp_ret_int) {
		cp_manager_log(error, manager,
			"cp_manager_init_all_sub_manager() error. return [%d]",
			tmp_ret_int);
		return -1;
	}

	//启动管理器注册器
	tmp_ret_int = cp_manager_start_all_sub_manager(manager);
	if (tmp_ret_int) {
		cp_manager_log(error, manager,
			"cp_manager_start_all_sub_manager() error. return [%d]",
			tmp_ret_int);
		return -1;
	}

	return 0;
}
//读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留
cp_int32_t stop_player_codec_manager(cp_fusion_player_codec_manager_t *manager)
{
	cp_int32_t										tmp_ret_int = 0;



	//创建管理器注册器
	tmp_ret_int = cp_manager_stop_all_sub_manager(manager);
	if (tmp_ret_int) {
		cp_manager_log(error, manager,
			"cp_manager_stop_all_sub_manager() error. return [%d]",
			tmp_ret_int);
		return -1;
	}

	return 0;
}
//设置模块参数
cp_int32_t ctrl_player_codec_manager(cp_fusion_player_codec_manager_t *manager, cp_int32_t optname, const cp_void_t* optval)
{
	return 0;
}
//模块创建接口，表示创建一个模块
cp_codec_t* create_player_codec_module(cp_fusion_player_codec_manager_t *manager, const cp_codec_info_t *info)
{
	return cp_manager_create_module_by_register(manager, info);
}

//模块查询接口，表示从管理器中查询一个模块
cp_codec_t* get_player_codec_module(cp_fusion_player_codec_manager_t *manager, const cp_codec_info_t *info)
{
	return CP_NULL;
}

//写模块数据，flag为写模式的扩展标志。默认为0，其他为预留
cp_int32_t register_player_codec_module(cp_fusion_player_codec_manager_t *manager, cp_codec_t *module)
{
	return 0;
}
//关闭模块
cp_int32_t cancel_player_codec_module(cp_fusion_player_codec_manager_t *manager, cp_codec_t *module)
{
	return 0;
}
//退出模块
cp_int32_t destroy_player_codec_module(cp_fusion_player_codec_manager_t *manager, cp_codec_t *module)
{
	return 0;
}
//设置模块参数
cp_int32_t ctrl_player_codec_module(cp_fusion_player_codec_manager_t *manager, cp_codec_t *module, cp_int32_t optname, const cp_void_t* optval)
{
	return 0;
}

