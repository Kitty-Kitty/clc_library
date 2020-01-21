/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_vdu_codec.h"
#include "cp_third_party.h"
#include "cp_include.h"
#include "css_status.h"


#ifndef PIX_FMT_YUV420P
#define PIX_FMT_YUV420P	AV_PIX_FMT_YUV420P
#endif


/*ģ�鴴���ӿڣ���ʾ����һ��ģ��*/
cp_int32_t init_vdu_codec(cp_vdu_codec_t *vdu_codec, const cp_vdu_codec_info_t *vdu_codec_info);
/*ģ������нӿڣ���ģ��init֮�󣬻ᱻ����*/
cp_int32_t open_vdu_codec(cp_vdu_codec_t *vdu_codec, const cp_vdu_codec_info_t *vdu_codec_info);
/*��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t read_vdu_codec(cp_vdu_codec_t *vdu_codec, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t write_vdu_codec(cp_vdu_codec_t *vdu_codec, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*�ر�ģ��*/
cp_int32_t close_vdu_codec(cp_vdu_codec_t *vdu_codec);
/*�˳�ģ��*/
cp_int32_t exit_vdu_codec(cp_vdu_codec_t *vdu_codec);
/*����ģ�����*/
cp_int32_t set_option_vdu_codec(cp_vdu_codec_t *vdu_codec, cp_int32_t optname, const cp_void_t* optval);
cp_int32_t get_option_vdu_codec(cp_vdu_codec_t *vdu_codec, cp_int32_t optname, cp_void_t* optval);

/*����һ��ģ��*/
cp_vdu_codec_t* create_vdu_codec(cp_module_register_t *register_info, cp_codec_manager_t *manager, cp_vdu_codec_info_t *info)
{
	cp_int32_t							ret_int = 0;
	cp_vdu_codec_t				*tmp_module = CP_NULL;
	cp_pool_info_t						tmp_pool_info = { 0, };


	if (!register_info || !manager || !info) {
		return CP_NULL;
	}

	tmp_module = cp_malloc_module(manager, cp_vdu_codec_t, &tmp_pool_info);
	if (!tmp_module) {
		return CP_NULL;
	}
	CP_MODULE_SET_HANDLERS(tmp_module, vdu_codec);
	return tmp_module;
}
/*�ͷ�ģ��*/
cp_int32_t destroy_vdu_codec(cp_codec_manager_t *manager, cp_vdu_codec_t* vdu_codec)
{
	if (!manager || !vdu_codec) {
		return -1;
	}
	cp_free_module(vdu_codec);
	return 0;
}

/*ģ�鴴���ӿڣ���ʾ����һ��ģ��*/
cp_int32_t init_vdu_codec(cp_vdu_codec_t *vdu_codec,
	const cp_vdu_codec_info_t *vdu_codec_info)
{
	return 0;
}

/*ģ������нӿڣ���ģ��init֮�󣬻ᱻ����*/
cp_int32_t open_vdu_codec(cp_vdu_codec_t *vdu_codec,
	const cp_vdu_codec_info_t *vdu_codec_info)
{
	return 0;
}

/*��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t read_vdu_codec(cp_vdu_codec_t *vdu_codec,
	cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}

/*дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t write_vdu_codec(cp_vdu_codec_t *vdu_codec,
	const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}

/*�ر�ģ��*/
cp_int32_t close_vdu_codec(cp_vdu_codec_t *vdu_codec)
{
	return 0;
}

/*�˳�ģ��*/
cp_int32_t exit_vdu_codec(cp_vdu_codec_t *vdu_codec)
{
	return 0;
}

/*����ģ�����*/
cp_int32_t set_option_vdu_codec(cp_vdu_codec_t *vdu_codec, cp_int32_t optname, const cp_void_t* optval)
{
	if (!vdu_codec || !optval) {
		return -1;
	}

	return 0;
}

cp_int32_t get_option_vdu_codec(cp_vdu_codec_t *vdu_codec, cp_int32_t optname, cp_void_t* optval)
{
	return 0;
}