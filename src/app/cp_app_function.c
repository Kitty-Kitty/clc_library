/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#if defined(__linux__)
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/signal.h>
#endif

#include "cp_app_function.h"
#include "cp_utils.h"
#include "cp_daemon.h"



//�����ػ���Ϣ
CP_EXTERN_GLOBAL_APP_DAEMON();



//��ӡapp��Ϣ��ָ���Ļ�����
cp_char_t *print_app_info(cp_app_info_t *app_info, cp_char_t *buf, cp_int32_t len)
{
	char				tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };


	if (!buf || !len) {
		return buf;
	}
	cp_memset(buf, 0, len);
	cp_snprintf(buf, len, "app[ t:%d(%d-%d-%d-%d) | n:%s/%s (%d) | d:%s ]-[%s]",
		app_info->type,
		CP_GET_LIBRARY_TYPE(app_info->type) >> 24,
		CP_GET_LIBRARY_REAL_MODULE_TYPE(app_info->type),
		0,
		CP_GET_LIBRARY_SUB_MODULE_TYPE(app_info->type),
		app_info->name,
		cp_version_itoa(app_info->version, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH),
		app_info->version,
		app_info->description,
		CP_VER);

	return buf;
}

//��ʼ��app
cp_int32_t init_app(cp_app_t *app, cp_app_info_t *app_info)
{
	cp_int32_t			ret_int = 0;



	//��ʼ�������ļ���Ϣ
	ret_int = init_app_config(app, app_info);
	if (ret_int) {
		cp_log_printf("init configure failed!");
		return ret_int;
	}
	//��ʼ����־����Ϣ
	ret_int = init_app_log(app, app_info);
	if (ret_int) {
		cp_log_printf("init log failed!");
		return ret_int;
	}
	//����ģ��
	ret_int = create_app_root_manager(app, app->root_module_manager_register.elts, cp_array_max_size(&app->root_module_manager_register));
	if (ret_int) {
		cp_app_log(error, app, "init_app() error! create_app_root_manager() error!");
		return ret_int;
	}

	return 0;
}

//����app
cp_int32_t start_app(cp_app_t *app, cp_app_info_t *app_info)
{
	cp_int32_t			ret_int = 0;



	//����ģ����Ϣ
	ret_int = start_app_manager(app, cp_array_get_elts(&app->root_module_manager_array),
		cp_array_length(&app->root_module_manager_array));
	if (ret_int) {
		cp_app_log(error, app, "start_app() error! start_app_manager() error!");
		return ret_int;
	}

	//����daemon
	ret_int = start_daemon_signal_thread(app);
	if (ret_int) {
		cp_app_log(error, app, "start_app() error! start_daemon_signal_thread() error!");
		return ret_int;
	}
	else {
		cp_app_log(notice, app, "start_daemon_signal_thread() success!");
	}

	return 0;
}

//ֹͣapp
cp_int32_t stop_app(cp_app_t *app)
{
	cp_int32_t			ret_int = 0;



	//ֹͣģ����Ϣ
	ret_int = stop_app_manager(app, cp_array_get_elts(&app->root_module_manager_array),
		cp_array_length(&app->root_module_manager_array));
	if (ret_int) {
		cp_app_log(error, app, "stop_app() error! stop_app_manager() error!");
		return ret_int;
	}
	//����ģ��������Ϣ
	ret_int = destroy_app_config(app);
	if (ret_int) {
		cp_app_log(error, app, "stop_app() error! destroy_app_config() error!");
		return ret_int;
	}
	//����ģ����־��Ϣ
	ret_int = destroy_app_log(app);
	if (ret_int) {
		cp_app_log(error, app, "stop_app() error! destroy_app_log() error!");
		return ret_int;
	}
	return 0;
}

//��ʾ��ȡ��ǰ��appָ��
cp_app_t *get_app()
{
	return cp_global_daemon_info->app;
}

//��ʼ��app�����ļ���Ϣ
cp_int32_t init_app_config(cp_app_t *app, cp_app_info_t *app_info)
{
	cp_int32_t			ret_int = 0;
	cp_char_t			*tmp_env_conf = CP_NULL;
	cp_char_t			*tmp_entry_conf = CP_NULL;



	//���ж��Ƿ�������entry_config_path
	if (cp_strlen(app_info->entry_config_path)) {
		tmp_entry_conf = app_info->entry_config_path;
		cp_log_printf("app_config used app_info [entry_config_path = %s] ", tmp_entry_conf);
	}
	else {
		//û�������û�������
		tmp_env_conf = cp_get_set_null_env(CP_DEFAULT_ENV_CP_CONF_FILE, CP_DEFAULT_CONF_FILE);
		if (!(tmp_env_conf)) {
			cp_log_printf("cp_get_env_conf error!");
			return -1;
		}
		tmp_entry_conf = tmp_env_conf;
		cp_log_printf("app_config used env_info [entry_config_path = %s] ", tmp_entry_conf);
	}

	app->conf = cp_conf_create(app);
	if (!(app->conf)) {
		cp_log_printf("cp_conf_create error!");
		return -1;
	}

	ret_int = cp_conf_init(app->conf, app, tmp_entry_conf);
	if (ret_int) {
		cp_log_printf("cp_conf_init error!");
		return -1;
	}

	return ret_int;
}

//����app�����ļ�
cp_int32_t destroy_app_config(cp_app_t *app)
{
	int			ret_int = 0;


	ret_int = cp_conf_destroy(app->conf);
	if (ret_int) {
		cp_log_printf("cp_conf_destroy error!");
		return -1;
	}
	return 0;
}

//��ʼ����־��Ϣ
cp_int32_t init_app_log(cp_app_t *app, cp_app_info_t *app_info)
{
	cp_int32_t			ret_int = 0;



	app->logger = cp_log_create();
	if (!(app->logger)) {
		cp_log_printf("cp_log_create error!");
		return -1;
	}

	ret_int = cp_log_init(app->logger, app->conf);
	if (ret_int) {
		cp_log_printf("log init error");
		return -2;
	}

	app->conf->logger = app->logger;
	return ret_int;
}

cp_int32_t destroy_app_log(cp_app_t *app)
{
	cp_int32_t			ret_int = 0;


	if (app && app->logger) {
		ret_int = app->logger->log_stop(app->logger, 0, CP_NULL);
		if (ret_int) {
			cp_log_printf("log stop error!");
			return 0;
		}
		ret_int = cp_log_destroy(app->logger);
		if (ret_int) {
			cp_log_printf("cp_log_destroy error!");
			return -1;
		}
	}
	
	return 0;
}



//����ģ���������ע��������ռ�
cp_int32_t create_app_root_register_memory(cp_app_t *app, cp_int32_t size)
{
	cp_void_t								*tmp_mem = CP_NULL;



	if (!app) {
		return -1;
	}
	//����ģ�����������������һ��ָ�����飬���������������ָ���ַ
	tmp_mem = cp_mpalloc(app->mpool, (cp_sizeof(cp_module_manager_register_t*) * size));
	if (!tmp_mem) {
		cp_app_log(error, app, 
			"create_app_root_register_memory() error! malloc error. manager_size[%d]",
			size);
		return -1;
	}
	cp_memset(tmp_mem, 0, cp_sizeof(cp_module_manager_register_t*) * size);
	cp_array_init(&(app->root_module_manager_register), tmp_mem, cp_sizeof(cp_module_manager_register_t*), size);
	return 0;
}

//����ģ���������ע��������ռ�
cp_int32_t destroy_app_root_register_memory(cp_app_t *app)
{
	if (!app) {
		return -1;
	}

	return 0;
}

//��Ҫ������������
cp_int32_t create_app_root_manager(cp_app_t *app, cp_module_manager_register_t **manager_register, cp_int32_t manager_size)
{
	cp_int32_t								i = 0;
	cp_void_t								*tmp_mem = CP_NULL;
	cp_module_manager_t						*tmp_manager = CP_NULL;
	cp_module_manager_info_t				tmp_manager_info = { 0, };
	cp_char_t								tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };



	if (!app) {
		return -1;
	}
	if (!manager_register || !manager_size) {
		cp_app_log(error, app, "create_app_root_manager() error! app[%p] manager_register[%p] manager_size[%d]",
			app,
			manager_register,
			manager_size);
		return -2;
	}
	//����ģ�����������������һ��ָ�����飬���������������ָ���ַ
	tmp_mem = cp_mpalloc(app->mpool, (cp_sizeof(cp_module_manager_t*) * CP_GET_LIBRARY_REAL_MODULE_TYPE(cp_module_manager_type_end)));
	if (!tmp_mem) {
		cp_app_log(error, app, "create_app_root_manager() error! malloc error. manager_size[%d]",
			manager_size);
		return -3;
	}
	cp_memset(tmp_mem, 0, cp_sizeof(cp_module_manager_t*) * CP_GET_LIBRARY_REAL_MODULE_TYPE(cp_module_manager_type_end));
	cp_array_init(&(app->root_module_manager_array), tmp_mem,
		cp_sizeof(cp_module_manager_t*), CP_GET_LIBRARY_REAL_MODULE_TYPE(cp_module_manager_type_end));

	//��ʼ��������ģ�������
	for (i = 0; i < manager_size; i++) {
		if (!manager_register[i]) {
			//�����ж��Ƿ�Ϊ�գ���Ϊ��0�������ǿ�ָ�룬û�б�ʹ�ã�ģ�鶼��1��ʼ���
			continue;
		}

		//׼��ģ������
		tmp_manager_info.app = app;
		tmp_manager_info.version = manager_register[i]->version;

		//�鿴һ���Ƿ��Ѿ����ڣ������򲻴���ģ�������
		tmp_manager = *(cp_module_manager_t**)cp_array_get(&(app->root_module_manager_array), i);
		if (!tmp_manager) {
			//����ģ��ע��Ĵ����ӿڴ���ģ��
			tmp_manager = cp_create_manager(manager_register[i], app, &tmp_manager_info);
			if (!tmp_manager) {
				cp_app_log(error, app, "create_app_root_manager() error! create %s error! return null.",
					cp_print_manager_register_info(manager_register[i], tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
				continue;
			}
		}

		//��ʼ��manager�Ļ�����Ϣ
		tmp_manager->register_info = *manager_register[i];

		//�����ɹ�����ģ�������Ӧ��λ��
		cp_array_set(&(app->root_module_manager_array), &tmp_manager, i);
		// 		cp_app_log(notice, app, "create %s success!",
		// 			cp_print_manager_register_info(manager_register[i], tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
	}
	return 0;
}
//������ģ�������
cp_int32_t create_app_all_sub_manager(cp_app_t *app)
{
	cp_int32_t								i = 0;
	cp_int32_t								tmp_ret_int = 0;
	cp_module_manager_t						**tmp_root_manager = CP_NULL;



	if (!app) {
		return -1;
	}

	for (i = 0; i < (cp_int32_t)cp_array_max_size(&app->root_module_manager_array); i++)	{
		tmp_root_manager = cp_array_get(&(app->root_module_manager_array), i);
		if (!(*tmp_root_manager) || !cp_array_is_empty(&(*tmp_root_manager)->module_manager_register)) {
			continue;
		}

		tmp_ret_int = cp_manager_create_all_sub_manager((*tmp_root_manager));
		if (!tmp_ret_int) {
			cp_manager_log(error, (*tmp_root_manager), "cp_manager_create_all_sub_manager() error! return [%d].",
				tmp_ret_int);
			continue;
		}
	}

	return 0;
}
//Ϊ���ڵ㴴����ģ�������
cp_int32_t create_app_root_sub_manager(cp_module_manager_t *root_manager)
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

	//���Ϊ��ʼ��������г�ʼ������
	if (!cp_array_is_null(&(root_manager->module_managers))) {
		tmp_mem = cp_palloc(root_manager->pool, (cp_sizeof(cp_module_manager_t*) * CP_LIBRARY_MODULE_MANAGER_MAX_SIZE));
		if (!tmp_mem) {
			cp_log_error(root_manager->logger, "create_app_all_sub_manager() error! malloc error.");
			return -2;
		}
		cp_memset(tmp_mem, 0, cp_sizeof(cp_module_manager_t*) * CP_LIBRARY_MODULE_MANAGER_MAX_SIZE);
		cp_array_init(&(root_manager->module_managers),
			tmp_mem, cp_sizeof(cp_module_manager_t*), CP_LIBRARY_MODULE_MANAGER_MAX_SIZE);
	}
	//��ʼ��������ģ�������
	for (i = 0; i < (cp_int32_t)cp_array_max_size(&root_manager->module_manager_register); i++) {
		tmp_sub_manager_register = cp_array_get(&(root_manager->module_manager_register), i);
		if (!(*tmp_sub_manager_register)) {
			//�����ж��Ƿ�Ϊ�գ���Ϊ��0�������ǿ�ָ�룬û�б�ʹ�ã�ģ�鶼��1��ʼ���
			continue;
		}

		//׼��ģ������
		tmp_manager_info.app = root_manager->app;
		tmp_manager_info.version = (*tmp_sub_manager_register)->version;

		//�鿴һ���Ƿ��Ѿ����ڣ������򲻴���ģ�������
		tmp_manager = *(cp_module_manager_t**)cp_array_get(&(root_manager->module_managers), i);
		if (!tmp_manager) {
			//����ģ��ע��Ĵ����ӿڴ���ģ��
			tmp_manager = cp_create_manager((*tmp_sub_manager_register), root_manager->app, &tmp_manager_info);
			if (!tmp_manager) {
				cp_log_error(root_manager->logger, "create_app_all_sub_manager() error! create %s error! return null.",
					cp_print_manager_register_info((*tmp_sub_manager_register), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
				continue;
			}
		}

		//��ʼ��manager�Ļ�����Ϣ
		tmp_manager->register_info = *(*tmp_sub_manager_register);

		//�����ɹ�����ģ�������Ӧ��λ��
		cp_array_set(&(root_manager->module_managers), &tmp_manager, i);
		// 		cp_log_notice(root_manager->logger, "create %s success!",
		// 			cp_print_manager_register_info((*tmp_sub_manager_register), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
	}

	return 0;
}
//��ʼ����ģ�������
cp_int32_t init_app_root_manager(cp_app_t *app, cp_module_manager_t **mm_array, cp_int32_t mm_size)
{
	cp_int32_t					i = 0;
	cp_int32_t					ret_int = 0;
	cp_module_manager_info_t	tmp_manager_info = { 0, };
	cp_char_t					tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };



	//��ʼ��������ģ�������
	for (i = 0; i < CP_GET_LIBRARY_REAL_MODULE_TYPE(cp_module_manager_type_end); i++) {
		if (mm_array[i]) {
			//׼��ģ������
			tmp_manager_info.app = app;
			tmp_manager_info.version = mm_array[i]->register_info.version;
			//���ó�ʼ���������ģ���ʼ��
			ret_int = cp_init_manager(mm_array[i], &tmp_manager_info);
			if (ret_int) {
				cp_app_log(error, app, "init_app_root_manager() error! init %s error! return[%d] error.",
					cp_print_manager_register_info(&(mm_array[i]->register_info), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH),
					ret_int);
				continue;
			}
			//����������ģ���������Ϣ
			ret_int = create_app_root_sub_manager(mm_array[i]);
			if (ret_int) {
				cp_log_printf("init_app_root_manager() error. create_app_root_sub_manager() error.");
				return ret_int;
			}
			// 			cp_app_log(notice, app, "init %s success!",
			// 				cp_print_manager_register_info(&(mm_array[i]->register_info), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		}
	}
	return 0;
}

//��ʼ����ģ���������Ϣ
cp_int32_t init_app_sub_manager(cp_app_t *app)
{
	cp_int32_t								i = 0;
	cp_int32_t								ret_int = 0;
	cp_module_manager_t						**tmp_root_manager = CP_NULL;
	cp_char_t								tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };



	if (!app) {
		return -1;
	}

	for (i = 0; i < (cp_int32_t)cp_array_max_size(&app->root_module_manager_array); i++)	{
		tmp_root_manager = cp_array_get(&(app->root_module_manager_array), i);
		if (!(*tmp_root_manager) || !cp_array_is_empty(&(*tmp_root_manager)->module_manager_register)) {
			continue;
		}
		//��ʼ��������ģ�������
		ret_int = cp_manager_init_all_sub_manager((*tmp_root_manager));
		if (ret_int) {
			cp_manager_log(error, (*tmp_root_manager), "cp_manager_init_all_sub_manager() error! create %s error! return [%d].",
				cp_print_manager_register_info(&(*tmp_root_manager)->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH),
				ret_int);
			continue;
		}
		//cp_manager_log(notice, (*tmp_root_manager), "init %s success!",
		//	cp_print_manager_register_info(&(*tmp_root_manager)->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
	}

	return 0;
}

//������ģ�������
cp_int32_t start_app_root_manager(cp_app_t *app, cp_module_manager_t **mm_array, cp_int32_t mm_size)
{
	cp_int32_t					i = 0;
	cp_int32_t					ret_int = 0;
	cp_module_manager_info_t	tmp_manager_info = { 0, };
	cp_char_t					tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };



	//��ʼ��������ģ�������
	for (i = 0; i < CP_GET_LIBRARY_REAL_MODULE_TYPE(cp_module_manager_type_end); i++) {
		if (mm_array[i]) {
			//׼��ģ������
			tmp_manager_info.app = app;
			tmp_manager_info.version = mm_array[i]->register_info.version;
			//���������������ģ������
			ret_int = cp_start_manager(mm_array[i], &tmp_manager_info);
			if (ret_int) {
				cp_app_log(error, app, "start_app_manager() error! start %s error! return[%d] error.",
					cp_print_manager_register_info(&(mm_array[i]->register_info), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH),
					ret_int);
				continue;
			}
			// 			cp_app_log(notice, app, "start %s success!",
			// 				cp_print_manager_register_info(&(mm_array[i]->register_info), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		}
	}
	return 0;
}

//������ģ�������
cp_int32_t start_app_sub_manager(cp_app_t *app)
{
	cp_int32_t								i = 0;
	cp_int32_t								ret_int = 0;
	cp_module_manager_t						**tmp_root_manager = CP_NULL;
	cp_char_t								tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };



	if (!app) {
		return -1;
	}

	for (i = 0; i < (cp_int32_t)cp_array_max_size(&app->root_module_manager_array); i++)	{
		tmp_root_manager = cp_array_get(&(app->root_module_manager_array), i);
		if (!(*tmp_root_manager) || !cp_array_is_empty(&(*tmp_root_manager)->module_manager_register)) {
			continue;
		}
		//��ʼ��������ģ�������
		ret_int = cp_manager_start_all_sub_manager((*tmp_root_manager));
		if (ret_int) {
			cp_manager_log(error, (*tmp_root_manager), "cp_manager_start_all_sub_manager() error! create %s error! return [%d].",
				cp_print_manager_register_info(&(*tmp_root_manager)->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH),
				ret_int);
			continue;
		}
	}

	return 0;
}

//ֹͣ���еĸ�ģ�������
cp_int32_t stop_app_root_manager(cp_app_t *app, cp_module_manager_t **mm_array, cp_int32_t mm_size)
{
	cp_int32_t					i = 0;
	cp_int32_t					ret_int = 0;
	cp_char_t					tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };


	if (!mm_array || !mm_size) {
		return 0;
	}

	//��ʼ��������ģ�������
	for (i = 0; i < CP_GET_LIBRARY_REAL_MODULE_TYPE(cp_module_manager_type_end); i++) {
		if (!mm_array[0]) {
			continue;
		}
		//���þ������ģ��ֹͣ
		ret_int = cp_stop_manager(mm_array[i]);
		if (ret_int) {
			cp_app_log(error, app, "stop_app_manager() error! stop %s error! return[%d] error.",
				cp_print_manager_register_info(&(mm_array[i]->register_info), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH),
				ret_int);
			continue;
		}
// 		cp_app_log(notice, app, "stop %s success!",
// 			cp_print_manager_register_info(&(mm_array[i]->register_info), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
	}
	return 0;
}

//����˵��: ֹͣ���е���ģ�������
cp_int32_t stop_app_sub_manager(cp_app_t *app)
{
	cp_int32_t								i = 0;
	cp_int32_t								ret_int = 0;
	cp_module_manager_t						**tmp_root_manager = CP_NULL;
	cp_char_t								tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };



	if (!app) {
		return -1;
	}

	for (i = 0; i < (cp_int32_t)cp_array_max_size(&app->root_module_manager_array); i++)	{
		tmp_root_manager = cp_array_get(&(app->root_module_manager_array), i);
		if (!(*tmp_root_manager) || !cp_array_is_empty(&(*tmp_root_manager)->module_manager_register)) {
			continue;
		}
		ret_int = cp_manager_stop_all_sub_manager((*tmp_root_manager));
		if (ret_int) {
			cp_manager_log(error, (*tmp_root_manager), "cp_manager_stop_all_sub_manager() error! create %s error! return [%d].",
				cp_print_manager_register_info(&(*tmp_root_manager)->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH),
				ret_int);
			continue;
		}

// 		cp_app_log(notice, app, "stop all sub manager for %s success!",
// 			cp_print_manager_register_info(&((*tmp_root_manager)->register_info), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
	}

	return 0;
}


/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: destroy_app_root_manager
*
* ����˵��: �������еĸ�ģ�������
*
* ��    ��: cp_app_t * app						[in]����˵��
* ��    ��: cp_module_manager_t * * mm_array						[in]����˵��
* ��    ��: cp_int32_t mm_size						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-08-21 15:31:06
******************************************************************************************************/
cp_int32_t destroy_app_root_manager(cp_app_t *app, cp_module_manager_t **mm_array, cp_int32_t mm_size)
{
	cp_int32_t					i = 0;
	cp_int32_t					ret_int = 0;
	cp_char_t					tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };



	if (!mm_array || !mm_size) {
		return 0;
	}

	//���ٸ���ģ�������
	//1�����������ٷ�pool manager
	for (i = 0; i < CP_GET_LIBRARY_REAL_MODULE_TYPE(cp_module_manager_type_end); i++) {
		if (mm_array[i] && cp_module_manager_type_pool != mm_array[i]->register_info.type) {
			//ret_int = cp_manager_destroy_all_sub_manager(mm_array[i]->)
			//���þ������ģ��ֹͣ
			ret_int = cp_destroy_manager(app, mm_array[i]);
			if (ret_int) {
				cp_app_log(error, app, "destroy_app_manager() error! destroy %s error! return[%d] error.",
					cp_print_manager_register_info(&(mm_array[i]->register_info), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH),
					ret_int);
				continue;
			}
			// 		cp_log_debug(app->logger, "destroy %s success!",
			// 			cp_print_manager_register_info(&(mm_array[i]->register_info), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		}
	}

	//���ٸ���ģ�������
	//2��������pool manager����
	for (i = 0; i < CP_GET_LIBRARY_REAL_MODULE_TYPE(cp_module_manager_type_end); i++) {
		if (mm_array[i] && cp_module_manager_type_pool == mm_array[i]->register_info.type) {
			//���þ������ģ��ֹͣ
			ret_int = cp_destroy_manager(app, mm_array[i]);
			if (ret_int) {
				cp_app_log(error, app, "destroy_app_manager() error! destroy %s error! return[%d] error.",
					cp_print_manager_register_info(&(mm_array[i]->register_info), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH),
					ret_int);
				continue;
			}
			// 		cp_log_debug(app->logger, "destroy %s success!",
			// 			cp_print_manager_register_info(&(mm_array[i]->register_info), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		}
	}

	//cp_free(mm_array);
	return 0;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: destroy_app_sub_manager
*
* ����˵��: �������е���ģ�������
*
* ��    ��: cp_app_t * app						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-08-21 15:31:32
******************************************************************************************************/
cp_int32_t destroy_app_sub_manager(cp_app_t *app)
{
	cp_int32_t								i = 0;
	cp_int32_t								ret_int = 0;
	cp_module_manager_t						**tmp_root_manager = CP_NULL;
	cp_char_t								tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };



	if (!app) {
		return -1;
	}

	for (i = 0; i < (cp_int32_t)cp_array_max_size(&app->root_module_manager_array); i++) {
		tmp_root_manager = cp_array_get(&(app->root_module_manager_array), i);
		if (!(*tmp_root_manager) || !cp_array_is_empty(&(*tmp_root_manager)->module_manager_register)) {
			continue;
		}
		ret_int = cp_manager_destroy_all_sub_manager((*tmp_root_manager));
		if (ret_int) {
			cp_manager_log(error, (*tmp_root_manager), "cp_manager_destroy_all_sub_manager() error! create %s error! return [%d].",
				cp_print_manager_register_info(&(*tmp_root_manager)->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH),
				ret_int);
			continue;
		}
	}

	return 0;
}

//��ʼ��app
cp_int32_t init_app_manager(cp_app_t *app, cp_module_manager_t **mm_array, cp_int32_t mm_size)
{
	cp_int32_t						ret_int = 0;


	//��ʼ����ģ�������
	ret_int = init_app_root_manager(app, mm_array, mm_size);
	if (ret_int) {
		cp_app_log(error, app, "init_app_root_manager() error! ");
		return ret_int;
	}

	//��ʼ����ģ���������Ϣ
	ret_int = init_app_sub_manager(app);
	if (ret_int) {
		cp_app_log(error, app, "init_app_sub_manager() error! ");
		return ret_int;
	}

	return 0;
}
//�������app
cp_int32_t start_app_manager(cp_app_t *app, cp_module_manager_t **mm_array, cp_int32_t mm_size)
{
	cp_int32_t						ret_int = 0;


	//������ģ�������
	ret_int = start_app_root_manager(app, mm_array, mm_size);
	if (ret_int) {
		cp_app_log(error, app, "start_app_root_manager() error! ");
		return ret_int;
	}

	//������ģ���������Ϣ
	ret_int = start_app_sub_manager(app);
	if (ret_int) {
		cp_app_log(error, app, "start_app_sub_manager() error! ");
		return ret_int;
	}

	return 0;
}

cp_int32_t stop_app_manager(cp_app_t *app, cp_module_manager_t **mm_array, cp_int32_t mm_size)
{
	cp_int32_t						ret_int = 0;


	//ֹͣ��ģ���������Ϣ
	ret_int = stop_app_sub_manager(app);
	if (ret_int) {
		cp_app_log(error, app, "stop_app_sub_manager() error! ");
		return ret_int;
	}

	//ֹͣ��ģ�������
	ret_int = stop_app_root_manager(app, mm_array, mm_size);
	if (ret_int) {
		cp_app_log(error, app, "stop_app_root_manager() error! ");
		return ret_int;
	}

	return 0;
}

cp_int32_t destroy_app_manager(cp_app_t *app, cp_module_manager_t **mm_array, cp_int32_t mm_size)
{
	cp_int32_t						ret_int = 0;


	//������ģ���������Ϣ
	ret_int = destroy_app_sub_manager(app);
	if (ret_int) {
		cp_app_log(error, app, "destroy_app_sub_manager() error! ");
		return ret_int;
	}

	//���ٸ�ģ�������
	ret_int = destroy_app_root_manager(app, mm_array, mm_size);
	if (ret_int) {
		cp_app_log(error, app, "destroy_app_root_manager() error! ");
		return ret_int;
	}

	return 0;
}

cp_int32_t start_daemon_signal_thread(cp_app_t *app)
{
	cp_int32_t			tmp_ret_int = 0;
	cp_char_t			tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };


	if (cp_global_daemon_info) {
		cp_global_daemon_info->signal_thread = cp_create_thread(app, cp_global_daemon_info->signal_thread_cb, app);
		if (!cp_global_daemon_info->signal_thread) {
			cp_app_log(fatal, app, "cp_create_thread() error!");

#if defined(__linux__)
			tmp_ret_int = kill(cp_global_daemon_info->master_pid, SIGQUIT);
			if (tmp_ret_int < 0) {
				cp_app_log(fatal, app,
					"start_daemon_signal_thread() failed. stop cp_app[%s]. master process[%d] is exit. worker process[%d] is exit. kill() return[%d] failed",
					cp_print_app_info(app->app_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH),
					cp_global_daemon_info->master_pid,
					cp_global_daemon_info->work_pid,
					tmp_ret_int
					);
			}
			exit(0);
#endif

			return -1;
		}
	}
	return 0;
}
