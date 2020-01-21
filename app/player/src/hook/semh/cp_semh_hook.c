/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_include.h"
#include "cp_semh_hook.h"
#include "cp_semh_request.h"




cp_semh_hook_t *cp_semh_hook_create();

/*模块创建接口，表示创建一个模块*/
cp_int32_t init_semh_hook(cp_semh_hook_t *semh_hook, const cp_semh_hook_info_t *semh_hook_info);
/*模块打开运行接口，在模块init之后，会被调用*/
cp_int32_t open_semh_hook(cp_semh_hook_t *semh_hook, const cp_semh_hook_info_t *semh_hook_info);
/*读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留*/
cp_int32_t read_semh_hook(cp_semh_hook_t *semh_hook, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*写模块数据，flag为写模式的扩展标志。默认为0，其他为预留*/
cp_int32_t write_semh_hook(cp_semh_hook_t *semh_hook, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*关闭模块*/
cp_int32_t close_semh_hook(cp_semh_hook_t *semh_hook);
/*退出模块*/
cp_int32_t exit_semh_hook(cp_semh_hook_t *semh_hook);
/*设置模块参数*/
cp_int32_t set_option_semh_hook(cp_semh_hook_t *semh_hook, cp_int32_t optname, const cp_void_t* optval);
cp_int32_t get_option_semh_hook(cp_semh_hook_t *semh_hook, cp_int32_t optname, cp_void_t* optval);

cp_int32_t connect_cb_semh_hook(cp_socket_t *socket, cp_int32_t status);										/*连接回调函数*/
cp_int32_t close_cb_semh_hook(cp_socket_t *socket, cp_int32_t status);											/*关闭回调函数*/
cp_int32_t read_cb_semh_hook(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status);	/*读回调函数*/
cp_int32_t write_cb_semh_hook(cp_socket_t *socket, cp_int32_t status);											/*写回调函数*/
cp_int32_t error_cb_semh_hook(cp_socket_t *socket, cp_int32_t status);											/*错误回调函数*/

cp_int32_t cp_open_queue_hook(cp_semh_hook_t *hook, const cp_css_hook_info_t *css_hook_info, cp_queue_t *queue);



cp_semh_hook_t* create_semh_hook(cp_module_register_t *register_info, cp_socket_manager_t *manager, cp_semh_hook_info_t *info)
{
	cp_int32_t							ret_int = 0;
	cp_semh_hook_t						*tmp_module = CP_NULL;
	cp_pool_info_t						tmp_pool_info = { 0, };
	cp_css_hook_register_t				*css_register_info = CP_NULL;



	if (!register_info || !manager || !info) {
		return CP_NULL;
	}
	css_register_info = (cp_css_hook_register_t*)register_info;

	tmp_module = cp_malloc_module(manager, cp_semh_hook_t, &tmp_pool_info);
	if (!tmp_module) {
		return CP_NULL;
	}
	CP_MODULE_SET_HANDLERS(tmp_module, semh_hook);
	CP_SOCKET_MODULE_SET_CALLBACK_HANDLERS(tmp_module, semh_hook);
	CP_INIT_HANDLE_SLAB_FILES(tmp_module);
	tmp_module->command = css_register_info->command;
	tmp_module->hook_handle = css_register_info->hook_hander;
	return tmp_module;
}

cp_int32_t destroy_semh_hook(cp_css_hook_manager_t *manager, cp_semh_hook_t* semh_hook)
{
	if (!manager || !semh_hook) {
		return -1;
	}
	cp_free_module(semh_hook);
	return 0;
}


/*模块创建接口，表示创建一个模块*/
cp_int32_t init_semh_hook(cp_semh_hook_t *semh_hook, const cp_semh_hook_info_t *semh_hook_info)
{
	return 0;
}
/*模块打开运行接口，在模块init之后，会被调用*/
cp_int32_t open_semh_hook(cp_semh_hook_t *semh_hook, const cp_semh_hook_info_t *semh_hook_info)
{
	cp_int32_t					ret_int = 0;
	cp_session_t				*tmp_sesssion = semh_hook_info->session;
	cp_css_hook_stack_t			*tmp_stack;
	cp_char_t					tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };




	//执行当前的函数内容
	if (!semh_hook || !semh_hook_info || !semh_hook->hook_handle) {
		return -1;
	}

	//判断是否超过最大栈数据，防止循环调用问题
	if (tmp_sesssion) {
		++(tmp_sesssion->stack_count);
		if (tmp_sesssion->stack_count > CP_HOOK_MAX_STACK_COUNT) {
			cp_log_error(semh_hook->logger, "module %s stack count[%d] more than [%d] error.",
				print_module_register_info(&semh_hook->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH),
				tmp_sesssion->stack_count,
				CP_HOOK_MAX_STACK_COUNT);
			return -1;
		}
	}
	//先执行入口函数
	ret_int = cp_open_queue_hook(semh_hook, (const cp_css_hook_info_t *)semh_hook_info, &semh_hook->entry);
	if (ret_int) {
		cp_log_error(semh_hook->logger, "module %s process entry queue error.",
			print_module_register_info(&semh_hook->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		return ret_int;
	}
	ret_int = semh_hook->hook_handle((cp_hook_t *)semh_hook, tmp_sesssion, tmp_sesssion->arg);
	if (ret_int) {
		//如果返回错误，则执行错误函数。默认定义为返回0表示正确，返回其他为错误
		ret_int = cp_open_queue_hook(semh_hook, (const cp_css_hook_info_t *)semh_hook_info, &semh_hook->error);
		if (ret_int) {
			cp_log_error(semh_hook->logger, "module %s process error queue error.",
				print_module_register_info(&semh_hook->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
			return ret_int;
		}
	}
	else {
		//如果返回正确，则执行正确函数。默认定义为返回0表示正确，返回其他为错误
		ret_int = cp_open_queue_hook(semh_hook, (const cp_css_hook_info_t *)semh_hook_info, &semh_hook->right);
		if (ret_int) {
			cp_log_error(semh_hook->logger, "module %s process right queue error.",
				print_module_register_info(&semh_hook->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
			return ret_int;
		}
	}

	if (tmp_sesssion && (tmp_sesssion->option & CP_SESSION_OPTION_SET_HISTORY)) {
		//这里的内存统一由内存池声请，释放时统一释放即可
		tmp_stack = cp_palloc(tmp_sesssion->pool, cp_sizeof(cp_css_hook_stack_t));
		if (tmp_stack) {
			//初始化调用信息，并加入历史队列中
			CP_CSS_HOOK_STACK_INIT_FIELDS(tmp_stack);
			CP_CSS_HOOK_STACK_SET_VALUE(tmp_stack, (cp_css_hook_t *)semh_hook, tmp_sesssion, tmp_sesssion->arg);
			cp_queue_insert_tail(&tmp_sesssion->hhsq, &tmp_stack->queue);
		}
	}

	return 0;
}
/*读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留*/
cp_int32_t read_semh_hook(cp_semh_hook_t *semh_hook, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}
/*写模块数据，flag为写模式的扩展标志。默认为0，其他为预留*/
cp_int32_t write_semh_hook(cp_semh_hook_t *semh_hook, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}
/*关闭模块*/
cp_int32_t close_semh_hook(cp_semh_hook_t *semh_hook)
{
	return 0;
}
/*退出模块*/
cp_int32_t exit_semh_hook(cp_semh_hook_t *semh_hook)
{
	return 0;
}
/*设置模块参数*/
cp_int32_t set_option_semh_hook(cp_semh_hook_t *semh_hook, cp_int32_t optname, const cp_void_t* optval)
{
	cp_int32_t							ret_int = 0;
	cp_player_t							*tmp_player = (cp_player_t *)semh_hook->manager->app;
	cp_player_info_t					*tmp_player_info = (cp_player_info_t *)(tmp_player->app_info);



	switch (optname)
	{
	case cp_css_hook_set_option_start_heartbeat:
	{
		//创建一个timer
		semh_hook->timer_task = cp_create_timer(semh_hook->manager->app);
		if (!semh_hook->timer_task) {
			cp_log_error(semh_hook->logger, "set_option_semh_hook() error. cp_create_timer() error.");
			return -1;
		}
		semh_hook->timer_task->data = semh_hook->manager->app;
		ret_int = cp_start_timer(semh_hook->timer_task, cp_semh_timer_task, 
			tmp_player_info->heartbeat_manager.heartbeat_interval_ms, 
			tmp_player_info->heartbeat_manager.heartbeat_interval_ms);
		if (ret_int) {
			cp_log_error(semh_hook->logger, "set_option_semh_hook() error. cp_start_timer() error.");
			return -1;
		}
	}
	break;
	case cp_css_hook_set_option_stop_heartbeat:
	{

	}
	break;
	case cp_css_hook_set_option_send_register:
	{
		//发送注册指令
		send_semh_center_register(semh_hook->manager->app);
	}
	break;
	default:
		cp_log_error(semh_hook->manager->app, "set_option_semh_hook() unknow optname[%d]", optname);
		break;
	}
	return 0;
}
cp_int32_t get_option_semh_hook(cp_semh_hook_t *semh_hook, cp_int32_t optname, cp_void_t* optval)
{
	return 0;
}


cp_int32_t connect_cb_semh_hook(cp_socket_t *socket, cp_int32_t status)
{
	return 0;
}

cp_int32_t close_cb_semh_hook(cp_socket_t *socket, cp_int32_t status)
{
	return 0;
}

cp_int32_t read_cb_semh_hook(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status)
{
	return 0;
}

cp_int32_t write_cb_semh_hook(cp_socket_t *socket, cp_int32_t status)
{
	return 0;
}

cp_int32_t error_cb_semh_hook(cp_socket_t *socket, cp_int32_t status)
{
	return 0;
}

cp_int32_t cp_open_queue_hook(cp_semh_hook_t *hook, const cp_css_hook_info_t *css_hook_info, cp_queue_t *queue)
{
	cp_int32_t								ret_int = 0;
	cp_queue_t								*current;
	cp_css_hook_block_t						*tmp_block;


	for (current = cp_queue_next(queue); current != queue;
		current = cp_queue_next(current)) {
		tmp_block = cp_queue_data(current, cp_css_hook_block_t, queue);
		if (!tmp_block || !tmp_block->hook) {
			continue;
		}
		tmp_block->hook->current_hook = CP_NULL;
		ret_int = cp_open_module(tmp_block->hook, (const cp_module_info_t *)css_hook_info);
		if (tmp_block->hook->current_hook) {
			ret_int = cp_open_module(tmp_block->hook->current_hook, (const cp_module_info_t *)css_hook_info);
		}
	}

	return 0;
}




