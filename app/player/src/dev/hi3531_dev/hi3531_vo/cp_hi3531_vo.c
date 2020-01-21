/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_hi3531_vo.h"
#include "cp_third_party.h"
#include "cp_include.h"
#include "css_status.h"




/*ģ�鴴���ӿڣ���ʾ����һ��ģ��*/
cp_int32_t init_hi3531_vo(cp_hi3531_vo_t *hi3531_vo, const cp_hi3531_vo_info_t *hi3531_vo_info);
/*ģ������нӿڣ���ģ��init֮�󣬻ᱻ����*/
cp_int32_t open_hi3531_vo(cp_hi3531_vo_t *hi3531_vo, const cp_hi3531_vo_info_t *hi3531_vo_info);
/*��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t read_hi3531_vo(cp_hi3531_vo_t *hi3531_vo, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t write_hi3531_vo(cp_hi3531_vo_t *hi3531_vo, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*�ر�ģ��*/
cp_int32_t close_hi3531_vo(cp_hi3531_vo_t *hi3531_vo);
/*�˳�ģ��*/
cp_int32_t exit_hi3531_vo(cp_hi3531_vo_t *hi3531_vo);
/*����ģ�����*/
cp_int32_t set_option_hi3531_vo(cp_hi3531_vo_t *hi3531_vo, cp_int32_t optname, const cp_void_t* optval);
/*��ȡģ�����*/
cp_int32_t get_option_hi3531_vo(cp_hi3531_vo_t *hi3531_vo, cp_int32_t optname, cp_void_t* optval);




/*����һ��ģ��*/
cp_hi3531_vo_t* create_hi3531_vo(cp_module_register_t *register_info, cp_codec_manager_t *manager, cp_hi3531_vo_info_t *info)
{
	cp_int32_t							ret_int = 0;
	cp_hi3531_vo_t						*tmp_module = CP_NULL;
	cp_pool_info_t						tmp_pool_info = { 0, };


	if (!register_info || !manager || !info) {
		return CP_NULL;
	}

	tmp_module = cp_malloc_module(manager, cp_hi3531_vo_t, &tmp_pool_info);
	if (!tmp_module) {
		return CP_NULL;
	}
	CP_MODULE_SET_HANDLERS(tmp_module, hi3531_vo);
	return tmp_module;
}

/*�ͷ�ģ��*/
cp_int32_t destroy_hi3531_vo(cp_codec_manager_t *manager, cp_hi3531_vo_t* hi3531_vo)
{
	if (!manager || !hi3531_vo) {
		return -1;
	}
	cp_free_module(hi3531_vo);
	return 0;
}

/*ģ�鴴���ӿڣ���ʾ����һ��ģ��*/
cp_int32_t init_hi3531_vo(cp_hi3531_vo_t *hi3531_vo,
	const cp_hi3531_vo_info_t *hi3531_vo_info)
{
	cp_int32_t										tmp_ret_int = 0;
	cp_hi3531_dev_vo_configure_t					*tmp_vo_conf = CP_NULL;



	if (!hi3531_vo_info || !hi3531_vo_info->data) {
		return -1;
	}

	//�����豸������Ϣ
	tmp_vo_conf = (cp_hi3531_dev_vo_configure_t *)(hi3531_vo_info->data);
	hi3531_vo->vo_conf = tmp_vo_conf;

	//����vo�ڴ���Ϣ
	tmp_ret_int = hi3531_vo_set_mem_conf(hi3531_vo, tmp_vo_conf);
	if (tmp_ret_int) {
		cp_hi3531_dev_log(error, hi3531_vo, "hi3531_vo_set_mem_conf() failed!");
		return -1;
	}
	else {
		cp_hi3531_dev_log(notice, hi3531_vo, "hi3531_vo_set_mem_conf() successed!");
	}

	//����vo pub������Ϣ
	tmp_ret_int = hi3531_vo_set_pub_attr(hi3531_vo, tmp_vo_conf);
	if (tmp_ret_int) {
		cp_hi3531_dev_log(error, hi3531_vo, "hi3531_vo_set_pub_attr() failed!");
		return -1;
	}
	else {
		cp_hi3531_dev_log(notice, hi3531_vo, "hi3531_vo_set_pub_attr() successed!");
	}

	//����vo dev video layer������Ϣ
	tmp_ret_int = hi3531_vo_set_dev_video_layer(hi3531_vo, tmp_vo_conf);
	if (tmp_ret_int) {
		cp_hi3531_dev_log(error, hi3531_vo, "hi3531_vo_set_dev_video_layer() failed!");
		return -1;
	}
	else {
		cp_hi3531_dev_log(notice, hi3531_vo, "hi3531_vo_set_dev_video_layer() successed!");
	}

	//����vo set channels info������Ϣ
	tmp_ret_int = hi3531_vo_set_channels_conf(hi3531_vo, tmp_vo_conf);
	if (tmp_ret_int) {
		cp_hi3531_dev_log(error, hi3531_vo, "hi3531_vo_set_channels_conf() failed!");
		return -1;
	}
	else {
		cp_hi3531_dev_log(notice, hi3531_vo, "hi3531_vo_set_channels_conf() successed!");
	}

	return 0;
}

/*ģ������нӿڣ���ģ��init֮�󣬻ᱻ����*/
cp_int32_t open_hi3531_vo(cp_hi3531_vo_t *hi3531_vo,
	const cp_hi3531_vo_info_t *hi3531_vo_info)
{
	cp_int32_t										tmp_ret_int = 0;
	cp_hi3531_dev_vo_configure_t					*tmp_vo_conf = CP_NULL;



	if (!hi3531_vo || !hi3531_vo_info || !hi3531_vo_info->data) {
		return -1;
	}

	//�����豸������Ϣ
	tmp_vo_conf = (cp_hi3531_dev_vo_configure_t *)(hi3531_vo_info->data);

	//����vo�豸
	tmp_ret_int = hi3531_vo_start_dev(hi3531_vo, tmp_vo_conf);
	if (tmp_ret_int) {
		cp_hi3531_dev_log(error, hi3531_vo, "hi3531_vo_start_dev() failed!");
		return -1;
	}
	else {
		cp_hi3531_dev_log(notice, hi3531_vo, "hi3531_vo_start_dev() successed!");
	}

	return 0;
}

/*��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t read_hi3531_vo(cp_hi3531_vo_t *hi3531_vo,
	cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{

	return 0;
}

/*дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t write_hi3531_vo(cp_hi3531_vo_t *hi3531_vo,
	const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	if (!buf || !(*buf)) {
		return -1;
	}

	if (cp_sizeof(cp_video_frame_process_t*) != len || !flag) {
		return -2;
	} 

	//��ʾ��ʼдvo��������
	return hi3531_vo_write_frame_data(hi3531_vo, (cp_video_frame_process_t*)(*buf));
}

/*�ر�ģ��*/
cp_int32_t close_hi3531_vo(cp_hi3531_vo_t *hi3531_vo)
{
	cp_int32_t										tmp_ret_int = 0;



	if (!hi3531_vo) {
		return -1;
	}

	//ֹͣvo�豸
	tmp_ret_int = hi3531_vo_stop_dev(hi3531_vo);
	if (tmp_ret_int) {
		cp_hi3531_dev_log(error, hi3531_vo, "hi3531_vo_stop_dev() failed!");
		return -1;
	}
	else {
		cp_hi3531_dev_log(notice, hi3531_vo, "hi3531_vo_stop_dev() successed!");
	}

	return 0;
}

/*�˳�ģ��*/
cp_int32_t exit_hi3531_vo(cp_hi3531_vo_t *hi3531_vo)
{
	return 0;
}

/*����ģ�����*/
cp_int32_t set_option_hi3531_vo(cp_hi3531_vo_t *hi3531_vo, cp_int32_t optname, const cp_void_t* optval)
{
	return 0;
}

cp_int32_t get_option_hi3531_vo(cp_hi3531_vo_t *hi3531_vo, cp_int32_t optname, cp_void_t* optval)
{
	return 0;
}
