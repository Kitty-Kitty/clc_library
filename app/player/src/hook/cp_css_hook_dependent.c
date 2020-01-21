/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_log.h"
#include "cp_css_hook_dependent.h"



cp_int32_t cp_css_add_entry_dependent(cp_css_hook_manager_t *manager, cp_css_semh_hook_type_e type, ...)
{
	cp_int32_t								ret_int = 0;
	cp_css_hook_t							*tmp_hook = CP_NULL;
	cp_char_t								tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };
	va_list									tmp_args;


	tmp_hook = (cp_css_hook_t*)manager->hook_array[CP_GET_LIBRARY_SUB_MODULE_TYPE(type)];
	if (!tmp_hook) {
		cp_log_warn(manager->logger, " entry dependent error. module type[%d] not found error.",
			type);
		return -1;
	}
	else {
		cp_log_notice(manager->logger, "starting to add a [entry] dependent. %s ",
			print_module_register_info(&tmp_hook->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
	}

	va_start(tmp_args, type);
	ret_int = cp_css_hook_dependent(manager, tmp_hook, &tmp_hook->entry, &tmp_args);
	ret_int = cp_css_hook_dependent(manager, tmp_hook, &tmp_hook->right, &tmp_args);
	if (ret_int) {
		cp_log_warn(manager->logger, "process add [right] dependent. %s failed!",
			print_module_register_info(&tmp_hook->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
	}
	else {
		cp_log_notice(manager->logger, "process add [right] dependent. %s successed!",
			print_module_register_info(&tmp_hook->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
	}
	va_end(tmp_args);

	return ret_int;
}

cp_int32_t cp_css_add_right_dependent(cp_css_hook_manager_t *manager, cp_css_semh_hook_type_e type, ...)
{
	cp_int32_t								ret_int = 0;
	cp_css_hook_t							*tmp_hook = CP_NULL;
	cp_char_t								tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };
	va_list									tmp_args;


	tmp_hook = (cp_css_hook_t*)manager->hook_array[CP_GET_LIBRARY_SUB_MODULE_TYPE(type)];
	if (!tmp_hook) {
		cp_log_warn(manager->logger, " right dependent error. module type[%d] not found error.",
			type);
		return -1;
	}
	else {
		cp_log_notice(manager->logger, "starting to add a [right] dependent. %s ",
			print_module_register_info(&tmp_hook->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
	}

	va_start(tmp_args, type);
	ret_int = cp_css_hook_dependent(manager, tmp_hook, &tmp_hook->right, &tmp_args);
	if (ret_int) {
		cp_log_warn(manager->logger, "process add [right] dependent. %s failed!",
			print_module_register_info(&tmp_hook->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
	}
	else {
		cp_log_notice(manager->logger, "process add [right] dependent. %s successed!",
			print_module_register_info(&tmp_hook->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
	}
	va_end(tmp_args);

	return ret_int;
}

cp_int32_t cp_css_add_error_dependent(cp_css_hook_manager_t *manager, cp_css_semh_hook_type_e type, ...)
{
	cp_int32_t								ret_int = 0;
	cp_css_hook_t							*tmp_hook = CP_NULL;
	cp_char_t								tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };
	va_list									tmp_args;


	tmp_hook = (cp_css_hook_t*)manager->hook_array[CP_GET_LIBRARY_SUB_MODULE_TYPE(type)];
	if (!tmp_hook) {
		cp_log_warn(manager->logger, " error dependent error. module type[%d] not found error.",
			type);
		return -1;
	}
	else {
		cp_log_notice(manager->logger, "starting to add a [error] dependent. %s ",
			print_module_register_info(&tmp_hook->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
	}

	va_start(tmp_args, type);
	ret_int = cp_css_hook_dependent(manager, tmp_hook, &tmp_hook->error, &tmp_args);
	if (ret_int) {
		cp_log_warn(manager->logger, "process add [error] dependent. %s failed!",
			print_module_register_info(&tmp_hook->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
	}
	else {
		cp_log_notice(manager->logger, "process add [error] dependent. %s successed!",
			print_module_register_info(&tmp_hook->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
	}
	va_end(tmp_args);

	return ret_int;
}

cp_int32_t cp_css_hook_dependent(cp_css_hook_manager_t *manager, cp_css_hook_t *hook, cp_queue_t *queue, va_list *args)
{
	cp_char_t								tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };
	cp_css_semh_hook_type_e					tmp_type = cp_css_semh_hook_type_global;
	cp_css_hook_t							*tmp_hook = CP_NULL;
	cp_css_hook_block_t						*tmp_hook_block;


	while (1)
	{
		tmp_type = va_arg(*args, cp_css_semh_hook_type_e);
		if (cp_css_semh_hook_type_end == tmp_type) {
			cp_log_notice(manager->logger, "%s hook dependent stoped. find a end flag type[%d].",
				print_module_register_info(&hook->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH),
				tmp_type);
			return 0;
		}
		if (!CP_CHECK_CSS_HOOK_TYPE(tmp_type)) {
			cp_log_warn(manager->logger, "%s hook dependent error. type[%d] error.",
				print_module_register_info(&hook->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH),
				tmp_type);
			return -1;
		}
		if (!manager->hook_array[CP_GET_LIBRARY_SUB_MODULE_TYPE(tmp_type)]) {
			cp_log_warn(manager->logger, "%s hook dependent error. module type[%d] not found error.",
				print_module_register_info(&hook->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH),
				tmp_type);
			return -2;
		}
		tmp_hook_block = (cp_css_hook_block_t*)cp_palloc(manager->pool, cp_sizeof(cp_css_hook_block_t));
		if (!tmp_hook_block) {
			cp_log_warn(manager->logger, "%s hook dependent type[%d] error. create [cp_css_hook_block_t] error.",
				print_module_register_info(&hook->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH),
				tmp_type);
			return -3;
		}
		tmp_hook_block->type = tmp_type;
		tmp_hook_block->hook = (cp_css_hook_t *)manager->hook_array[CP_GET_LIBRARY_SUB_MODULE_TYPE(tmp_type)];
		cp_queue_init(&tmp_hook_block->queue);
		cp_queue_insert_tail(queue, &tmp_hook_block->queue);

		cp_log_info(manager->logger, "%s add hook dependent %s successed.",
			print_module_register_info(&hook->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH),
			print_module_register_info(&tmp_hook_block->hook->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
	}

	return 0;
}