/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_hi3531_sdl.h"
#include "cp_third_party.h"
#include "cp_include.h"
#include "css_status.h"


#ifndef PIX_FMT_YUV420P
#define PIX_FMT_YUV420P	AV_PIX_FMT_YUV420P
#endif


/*ģ�鴴���ӿڣ���ʾ����һ��ģ��*/
cp_int32_t init_hi3531_sdl(cp_hi3531_sdl_t *hi3531_sdl, const cp_hi3531_sdl_info_t *hi3531_sdl_info);
/*ģ������нӿڣ���ģ��init֮�󣬻ᱻ����*/
cp_int32_t open_hi3531_sdl(cp_hi3531_sdl_t *hi3531_sdl, const cp_hi3531_sdl_info_t *hi3531_sdl_info);
/*��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t read_hi3531_sdl(cp_hi3531_sdl_t *hi3531_sdl, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t write_hi3531_sdl(cp_hi3531_sdl_t *hi3531_sdl, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*�ر�ģ��*/
cp_int32_t close_hi3531_sdl(cp_hi3531_sdl_t *hi3531_sdl);
/*�˳�ģ��*/
cp_int32_t exit_hi3531_sdl(cp_hi3531_sdl_t *hi3531_sdl);
/*����ģ�����*/
cp_int32_t set_option_hi3531_sdl(cp_hi3531_sdl_t *hi3531_sdl, cp_int32_t optname, const cp_void_t* optval);
cp_int32_t get_option_hi3531_sdl(cp_hi3531_sdl_t *hi3531_sdl, cp_int32_t optname, cp_void_t* optval);




/*����һ��ģ��*/
cp_hi3531_sdl_t* create_hi3531_sdl(cp_module_register_t *register_info, cp_codec_manager_t *manager, cp_hi3531_sdl_info_t *info)
{
	cp_int32_t							ret_int = 0;
	cp_hi3531_sdl_t				*tmp_module = CP_NULL;
	cp_pool_info_t						tmp_pool_info = { 0, };


	if (!register_info || !manager || !info) {
		return CP_NULL;
	}

	tmp_module = cp_malloc_module(manager, cp_hi3531_sdl_t, &tmp_pool_info);
	if (!tmp_module) {
		return CP_NULL;
	}
	CP_MODULE_SET_HANDLERS(tmp_module, hi3531_sdl);
	return tmp_module;
}

/*�ͷ�ģ��*/
cp_int32_t destroy_hi3531_sdl(cp_codec_manager_t *manager, cp_hi3531_sdl_t* hi3531_sdl)
{
	if (!manager || !hi3531_sdl) {
		return -1;
	}
	cp_free_module(hi3531_sdl);
	return 0;
}

/*ģ�鴴���ӿڣ���ʾ����һ��ģ��*/
cp_int32_t init_hi3531_sdl(cp_hi3531_sdl_t *hi3531_sdl,
	const cp_hi3531_sdl_info_t *hi3531_sdl_info)
{
	cp_int32_t						tmp_ret_int = 0;
	cp_hi3531_dev_configure_t		*tmp_dev_conf = CP_NULL;


	if (!hi3531_sdl || !hi3531_sdl_info || !hi3531_sdl_info->data) {
		return -1;
	}

	//��ȡ�����ļ�
	tmp_ret_int = hi3531_sdl_parse_configure((cp_module_t*)hi3531_sdl, &hi3531_sdl->hacc);
	if (tmp_ret_int) {
		cp_hi3531_dev_log(error, hi3531_sdl, "hi3531_sdl_parse_configure() error.");
		return -1;
	}

	//�����豸������Ϣ
	tmp_dev_conf = (cp_hi3531_dev_configure_t *)(hi3531_sdl_info->data);

	//����vo �豸�б�
	tmp_ret_int = create_hi3531_vo_dev_list(hi3531_sdl, tmp_dev_conf);
	if (tmp_ret_int) {
		cp_hi3531_dev_log(error, hi3531_sdl, "create_hi3531_vo_dev_list() error.");
		return -1;
	}
	else {
		cp_hi3531_dev_log(notice, hi3531_sdl, "create_hi3531_vo_dev_list() successed.");
	}

	cp_hi3531_dev_log(notice, hi3531_sdl, "init() successed.");
	return 0;
}

/*ģ������нӿڣ���ģ��init֮�󣬻ᱻ����*/
cp_int32_t open_hi3531_sdl(cp_hi3531_sdl_t *hi3531_sdl,
	const cp_hi3531_sdl_info_t *hi3531_sdl_info)
{
	cp_int32_t						tmp_ret_int = 0;
	cp_hi3531_dev_configure_t		*tmp_dev_conf = CP_NULL;



	if (!hi3531_sdl || !hi3531_sdl_info || !hi3531_sdl_info->data) {
		return -1;
	}

	//�����豸������Ϣ
	tmp_dev_conf = (cp_hi3531_dev_configure_t *)(hi3531_sdl_info->data);

	//����vo �豸�б�
	tmp_ret_int = start_hi3531_vo_dev_list(hi3531_sdl, tmp_dev_conf);
	if (tmp_ret_int) {
		cp_hi3531_dev_log(error, hi3531_sdl, "start_hi3531_vo_dev_list() error.");
		return -1;
	}
	else {
		cp_hi3531_dev_log(notice, hi3531_sdl, "start_hi3531_vo_dev_list() successed.");
	}

	cp_hi3531_dev_log(notice, hi3531_sdl, "open() successed.");
	return 0;
}

/*��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t read_hi3531_sdl(cp_hi3531_sdl_t *hi3531_sdl,
	cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}

/*дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t write_hi3531_sdl(cp_hi3531_sdl_t *hi3531_sdl,
	const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	cp_int32_t						tmp_ret_int = 0;
	cp_video_frame_packet_t			*tmp_vfp = CP_NULL;



	if (!buf || !*buf || !len) {
		return -1;
	}

	//ת��ý�����ݣ���У�����ݺϷ���
	tmp_vfp = *((cp_video_frame_packet_t**)buf);
	if (cp_media_packet_type_video != tmp_vfp->type) {
		cp_module_log(error, hi3531_sdl,
			"unknow media pakcet type[%d] error.",
			tmp_vfp->type);
		return -2;
	}

	//������Ƶ֡����
	switch (tmp_vfp->mp_buf.buf_type)
	{
		//��ʾ��ʨ��ʽ
		case cp_media_packet_buf_type_none:
		case cp_media_packet_buf_type_hi:
		{
			return write_hi3531_frame_data(hi3531_sdl, buf, len, flag);
		}
		break;
		//��ʾffmpeg��ʽ
// 		case cp_media_packet_buf_type_ffmpeg:
// 		{
// 			return write_ffmpeg_frame_data(hi3531_sdl, buf, len, flag);
// 		}
// 		break;
		default:
		{
			cp_module_log(error, hi3531_sdl,
				"unknow media pakcet buf_type[%d] error.",
				tmp_vfp->mp_buf.buf_type);
			return -3;
		}
		break;
	}

	return 0;
}

/*�ر�ģ��*/
cp_int32_t close_hi3531_sdl(cp_hi3531_sdl_t *hi3531_sdl)
{
	cp_int32_t						tmp_ret_int = 0;
	cp_hi3531_dev_configure_t		*tmp_dev_conf = CP_NULL;


	if (!hi3531_sdl || !hi3531_sdl->info) {
		return -1;
	}

	//�����豸������Ϣ
	tmp_dev_conf = (cp_hi3531_dev_configure_t *)(hi3531_sdl->info);

	//ֹͣvo �豸�б�
	tmp_ret_int = stop_hi3531_vo_dev_list(hi3531_sdl, tmp_dev_conf);
	if (tmp_ret_int) {
		cp_hi3531_dev_log(error, hi3531_sdl, "stop_hi3531_vo_dev_list() error.");
		return -1;
	}
	else {
		cp_hi3531_dev_log(notice, hi3531_sdl, "stop_hi3531_vo_dev_list() successed.");
	}

	return 0;
}

/*�˳�ģ��*/
cp_int32_t exit_hi3531_sdl(cp_hi3531_sdl_t *hi3531_sdl)
{
	cp_int32_t						tmp_ret_int = 0;
	cp_hi3531_dev_configure_t		*tmp_dev_conf = CP_NULL;


	if (!hi3531_sdl || !hi3531_sdl->info) {
		return -1;
	}

	//�����豸������Ϣ
	tmp_dev_conf = (cp_hi3531_dev_configure_t *)(hi3531_sdl->info);

	//ֹͣvo �豸�б�
	tmp_ret_int = destory_hi3531_vo_dev_list(hi3531_sdl, tmp_dev_conf);
	if (tmp_ret_int) {
		cp_hi3531_dev_log(error, hi3531_sdl, "destory_hi3531_vo_dev_list() error.");
		return -1;
	}
	else {
		cp_hi3531_dev_log(notice, hi3531_sdl, "destory_hi3531_vo_dev_list() successed.");
	}

	return 0;
}

/*����ģ�����*/
cp_int32_t set_option_hi3531_sdl(cp_hi3531_sdl_t *hi3531_sdl, cp_int32_t optname, const cp_void_t* optval)
{
	if (!hi3531_sdl || !optval) {
		return -1;
	}

	cp_hi3531_dev_log(notice, hi3531_sdl, "set_option_hi3531_sdl() failed");

	return -2;
}

cp_int32_t get_option_hi3531_sdl(cp_hi3531_sdl_t *hi3531_sdl, cp_int32_t optname, cp_void_t* optval)
{
	return 0;
}
