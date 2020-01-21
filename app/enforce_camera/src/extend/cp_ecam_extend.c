/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_ecam_extend.h"
#include "cp_third_party.h"
#include "cp_include.h"
#include "css_status.h"



cp_ecam_extend_t *cp_ecam_extend_create();
/*ģ�鴴���ӿڣ���ʾ����һ��ģ��*/
cp_int32_t init_ecam_extend(cp_ecam_extend_t *ecam_extend, const cp_ecam_extend_info_t *ecam_extend_info);
/*ģ������нӿڣ���ģ��init֮�󣬻ᱻ����*/
cp_int32_t open_ecam_extend(cp_ecam_extend_t *ecam_extend, const cp_ecam_extend_info_t *ecam_extend_info);
/*��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t read_ecam_extend(cp_ecam_extend_t *ecam_extend, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t write_ecam_extend(cp_ecam_extend_t *ecam_extend, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*�ر�ģ��*/
cp_int32_t close_ecam_extend(cp_ecam_extend_t *ecam_extend);
/*�˳�ģ��*/
cp_int32_t exit_ecam_extend(cp_ecam_extend_t *ecam_extend);
/*����ģ�����*/
cp_int32_t set_option_ecam_extend(cp_ecam_extend_t *ecam_extend, cp_int32_t optname, const cp_void_t* optval);
cp_int32_t get_option_ecam_extend(cp_ecam_extend_t *ecam_extend, cp_int32_t optname, cp_void_t* optval);



cp_ecam_extend_t* create_ecam_extend(cp_module_register_t *register_info, cp_socket_manager_t *manager, cp_ecam_extend_info_t *info)
{
	cp_int32_t							ret_int = 0;
	cp_ecam_extend_t						*tmp_module = CP_NULL;
	cp_pool_info_t						tmp_pool_info = { 0, };


	if (!register_info || !manager || !info) {
		return CP_NULL;
	}

	tmp_module = cp_malloc_module(manager, cp_ecam_extend_t, &tmp_pool_info);
	if (!tmp_module) {
		return CP_NULL;
	}

	return tmp_module;
}

cp_int32_t destroy_ecam_extend(cp_ecam_extend_manager_t *manager, cp_ecam_extend_t* ecam_extend)
{
	if (!manager || !ecam_extend) {
		return -1;
	}
	cp_free_module(ecam_extend);
	return 0;
}

/*ģ�鴴���ӿڣ���ʾ����һ��ģ��*/
cp_int32_t init_ecam_extend(cp_ecam_extend_t *ecam_extend, const cp_ecam_extend_info_t *ecam_extend_info)
{
	return 0;
}
/*ģ������нӿڣ���ģ��init֮�󣬻ᱻ����*/
cp_int32_t open_ecam_extend(cp_ecam_extend_t *ecam_extend, const cp_ecam_extend_info_t *ecam_extend_info)
{
	return 0;
}
/*��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t read_ecam_extend(cp_ecam_extend_t *ecam_extend, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}
/*дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t write_ecam_extend(cp_ecam_extend_t *ecam_extend, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}
/*�ر�ģ��*/
cp_int32_t close_ecam_extend(cp_ecam_extend_t *ecam_extend)
{
	return 0;
}
/*�˳�ģ��*/
cp_int32_t exit_ecam_extend(cp_ecam_extend_t *ecam_extend)
{
	return 0;
}
/*����ģ�����*/
cp_int32_t set_option_ecam_extend(cp_ecam_extend_t *ecam_extend, cp_int32_t optname, const cp_void_t* optval)
{
	return 0;
}

cp_int32_t get_option_ecam_extend(cp_ecam_extend_t *ecam_extend, cp_int32_t optname, cp_void_t* optval)
{
	return 0;
}

