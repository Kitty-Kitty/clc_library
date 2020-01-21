/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_qt_svg_codec.h"
#include "cp_qt_svg_codec_option_function.h"


/*ģ�鴴���ӿڣ���ʾ����һ��ģ��*/
cp_int32_t init_qt_svg_codec(cp_qt_svg_codec_t *qt_svg_codec, const cp_qt_svg_codec_info_t *qt_svg_codec_info);
/*ģ������нӿڣ���ģ��init֮�󣬻ᱻ����*/
cp_int32_t open_qt_svg_codec(cp_qt_svg_codec_t *qt_svg_codec, const cp_qt_svg_codec_info_t *qt_svg_codec_info);
/*��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t read_qt_svg_codec(cp_qt_svg_codec_t *qt_svg_codec, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t write_qt_svg_codec(cp_qt_svg_codec_t *qt_svg_codec, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*�ر�ģ��*/
cp_int32_t close_qt_svg_codec(cp_qt_svg_codec_t *qt_svg_codec);
/*�˳�ģ��*/
cp_int32_t exit_qt_svg_codec(cp_qt_svg_codec_t *qt_svg_codec);
/*����ģ�����*/
cp_int32_t set_option_qt_svg_codec(cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, const cp_void_t* optval);
cp_int32_t get_option_qt_svg_codec(cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, cp_void_t* optval);

/*����һ��ģ��*/
cp_qt_svg_codec_t* create_qt_svg_codec(cp_module_register_t *register_info, cp_codec_manager_t *manager, cp_qt_svg_codec_info_t *info)
{
	cp_int32_t							ret_int = 0;
	cp_qt_svg_codec_t				*tmp_module = CP_NULL;
	cp_pool_info_t						tmp_pool_info = { 0, };


	if (!register_info || !manager || !info) {
		return CP_NULL;
	}

	tmp_module = cp_malloc_module(manager, cp_qt_svg_codec_t, &tmp_pool_info);
	if (!tmp_module) {
		return CP_NULL;
	}
	CP_MODULE_SET_HANDLERS(tmp_module, qt_svg_codec);
	return tmp_module;
}
/*�ͷ�ģ��*/
cp_int32_t destroy_qt_svg_codec(cp_codec_manager_t *manager, cp_qt_svg_codec_t* qt_svg_codec)
{
	if (!manager || !qt_svg_codec) {
		return -1;
	}
	cp_free_module(qt_svg_codec);
	return 0;
}

/*ģ�鴴���ӿڣ���ʾ����һ��ģ��*/
cp_int32_t init_qt_svg_codec(cp_qt_svg_codec_t *qt_svg_codec,
	const cp_qt_svg_codec_info_t *qt_svg_codec_info)
{
	cp_int32_t								ret_int = 0;


	ret_int = cp_qt_svg_codec_create_option_handle(qt_svg_codec);
	if (ret_int) {
		cp_module_log(error, qt_svg_codec, 
			"cp_qt_svg_codec_create_option_handle()error.");
		return -1;
	}

	return 0;
}

/*ģ������нӿڣ���ģ��init֮�󣬻ᱻ����*/
cp_int32_t open_qt_svg_codec(cp_qt_svg_codec_t *qt_svg_codec,
	const cp_qt_svg_codec_info_t *qt_svg_codec_info)
{
	return 0;
}

/*��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t read_qt_svg_codec(cp_qt_svg_codec_t *qt_svg_codec,
	cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}

/*дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t write_qt_svg_codec(cp_qt_svg_codec_t *qt_svg_codec,
	const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}

/*�ر�ģ��*/
cp_int32_t close_qt_svg_codec(cp_qt_svg_codec_t *qt_svg_codec)
{
	return 0;
}

/*�˳�ģ��*/
cp_int32_t exit_qt_svg_codec(cp_qt_svg_codec_t *qt_svg_codec)
{
	cp_int32_t								ret_int = 0;


	ret_int = cp_qt_svg_codec_destroy_option_handle(qt_svg_codec);
	if (ret_int) {
		cp_module_log(error, qt_svg_codec, 
			"cp_qt_svg_codec_destroy_option_handle()error.");
		return -1;
	}

	return 0;
}

/*����ģ�����*/
cp_int32_t set_option_qt_svg_codec(cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, const cp_void_t* optval)
{
	return cp_qt_svg_codec_set_option_process(qt_svg_codec, optname, optval);
}

cp_int32_t get_option_qt_svg_codec(cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, cp_void_t* optval)
{
	return cp_qt_svg_codec_get_option_process(qt_svg_codec, optname, optval);
}
