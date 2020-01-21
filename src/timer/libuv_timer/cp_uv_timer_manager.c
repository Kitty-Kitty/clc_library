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
#include "cp_uv_timer_manager.h"
#include "cp_include.h"




//ģ�鴴���ӿڣ���ʾ����һ��ģ��
cp_int32_t init_uv_timer_manager(cp_uv_timer_manager_t *manager, const cp_uv_timer_manager_info_t *info);
//ģ������нӿڣ���ģ��init֮�󣬻ᱻ����
cp_int32_t start_uv_timer_manager(cp_uv_timer_manager_t *manager, const cp_uv_timer_manager_info_t *info);
//��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��
cp_int32_t stop_uv_timer_manager(cp_uv_timer_manager_t *manager);
//����ģ�����
cp_int32_t ctrl_uv_timer_manager(cp_uv_timer_manager_t *manager, cp_int32_t optname, const cp_void_t* optval);
//ģ�鴴���ӿڣ���ʾ����һ��ģ��
cp_timer_t* create_uv_timer_module(cp_uv_timer_manager_t *manager, const cp_timer_info_t *info);
//ģ���ѯ�ӿڣ���ʾ�ӹ������в�ѯһ��ģ��
cp_timer_t* get_uv_timer_module(cp_uv_timer_manager_t *manager, const cp_timer_info_t *info);
//дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��
cp_int32_t register_uv_timer_module(cp_uv_timer_manager_t *manager, cp_timer_t *timer);
//�ر�ģ��
cp_int32_t cancel_uv_timer_module(cp_uv_timer_manager_t *manager, cp_timer_t *timer);
//�˳�ģ��
cp_int32_t destroy_uv_timer_module(cp_uv_timer_manager_t *manager, cp_timer_t *timer);
//����ģ�����
cp_int32_t ctrl_uv_timer_module(cp_uv_timer_manager_t *manager, cp_timer_t *timer, cp_int32_t optname, const cp_void_t* optval);
//������ʱ��loop
cp_void_t start_uv_timer_manager_loop(cp_void_t *manager);
//Ĭ�ϵĶ�ʱ���ص�����
void uv_timer_manager_timer_callback(uv_timer_t* handle);


cp_uv_timer_manager_t* create_uv_timer_manager(cp_module_manager_register_t *register_info, cp_app_t *app, cp_uv_timer_manager_info_t *info)
{
	cp_uv_timer_manager_t			*tmp_manager = CP_NULL;


	if (!app || !info) {
		return tmp_manager;
	}

	//����һ��manager �ڴ�ռ�
	CP_MODULE_MANAGER_MALLOC(tmp_manager, app, cp_uv_timer_manager_t);

	if (tmp_manager) {
		//����manager��Ϣ
		tmp_manager->register_info = *register_info;
		//Ϊ�豸����ռ�
		tmp_manager->pool = cp_create_pool(app);
		//����һ��loop
		tmp_manager->loop = (uv_loop_t *)cp_palloc(tmp_manager->pool, sizeof(uv_loop_t));
		//���ø��ֲ������
		CP_MODULE_MANAGER_SET_HANDLERS(tmp_manager, uv_timer);
		//��ʼ��ģ���е����ж���
		cp_manager_create_register_memory(tmp_manager, CP_LIBRARY_MODULE_MANAGER_MAX_SIZE,
			CP_LIBRARY_MODULE_MANAGER_MAX_SIZE, CP_LIBRARY_MODULE_MAX_SIZE);
	}	
	return tmp_manager;
}

cp_int32_t destroy_uv_timer_manager(cp_app_t *app, cp_uv_timer_manager_t* manager)
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

//ģ�鴴���ӿڣ���ʾ����һ��ģ��
cp_int32_t init_uv_timer_manager(cp_uv_timer_manager_t *manager, const cp_uv_timer_manager_info_t *info)
{
	//������ģ���������moduleע����Ϣ
	CP_MODULE_DEPENDENT(timer, manager->app);

	//uv_loop_init() ����ʹ��_CrtDumpMemoryLeaks();���ԣ�����32bytes�ֽڵ�й©
	uv_loop_init(manager->loop);

	uv_timer_init(manager->loop, &(manager->uv_timer));
	manager->uv_timer.data = manager;
	manager->times = 0;

	return 0;
}
//ģ������нӿڣ���ģ��init֮�󣬻ᱻ����
cp_int32_t start_uv_timer_manager(cp_uv_timer_manager_t *manager, const cp_uv_timer_manager_info_t *info)
{
	cp_int64_t					tmp_interval = 0;
	cp_char_t					tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };


	//uv_timer_start(&(manager->uv_timer), uv_timer_manager_timer_callback, info->timeout, info->repeat);
	//��ȡϵͳʱ��
	cp_gettimeofday(&manager->app->system_tv, CP_NULL);

	//��ȡ�䴦����
	if (manager->conf) {
		tmp_interval = cp_conf_xml_gettime_ns(manager->conf->conf_xml,
			CP_CONF_STRING_CP_SYSTEM, CP_CONF_STRING_TIMER_RESOLUTION, 0);
		if (tmp_interval <= 0) {
			cp_manager_log(warn, manager,
				"start_uv_timer_manager() warning. cp_conf_xml_gettime_ns() element[%s : %s] value[%d ns] failed! used default[%d ms]",
				CP_CONF_STRING_CP_SYSTEM,
				CP_CONF_STRING_TIMER_RESOLUTION,
				tmp_interval,
				CP_UV_TIMER_MANAGER_DEFAULT_INTERVAL);
			tmp_interval = CP_UV_TIMER_MANAGER_DEFAULT_INTERVAL * CP_CONF_XML_TIME_THOUND * CP_CONF_XML_TIME_THOUND;
		}

		tmp_interval /= (CP_CONF_XML_TIME_THOUND * CP_CONF_XML_TIME_THOUND);
	}
	
	if (tmp_interval <= 0) {
		tmp_interval = CP_UV_TIMER_MANAGER_DEFAULT_INTERVAL;
	}

	//������ʱ��
	uv_timer_start(&(manager->uv_timer), uv_timer_manager_timer_callback, CP_UV_TIMER_MANAGER_BEGIN_INTERVAL, tmp_interval);
	manager->thread = cp_create_thread(manager->app, start_uv_timer_manager_loop, manager);
	if (!manager->thread) {
		cp_log_error(manager->logger, "start %s error!",
			cp_print_manager_register_info(&manager->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		return -1;
	}

	return 0;
}
//��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��
cp_int32_t stop_uv_timer_manager(cp_uv_timer_manager_t *manager)
{
	if (!manager || !manager->loop) {
		return -1;
	}

	uv_timer_stop(&(manager->uv_timer));
	uv_stop(manager->loop);
	uv_loop_close(manager->loop);

	if (manager->thread) {
		cp_thread_join(manager->thread);
		cp_destroy_thread(manager->thread);
	}

	//uv_loop_delete(manager->loop);

	return 0;
}
//����ģ�����
cp_int32_t ctrl_uv_timer_manager(cp_uv_timer_manager_t *manager, cp_int32_t optname, const cp_void_t* optval)
{
	return 0;
}
//ģ�鴴���ӿڣ���ʾ����һ��ģ��
cp_timer_t* create_uv_timer_module(cp_uv_timer_manager_t *manager, const cp_timer_info_t *info)
{
	return CP_NULL;
}
//ģ���ѯ�ӿڣ���ʾ�ӹ������в�ѯһ��ģ��
cp_timer_t* get_uv_timer_module(cp_uv_timer_manager_t *manager, const cp_timer_info_t *info)
{
	return CP_NULL;
}
//дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��
cp_int32_t register_uv_timer_module(cp_uv_timer_manager_t *manager, cp_timer_t *module)
{
	return 0;
}
//�ر�ģ��
cp_int32_t cancel_uv_timer_module(cp_uv_timer_manager_t *manager, cp_timer_t *module)
{
	return 0;
}
//�˳�ģ��
cp_int32_t destroy_uv_timer_module(cp_uv_timer_manager_t *manager, cp_timer_t *module)
{
	return 0;
}
//����ģ�����
cp_int32_t ctrl_uv_timer_module(cp_uv_timer_manager_t *manager, cp_timer_t *module, cp_int32_t optname, const cp_void_t* optval)
{
	return 0;
}

cp_void_t start_uv_timer_manager_loop(cp_void_t *manager)
{
	cp_uv_timer_manager_t			*tmp_manager = (cp_uv_timer_manager_t *)manager;
	uv_run(tmp_manager->loop, UV_RUN_DEFAULT);
	//return 0;
}

void uv_timer_manager_timer_callback(uv_timer_t* handle)
{
	cp_char_t					tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };


	cp_uv_timer_manager_t *manager = (cp_uv_timer_manager_t *)handle->data;

	//��ȡϵͳʱ��
	cp_gettimeofday(&manager->app->system_tv, CP_NULL);

	++(manager->times);
	if (manager->times > CP_MAX_INT) {
		manager->times = 0;
	}

	if (!(manager->times % CP_UV_TIMER_MANAGER_DEFAULT_PRINT_COUNT)) {
		cp_log_notice(manager->logger, "%s timer!",
			cp_print_manager_register_info(&manager->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
	}
}


