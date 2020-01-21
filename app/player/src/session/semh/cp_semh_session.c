/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_semh_session.h"
#include "cp_semh_hook_core.h"




cp_semh_session_t *cp_semh_session_create();

/*模块创建接口，表示创建一个模块*/
cp_int32_t init_semh_session(cp_semh_session_t *semh_session, const cp_semh_session_info_t *semh_session_info);
/*模块打开运行接口，在模块init之后，会被调用*/
cp_int32_t open_semh_session(cp_semh_session_t *semh_session, const cp_semh_session_info_t *semh_session_info);
/*读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留*/
cp_int32_t read_semh_session(cp_semh_session_t *semh_session, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*写模块数据，flag为写模式的扩展标志。默认为0，其他为预留*/
cp_int32_t write_semh_session(cp_semh_session_t *semh_session, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*关闭模块*/
cp_int32_t close_semh_session(cp_semh_session_t *semh_session);
/*退出模块*/
cp_int32_t exit_semh_session(cp_semh_session_t *semh_session);
/*设置模块参数*/
cp_int32_t set_option_semh_session(cp_semh_session_t *semh_session, cp_int32_t optname, const cp_void_t* optval);
cp_int32_t get_option_semh_session(cp_semh_session_t *semh_session, cp_int32_t optname, cp_void_t* optval);

cp_int32_t connect_cb_semh_session(cp_socket_t *socket, cp_int32_t status);										/*连接回调函数*/
cp_int32_t close_cb_semh_session(cp_socket_t *socket, cp_int32_t status);											/*关闭回调函数*/
cp_int32_t read_cb_semh_session(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status);	/*读回调函数*/
cp_int32_t write_cb_semh_session(cp_socket_t *socket, cp_int32_t status);											/*写回调函数*/
cp_int32_t error_cb_semh_session(cp_socket_t *socket, cp_int32_t status);											/*错误回调函数*/

//各种操作选项的处理
cp_char_t *option_semh_set_print_information(cp_void_t *emh, cp_char_t *buf, cp_int32_t len);


/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: semh_session_get_semh_hook
*
* 函数说明: semh session从管理器中查询需要的hook
*
* 参    数: cp_semh_session_t * semh_session						[in]参数说明
* 参    数: const cp_semh_session_info_t * semh_session_info						[in]参数说明
* 参    数: cp_int32_t command									[in]参数说明
*
* 返 回 值: cp_hook_t *
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-07-01 16:32:34
******************************************************************************************************/
cp_hook_t *semh_session_get_semh_hook
(cp_semh_session_t *semh_session, const cp_semh_session_info_t *semh_session_info, cp_int32_t command);


/*创建模块*/
cp_semh_session_t* create_semh_session(cp_module_register_t *register_info, cp_socket_manager_t *manager, cp_semh_session_info_t *info)
{
	cp_int32_t							ret_int = 0;
	cp_semh_session_t					*tmp_module = CP_NULL;
	cp_pool_info_t						tmp_pool_info = { 0, };

	

	if (!register_info || !manager || !info) {
		return CP_NULL;
	}

	tmp_module = cp_malloc_module(manager, cp_semh_session_t, &tmp_pool_info);
	if (!tmp_module) {
		return CP_NULL;
	}
	CP_MODULE_SET_HANDLERS(tmp_module, semh_session);
	CP_SOCKET_MODULE_SET_CALLBACK_HANDLERS(tmp_module, semh_session);
	return tmp_module;
}
/*销毁模块*/
cp_int32_t destroy_semh_session(cp_css_session_manager_t *manager, cp_semh_session_t* semh_session)
{
	if (!manager || !semh_session) {
		return -1;
	}
	cp_free_module(semh_session);
	return 0;
}


/*模块创建接口，表示创建一个模块*/
cp_int32_t init_semh_session(cp_semh_session_t *semh_session, const cp_semh_session_info_t *semh_session_info)
{
	cp_css_hook_t							*tmp_hook;
	cp_css_hook_manager_t					*tmp_manager;
	cp_char_t								tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };
	cp_module_info_t						tmp_module_info;
	cp_module_manager_info_t				tmp_module_manager_info;



	//初始化slab数据
	CP_INIT_HANDLE_SLAB_FILES(semh_session);
	//将全局的handle挂载到session中
	//CP_MODULE_MANAGER_INFO_SET_TYPE(&tmp_module_manager_info, cp_module_manager_type_hook);
	CP_MODULE_MANAGER_INFO_SET_TYPE(&tmp_module_manager_info, CP_MODULE_MANAGER_TYPE_HOOK(1));
	tmp_manager = (cp_css_hook_manager_t*)cp_get_manager(CP_NULL, &tmp_module_manager_info);
	if (!tmp_manager) {
		cp_log_error(semh_session->logger, "init session %s error. not found hook manager.",
			print_module_register_info(&semh_session->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		return -1;
	}

	CP_MODULE_INFO_SET_TYPE(&tmp_module_info, cp_css_semh_hook_type_global);
	tmp_hook = (cp_css_hook_t*)cp_manager_get_module(tmp_manager, &tmp_module_info);
	if (!tmp_hook) {
		cp_log_error(semh_session->logger, "init session %s error. ",
			print_module_register_info(&semh_session->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		return -1;
	}
	semh_session->global_hook = (cp_hook_t *)tmp_hook;
	//从hookmanager中复制handle复制handle数据
	//cp_copy_hook(semh_session, tmp_hook);

	return 0;
}
/*模块打开运行接口，在模块init之后，会被调用*/
cp_int32_t open_semh_session(cp_semh_session_t *semh_session, const cp_semh_session_info_t *semh_session_info)
{
	cp_int32_t							ret_int = 0;
	gmp_gmph_semh_t						*tmp_semh = CP_NULL;
	cp_hook_t							*tmp_current_hook = CP_NULL;
	cp_hook_info_t						tmp_hook_info = { 0, };


	//校验数据完整性
	if (!semh_session || !semh_session->socket || !semh_session->buf
		|| !cp_buf_get_length(semh_session->buf)) {
		return -1;
	}
	//校验数据是否合法
	tmp_semh = (gmp_gmph_semh_t*)(cp_buf_get_pos(semh_session->buf));
	if (gmp_gmph_emh_type_semh != tmp_semh->bmh.emht) {
		return -2;
	} else {
		//如果是合法的，则设置session信息；并且格式化打印信息
		semh_session->semh_p = tmp_semh;
		set_option_semh_session(semh_session, cp_module_option_set_print_information, CP_NULL);
	}
	CP_HOOK_INFO_SET_SESSION_INFO(&tmp_hook_info, semh_session, &(semh_session->hhsq));

	//第一次操作的时候是先执行全局的hook
	if (semh_session->global_hook) {
		//如果存在第一个全局函数，则说明入口函数由配置指定，不需要单独实现
		semh_session->current_hook = semh_session->global_hook;
	} else {
		semh_session->current_hook = semh_session_get_semh_hook(semh_session, semh_session_info, tmp_semh->command);
	}
	//根据semh指令查找对应的hook
	//一直循环执行hook
	while (1)
	{
		tmp_current_hook = semh_session->current_hook;
		semh_session->current_hook = CP_NULL;
		if (!tmp_current_hook) {
			break;
		}
		ret_int = cp_open_module(tmp_current_hook, &tmp_hook_info);
		if (ret_int || !semh_session->current_hook) {
			//semh_session->current_hook == tmp_current_hook
			//如果执行失败、下一个hook为空则退出
			break;
		}
	}
	return 0;
}
/*读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留*/
cp_int32_t read_semh_session(cp_semh_session_t *semh_session, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}
/*写模块数据，flag为写模式的扩展标志。默认为0，其他为预留*/
cp_int32_t write_semh_session(cp_semh_session_t *semh_session, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}
/*关闭模块*/
cp_int32_t close_semh_session(cp_semh_session_t *semh_session)
{
	return 0;
}
/*退出模块*/
cp_int32_t exit_semh_session(cp_semh_session_t *semh_session)
{
	return 0;
}
/*设置模块参数*/
cp_int32_t set_option_semh_session(cp_semh_session_t *semh_session, cp_int32_t optname, const cp_void_t* optval)
{
	cp_char_t						*tmp_socket_info_buf = CP_APP_STR_NULL_FLAG;
	cp_char_t						tmp_semh_info_buf[CP_SEMH_SESSION_BUFFER_LENGTH] = { 0, };



	if (!semh_session) {
		return -1;
	}

	switch (optname)
	{
	case cp_module_option_set_print_information:
	{
		//这里生成semh部分信息
		option_semh_set_print_information(semh_session->semh_p, 
			tmp_semh_info_buf, cp_sizeof(tmp_semh_info_buf));

		//这里获取socket部分信息
		if (!cp_set_option_module(semh_session->socket, cp_module_option_set_print_information, CP_NULL)) {
			cp_get_option_module(semh_session->socket, cp_module_option_get_print_information, &tmp_socket_info_buf);
		}
		cp_snprintf(semh_session->semh_si, cp_sizeof(semh_session->semh_si),
			"%s %s",
			tmp_semh_info_buf,
			tmp_socket_info_buf);
	}
	break;
	default:
	{
		cp_log_error(semh_session->logger, "unknow option[%d] type!", optname);
		return -1;
	}
	break;
	}
	return 0;
}
/*获取模块参数*/
cp_int32_t get_option_semh_session(cp_semh_session_t *semh_session, cp_int32_t optname, cp_void_t* optval)
{
	if (!semh_session) {
		return -1;
	}

	switch (optname)
	{
	case cp_module_option_get_print_information:
	{
		*((cp_char_t**)optval) = semh_session->semh_si;
	}
	break;
	default:
	{
		cp_log_error(semh_session->logger, "unknow option[%d] type!", optname);
		return -1;
	}
	break;
	}
	return 0;
}


cp_int32_t connect_cb_semh_session(cp_socket_t *socket, cp_int32_t status)
{
	return 0;
}

cp_int32_t close_cb_semh_session(cp_socket_t *socket, cp_int32_t status)
{
	return 0;
}

cp_int32_t read_cb_semh_session(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status)
{
	return 0;
}

cp_int32_t write_cb_semh_session(cp_socket_t *socket, cp_int32_t status)
{
	return 0;
}

cp_int32_t error_cb_semh_session(cp_socket_t *socket, cp_int32_t status)
{
	return 0;
}

cp_hook_t *semh_session_get_semh_hook(cp_semh_session_t *semh_session, const cp_semh_session_info_t *semh_session_info, cp_int32_t command)
{
	cp_hook_manager_t				*tmp_manager = CP_NULL;
	cp_css_hook_info_t				tmp_css_hoot_info = { 0, };
	cp_module_manager_info_t		tmp_module_manager_info = { 0, };


	if (!semh_session || !semh_session_info) {
		return CP_NULL;
	}

	CP_MODULE_MANAGER_INFO_SET_TYPE(&tmp_module_manager_info, cp_module_manager_type_hook);
	tmp_manager = (cp_hook_manager_t*)cp_get_manager(CP_NULL, &tmp_module_manager_info);
	if (!tmp_manager) {
		return CP_NULL;
	}
	tmp_css_hoot_info.command = command;
	return (cp_hook_t*)cp_manager_get_module(tmp_manager, &tmp_css_hoot_info);
}

cp_char_t *option_semh_set_print_information(cp_void_t *emh, cp_char_t *buf, cp_int32_t len)
{
	return print_gmph_emh(emh, buf, len, cp_true);
}

