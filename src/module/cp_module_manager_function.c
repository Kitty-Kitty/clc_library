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

//����һ��ģ��
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
	//����ģ��ע��Ĵ����ӿڴ���ģ��
	tmp_manager = register_info->manager_create(register_info, app, info);
	if (!tmp_manager) {
		cp_app_log(error, app, "create %s error! return null.",
			tmp_buf);
		return tmp_manager;
	}
	//��ʼ��manager�Ļ�����Ϣ
	if (!tmp_manager->register_info.name) {
		tmp_manager->register_info = *register_info;
	}
	//��ʼ��������Ϣ	
	tmp_manager->app = app;
	tmp_manager->logger = app->logger;
	tmp_manager->conf = app->conf;
	cp_queue_init(&tmp_manager->modules);

	//��ʼ��ģ���������
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

//����ָ��ģ��
cp_int32_t _destroy_manager(cp_app_t *app, cp_module_manager_t *manager)
{
	cp_int32_t					ret_int = 0;
	cp_char_t					tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };


	if (!manager) {
		return -1;
	}

	print_manager_register_info_f(&(manager->register_info), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH);

	//���ٸ���ģ�������
	if (!manager->register_info.manager_destroy) {
		cp_app_log(error, app, "destroy [0x%x] %s error! handle[manager_destroy = null]",
			manager,
			tmp_buf);
		return -1;
	}
	//����ģ�������������
	cp_mutex_destroy(&manager->module_mutex);
	//���þ������ģ��ֹͣ
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

//ģ�鴴���ӿڣ���ʾ����һ��ģ��
cp_int32_t _init_manager(cp_module_manager_t *manager, const cp_module_manager_info_t *info)
{
	cp_int32_t					ret_int = 0;
	cp_char_t					tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };

	if (!manager) {
		return -1;
	}
	//��ʼ������
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

//ģ������нӿڣ���ģ��init֮�󣬻ᱻ����
cp_int32_t _start_manager(cp_module_manager_t *manager, const cp_module_manager_info_t *info)
{
	cp_int32_t					ret_int = 0;
	cp_char_t					tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };



	if (!manager) {
		return -1;
	}
	//�����û��Զ�����ӿ�
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

//��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��
cp_int32_t _stop_manager(cp_module_manager_t *manager)
{
	cp_int32_t					ret_int = 0;
	cp_char_t					tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };


	if (!manager) {
		return -1;
	}
	//ֹͣģ��
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

//����ģ�����
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

//��ȡģ�������
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

		//����һ��root������
		tmp_root_manager = *((cp_module_manager_t**)cp_array_get(&app->root_module_manager_array,
			CP_GET_LIBRARY_REAL_MODULE_TYPE(info->type)));
		if (!CP_GET_LIBRARY_SUB_MODULE_TYPE(info->type)) {
			//�����ģ�������Ϊ�գ��ͱ�ʾ���ҵľ��Ǹ�������
			return tmp_root_manager;
		}
		//��ȡ��ģ�������
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

//ģ�鴴���ӿڣ���ʾ����һ��ģ��
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

//ͨ��ģ�鴴���ӿڣ���ʾ����һ��ģ��
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

//ͨ��ģ�鴴���ӿڣ�����ģ��type����һ��ģ��
cp_module_t* _manager_create_module_by_type(cp_module_manager_t *manager, cp_int32_t type)
{
	cp_module_info_t		tmp_module_info = { 0, };


	tmp_module_info.type = type;
	return _manager_create_module_by_register(manager, &tmp_module_info);
}

//����һ��ģ��ӿ�
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

//дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��
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
		//�����´�����ģ�鶼����ӵ����е�β��
		cp_queue_insert_tail(&manager->modules, &module->queue);
		//����
		CP_MODULE_SET_STATUS(module, cp_module_status_registed);
	}

	return ret_int;
}

//�ر�ģ��
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
			//ɾ��ģ��
			cp_queue_remove(&module->queue);
			cp_queue_init(&module->queue);
			CP_MODULE_UNSET_STATUS(module, cp_module_status_registed);
		}
		//cp_memset(&module->queue, 0, cp_sizeof(cp_queue_t));
	}

	return 0;
}

//�˳�ģ��
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

//��ʾ���ٸù������������Ѿ�������ģ��
cp_int32_t _manager_destroy_all_module(cp_module_manager_t *manager)
{
	cp_queue_t								*current = CP_NULL;
	cp_module_t								*tmp_module = CP_NULL;



	if (!manager || !manager->destroy_module) {
		return -1;
	}

	//�������������Ѿ�������������ģ��
	for (current = cp_queue_next(&manager->modules); current != &manager->modules;
		current = cp_queue_next(&manager->modules)) {
		tmp_module = cp_queue_data(current, cp_module_t, queue);
		cp_manager_destroy_module(manager, tmp_module);
	}

	return 0;
}

//����ģ�����
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

//��ʾ��ȡ����������Ϣ
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

//��ʾ�豸��������ע����Ϣ
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
	//�жϵ�ǰ���͵�ģ��������Ƿ��Ѿ�������
	tmp_manager = _manager_get_root_manager(app, type);
	if (tmp_manager) {
		//����Ѿ����ڣ���������ֱ�ӷ��سɹ�
		return 0;
	}
	//��������ڣ�����Ҫ���д�������
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

//��ȡ��ģ�������
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

//��ȡ�������µ�ģ��
cp_module_t* _manager_get_sub_module(cp_app_t *app, cp_int32_t manager_type, cp_int32_t module_type)
{
	cp_module_t									*tmp_module = CP_NULL;
	cp_module_manager_t							*tmp_root_manager = CP_NULL;
	cp_module_manager_t							*tmp_manager = CP_NULL;
	cp_module_info_t							tmp_module_info = { 0, };



	//��ȡ��������
	tmp_root_manager = _manager_get_root_manager(app, manager_type);
	if (!tmp_root_manager) {
		return NULL;
	}

	//��ȡ��Ƶ���������
	tmp_manager = _manager_get_sub_manager(tmp_root_manager, manager_type);
	if (!tmp_manager) {
		return CP_NULL;
	}
	//����һ������ģ��
	CP_MODULE_INFO_SET_TYPE(&tmp_module_info, module_type);
	//�Ȳ���һ��ģ���Ƿ����
	tmp_module = cp_manager_get_module(tmp_manager, &tmp_module_info);
	if (!tmp_module) {
		return CP_NULL;
	}
	return tmp_module;
}

//������ģ�������
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

	//���Ϊ��ʼ��������г�ʼ������
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
	//��ʼ��������ģ�������
	for (i = 0; i < (cp_int32_t)cp_array_max_size(&(root_manager->module_manager_register)); i++) {
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
				cp_manager_log(error, root_manager, "create_app_all_sub_manager() error! create %s error! return null.",
					cp_print_manager_register_info((*tmp_sub_manager_register), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
				continue;
			}
			else {
				cp_manager_log(notice, root_manager, " create %s success!",
					cp_print_manager_register_info((*tmp_sub_manager_register), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
			}
		}

		//��ʼ��manager�Ļ�����Ϣ
		tmp_manager->register_info = *(*tmp_sub_manager_register);

		//�����ɹ�����ģ�������Ӧ��λ��
		cp_array_set(&(root_manager->module_managers), &tmp_manager, i);
	}

	return 0;
}

//������ģ�������
cp_int32_t _manager_destroy_all_sub_manager(cp_module_manager_t *root_manager)
{
	cp_int32_t								i = 0;
	cp_int32_t								ret_int = 0;
	cp_module_manager_t						**tmp_sub_manager = CP_NULL;
	cp_char_t								tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };



	if (!root_manager) {
		return -1;
	}

	//��ʼ��������ģ�������
	for (i = 0; i <= (cp_int32_t)root_manager->module_managers.nelts; i++) {
		tmp_sub_manager = cp_array_get(&(root_manager->module_managers), i);
		if (!(*tmp_sub_manager)) {
			//�����ж��Ƿ�Ϊ�գ���Ϊ��0�������ǿ�ָ�룬û�б�ʹ�ã�ģ�鶼��1��ʼ���
			continue;
		}

		cp_manager_log(notice, root_manager, "cp_destroy_manager() %s ",
			cp_print_manager_register_info(&(*tmp_sub_manager)->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));

		//����ģ��ע��Ĵ����ӿڴ���ģ��
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

//��ʼ����ģ�������
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

	//��ʼ��������ģ�������
	for (i = 0; i < (cp_int32_t)cp_array_max_size(&(root_manager->module_managers)); i++) {
		tmp_sub_manager = cp_array_get(&(root_manager->module_managers), i);
		if (!(*tmp_sub_manager)) {
			//�����ж��Ƿ�Ϊ�գ���Ϊ��0�������ǿ�ָ�룬û�б�ʹ�ã�ģ�鶼��1��ʼ���
			continue;
		}

		//׼��ģ������
		tmp_manager_info.app = root_manager->app;

		//����ģ��ע��Ĵ����ӿڴ���ģ��
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

//������ģ�������
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

	//��ʼ��������ģ�������
	for (i = 0; i < (cp_int32_t)cp_array_max_size(&(root_manager->module_managers)); i++) {
		tmp_sub_manager = cp_array_get(&(root_manager->module_managers), i);
		if (!(*tmp_sub_manager)) {
			//�����ж��Ƿ�Ϊ�գ���Ϊ��0�������ǿ�ָ�룬û�б�ʹ�ã�ģ�鶼��1��ʼ���
			continue;
		}

		//׼��ģ������
		tmp_manager_info.app = root_manager->app;

		//����ģ��ע��Ĵ����ӿڴ���ģ��
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

//ֹͣ��ģ�������
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

	//��ʼ��������ģ�������
	for (i = 0; i < (cp_int32_t)cp_array_max_size(&(root_manager->module_managers)); i++) {
		tmp_sub_manager = cp_array_get(&(root_manager->module_managers), i);
		if (!(*tmp_sub_manager)) {
			//�����ж��Ƿ�Ϊ�գ���Ϊ��0�������ǿ�ָ�룬û�б�ʹ�ã�ģ�鶼��1��ʼ���
			continue;
		}

		//׼��ģ������
		tmp_manager_info.app = root_manager->app;

		//����ģ��ע��Ĵ����ӿڴ���ģ��
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
