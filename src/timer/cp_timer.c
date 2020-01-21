/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_timer.h"
#include "cp_include.h"



/*ģ�鴴���ӿڣ���ʾ����һ��ģ��*/
cp_int32_t init_timer(cp_timer_t *timer, const cp_timer_info_t *timer_info);
/*ģ������нӿڣ���ģ��init֮�󣬻ᱻ����*/
cp_int32_t open_timer(cp_timer_t *timer, const cp_timer_info_t *timer_info);
/*��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t read_timer(cp_timer_t *timer, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t write_timer(cp_timer_t *timer, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*�ر�ģ��*/
cp_int32_t close_timer(cp_timer_t *timer);
/*�˳�ģ��*/
cp_int32_t exit_timer(cp_timer_t *timer);
/*����ģ�����*/
cp_int32_t set_option_timer(cp_timer_t *timer, cp_int32_t optname, const cp_void_t* optval);
cp_int32_t get_option_timer(cp_timer_t *timer, cp_int32_t optname, cp_void_t* optval);



cp_timer_t *cp_create_timer(const cp_app_t *app)
{
	cp_timer_manager_t			*tmp_manager = CP_NULL;
	cp_module_register_t		*tmp_module_register = CP_NULL;
	cp_timer_info_t				tmp_timer_info;
	cp_module_manager_info_t	tmp_module_manager_info;



	CP_MODULE_MANAGER_INFO_SET_TYPE(&tmp_module_manager_info, CP_MODULE_MANAGER_TYPE_TIMER(1));
	tmp_manager = (cp_timer_manager_t*)cp_get_manager(app, &tmp_module_manager_info);
	if (!tmp_manager) {
		return CP_NULL;
	}
	cp_memset(&tmp_timer_info, 0, cp_sizeof(tmp_timer_info));

	//�����Ȼ�ȡģ���ע����
	tmp_module_register = cp_manager_get_module_register(tmp_manager, CP_MODULE_TYPE_TIMER(1));
	if (!tmp_module_register) {
		return CP_NULL;
	}

	return (cp_timer_t *)cp_create_module(tmp_module_register, tmp_manager, &tmp_timer_info);
}

cp_int32_t cp_start_timer(cp_timer_t *timer, cp_timer_cb timer_cb, cp_uint64_t timeout, cp_uint64_t repeat)
{
	cp_int32_t					ret_int = 0;
	cp_timer_info_t				tmp_timer_info;



	//������Ϣ
	cp_memset(&tmp_timer_info, 0, cp_sizeof(tmp_timer_info));
	tmp_timer_info.timer_cb = timer_cb;
	tmp_timer_info.timeout = timeout;
	tmp_timer_info.repeat = repeat;
	//��ʼ��timer
	ret_int = cp_init_module(timer, &tmp_timer_info);
	if (ret_int) {
		return ret_int;
	}
	//����timer
	return cp_open_module(timer, &tmp_timer_info);
}

cp_int32_t cp_stop_timer(cp_timer_t *timer)
{
	return cp_close_module(timer);
}

cp_int32_t cp_destroy_timer(cp_timer_t *timer)
{
	cp_timer_manager_t				*tmp_manager = CP_NULL;
	cp_module_manager_info_t		tmp_module_manager_info;


	if (!timer) {
		return 0;
	}

	CP_MODULE_MANAGER_INFO_SET_TYPE(&tmp_module_manager_info, cp_module_manager_type_timer);
	tmp_manager = (cp_timer_manager_t*)cp_get_manager(timer->manager->app, &tmp_module_manager_info);

	return cp_destroy_module(tmp_manager, timer);
}


/*ģ�鴴���ӿڣ���ʾ����һ��ģ��*/
cp_int32_t init_timer(cp_timer_t *timer, const cp_timer_info_t *timer_info)
{
	return 0;
}
/*ģ������нӿڣ���ģ��init֮�󣬻ᱻ����*/
cp_int32_t open_timer(cp_timer_t *timer, const cp_timer_info_t *timer_info)
{
	return 0;
}
/*��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t read_timer(cp_timer_t *timer, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}
/*дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t write_timer(cp_timer_t *timer, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}
/*�ر�ģ��*/
cp_int32_t close_timer(cp_timer_t *timer)
{
	return 0;
}
/*�˳�ģ��*/
cp_int32_t exit_timer(cp_timer_t *timer)
{
	return 0;
}
/*����ģ�����*/
cp_int32_t set_option_timer(cp_timer_t *timer, cp_int32_t optname, const cp_void_t* optval)
{
	return 0;
}
cp_int32_t get_option_timer(cp_timer_t *timer, cp_int32_t optname, cp_void_t* optval)
{
	return 0;
}


