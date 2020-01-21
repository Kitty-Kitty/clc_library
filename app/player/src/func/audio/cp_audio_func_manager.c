/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_include.h"
#include "cp_audio_func_manager.h"



cp_int32_t	check_audio_module(cp_audio_func_t *func, cp_media_channel_info_t *mci)
{
	if (!func || !mci) {
		return -1;
	}

	//判断媒体ID是否相同
#if 0
	if (func->mci.channel_info.index == mci->channel_info.index &&
		func->mci.group_id == mci->group_id &&
		!cp_strncmp(func->mci.channel_info.play_session, mci->channel_info.play_session, CP_APP_DEFAULT_SESSION_ID_LENGTH) &&
		!cp_strncmp(func->mci.media_info.id, mci->media_info.id, CP_APP_DEFAULT_ID_LENGTH)) {

		return 0;
	}
#endif
	if (!cp_strncmp(func->mci.media_info.id, mci->media_info.id, CP_APP_DEFAULT_ID_LENGTH)) {
		return 0;
	}

	return -1;
}



//模块初始化接口，在模块create之后，会被调用
cp_int32_t init_audio_func_manager(cp_audio_func_manager_t *manager, const cp_audio_func_manager_info_t *info);
//模块打开运行接口，在模块init之后，会被调用
cp_int32_t start_audio_func_manager(cp_audio_func_manager_t *manager, const cp_audio_func_manager_info_t *info);
//读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留
cp_int32_t stop_audio_func_manager(cp_audio_func_manager_t *manager);
//设置模块参数
cp_int32_t ctrl_audio_func_manager(cp_audio_func_manager_t *manager, cp_int32_t optname, const cp_void_t* optval);
//模块初始化接口，在模块create之后，会被调用
cp_audio_func_t* create_audio_func_module(cp_audio_func_manager_t *manager, const cp_audio_func_info_t *info);
//模块查询接口，表示从管理器中查询一个模块
cp_audio_func_t* get_audio_func_module(cp_audio_func_manager_t *manager, const cp_audio_func_info_t *info);
//写模块数据，flag为写模式的扩展标志。默认为0，其他为预留
cp_int32_t register_audio_func_module(cp_audio_func_manager_t *manager, cp_audio_func_t *func);
//关闭模块
cp_int32_t cancel_audio_func_module(cp_audio_func_manager_t *manager, cp_audio_func_t *func);
//退出模块
cp_int32_t destroy_audio_func_module(cp_audio_func_manager_t *manager, cp_audio_func_t *func);
//设置模块参数
cp_int32_t ctrl_audio_func_module(cp_audio_func_manager_t *manager, cp_audio_func_t *func, cp_int32_t optname, const cp_void_t* optval);




cp_audio_func_manager_t* create_audio_func_manager(cp_module_manager_register_t *register_info, cp_app_t *app, cp_audio_func_manager_info_t *info)
{
	cp_audio_func_manager_t			*tmp_manager = CP_NULL;


	if (!app || !info) {
		return tmp_manager;
	}

	//配置一个manager 内存空间
	CP_MODULE_MANAGER_MALLOC(tmp_manager, app, cp_audio_func_manager_t);

	if (tmp_manager) {
		//配置manager信息
		tmp_manager->register_info = *register_info;
		//为设备分配空间
		tmp_manager->pool = cp_create_pool(app);
		//设置各种操作句柄
		CP_MODULE_MANAGER_SET_HANDLERS(tmp_manager, audio_func);
		//初始化模块中的所有队列
		cp_manager_create_register_memory(tmp_manager, CP_LIBRARY_MODULE_MANAGER_MAX_SIZE,
			CP_LIBRARY_MODULE_MANAGER_MAX_SIZE, CP_LIBRARY_MODULE_MAX_SIZE);
	}
	return tmp_manager;
}

cp_int32_t destroy_audio_func_manager(cp_app_t *app, cp_audio_func_manager_t* manager)
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



//模块初始化接口，在模块create之后，会被调用
cp_int32_t init_audio_func_manager(cp_audio_func_manager_t *manager, const cp_audio_func_manager_info_t *info)
{
	cp_void_t										*tmp_p = CP_NULL;
	cp_int32_t										tmp_ret_int = 0;



	tmp_p = cp_palloc(manager->pool, cp_sizeof(cp_audio_func_t*) * CP_AUDIO_FUNC_MAX_NUMBER);
	if (!tmp_p) {
		cp_manager_log(error, manager, "init_audio_func_manager() error. cp_palloc() size[%d] failed!",
			cp_sizeof(cp_audio_func_t*) * CP_AUDIO_FUNC_MAX_NUMBER);
		return -1;
	}
	cp_memset(tmp_p, 0, cp_sizeof(cp_audio_func_t*) * CP_AUDIO_FUNC_MAX_NUMBER);
	cp_array_init(&manager->audio_modules, tmp_p, cp_sizeof(cp_audio_func_t*), CP_AUDIO_FUNC_MAX_NUMBER);
	cp_mutex_init(&manager->vm_mutex);

	//初始化模块消息管理器
	manager->mmm = create_module_message_manager((cp_module_manager_t *)manager);
	if (!manager->mmm) {
		cp_manager_log(error, manager,
			"init_audio_func_manager() error. create_module_message_manager() error.");
		return -2;
	}

	tmp_ret_int = init_module_message_manager((cp_module_manager_t *)manager, manager->mmm);
	if (tmp_ret_int) {
		cp_manager_log(error, manager,
			"init_audio_func_manager() error. init_module_message_manager() error.");
		return -3;
	}

	return 0;
}
//模块打开运行接口，在模块init之后，会被调用
cp_int32_t start_audio_func_manager(cp_audio_func_manager_t *manager, const cp_audio_func_manager_info_t *info)
{
#if 0
	cp_int32_t							i = 0;
	cp_module_register_t				*tmp_module_register = CP_NULL;


	//根据模块注册器，创建各个模块
	for (i = 0; i < cp_array_max_size(&manager->module_register); i++) {
		tmp_module_register = *(cp_module_register_t**)cp_array_get(&manager->module_register, i);
		if (!tmp_module_register) {
			continue;
		}
		cp_create_module(tmp_module_register, manager, info);
	}
#endif
	cp_int32_t										tmp_ret_int = 0;



	tmp_ret_int = start_module_message_manager(manager->mmm);
	if (tmp_ret_int) {
		cp_manager_log(error, manager,
			"start_audio_func_manager() error. start_module_message_manager() error.");
		return -2;
	}
	return 0;
}
//读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留
cp_int32_t stop_audio_func_manager(cp_audio_func_manager_t *manager)
{
	cp_int32_t										tmp_ret_int = 0;



	tmp_ret_int = stop_module_message_manager(manager->mmm);
	if (tmp_ret_int) {
		cp_manager_log(error, manager,
			"stop_audio_func_manager() error. stop_module_message_manager() error.");
		return -2;
	}

	return 0;
}
//设置模块参数
cp_int32_t ctrl_audio_func_manager(cp_audio_func_manager_t *manager, cp_int32_t optname, const cp_void_t* optval)
{
	return 0;
}
//模块初始化接口，在模块create之后，会被调用
cp_audio_func_t* create_audio_func_module(cp_audio_func_manager_t *manager, const cp_audio_func_info_t *info)
{
	return (cp_audio_func_t*)cp_manager_create_module_by_register(manager, info);
}
//模块查询接口，表示从管理器中查询一个模块
cp_audio_func_t* get_audio_func_module(cp_audio_func_manager_t *manager, const cp_audio_func_info_t *info)
{
	cp_int32_t						i = 0;
	cp_int32_t						tmp_find_number = 0;
	cp_int32_t						tmp_number = 0;
	cp_int32_t						tmp_max_size = 0;
	cp_audio_func_t					**tmp_vf = CP_NULL;
	cp_audio_func_t					*tmp_ret_vf = CP_NULL;



	if (!manager || !info || !info->data) {
		return CP_NULL;
	}

	//这里采用遍历查找方式进行处理
	//如果需要优化性能可以
	cp_mutex_lock(&manager->vm_mutex);
	tmp_number = cp_array_length(&manager->audio_modules);
	tmp_max_size = cp_array_max_size(&manager->audio_modules);
	for (i = 0; i < tmp_max_size && tmp_find_number < tmp_number; i++) {
		if (!cp_array_get(&manager->audio_modules, i)) {
			continue;
		}
		tmp_vf = (cp_audio_func_t**)cp_array_get(&manager->audio_modules, i);
		if (!(*tmp_vf)) {
			continue;
		}
		++tmp_find_number;
		if (!check_audio_module((cp_audio_func_t*)(*tmp_vf), (cp_media_channel_info_t*)info->data)) {
			tmp_ret_vf = (*tmp_vf);
			break;
		}
	}
	cp_mutex_unlock(&manager->vm_mutex);
	return tmp_ret_vf;
}
//写模块数据，flag为写模式的扩展标志。默认为0，其他为预留
cp_int32_t register_audio_func_module(cp_audio_func_manager_t *manager, cp_audio_func_t *module)
{
	cp_int32_t						i = 0;
	cp_int32_t						tmp_number = 0;
	cp_int32_t						tmp_max_size = 0;
	cp_int32_t						tmp_ret_int = -1;
	cp_audio_func_t					**tmp_vf = CP_NULL;


	if (!manager || !module) {
		return -1;
	}

	//这里采用遍历查找方式进行处理
	//如果需要优化性能可以
	cp_mutex_lock(&manager->vm_mutex);
	tmp_number = cp_array_length(&manager->audio_modules);
	tmp_max_size = cp_array_max_size(&manager->audio_modules);
	for (i = 0; i < tmp_max_size; i++) {
		if (!cp_array_get(&manager->audio_modules, i)) {
			continue;
		}
		tmp_vf = (cp_audio_func_t**)cp_array_get(&manager->audio_modules, i);
		if (!(*tmp_vf)) {
			cp_array_set(&manager->audio_modules, &module, i);
			tmp_ret_int = 0;
			break;
		}
	}
	cp_mutex_unlock(&manager->vm_mutex);
	return tmp_ret_int;
}
//关闭模块
cp_int32_t cancel_audio_func_module(cp_audio_func_manager_t *manager, cp_audio_func_t *module)
{
	cp_int32_t						i = 0;
	cp_int32_t						tmp_number = 0;
	cp_int32_t						tmp_max_size = 0;
	cp_int32_t						tmp_ret_int = -1;
	cp_audio_func_t					**tmp_vf = CP_NULL;


	if (!manager || !module) {
		return -1;
	}

	//这里采用遍历查找方式进行处理
	//如果需要优化性能可以
	cp_mutex_lock(&manager->vm_mutex);
	tmp_number = cp_array_length(&manager->audio_modules);
	tmp_max_size = cp_array_max_size(&manager->audio_modules);
	for (i = 0; i < tmp_max_size; i++) {
		if (!cp_array_get(&manager->audio_modules, i)) {
			continue;
		}
		tmp_vf = (cp_audio_func_t**)cp_array_get(&manager->audio_modules, i);
		if (module == (*tmp_vf)) {
			tmp_vf = CP_NULL;
			cp_array_set(&manager->audio_modules, &tmp_vf, i);
			tmp_ret_int = 0;
			break;
		}
	}
	cp_mutex_unlock(&manager->vm_mutex);
	return tmp_ret_int;
}
//退出模块
cp_int32_t destroy_audio_func_module(cp_audio_func_manager_t *manager, cp_audio_func_t *module)
{
	return 0;
}
//设置模块参数
cp_int32_t ctrl_audio_func_module(cp_audio_func_manager_t *manager, cp_audio_func_t *module, cp_int32_t optname, const cp_void_t* optval)
{
	return 0;
}





