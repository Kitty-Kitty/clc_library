
/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#include "cp_include.h"
#include "cp_demo_codec_core.h"





/*ģ�鴴���ӿڣ���ʾ����һ��ģ��*/
cp_int32_t init_demo_codec(cp_demo_codec_t *demo_codec, const cp_demo_codec_info_t *info);
/*ģ������нӿڣ���ģ��init֮�󣬻ᱻ����*/
cp_int32_t open_demo_codec(cp_demo_codec_t *demo_codec, const cp_demo_codec_info_t *info);
/*��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t read_demo_codec(cp_demo_codec_t *demo_codec, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t write_demo_codec(cp_demo_codec_t *demo_codec, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*�ر�ģ��*/
cp_int32_t close_demo_codec(cp_demo_codec_t *demo_codec);
/*�˳�ģ��*/
cp_int32_t exit_demo_codec(cp_demo_codec_t *demo_codec);
/*����ģ�����*/
cp_int32_t set_option_demo_codec(cp_demo_codec_t *demo_codec, cp_int32_t optname, const cp_void_t* optval);
cp_int32_t get_option_demo_codec(cp_demo_codec_t *demo_codec, cp_int32_t optname, cp_void_t* optval);





cp_demo_codec_t* create_demo_codec(cp_module_register_t *register_info, cp_codec_manager_t *manager, cp_demo_codec_info_t *info)
{
	cp_demo_codec_t						*tmp_module = CP_NULL;
	cp_pool_info_t						tmp_pool_info = { 0, };


	if (!register_info || !manager || !info) {
		return CP_NULL;
	}

	tmp_module = cp_malloc_module(manager, cp_demo_codec_t, &tmp_pool_info);
	if (!tmp_module) {
		return CP_NULL;
	}

	return tmp_module;
}

cp_int32_t destroy_demo_codec(cp_codec_manager_t *manager, cp_demo_codec_t* demo_codec)
{
	if (!manager || !demo_codec) {
		return -1;
	}
	cp_free_module(demo_codec);
	return 0;
}

/*ģ�鴴���ӿڣ���ʾ����һ��ģ��*/
cp_int32_t init_demo_codec(cp_demo_codec_t *demo_codec, const cp_demo_codec_info_t *info)
{
	return 0;
}
/*ģ������нӿڣ���ģ��init֮�󣬻ᱻ����*/
cp_int32_t open_demo_codec(cp_demo_codec_t *demo_codec, const cp_demo_codec_info_t *info)
{

	return 0;
}
/*��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t read_demo_codec(cp_demo_codec_t *demo_codec, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}
/*дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t write_demo_codec(cp_demo_codec_t *demo_codec, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}
/*�ر�ģ��*/
cp_int32_t close_demo_codec(cp_demo_codec_t *demo_codec)
{
	return 0;
}
/*�˳�ģ��*/
cp_int32_t exit_demo_codec(cp_demo_codec_t *demo_codec)
{
	return 0;
}
/*����ģ�����*/
cp_int32_t set_option_demo_codec(cp_demo_codec_t *demo_codec, cp_int32_t optname, const cp_void_t* optval)
{
	return 0;
}

cp_int32_t get_option_demo_codec(cp_demo_codec_t *demo_codec, cp_int32_t optname, cp_void_t* optval)
{
	return 0;
}


