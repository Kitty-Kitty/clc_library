/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_hi3531_tde.h"
#include "cp_third_party.h"
#include "cp_include.h"


#ifndef PIX_FMT_YUV420P
#define PIX_FMT_YUV420P	AV_PIX_FMT_YUV420P
#endif


/*ģ�鴴���ӿڣ���ʾ����һ��ģ��*/
cp_int32_t init_hi3531_tde(cp_hi3531_tde_t *hi3531_tde, const cp_hi3531_tde_info_t *hi3531_tde_info);
/*ģ������нӿڣ���ģ��init֮�󣬻ᱻ����*/
cp_int32_t open_hi3531_tde(cp_hi3531_tde_t *hi3531_tde, const cp_hi3531_tde_info_t *hi3531_tde_info);
/*��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t read_hi3531_tde(cp_hi3531_tde_t *hi3531_tde, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t write_hi3531_tde(cp_hi3531_tde_t *hi3531_tde, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*�ر�ģ��*/
cp_int32_t close_hi3531_tde(cp_hi3531_tde_t *hi3531_tde);
/*�˳�ģ��*/
cp_int32_t exit_hi3531_tde(cp_hi3531_tde_t *hi3531_tde);
/*����ģ�����*/
cp_int32_t set_option_hi3531_tde(cp_hi3531_tde_t *hi3531_tde, cp_int32_t optname, const cp_void_t* optval);
cp_int32_t get_option_hi3531_tde(cp_hi3531_tde_t *hi3531_tde, cp_int32_t optname, cp_void_t* optval);




/*����һ��ģ��*/
cp_hi3531_tde_t* create_hi3531_tde(cp_module_register_t *register_info, cp_codec_manager_t *manager, cp_hi3531_tde_info_t *info)
{
	cp_int32_t							ret_int = 0;
	cp_hi3531_tde_t						*tmp_module = CP_NULL;
	cp_pool_info_t						tmp_pool_info = { 0, };


	if (!register_info || !manager || !info) {
		return CP_NULL;
	}

	tmp_module = cp_malloc_module(manager, cp_hi3531_tde_t, &tmp_pool_info);
	if (!tmp_module) {
		return CP_NULL;
	}
	CP_MODULE_SET_HANDLERS(tmp_module, hi3531_tde);
	return tmp_module;
}

/*�ͷ�ģ��*/
cp_int32_t destroy_hi3531_tde(cp_codec_manager_t *manager, cp_hi3531_tde_t* hi3531_tde)
{
	if (!manager || !hi3531_tde) {
		return -1;
	}
	cp_free_module(hi3531_tde);
	return 0;
}

/*ģ�鴴���ӿڣ���ʾ����һ��ģ��*/
cp_int32_t init_hi3531_tde(cp_hi3531_tde_t *hi3531_tde,
	const cp_hi3531_tde_info_t *hi3531_tde_info)
{
	cp_int32_t						tmp_ret_int = 0;



	//��ȡ�����ļ�
	tmp_ret_int = hi3531_tde_parse_configure((cp_module_t*)hi3531_tde, &hi3531_tde->hacc);
	if (tmp_ret_int) {
		cp_hi3531_dev_log(error, hi3531_tde, "hi3531_tde_parse_configure() error.");
		return -1;
	}

	//��ʼ��tde�豸��Ϣ
	tmp_ret_int = hi3531_tde_init_dev(hi3531_tde, &hi3531_tde->hacc);
	if (tmp_ret_int) {
		cp_hi3531_dev_log(error, hi3531_tde, "hi3531_tde_init_dev() failed!");
		return -1;
	}
	else {
		cp_hi3531_dev_log(notice, hi3531_tde, "hi3531_tde_init_dev() successed!");
	}

	cp_hi3531_dev_log(notice, hi3531_tde, "init() successed.");
	return 0;
}

/*ģ������нӿڣ���ģ��init֮�󣬻ᱻ����*/
cp_int32_t open_hi3531_tde(cp_hi3531_tde_t *hi3531_tde,
	const cp_hi3531_tde_info_t *hi3531_tde_info)
{
	cp_int32_t					tmp_ret_int = 0;


	//��ʼ��tde�豸��Ϣ
	tmp_ret_int = hi3531_tde_start_dev(hi3531_tde, &hi3531_tde->hacc);
	if (tmp_ret_int) {
		cp_hi3531_dev_log(error, hi3531_tde, "hi3531_tde_start_dev() failed!");
		return -1;
	}
	else {
		cp_hi3531_dev_log(notice, hi3531_tde, "hi3531_tde_start_dev() successed!");
	}

	cp_hi3531_dev_log(notice, hi3531_tde, "open() successed.");
	return 0;
}

/*��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t read_hi3531_tde(cp_hi3531_tde_t *hi3531_tde,
	cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}

/*дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t write_hi3531_tde(cp_hi3531_tde_t *hi3531_tde,
	const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
#if 0
	cp_int32_t						tmp_ret_int = 0;
	cp_video_frame_process_t		*tmp_vfproc = CP_NULL;



	if (!buf || !*buf || !len) {
		return -1;
	}

	//ת��ý�����ݣ���У�����ݺϷ���
	tmp_vfproc = *((cp_video_frame_process_t**)buf);
	if (!tmp_vfproc || !tmp_vfproc->mpro || !tmp_vfproc->vfpp) {
		cp_module_log(error, hi3531_tde,
			"write video frame process is null error. ");
		return -2;
	}

	switch (tmp_vfproc->vfp_type)
	{
		case cp_video_frame_process_type_fill:
		{
			//���ͼ������
			return hi3531_tde_video_frame_fill(hi3531_tde, tmp_vfproc->mpro->ms, tmp_vfproc->mpro->mp, tmp_vfproc->vfpp);
		}
		break;
		case cp_video_frame_process_type_copy:
		{
			//��Ƶ֡���ٿ���ͼ��
			return hi3531_tde_video_frame_copy(hi3531_tde, tmp_vfproc->mpro->ms, tmp_vfproc->mpro->mp, tmp_vfproc->vfpp);
		}
		break;
		case cp_video_frame_process_type_resize:
		{
			//����ͼ������
			return hi3531_tde_video_frame_resize(hi3531_tde, tmp_vfproc->mpro->ms, tmp_vfproc->mpro->mp, tmp_vfproc->vfpp);
		}
		break;
		case cp_video_frame_process_type_copy_resize:
		{
			//����ͼ������
			return hi3531_tde_video_frame_copy_resize(hi3531_tde, tmp_vfproc->mpro->ms, tmp_vfproc->mpro->mp, tmp_vfproc->vfpp);
		}
		break;
		default:
		{
			cp_module_log(error, hi3531_tde,
				"write video frame process error. unknow video frame process type[%d]",
				tmp_vfproc->vfp_type);
			return -3;
		}
		break;
	}
#endif

	return 0;
}

/*�ر�ģ��*/
cp_int32_t close_hi3531_tde(cp_hi3531_tde_t *hi3531_tde)
{
	cp_int32_t					tmp_ret_int = 0;

	//��ʼ��tde�豸��Ϣ
	tmp_ret_int = hi3531_tde_stop_dev(hi3531_tde, &hi3531_tde->hacc);
	if (tmp_ret_int) {
		cp_hi3531_dev_log(error, hi3531_tde, "hi3531_tde_stop_dev() failed!");
		return -1;
	}
	else {
		cp_hi3531_dev_log(notice, hi3531_tde, "hi3531_tde_stop_dev() successed!");
	}

	return 0;
}

/*�˳�ģ��*/
cp_int32_t exit_hi3531_tde(cp_hi3531_tde_t *hi3531_tde)
{
	return 0;
}

/*����ģ�����*/
cp_int32_t set_option_hi3531_tde(cp_hi3531_tde_t *hi3531_tde, cp_int32_t optname, const cp_void_t* optval)
{
	if (!hi3531_tde || !optval) {
		return -1;
	}

	cp_hi3531_dev_log(notice, hi3531_tde, "set_option_hi3531_tde() failed");

	return -2;
}

cp_int32_t get_option_hi3531_tde(cp_hi3531_tde_t *hi3531_tde, cp_int32_t optname, cp_void_t* optval)
{
	cp_int32_t						tmp_ret_int = 0;
	cp_video_frame_process_t		*tmp_vfproc = CP_NULL;



	if (!hi3531_tde || !optval) {
		return -1;
	}

	//ת��ý�����ݣ���У�����ݺϷ���
	tmp_vfproc = *((cp_video_frame_process_t**)optval);
	if (!tmp_vfproc || !tmp_vfproc->mpro || !tmp_vfproc->vfpp) {
		cp_module_log(error, hi3531_tde,
			"process video frame process is null error. ");
		return -2;
	}

	switch (optname)
	{
		case cp_hi3531_tde_option_get_copy:
		{
			//��Ƶ֡���ٿ���ͼ��
			return hi3531_tde_video_frame_copy(hi3531_tde, tmp_vfproc->mpro->ms, tmp_vfproc->mpro->mp, tmp_vfproc->vfpp);
		}
		break;
		case cp_hi3531_tde_option_get_fill:
		{
			//���ͼ������
			return hi3531_tde_video_frame_fill(hi3531_tde, tmp_vfproc->mpro->ms, tmp_vfproc->mpro->mp, tmp_vfproc->vfpp);
		}
		break;
		case cp_hi3531_tde_option_get_resize:
		{
			//����ͼ������
			return hi3531_tde_video_frame_resize(hi3531_tde, tmp_vfproc->mpro->ms, tmp_vfproc->mpro->mp, tmp_vfproc->vfpp);
		}
		break;
		default:
		{
			cp_module_log(error, hi3531_tde,
				"write video frame process error. unknow video frame process type[%d]",
				tmp_vfproc->vfp_type);
			return -3;
		}
		break;
	}

	return 0;
}
