/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/


#include "cp_string.h"
#include "cp_app_core.h"
#include "cp_module_manager_function.h"



cp_char_t *print_manager_register_info_f(cp_module_manager_register_t *manager_register, cp_char_t *buf, cp_int32_t len)
{
	char				tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };


	if (!manager_register || !buf || !len) {
		return buf;
	}
	cp_memset(buf, 0, len);

	cp_snprintf(buf, len, "manager[ t:%d(%d-%d-%d-%d) | n:%s/%s (%d) | d:%s ]-[%s]",
		manager_register->type,
		CP_GET_LIBRARY_TYPE(manager_register->type) >> 24,
		CP_GET_LIBRARY_REAL_MODULE_TYPE(manager_register->type),
		0,
		CP_GET_LIBRARY_SUB_MODULE_TYPE(manager_register->type),
		manager_register->name,
		cp_version_itoa(manager_register->version, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH),
		manager_register->version,
		manager_register->description,
		CP_VER);
	buf[len - 1] = 0;
	return buf;
}

cp_module_manager_t* _malloc_module_manager(cp_app_t *app, cp_int32_t manager_mem_size, cp_module_info_t *info)
{
	cp_module_manager_t							*tmp_module_manager = CP_NULL;
	cp_pool_t									*tmp_pool = CP_NULL;


	tmp_pool = cp_create_pool_ex(app, (cp_pool_info_t*)info);
	if (!tmp_pool) {
		cp_app_log(error, app, "module malloc() create pool error.");
		return CP_NULL;
	}

	tmp_module_manager = (cp_module_manager_t*)cp_palloc(tmp_pool, cp_sizeof(manager_mem_size));
	if (!tmp_module_manager) {
		cp_destroy_pool(tmp_pool);
		cp_app_log(error, app, "palloc() module error.");
		return CP_NULL;
	}
	cp_memset(tmp_module_manager, 0, cp_sizeof(manager_mem_size));
	tmp_module_manager->pool = tmp_pool;

	return tmp_module_manager;
}

cp_int32_t _free_module_manager(cp_module_manager_t *manager)
{
	if (manager && manager->pool) {
		cp_destroy_pool((manager)->pool);
	}

	return 0;
}

//创建一个模块
cp_module_manager_t* _create_manager(cp_module_manager_register_t *register_info, cp_app_t *app, cp_module_manager_info_t *info)
{
	cp_module_manager_t			*tmp_manager = CP_NULL;
	cp_int32_t					ret_int = 0;
	cp_char_t					tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };



	if (!register_info) {
		return tmp_manager;
	}

	print_manager_register_info_f(register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH);

	if (!register_info->manager_create) {
		cp_app_log(error, app, "create %s error! handle[manager_create = null]",
			tmp_buf);
		return tmp_manager;
	}
	//调用模块注册的创建接口创建模块
	tmp_manager = register_info->manager_create(register_info, app, info);
	if (!tmp_manager) {
		cp_app_log(error, app, "create %s error! return null.",
			tmp_buf);
		return tmp_manager;
	}
	//初始化manager的基础信息
	if (!tmp_manager->register_info.name) {
		tmp_manager->register_info = *register_info;
	}
	//初始化其他信息	
	tmp_manager->app = app;
	tmp_manager->logger = app->logger;
	tmp_manager->conf = app->conf;
	cp_queue_init(&tmp_manager->modules);

	//初始化模块管理互斥量
	ret_int = cp_mutex_init(&tmp_manager->module_mutex);
	if (ret_int) {
		cp_app_log(error, app, "manager [0x%x] %s init module_mutex error! return [%d].",
			tmp_manager,
			tmp_buf,
			ret_int);
		return CP_NULL;
	}
	cp_app_log(notice, app, "create [0x%x] %s success!",
		tmp_manager,
		tmp_buf);

	return tmp_manager;
}

//销毁指定模块
cp_int32_t _destroy_manager(cp_app_t *app, cp_module_manager_t *manager)
{
	cp_int32_t					ret_int = 0;
	cp_char_t					tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };


	if (!manager) {
		return -1;
	}

	print_manager_register_info_f(&(manager->register_info), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH);

	//销毁各个模块管理器
	if (!manager->register_info.manager_destroy) {
		cp_app_log(error, app, "destroy [0x%x] %s error! handle[manager_destroy = null]",
			manager,
			tmp_buf);
		return -1;
	}
	//销毁模块管理器互斥量
	cp_mutex_destroy(&manager->module_mutex);
	//调用句柄进行模块停止
	ret_int = manager->register_info.manager_destroy(app, manager);
	if (ret_int) {
		cp_app_log(error, app, "destroy [0x%x] %s error! return[%d] error.",
			manager,
			tmp_buf,
			ret_int);
		return -2;
	}
	cp_app_log(notice, app, "destroy [0x%x] %s success!",
		manager,
		tmp_buf);
	return 0;
}

//模块创建接口，表示创建一个模块
cp_int32_t _init_manager(cp_module_manager_t *manager, const cp_module_manager_info_t *info)
{
	cp_int32_t					ret_int = 0;
	cp_char_t					tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };

	if (!manager) {
		return -1;
	}
	//初始化参数
	if (info && manager) {
		manager->app = info->app;
		manager->logger = info->app->logger;
		manager->conf = info->app->conf;
	}

	if (!manager->init) {
		cp_log_error(manager->app->logger, "init [0x%x] %s error! handle[init = null]",
			manager,
			print_manager_register_info_f(&(manager->register_info), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		return -2;
	}
	ret_int = manager->init(manager, info);
	if (!ret_int) {
		CP_MODULE_SET_STATUS(manager, cp_module_status_init);
	}
	return ret_int;
}

//模块打开运行接口，在模块init之后，会被调用
cp_int32_t _start_manager(cp_module_manager_t *manager, const cp_module_manager_info_t *info)
{
	cp_int32_t					ret_int = 0;
	cp_char_t					tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };



	if (!manager) {
		return -1;
	}
	//启动用户自动定义接口
	if (!manager->start) {
		cp_log_error(manager->app->logger, "start [0x%x] %s error! handle[start = null]",
			manager,
			print_manager_register_info_f(&(manager->register_info), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		return -2;
	}
	ret_int = manager->start(manager, info);
	if (!ret_int) {
		CP_MODULE_SET_STATUS(manager, cp_module_status_start);
	}
	return ret_int;
}

//读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留
cp_int32_t _stop_manager(cp_module_manager_t *manager)
{
	cp_int32_t					ret_int = 0;
	cp_char_t					tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };


	if (!manager) {
		return -1;
	}
	//停止模块
	if (!manager->stop) {
		cp_log_error(manager->app->logger, "stop [0x%x] %s error! handle[stop = null]",
			manager,
			print_manager_register_info_f(&(manager->register_info), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		return -2;
	}
	ret_int = manager->stop(manager);
	if (!ret_int) {
		CP_MODULE_UNSET_STATUS(manager, cp_module_status_start);
	}
	return ret_int;
}

//设置模块参数
cp_int32_t _ctrl_manager(cp_module_manager_t *manager, cp_int32_t optname, const cp_void_t* optval)
{
	cp_char_t					tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };


	if (!manager) {
		return -1;
	}

	if (!manager->ctrl) {
		cp_log_error(manager->app->logger, "ctrl [0x%x] %s error! handle[ctrl = null]",
			manager,
			print_manager_register_info_f(&(manager->register_info), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		return -2;
	}

	return manager->ctrl(manager, optname, optval);
}

//获取模块管理器
cp_module_manager_t* _get_manager(const cp_app_t *app, const cp_module_manager_info_t *info)
{
	cp_module_manager_t							*tmp_root_manager = CP_NULL;




	if (!info) {
		return CP_NULL;
	}
	if (!app) {
		return CP_NULL;
	}
	if (info->type >= 0 && CP_GET_LIBRARY_REAL_MODULE_TYPE(info->type) <
		CP_GET_LIBRARY_REAL_MODULE_TYPE(cp_module_manager_type_end)) {

		//先找一个root管理器
		tmp_root_manager = *((cp_module_manager_t**)cp_array_get(&app->root_module_manager_array,
			CP_GET_LIBRARY_REAL_MODULE_TYPE(info->type)));
		if (!CP_GET_LIBRARY_SUB_MODULE_TYPE(info->type)) {
			//如果子模块管理器为空，就表示查找的就是根管理器
			return tmp_root_manager;
		}
		//获取子模块管理器
		if (tmp_root_manager) {
			if (CP_GET_LIBRARY_SUB_MODULE_TYPE(info->type) >
				(cp_int32_t)cp_array_max_size(&tmp_root_manager->module_managers)) {
				return CP_NULL;
			}

			return *((cp_module_manager_t**)cp_array_get(&tmp_root_manager->module_managers,
				CP_GET_LIBRARY_SUB_MODULE_TYPE(info->type)));
		}
	}
	return CP_NULL;
}

//模块创建接口，表示创建一个模块
cp_module_t* _manager_create_module(cp_module_manager_t *manager, const cp_module_info_t *info)
{
	if (!manager || !info) {
		return CP_NULL;
	}

	if (manager->create_module) {
		return manager->create_module(manager, info);
	}

	return CP_NULL;
}

//通用模块创建接口，表示创建一个模块
cp_module_t* _manager_create_module_by_register(cp_module_manager_t *manager, const cp_module_info_t *info)
{
	cp_module_t				*tmp_module = CP_NULL;
	cp_module_register_t	*tmp_module_register = CP_NULL;


	if (!manager || !info) {
		return CP_NULL;
	}

	if (!manager->module_register.nelts) {
		return CP_NULL;
	}

	tmp_module_register = _manager_get_module_register(manager, info->type);
	if (tmp_module_register) {
		tmp_module = cp_create_module(tmp_module_register, manager, info);
	}

	return tmp_module;
}

//通用模块创建接口，根据模块type创建一个模块
cp_module_t* _manager_create_module_by_type(cp_module_manager_t *manager, cp_int32_t type)
{
	cp_module_info_t		tmp_module_info = { 0, };


	tmp_module_info.type = type;
	return _manager_create_module_by_register(manager, &tmp_module_info);
}

//查找一个模块接口
cp_module_t* _manager_get_module(cp_module_manager_t *manager, const cp_module_info_t *info)
{
	cp_int32_t				i = 0;
	cp_module_t				*tmp_module = CP_NULL;


	if (!manager || !info) {
		return CP_NULL;
	}
	if (!manager->get_module) {
		return CP_NULL;
	}

	return manager->get_module(manager, info);
}

//写模块数据，flag为写模式的扩展标志。默认为0，其他为预留
cp_int32_t _manager_register_module(cp_module_manager_t *manager, cp_module_t *module)
{
	cp_int32_t				ret_int = 0;


	if (!manager || !module) {
		return -1;
	}

	if (manager->register_module) {
		ret_int = manager->register_module(manager, module);
	}

	if (!ret_int && module && module->queue.next == &module->queue
		&& module->queue.prev == &module->queue) {
		//所有新创建的模块都是添加到队列的尾部
		cp_queue_insert_tail(&manager->modules, &module->queue);
		//设置
		CP_MODULE_SET_STATUS(module, cp_module_status_registed);
	}

	return ret_int;
}

//关闭模块
cp_int32_t _manager_cancel_module(cp_module_manager_t *manager, cp_module_t *module)
{
	cp_int32_t				ret_int = 0;


	if (!manager || !module) {
		return -1;
	}

	if (manager->cancel_module) {
		ret_int = manager->cancel_module(manager, module);
	}

	if (!ret_int && module && module->queue.next != &module->queue
		&& module->queue.prev != &module->queue) {
		if (module->queue.next && module->queue.prev) {
			//删除模块
			cp_queue_remove(&module->queue);
			cp_queue_init(&module->queue);
			CP_MODULE_UNSET_STATUS(module, cp_module_status_registed);
		}
		//cp_memset(&module->queue, 0, cp_sizeof(cp_queue_t));
	}

	return 0;
}

//退出模块
cp_int32_t _manager_destroy_module(cp_module_manager_t *manager, cp_module_t *module)
{
	if (!manager || !module) {
		return -1;
	}

	if (manager->destroy_module) {
		return manager->destroy_module(manager, module);
	}

	return 0;
}

//表示销毁该管理器的所有已经创建的模块
cp_int32_t _manager_destroy_all_module(cp_module_manager_t *manager)
{
	cp_queue_t								*current = CP_NULL;
	cp_module_t								*tmp_module = CP_NULL;



	if (!manager || !manager->destroy_module) {
		return -1;
	}

	//遍历管理器下已经创建的所有子模块
	for (current = cp_queue_next(&manager->modules); current != &manager->modules;
		current = cp_queue_next(&manager->modules)) {
		tmp_module = cp_queue_data(current, cp_module_t, queue);
		cp_manager_destroy_module(manager, tmp_module);
	}

	return 0;
}

//设置模块参数
cp_int32_t _manager_ctrl_module(cp_module_manager_t *manager,
	cp_module_t *module, cp_int32_t optname, const cp_void_t* optval)
{
	if (!manager) {
		return -1;
	}

	if (manager->ctrl_module) {
		return manager->ctrl_module(manager, module, optname, optval);
	}

	return 0;
}

//表示获取根管理器信息
cp_module_manager_t* _manager_get_root_manager(cp_app_t *app, cp_int32_t type)
{
	if (!app || CP_GET_LIBRARY_TYPE(type) != CP_LIBRARY_MODULE_MANAGER_TYPE) {
		return CP_NULL;
	}
	if (CP_GET_LIBRARY_REAL_MODULE_TYPE(type) >=
		(cp_int32_t)cp_array_max_size(&app->root_module_manager_array)) {
		return CP_NULL;
	}

	return *((cp_module_manager_t**)
		cp_array_get(&(app->root_module_manager_array), CP_GET_LIBRARY_REAL_MODULE_TYPE(type)));
}

//表示设备根管理器注册信息
cp_int32_t _manager_set_root_manager(cp_app_t *app, cp_int32_t type)
{
	cp_module_manager_t					*tmp_manager = CP_NULL;
	cp_module_manager_register_t		*tmp_manager_register = CP_NULL;
	cp_module_manager_info_t			tmp_manager_info = { 0, };




	if (!app || CP_GET_LIBRARY_TYPE(type) != CP_LIBRARY_MODULE_MANAGER_TYPE) {
		return -1;
	}
	if (CP_GET_LIBRARY_REAL_MODULE_TYPE(type) >=
		(cp_int32_t)cp_array_max_size(&app->root_module_manager_array)) {
		return -2;
	}
	//判断当前类型的模块管理器是否已经被创建
	tmp_manager = _manager_get_root_manager(app, type);
	if (tmp_manager) {
		//如果已经存在，则不做处理，直接返回成功
		return 0;
	}
	//如果不存在，则需要进行创建操作
	tmp_manager_register = _manager_get_root_manager_register(app, type);
	if (!tmp_manager_register) {
		return -3;
	}
	tmp_manager = cp_create_manager(tmp_manager_register, app, &tmp_manager_info);
	if (!tmp_manager) {
		return -4;
	}

	cp_array_set(&(app->root_module_manager_array),
		&tmp_manager, CP_GET_LIBRARY_REAL_MODULE_TYPE(type));
	return 0;
}

//获取子模块管理器
cp_module_manager_t* _manager_get_sub_manager(cp_module_manager_t *root_manager, cp_int32_t type)
{
	if (!root_manager || CP_GET_LIBRARY_TYPE(type) != CP_LIBRARY_MODULE_MANAGER_TYPE) {
		return CP_NULL;
	}

	if (CP_GET_LIBRARY_SUB_MODULE_TYPE(type) >
		(cp_int32_t)cp_array_max_size(&root_manager->module_managers)) {
		return CP_NULL;
	}

	return *((cp_module_manager_t**)cp_array_get(&root_manager->module_managers,
		CP_GET_LIBRARY_SUB_MODULE_TYPE(type)));
}

//获取管理器下的模块
cp_module_t* _manager_get_sub_module(cp_app_t *app, cp_int32_t manager_type, cp_int32_t module_type)
{
	cp_module_t									*tmp_module = CP_NULL;
	cp_module_manager_t							*tmp_root_manager = CP_NULL;
	cp_module_manager_t							*tmp_manager = CP_NULL;
	cp_module_info_t							tmp_module_info = { 0, };



	//获取根管理器
	tmp_root_manager = _manager_get_root_manager(app, manager_type);
	if (!tmp_root_manager) {
		return NULL;
	}

	//获取音频处理管理器
	tmp_manager = _manager_get_sub_manager(tmp_root_manager, manager_type);
	if (!tmp_manager) {
		return CP_NULL;
	}
	//创建一个处理模块
	CP_MODULE_INFO_SET_TYPE(&tmp_module_info, module_type);
	//先查找一个模块是否存在
	tmp_module = cp_manager_get_module(tmp_manager, &tmp_module_info);
	if (!tmp_module) {
		return CP_NULL;
	}
	return tmp_module;
}

//创建子模块管理器
cp_int32_t _manager_create_all_sub_manager(cp_module_manager_t *root_manager)
{
	cp_int32_t								i = 0;
	cp_void_t								*tmp_mem = CP_NULL;
	cp_module_manager_t						*tmp_manager = CP_NULL;
	cp_module_manager_register_t			**tmp_sub_manager_register = CP_NULL;
	cp_module_manager_info_t				tmp_manager_info = { 0, };
	cp_char_t								tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };



	if (!root_manager) {
		return -1;
	}

	//如果为初始化，则进行初始化处理
	if (!cp_array_is_null(&(root_manager->module_managers))) {
		tmp_mem = cp_palloc(root_manager->pool, (cp_sizeof(cp_module_manager_t*) * CP_LIBRARY_MODULE_MANAGER_MAX_SIZE));
		if (!tmp_mem) {
			cp_manager_log(error, root_manager, "create_all_sub_manager() error! malloc error.");
			return -2;
		}
		cp_memset(tmp_mem, 0, cp_sizeof(cp_module_manager_t*) * CP_LIBRARY_MODULE_MANAGER_MAX_SIZE);
		cp_array_init(&(root_manager->module_managers),
			tmp_mem, cp_sizeof(cp_module_manager_t*), CP_LIBRARY_MODULE_MANAGER_MAX_SIZE);
	}
	//开始创建各个模块管理器
	for (i = 0; i < (cp_int32_t)cp_array_max_size(&(root_manager->module_manager_register)); i++) {
		tmp_sub_manager_register = cp_array_get(&(root_manager->module_manager_register), i);
		if (!(*tmp_sub_manager_register)) {
			//这里判断是否为空，因为第0个可能是空指针，没有被使用，模块都是1开始编号
			continue;
		}

		//准备模块数据
		tmp_manager_info.app = root_manager->app;
		tmp_manager_info.version = (*tmp_sub_manager_register)->version;

		//查看一下是否已经存在，存在则不创建模块管理器
		tmp_manager = *(cp_module_manager_t**)cp_array_get(&(root_manager->module_managers), i);
		if (!tmp_manager) {
			//调用模块注册的创建接口创建模块
			tmp_manager = cp_create_manager((*tmp_sub_manager_register), root_manager->app, &tmp_manager_info);
			if (!tmp_manager) {
				cp_manager_log(error, root_manager, "create_app_all_sub_manager() error! create %s error! return null.",
					cp_print_manager_register_info((*tmp_sub_manager_register), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
				continue;
			}
			else {
				cp_manager_log(notice, root_manager, " create %s success!",
					cp_print_manager_register_info((*tmp_sub_manager_register), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
			}
		}

		//初始化manager的基础信息
		tmp_manager->register_info = *(*tmp_sub_manager_register);

		//创建成功，将模块存在相应的位置
		cp_array_set(&(root_manager->module_managers), &tmp_manager, i);
	}

	return 0;
}

//销毁子模块管理器
cp_int32_t _manager_destroy_all_sub_manager(cp_module_manager_t *root_manager)
{
	cp_int32_t								i = 0;
	cp_int32_t								ret_int = 0;
	cp_module_manager_t						**tmp_sub_manager = CP_NULL;
	cp_char_t								tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };



	if (!root_manager) {
		return -1;
	}

	//开始创建各个模块管理器
	for (i = 0; i <= (cp_int32_t)root_manager->module_managers.nelts; i++) {
		tmp_sub_manager = cp_array_get(&(root_manager->module_managers), i);
		if (!(*tmp_sub_manager)) {
			//这里判断是否为空，因为第0个可能是空指针，没有被使用，模块都是1开始编号
			continue;
		}

		cp_manager_log(notice, root_manager, "cp_destroy_manager() %s ",
			cp_print_manager_register_info(&(*tmp_sub_manager)->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));

		//调用模块注册的创建接口创建模块
		ret_int = cp_destroy_manager(root_manager->app, (*tmp_sub_manager));
		if (ret_int) {
			cp_manager_log(error, root_manager, "cp_destroy_manager() error! manager[0x%x] error! return [%d].",
				(*tmp_sub_manager),
				ret_int);
			continue;
		}
	}

	return 0;
}

//初始化子模块管理器
cp_int32_t _manager_init_all_sub_manager(cp_module_manager_t *root_manager)
{
	cp_int32_t								i = 0;
	cp_int32_t								ret_int = 0;
	cp_module_manager_t						**tmp_sub_manager = CP_NULL;
	cp_module_manager_info_t				tmp_manager_info = { 0, };
	cp_char_t								tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };



	if (!root_manager) {
		return -1;
	}

	//开始创建各个模块管理器
	for (i = 0; i < (cp_int32_t)cp_array_max_size(&(root_manager->module_managers)); i++) {
		tmp_sub_manager = cp_array_get(&(root_manager->module_managers), i);
		if (!(*tmp_sub_manager)) {
			//这里判断是否为空，因为第0个可能是空指针，没有被使用，模块都是1开始编号
			continue;
		}

		//准备模块数据
		tmp_manager_info.app = root_manager->app;

		//调用模块注册的创建接口创建模块
		ret_int = cp_init_manager((*tmp_sub_manager), &tmp_manager_info);
		if (ret_int) {
			cp_manager_log(error, root_manager, "init_app_sub_manager() error! create %s error! return null.",
				cp_print_manager_register_info(&(*tmp_sub_manager)->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
			continue;
		}
		cp_manager_log(notice, root_manager, "init %s success!",
			cp_print_manager_register_info(&(*tmp_sub_manager)->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
	}

	return 0;
}

//启动子模块管理器
cp_int32_t _manager_start_all_sub_manager(cp_module_manager_t *root_manager)
{
	cp_int32_t								i = 0;
	cp_int32_t								ret_int = 0;
	cp_module_manager_t						**tmp_sub_manager = CP_NULL;
	cp_module_manager_info_t				tmp_manager_info = { 0, };
	cp_char_t								tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };



	if (!root_manager) {
		return -1;
	}

	//开始创建各个模块管理器
	for (i = 0; i < (cp_int32_t)cp_array_max_size(&(root_manager->module_managers)); i++) {
		tmp_sub_manager = cp_array_get(&(root_manager->module_managers), i);
		if (!(*tmp_sub_manager)) {
			//这里判断是否为空，因为第0个可能是空指针，没有被使用，模块都是1开始编号
			continue;
		}

		//准备模块数据
		tmp_manager_info.app = root_manager->app;

		//调用模块注册的创建接口创建模块
		ret_int = cp_start_manager((*tmp_sub_manager), &tmp_manager_info);
		if (ret_int) {
			cp_manager_log(error, root_manager, "cp_start_manager() error! create %s error! return [%d].",
				cp_print_manager_register_info(&(*tmp_sub_manager)->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH),
				ret_int);
			continue;
		}
		cp_manager_log(notice, root_manager, "start %s success!",
			cp_print_manager_register_info(&(*tmp_sub_manager)->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
	}

	return 0;
}

//停止子模块管理器
cp_int32_t _manager_stop_all_sub_manager(cp_module_manager_t *root_manager)
{
	cp_int32_t								i = 0;
	cp_int32_t								ret_int = 0;
	cp_module_manager_t						**tmp_sub_manager = CP_NULL;
	cp_module_manager_info_t				tmp_manager_info = { 0, };
	cp_char_t								tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };



	if (!root_manager) {
		return -1;
	}

	//开始创建各个模块管理器
	for (i = 0; i < (cp_int32_t)cp_array_max_size(&(root_manager->module_managers)); i++) {
		tmp_sub_manager = cp_array_get(&(root_manager->module_managers), i);
		if (!(*tmp_sub_manager)) {
			//这里判断是否为空，因为第0个可能是空指针，没有被使用，模块都是1开始编号
			continue;
		}

		//准备模块数据
		tmp_manager_info.app = root_manager->app;

		//调用模块注册的创建接口创建模块
		ret_int = cp_stop_manager((*tmp_sub_manager));
		if (ret_int) {
			cp_manager_log(error, root_manager, "cp_stop_manager() error! create %s error! return [%d].",
				cp_print_manager_register_info(&(*tmp_sub_manager)->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH),
				ret_int);
			continue;
		}
		cp_manager_log(notice, root_manager, "stop %s success!",
			cp_print_manager_register_info(&(*tmp_sub_manager)->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
	}

	return 0;
}
