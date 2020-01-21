/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_hi3531_vpss.h"
#include "cp_third_party.h"
#include "cp_include.h"
#include "css_status.h"


#ifndef PIX_FMT_YUV420P
#define PIX_FMT_YUV420P	AV_PIX_FMT_YUV420P
#endif


/*ģ�鴴���ӿڣ���ʾ����һ��ģ��*/
cp_int32_t init_hi3531_vpss(cp_hi3531_vpss_t *hi3531_vpss, const cp_hi3531_vpss_info_t *hi3531_vpss_info);
/*ģ������нӿڣ���ģ��init֮�󣬻ᱻ����*/
cp_int32_t open_hi3531_vpss(cp_hi3531_vpss_t *hi3531_vpss, const cp_hi3531_vpss_info_t *hi3531_vpss_info);
/*��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t read_hi3531_vpss(cp_hi3531_vpss_t *hi3531_vpss, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t write_hi3531_vpss(cp_hi3531_vpss_t *hi3531_vpss, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*�ر�ģ��*/
cp_int32_t close_hi3531_vpss(cp_hi3531_vpss_t *hi3531_vpss);
/*�˳�ģ��*/
cp_int32_t exit_hi3531_vpss(cp_hi3531_vpss_t *hi3531_vpss);
/*����ģ�����*/
cp_int32_t set_option_hi3531_vpss(cp_hi3531_vpss_t *hi3531_vpss, cp_int32_t optname, const cp_void_t* optval);
cp_int32_t get_option_hi3531_vpss(cp_hi3531_vpss_t *hi3531_vpss, cp_int32_t optname, cp_void_t* optval);




/*����һ��ģ��*/
cp_hi3531_vpss_t* create_hi3531_vpss(cp_module_register_t *register_info, cp_codec_manager_t *manager, cp_hi3531_vpss_info_t *info)
{
	cp_int32_t							ret_int = 0;
	cp_hi3531_vpss_t				*tmp_module = CP_NULL;
	cp_pool_info_t						tmp_pool_info = { 0, };


	if (!register_info || !manager || !info) {
		return CP_NULL;
	}

	tmp_module = cp_malloc_module(manager, cp_hi3531_vpss_t, &tmp_pool_info);
	if (!tmp_module) {
		return CP_NULL;
	}
	CP_MODULE_SET_HANDLERS(tmp_module, hi3531_vpss);
	return tmp_module;
}

/*�ͷ�ģ��*/
cp_int32_t destroy_hi3531_vpss(cp_codec_manager_t *manager, cp_hi3531_vpss_t* hi3531_vpss)
{
	if (!manager || !hi3531_vpss) {
		return -1;
	}
	cp_free_module(hi3531_vpss);
	return 0;
}

/*ģ�鴴���ӿڣ���ʾ����һ��ģ��*/
cp_int32_t init_hi3531_vpss(cp_hi3531_vpss_t *hi3531_vpss,
	const cp_hi3531_vpss_info_t *hi3531_vpss_info)
{
	cp_int32_t						tmp_ret_int = 0;



	//��ȡ�����ļ�
	tmp_ret_int = hi3531_vpss_parse_configure((cp_module_t*)hi3531_vpss, &hi3531_vpss->hacc);
	if (tmp_ret_int) {
		cp_hi3531_dev_log(error, hi3531_vpss, "hi3531_vpss_parse_configure() error.");
		return -1;
	}

	cp_hi3531_dev_log(notice, hi3531_vpss, "init() successed.");
	return 0;
}

/*ģ������нӿڣ���ģ��init֮�󣬻ᱻ����*/
cp_int32_t open_hi3531_vpss(cp_hi3531_vpss_t *hi3531_vpss,
	const cp_hi3531_vpss_info_t *hi3531_vpss_info)
{
	cp_int32_t					tmp_ret_int = 0;



#if defined(CP_HI3531_VPSS_FILE_DEBUG)
	if (!hi3531_vpss->file) {
		hi3531_vpss->file = fopen(CP_HI3531_VPSS_VIDEO_DEMO_FILE_PATH, "wb");
	}
#endif

#if defined(CP_HI3531_VPSS_FILE_DEMO)
	cp_void_t				*tmp_data = CP_NULL;


	/*��ʾ�򿪲����õ��ļ�*/
	hi3531_vpss->video_file = fopen(CP_HI3531_VPSS_VIDEO_FILE_PATH, "rb");
	if (!hi3531_vpss->video_file) {
		cp_hi3531_dev_log(error, hi3531_vpss,
			"start_hi3531_vpss_get_stream() error. open file[%s] failed!",
			CP_HI3531_VPSS_VIDEO_FILE_PATH);
		return -1;
	}
	tmp_data = cp_palloc(hi3531_vpss->pool, CP_HI3531_VPSS_VIDEO_BUFFER_LENGTH);
	if (!tmp_data) {
		cp_hi3531_dev_log(error, hi3531_vpss,
			"start_hi3531_vpss_get_stream() error. create buffer failed!");
		return -1;
	}
	cp_buf_assemble(&hi3531_vpss->data_buf, tmp_data, CP_HI3531_VPSS_VIDEO_BUFFER_LENGTH);

	hi3531_vpss->rtp_sd = create_rtp_socket_data(hi3531_vpss->pool);
	if (!hi3531_vpss->rtp_sd) {
		cp_hi3531_dev_log(error, hi3531_vpss,
			"create_rtp_socket_data() socket_data[%d] failed!");
		return -1;
	}

#endif
	cp_hi3531_dev_log(notice, hi3531_vpss, "open() successed.");
	return 0;
}

/*��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t read_hi3531_vpss(cp_hi3531_vpss_t *hi3531_vpss,
	cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}

/*дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t write_hi3531_vpss(cp_hi3531_vpss_t *hi3531_vpss,
	const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}

/*�ر�ģ��*/
cp_int32_t close_hi3531_vpss(cp_hi3531_vpss_t *hi3531_vpss)
{
	cp_int32_t					tmp_ret_int = 0;


#if defined(CP_HI3531_VPSS_FILE_DEBUG)
	if (hi3531_vpss->file) {
		fclose(hi3531_vpss->file);
	}
#endif

#if defined(CP_HI3531_VPSS_FILE_DEMO)
	if (hi3531_vpss->video_file) {
		fclose(hi3531_vpss->video_file);
	}
#endif

	return 0;
}

/*�˳�ģ��*/
cp_int32_t exit_hi3531_vpss(cp_hi3531_vpss_t *hi3531_vpss)
{
	return 0;
}

/*����ģ�����*/
cp_int32_t set_option_hi3531_vpss(cp_hi3531_vpss_t *hi3531_vpss, cp_int32_t optname, const cp_void_t* optval)
{
	if (!hi3531_vpss || !optval) {
		return -1;
	}

	cp_hi3531_dev_log(notice, hi3531_vpss, "set_option_hi3531_vpss() failed");

	return -2;
}

cp_int32_t get_option_hi3531_vpss(cp_hi3531_vpss_t *hi3531_vpss, cp_int32_t optname, cp_void_t* optval)
{
	return 0;
}
