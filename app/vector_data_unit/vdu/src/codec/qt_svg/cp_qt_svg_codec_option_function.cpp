/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-08-09

Description:

**************************************************************************/



#include "cp_qt_svg_codec_option_function.h"
#include "cp_qt_svg_include.h"



cp_module_option_handle_t				cp_qt_svg_codec_option_handle_array[] = {
	CP_MODULE_SET_OPTION_REGISTER(
		cp_qt_svg_process_option_create_channel,
		cp_qt_svg_codec_set_option_process_create_channel,
		"create a svg channel",
		"optval: struct cp_vdu_channel_process_s"
	),
	CP_MODULE_SET_OPTION_REGISTER(
		cp_qt_svg_process_option_destroy_channel,
		cp_qt_svg_codec_set_option_process_destroy_channel,
		"detroy a svg channel",
		"optval: struct cp_vdu_channel_process_s"
	),
	CP_MODULE_SET_OPTION_REGISTER(
		cp_qt_svg_process_option_destroy_all_channel,
		cp_qt_svg_codec_set_option_process_destroy_all_channel,
		"detroy a svg all channel",
		"optval: struct cp_vdu_process_s"
	),
	CP_MODULE_SET_OPTION_REGISTER(
		cp_qt_svg_process_option_set_roi,
		cp_qt_svg_codec_set_option_process_set_roi,
		"set process roi",
		"optval: struct cp_vdu_process_s"
	),
	CP_MODULE_SET_OPTION_REGISTER(
		cp_qt_svg_process_option_clear_roi,
		cp_qt_svg_codec_set_option_process_clear_roi,
		"process clear roi",
		"optval: struct cp_vdu_process_s"
	),
	CP_MODULE_SET_OPTION_REGISTER(
		cp_qt_svg_process_option_set_coordinate,
		cp_qt_svg_codec_set_option_process_set_coordinate,
		"set coordinate",
		"optval: struct cp_vdu_process_s"
	),
	CP_MODULE_SET_OPTION_REGISTER(
		cp_qt_svg_process_option_set_debug_info,
		cp_qt_svg_codec_set_option_process_set_debug_info,
		"set debug_info",
		"optval: struct cp_vdu_process_s"
	),
	CP_MODULE_SET_OPTION_REGISTER(
		cp_qt_svg_channel_option_set_channel_index,
		cp_qt_svg_codec_set_option_process_set_channel_index,
		"set channel index",
		"optval: struct cp_vdu_channel_process_s"
	),
	//////////////////////////////////////////////////////////////////////////
	CP_MODULE_SET_OPTION_REGISTER(
		cp_qt_svg_channel_option_set_insert_channel,
		cp_qt_svg_codec_set_option_channel_set_insert_channel,
		"set insert channel ",
		"optval: struct cp_vdu_channel_process_s"
	),
	CP_MODULE_SET_OPTION_REGISTER(
		cp_qt_svg_channel_option_set_remove_channel,
		cp_qt_svg_codec_set_option_channel_set_remove_channel,
		"set remove channel",
		"optval: struct cp_vdu_channel_process_s"
	),
	CP_MODULE_SET_OPTION_REGISTER(
		cp_qt_svg_channel_option_set_roi,
		cp_qt_svg_codec_set_option_channel_set_roi,
		"set channel roi",
		"optval: struct cp_vdu_channel_process_s"
	),
	CP_MODULE_SET_OPTION_REGISTER(
		cp_qt_svg_channel_option_clear_roi,
		cp_qt_svg_codec_set_option_channel_clear_roi,
		"clear channel roi",
		"optval: struct cp_vdu_channel_process_s"
	),
	CP_MODULE_SET_OPTION_REGISTER(
		cp_qt_svg_channel_option_set_vector_stream,
		cp_qt_svg_codec_set_option_channel_set_vector_stream,
		"set vector stream",
		"optval: struct cp_vdu_channel_process_s"
	),
	//////////////////////////////////////////////////////////////////////////
	//��ȡѡ��
	//////////////////////////////////////////////////////////////////////////
	CP_MODULE_GET_OPTION_REGISTER(
		cp_qt_svg_process_option_get_roi,
		cp_qt_svg_codec_set_option_process_get_roi,
		"get roi",
		"optval: struct cp_vdu_process_s"
	),
	CP_MODULE_GET_OPTION_REGISTER(
		cp_qt_svg_process_option_get_roi_pixel,
		cp_qt_svg_codec_set_option_process_get_roi_pixel,
		"get roi pixel",
		"optval: struct cp_vdu_process_s"
	),
	CP_MODULE_GET_OPTION_REGISTER(
		cp_qt_svg_process_option_get_rect_pixel,
		cp_qt_svg_codec_set_option_process_get_rect_pixel,
		"get rect pixel",
		"optval: struct cp_vdu_process_s"
	),
	CP_MODULE_GET_OPTION_REGISTER(
		cp_qt_svg_process_option_get_status,
		cp_qt_svg_codec_set_option_process_get_status,
		"get status",
		"optval: struct cp_vdu_process_s"
	),
	CP_MODULE_GET_OPTION_REGISTER(
		cp_qt_svg_process_option_get_coordinate,
		cp_qt_svg_codec_set_option_process_get_coordinate,
		"get coordinate",
		"optval: struct cp_vdu_process_s"
	),
	//////////////////////////////////////////////////////////////////////////
	//��ʾ��ȡͨ��ѡ��
	//////////////////////////////////////////////////////////////////////////
	CP_MODULE_GET_OPTION_REGISTER(
		cp_qt_svg_channel_option_get_channel_index,
		cp_qt_svg_codec_get_option_channel_get_channel_index,
		"get channel index",
		"optval: struct cp_vdu_channel_process_s"
	),
	CP_MODULE_GET_OPTION_REGISTER(
		cp_qt_svg_channel_option_get_roi,
		cp_qt_svg_codec_get_option_channel_get_roi,
		"get channel roi",
		"optval: struct cp_vdu_channel_process_s"
	),
	CP_MODULE_GET_OPTION_REGISTER(
		cp_qt_svg_channel_option_get_roi_pixel,
		cp_qt_svg_codec_get_option_channel_get_roi_pixel,
		"get channel roi pixel",
		"optval: struct cp_vdu_channel_process_s"
	),
	CP_MODULE_GET_OPTION_REGISTER(
		cp_qt_svg_channel_option_get_rect_pixel,
		cp_qt_svg_codec_get_option_channel_get_rect_pixel,
		"get channel rect pixel",
		"optval: struct cp_vdu_channel_process_s"
	),
	CP_MODULE_GET_OPTION_REGISTER(
		cp_qt_svg_channel_option_get_status,
		cp_qt_svg_codec_get_option_channel_get_status,
		"get channel status",
		"optval: struct cp_vdu_channel_process_s"
	),


};


cp_int32_t cp_qt_svg_codec_create_option_handle(cp_qt_svg_codec_t *codec)
{
	cp_int32_t							tmp_ret_int = 0;
	cp_qt_svg_process_info_t			tmp_svg_process_info = { 0, };


	//����һ��svg process����
	codec->svg_process = create_qt_svg_process(codec, &tmp_svg_process_info);
	if (!codec->svg_process) {
		cp_module_log(error, codec, "create_qt_svg_process() error.");
		return cp_vdu_status_create_source_failed;
	}
	else {
		cp_module_log(notice, codec, "create qt_svg_process[0x%x] success.",
			codec->svg_process);
	}

	//��ʼ��process
	tmp_ret_int = init_qt_svg_process(codec->svg_process, &tmp_svg_process_info);
	if (tmp_ret_int) {
		destroy_svg_process(codec->svg_process);
		cp_module_log(error, codec, "init_qt_svg_process() failed. qt_svg_process[0x%x].",
			codec->svg_process);
		return tmp_ret_int;
	}
	else {
		cp_module_log(notice, codec, "init qt_svg_process[0x%x] success.",
			codec->svg_process);
	}

	//����process
	tmp_ret_int = start_qt_svg_process(codec->svg_process, &tmp_svg_process_info);
	if (tmp_ret_int) {
		destroy_svg_process(codec->svg_process);
		cp_module_log(error, codec, "start_qt_svg_process() failed. qt_svg_process[0x%x].",
			codec->svg_process);
		return tmp_ret_int;
	}
	else {
		cp_module_log(notice, codec, "start qt_svg_process[0x%x] success.",
			codec->svg_process);
	}

	return 0;
}

cp_int32_t cp_qt_svg_codec_destroy_option_handle(cp_qt_svg_codec_t *codec)
{
	cp_int32_t							tmp_ret_int = 0;


	if (codec->svg_process) {
		//ֹͣprocess����
		tmp_ret_int = stop_qt_svg_process(codec->svg_process);
		if (tmp_ret_int) {
			cp_module_log(error, codec, "stop_qt_svg_process() failed. qt_svg_process[0x%x].",
				codec->svg_process);
		}
		else {
			cp_module_log(notice, codec, "stop qt_svg_process[0x%x] success.",
				codec->svg_process);
		}
		//����process����
		destroy_svg_process(codec->svg_process);
		cp_module_log(notice, codec, "destroy_svg_process() success. qt_svg_process[0x%x].",
			codec->svg_process);
	}
	return 0;
}





/*ѡ���ģ�����*/
/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: cp_qt_svg_codec_set_option_process
*
* ����ȫ��: cp_qt_svg_codec_set_option_process
*
* ��������: public
*
* ����˵��: ѡ���ģ�����
*
* ��    ��: cp_qt_svg_codec_t * qt_svg_codec						[in/out]����˵��
* ��    ��: cp_int32_t optname						[in/out]����˵��
* ��    ��: const cp_void_t * optval						[in/out]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2018-2-2 9:27:00
********************************************************************************/
cp_int32_t cp_qt_svg_codec_set_option_process(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, const cp_void_t* optval)
{
	cp_int32_t					i = 0;
	cp_int32_t					tmp_ret_int = 0;


	//�ж��Ƿ�Ϊset option
	if (!CP_MODULE_OPTION_CHECK_SET_FLAG(optname)) {
		cp_module_log(error, qt_svg_codec,
			"invalid optname[%d]. please used \"CP_MODULE_OPTION_MAKE_SET_FLAG\" create option",
			optname);
		return -1;
	}

	//����option�����Ҷ�Ӧoption�Ĵ�����
	for (i = 0; i < cp_ary_size(cp_qt_svg_codec_option_handle_array); i++) {
		if (optname == cp_qt_svg_codec_option_handle_array[i].optname &&
			cp_qt_svg_codec_option_handle_array[i].set_option_handle) {
			//����option�Ĵ�����������option����
			tmp_ret_int = cp_qt_svg_codec_option_handle_array[i].set_option_handle(
				(cp_module_t *)qt_svg_codec, optname, optval);
			if (tmp_ret_int) {
				cp_module_log(error, qt_svg_codec,
					"process set option[optname:%d name:\"%s\" desc:\"%s\"] error. return[%d]",
					optname,
					cp_qt_svg_codec_option_handle_array[i].name,
					cp_qt_svg_codec_option_handle_array[i].description,
					tmp_ret_int);
			}
			else {
				cp_module_log(notice, qt_svg_codec,
					"process set option[optname:%d name:\"%s\" desc:\"%s\"] success.",
					optname,
					cp_qt_svg_codec_option_handle_array[i].name,
					cp_qt_svg_codec_option_handle_array[i].description);
			}

			//����״̬��Ϣ
			cp_qt_svg_codec_update_status(qt_svg_codec, optname, optval, tmp_ret_int);

			return tmp_ret_int;
		}
	}

	cp_module_log(error, qt_svg_codec, "unsupport set option[%d] error. ",
		optname);

	return cp_vdu_status_operation_option_failed;
}

/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: cp_qt_svg_codec_get_option_process
*
* ����ȫ��: cp_qt_svg_codec_get_option_process
*
* ��������: public
*
* ����˵��: ѡ���ģ�����
*
* ��    ��: cp_qt_svg_codec_t * qt_svg_codec						[in/out]����˵��
* ��    ��: cp_int32_t optname						[in/out]����˵��
* ��    ��: cp_void_t * optval						[in/out]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2018-2-2 9:27:09
********************************************************************************/
cp_int32_t cp_qt_svg_codec_get_option_process(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, cp_void_t* optval)
{
	cp_int32_t					i = 0;
	cp_int32_t					tmp_ret_int = 0;


	//�ж��Ƿ�Ϊset option
	if (!CP_MODULE_OPTION_CHECK_GET_FLAG(optname)) {
		cp_module_log(error, qt_svg_codec,
			"invalid optname[%d]. please used \"CP_MODULE_OPTION_MAKE_GET_FLAG\" create option",
			optname);
		return -1;
	}

	//����option�����Ҷ�Ӧoption�Ĵ�����
	for (i = 0; i < cp_ary_size(cp_qt_svg_codec_option_handle_array); i++) {
		if (optname == cp_qt_svg_codec_option_handle_array[i].optname &&
			cp_qt_svg_codec_option_handle_array[i].get_option_handle) {
			//����option�Ĵ�����������option����
			tmp_ret_int = cp_qt_svg_codec_option_handle_array[i].get_option_handle(
				(cp_module_t *)qt_svg_codec, optname, optval);
			if (tmp_ret_int) {
				cp_module_log(error, qt_svg_codec,
					"process get option[optname:%d name:\"%s\" desc:\"%s\"] error. return[%d]",
					optname,
					cp_qt_svg_codec_option_handle_array[i].name,
					cp_qt_svg_codec_option_handle_array[i].description,
					tmp_ret_int);
			}
			else {
				cp_module_log(notice, qt_svg_codec,
					"process get option[optname:%d name:\"%s\" desc:\"%s\"] success.",
					optname,
					cp_qt_svg_codec_option_handle_array[i].name,
					cp_qt_svg_codec_option_handle_array[i].description);
			}

			//����״̬��Ϣ
			cp_qt_svg_codec_update_status(qt_svg_codec, optname, optval, tmp_ret_int);

			return tmp_ret_int;
		}
	}

	cp_module_log(error, qt_svg_codec, "unsupport get option[%d] error. ",
		optname);

	return cp_vdu_status_operation_option_failed;
}

cp_int32_t cp_qt_svg_codec_update_status(cp_qt_svg_codec_t *qt_svg_codec,
	cp_int32_t optname, const cp_void_t* optval, cp_int32_t status)
{
	if (!qt_svg_codec || !qt_svg_codec->svg_process || !optval) {
		return cp_vdu_status_null_pointer;
	}

	return cp_qt_svg_codec_update_process_status((cp_vdu_process_t *)optval, status);
#if 0

	cp_vdu_process_t			*tmp_vdu_process = CP_NULL;
	cp_vdu_channel_process_t	*tmp_vdu_channel_process = CP_NULL;


	if (!qt_svg_codec || !qt_svg_codec->svg_process || !optval) {
		return cp_vdu_status_null_pointer;
	}

	tmp_vdu_process = (cp_vdu_process_t *)optval;
	tmp_vdu_channel_process = (cp_vdu_channel_process_t *)optval;

	switch (optname)
	{
	case cp_qt_svg_process_option_create_channel:
	case cp_qt_svg_process_option_destroy_channel:
	case cp_qt_svg_process_option_destroy_all_channel:
	case cp_qt_svg_process_option_set_roi:
	case cp_qt_svg_process_option_clear_roi:
	case cp_qt_svg_process_option_set_coordinate:
	{
		return cp_qt_svg_codec_update_process_status(tmp_vdu_process, status);
	}
	break;
	//2��channel����
	case cp_qt_svg_channel_option_set_channel_index:
	case cp_qt_svg_channel_option_set_insert_channel:
	case cp_qt_svg_channel_option_set_remove_channel:
	case cp_qt_svg_channel_option_set_roi:
	case cp_qt_svg_channel_option_clear_roi:
	case cp_qt_svg_channel_option_set_vector_stream:
	{
		return cp_qt_svg_codec_update_channel_process_status(tmp_vdu_channel_process, status);
	}
	break;
	//��ȡѡ��
	//1��process����
	case cp_qt_svg_process_option_get_roi:
	case cp_qt_svg_process_option_get_roi_pixel:
	case cp_qt_svg_process_option_get_rect_pixel:
	case cp_qt_svg_process_option_get_status:
	case cp_qt_svg_process_option_get_coordinate:
	{
		return cp_qt_svg_codec_update_process_status(tmp_vdu_process, status);
	}
	break;
	//2��channelͨ������
	case cp_qt_svg_channel_option_get_channel_index:
	case cp_qt_svg_channel_option_get_roi:
	case cp_qt_svg_channel_option_get_roi_pixel:
	case cp_qt_svg_channel_option_get_rect_pixel:
	case cp_qt_svg_channel_option_get_status:
	{
		return cp_qt_svg_codec_update_channel_process_status(tmp_vdu_channel_process, status);
	}
	break;
	default:
	{

	}
	break;
	}
	return 0;
#endif
}

//����status״̬��Ϣ
cp_int32_t cp_qt_svg_codec_update_process_status(
	cp_vdu_process_t *vdu_process, cp_int32_t status)
{
	if (!vdu_process) {
		return cp_vdu_status_null_pointer;
	}

	vdu_process->error_no = status;

	return 0;
}

cp_int32_t cp_qt_svg_codec_update_channel_process_status(
	cp_vdu_channel_process_t *vdu_channel_process, cp_int32_t status)
{
	if (!vdu_channel_process) {
		return cp_vdu_status_null_pointer;
	}

	vdu_channel_process->error_no = status;

	return 0;
}







cp_int32_t cp_qt_svg_codec_set_option_process_create_channel(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, const cp_void_t* optval)
{
	cp_qt_svg_channel_t			*tmp_qt_svg_channel = CP_NULL;
	cp_vdu_channel_process_t	*tmp_vdu_channel_process = CP_NULL;



	if (!qt_svg_codec || !qt_svg_codec->svg_process || !optval) {
		return cp_vdu_status_null_pointer;
	}
	tmp_vdu_channel_process = (cp_vdu_channel_process_t *)optval;

	//����qt_svg_channel
	tmp_qt_svg_channel = qt_svg_process_create_max_svg_channel(qt_svg_codec->svg_process);
	if (!tmp_qt_svg_channel) {
		return cp_vdu_status_system_error;
	}

	//���ö������
	tmp_vdu_channel_process->channel = tmp_qt_svg_channel;
	tmp_vdu_channel_process->index = tmp_vdu_channel_process->index;

	return 0;
}

//����channel��ͨ��������
cp_int32_t cp_qt_svg_codec_set_option_process_set_channel_index(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, const cp_void_t* optval)
{
	cp_int32_t							tmp_ret_int = 0;
	cp_qt_svg_channel_t					*tmp_qt_svg_channel = CP_NULL;
	cp_vdu_channel_process_t			*tmp_vdu_channel_process = CP_NULL;



	if (!qt_svg_codec || !qt_svg_codec->svg_process || !optval) {
		return cp_vdu_status_null_pointer;
	}
	tmp_vdu_channel_process = (cp_vdu_channel_process_t *)optval;
	tmp_qt_svg_channel = (cp_qt_svg_channel_t *)tmp_vdu_channel_process->channel;

	//����channel��index����
	tmp_ret_int = qt_svg_process_update_svg_channel_index(
		tmp_qt_svg_channel->process, tmp_qt_svg_channel, tmp_vdu_channel_process->index);
	if (tmp_ret_int) {
		return tmp_ret_int;
	}

	return 0;
}

cp_int32_t cp_qt_svg_codec_set_option_process_destroy_channel(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, const cp_void_t* optval)
{
	cp_int32_t							tmp_ret_int = 0;
	cp_qt_svg_channel_t					*tmp_qt_svg_channel = CP_NULL;
	cp_vdu_channel_process_t			*tmp_vdu_channel_process = CP_NULL;



	if (!qt_svg_codec || !qt_svg_codec->svg_process || !optval) {
		return cp_vdu_status_null_pointer;
	}
	tmp_vdu_channel_process = (cp_vdu_channel_process_t *)optval;
	tmp_qt_svg_channel = (cp_qt_svg_channel_t *)tmp_vdu_channel_process->channel;

	//����channel
	tmp_ret_int = qt_svg_process_destroy_svg_channel(
		tmp_qt_svg_channel->process, tmp_qt_svg_channel);
	if (tmp_ret_int) {
		return tmp_ret_int;
	}

	return 0;
}

/*��������ģ��*/
cp_int32_t cp_qt_svg_codec_set_option_process_destroy_all_channel(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, const cp_void_t* optval)
{
	cp_int32_t					tmp_ret_int = 0;
	cp_qt_svg_process_t			*tmp_qt_svg_process = CP_NULL;
	cp_vdu_process_t			*tmp_vdu_process = CP_NULL;



	if (!qt_svg_codec || !qt_svg_codec->svg_process || !optval) {
		return cp_vdu_status_null_pointer;
	}
	tmp_vdu_process = (cp_vdu_process_t *)optval;
	tmp_qt_svg_process = qt_svg_codec->svg_process;

	//����channel
	tmp_ret_int = qt_svg_process_destroy_all_svg_channel(tmp_qt_svg_process);
	if (tmp_ret_int) {
		return tmp_ret_int;
	}

	return 0;
}

/*����ģ��ĸ���Ȥ����*/
cp_int32_t cp_qt_svg_codec_set_option_process_set_roi(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, const cp_void_t* optval)
{
	cp_int32_t					tmp_ret_int = 0;
	cp_qt_svg_process_t			*tmp_qt_svg_process = CP_NULL;
	cp_vdu_process_t			*tmp_vdu_process = CP_NULL;



	if (!qt_svg_codec || !qt_svg_codec->svg_process || !optval) {
		return cp_vdu_status_null_pointer;
	}
	tmp_vdu_process = (cp_vdu_process_t *)optval;
	tmp_qt_svg_process = qt_svg_codec->svg_process;

	//����process��roi����
	tmp_ret_int = qt_svg_process_set_roi(tmp_qt_svg_process,
		tmp_vdu_process->vdu_rect);
	if (tmp_ret_int) {
		return tmp_ret_int;
	}

	return 0;
}

/*���ģ��ĸ���Ȥ����*/
cp_int32_t cp_qt_svg_codec_set_option_process_clear_roi(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, const cp_void_t* optval)
{
	cp_int32_t					tmp_ret_int = 0;
	cp_qt_svg_process_t			*tmp_qt_svg_process = CP_NULL;
	cp_vdu_process_t			*tmp_vdu_process = CP_NULL;



	if (!qt_svg_codec || !qt_svg_codec->svg_process || !optval) {
		return cp_vdu_status_null_pointer;
	}
	tmp_vdu_process = (cp_vdu_process_t *)optval;
	tmp_qt_svg_process = qt_svg_codec->svg_process;

	//����process��roi����
	tmp_ret_int = qt_svg_process_clear_roi(tmp_qt_svg_process);
	if (tmp_ret_int) {
		return tmp_ret_int;
	}

	return 0;
}

/*����ģ�������ռ�*/
cp_int32_t cp_qt_svg_codec_set_option_process_set_coordinate(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, const cp_void_t* optval)
{
	cp_int32_t					tmp_ret_int = 0;
	cp_qt_svg_process_t			*tmp_qt_svg_process = CP_NULL;
	cp_vdu_process_t			*tmp_vdu_process = CP_NULL;



	if (!qt_svg_codec || !qt_svg_codec->svg_process || !optval) {
		return cp_vdu_status_null_pointer;
	}
	tmp_vdu_process = (cp_vdu_process_t *)optval;
	tmp_qt_svg_process = qt_svg_codec->svg_process;

	//����process��coordinate����
	tmp_ret_int = qt_svg_process_set_coordinate(tmp_qt_svg_process,
		tmp_vdu_process->coordinate);
	if (tmp_ret_int) {
		return tmp_ret_int;
	}

	return 0;
}

/*����debug��Ϣ*/
cp_int32_t cp_qt_svg_codec_set_option_process_set_debug_info(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, const cp_void_t* optval)
{
	cp_int32_t									tmp_ret_int = 0;
	cp_qt_svg_process_t							*tmp_qt_svg_process = CP_NULL;
	cp_vdu_process_t							*tmp_vdu_process = CP_NULL;
	cp_qt_svg_process_debug_info_t				tmp_debug_info;



	if (!qt_svg_codec || !qt_svg_codec->svg_process || !optval) {
		return cp_vdu_status_null_pointer;
	}
	tmp_vdu_process = (cp_vdu_process_t *)optval;
	tmp_qt_svg_process = qt_svg_codec->svg_process;

	tmp_debug_info.is_save_file = tmp_vdu_process->is_debug_mode;
	if (tmp_debug_info.is_save_file) {
		if (tmp_vdu_process->debug_path &&
			cp_strlen(tmp_vdu_process->debug_path) < cp_sizeof(tmp_qt_svg_process->debug_info.path)) {
			cp_strcpy(tmp_debug_info.path, tmp_vdu_process->debug_path);
		}
	}

	//����process��coordinate����
	tmp_ret_int = qt_svg_process_set_debug_info(tmp_qt_svg_process, tmp_debug_info);
	if (tmp_ret_int) {
		return tmp_ret_int;
	}

	return 0;
}

/*����ͨ��*/
cp_int32_t cp_qt_svg_codec_set_option_channel_set_insert_channel(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, const cp_void_t* optval)
{
	cp_int32_t					tmp_ret_int = 0;
	cp_qt_svg_process_t			*tmp_qt_svg_process = CP_NULL;
	cp_vdu_process_t			*tmp_vdu_process = CP_NULL;
	cp_qt_svg_channel_t			*tmp_qt_svg_channel = CP_NULL;



	if (!qt_svg_codec || !qt_svg_codec->svg_process || !optval) {
		return cp_vdu_status_null_pointer;
	}
	tmp_vdu_process = (cp_vdu_process_t *)optval;
	tmp_qt_svg_process = qt_svg_codec->svg_process;
	tmp_qt_svg_channel = (cp_qt_svg_channel_t *)tmp_vdu_process->channel;

	//����channel
	tmp_ret_int = qt_svg_process_insert_svg_channel(tmp_qt_svg_process,
		tmp_qt_svg_channel,
		tmp_vdu_process->vdu_rect);
	if (tmp_ret_int) {
		return tmp_ret_int;
	}

	return 0;
}

/*ɾ��ͨ��*/
cp_int32_t cp_qt_svg_codec_set_option_channel_set_remove_channel(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, const cp_void_t* optval)
{
	cp_int32_t					tmp_ret_int = 0;
	cp_qt_svg_process_t			*tmp_qt_svg_process = CP_NULL;
	cp_qt_svg_channel_t			*tmp_qt_svg_channel = CP_NULL;
	cp_vdu_process_t			*tmp_vdu_process = CP_NULL;



	if (!qt_svg_codec || !qt_svg_codec->svg_process || !optval) {
		return cp_vdu_status_null_pointer;
	}
	tmp_vdu_process = (cp_vdu_process_t *)optval;
	tmp_qt_svg_process = qt_svg_codec->svg_process;
	tmp_qt_svg_channel = (cp_qt_svg_channel_t *)tmp_vdu_process->channel;

	//ɾ��channel
	tmp_ret_int = qt_svg_process_remove_svg_channel(tmp_qt_svg_process,
		tmp_qt_svg_channel);
	if (tmp_ret_int) {
		return tmp_ret_int;
	}

	return 0;
}

/*����ͨ���ĸ���Ȥ����*/
cp_int32_t cp_qt_svg_codec_set_option_channel_set_roi(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, const cp_void_t* optval)
{
	cp_int32_t					tmp_ret_int = 0;
	cp_qt_svg_channel_t			*tmp_qt_svg_channel = CP_NULL;
	cp_vdu_channel_process_t	*tmp_vdu_channel_process = CP_NULL;



	if (!qt_svg_codec || !qt_svg_codec->svg_process || !optval) {
		return cp_vdu_status_null_pointer;
	}
	tmp_vdu_channel_process = (cp_vdu_channel_process_t *)optval;
	tmp_qt_svg_channel = (cp_qt_svg_channel_t *)tmp_vdu_channel_process->channel;

	//����roi����
	tmp_ret_int = qt_svg_channel_set_roi(tmp_qt_svg_channel,
		tmp_vdu_channel_process->vdu_rect);
	if (tmp_ret_int) {
		return tmp_ret_int;
	}

	return 0;
}

/*���ͨ���ĸ���Ȥ����*/
cp_int32_t cp_qt_svg_codec_set_option_channel_clear_roi(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, const cp_void_t* optval)
{
	cp_int32_t					tmp_ret_int = 0;
	cp_qt_svg_channel_t			*tmp_qt_svg_channel = CP_NULL;
	cp_vdu_channel_process_t	*tmp_vdu_channel_process = CP_NULL;



	if (!qt_svg_codec || !qt_svg_codec->svg_process || !optval) {
		return cp_vdu_status_null_pointer;
	}
	tmp_vdu_channel_process = (cp_vdu_channel_process_t *)optval;
	tmp_qt_svg_channel = (cp_qt_svg_channel_t *)tmp_vdu_channel_process->channel;

	//���channel��roi����
	tmp_ret_int = qt_svg_channel_clear_roi(tmp_qt_svg_channel);
	if (tmp_ret_int) {
		return tmp_ret_int;
	}

	return 0;
}

/*����ʸ��������*/
cp_int32_t cp_qt_svg_codec_set_option_channel_set_vector_stream(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, const cp_void_t* optval)
{
	cp_int32_t					tmp_ret_int = 0;
	cp_qt_svg_channel_t			*tmp_qt_svg_channel = CP_NULL;
	cp_vdu_channel_process_t	*tmp_vdu_channel_process = CP_NULL;



	if (!qt_svg_codec || !qt_svg_codec->svg_process || !optval) {
		return cp_vdu_status_null_pointer;
	}
	tmp_vdu_channel_process = (cp_vdu_channel_process_t *)optval;
	tmp_qt_svg_channel = (cp_qt_svg_channel_t *)tmp_vdu_channel_process->channel;

	//����svg �ļ�������
	tmp_ret_int = qt_svg_channel_vector_stream(tmp_qt_svg_channel,
		(cp_uchar_t *)(tmp_vdu_channel_process->buf),
		tmp_vdu_channel_process->buf_length);
	if (tmp_ret_int) {
		return tmp_ret_int;
	}

	return 0;
}






/*��ȡģ��ĸ���Ȥ����*/
cp_int32_t cp_qt_svg_codec_set_option_process_get_roi(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, cp_void_t* optval)
{
	cp_int32_t					tmp_ret_int = 0;
	cp_qt_svg_process_t			*tmp_qt_svg_process = CP_NULL;
	cp_vdu_process_t			*tmp_vdu_process = CP_NULL;



	if (!qt_svg_codec || !qt_svg_codec->svg_process || !optval) {
		return cp_vdu_status_null_pointer;
	}
	tmp_vdu_process = (cp_vdu_process_t *)optval;
	tmp_qt_svg_process = qt_svg_codec->svg_process;

	//��ȡprocess��roi����
	tmp_ret_int = qt_svg_process_get_roi(tmp_qt_svg_process,
		&(tmp_vdu_process->vdu_rect));
	if (tmp_ret_int) {
		return tmp_ret_int;
	}

	return 0;
}

/*��ȡģ��ĸ���Ȥ�����ͼ������*/
cp_int32_t cp_qt_svg_codec_set_option_process_get_roi_pixel(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, cp_void_t* optval)
{
	cp_int32_t					tmp_ret_int = 0;
	cp_qt_svg_process_t			*tmp_qt_svg_process = CP_NULL;
	cp_vdu_process_t			*tmp_vdu_process = CP_NULL;



	if (!qt_svg_codec || !qt_svg_codec->svg_process || !optval) {
		return cp_vdu_status_null_pointer;
	}
	tmp_vdu_process = (cp_vdu_process_t *)optval;
	tmp_qt_svg_process = qt_svg_codec->svg_process;

	//��ȡprocess��roi����
	tmp_ret_int = qt_svg_process_get_roi_pixel(tmp_qt_svg_process,
		tmp_vdu_process->buf,
		tmp_vdu_process->buf_length,
		tmp_vdu_process->pixel_format,
		CP_NULL);
	if (tmp_ret_int <= 0) {
		return tmp_ret_int;
	}
	tmp_vdu_process->image_length = tmp_ret_int;

	return 0;
}

/*��ȡģ���ָ�������ͼ������*/
cp_int32_t cp_qt_svg_codec_set_option_process_get_rect_pixel(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, cp_void_t* optval)
{
	cp_int32_t					tmp_ret_int = 0;
	cp_qt_svg_process_t			*tmp_qt_svg_process = CP_NULL;
	cp_vdu_process_t			*tmp_vdu_process = CP_NULL;



	if (!qt_svg_codec || !qt_svg_codec->svg_process || !optval) {
		return cp_vdu_status_null_pointer;
	}
	tmp_vdu_process = (cp_vdu_process_t *)optval;
	tmp_qt_svg_process = qt_svg_codec->svg_process;

	//��ȡprocess��roi����
	tmp_ret_int = qt_svg_process_get_rect_pixel(tmp_qt_svg_process,
		tmp_vdu_process->buf,
		tmp_vdu_process->buf_length,
		tmp_vdu_process->pixel_format,
		tmp_vdu_process->vdu_rect,
		CP_NULL);
	if (tmp_ret_int <= 0) {
		return tmp_ret_int;
	}
	tmp_vdu_process->image_length = tmp_ret_int;

	return 0;
}

/*��ȡģ���״̬��*/
cp_int32_t cp_qt_svg_codec_set_option_process_get_status(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, cp_void_t* optval)
{
	cp_vdu_process_t			*tmp_vdu_process = CP_NULL;



	if (!qt_svg_codec || !qt_svg_codec->svg_process || !optval) {
		return cp_vdu_status_null_pointer;
	}
	tmp_vdu_process = (cp_vdu_process_t *)optval;
	tmp_vdu_process->error_no = tmp_vdu_process->error_no;

	return 0;
}

/*��ȡģ�������ռ���Ϣ*/
cp_int32_t cp_qt_svg_codec_set_option_process_get_coordinate(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, cp_void_t* optval)
{
	cp_int32_t					tmp_ret_int = 0;
	cp_qt_svg_process_t			*tmp_qt_svg_process = CP_NULL;
	cp_vdu_process_t			*tmp_vdu_process = CP_NULL;



	if (!qt_svg_codec || !qt_svg_codec->svg_process || !optval) {
		return cp_vdu_status_null_pointer;
	}
	tmp_vdu_process = (cp_vdu_process_t *)optval;
	tmp_qt_svg_process = qt_svg_codec->svg_process;

	//��ȡprocess��coordinate����
	tmp_ret_int = qt_svg_process_get_coordinate(tmp_qt_svg_process,
		&(tmp_vdu_process->coordinate));
	if (tmp_ret_int) {
		return tmp_ret_int;
	}

	return 0;
}





/*��ȡͨ����������*/
cp_int32_t cp_qt_svg_codec_get_option_channel_get_channel_index(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, cp_void_t* optval)
{
	cp_int32_t					tmp_ret_int = 0;
	cp_qt_svg_channel_t			*tmp_qt_svg_channel = CP_NULL;
	cp_vdu_channel_process_t	*tmp_vdu_channel_process = CP_NULL;



	if (!qt_svg_codec || !qt_svg_codec->svg_process || !optval) {
		return cp_vdu_status_null_pointer;
	}

	tmp_vdu_channel_process = (cp_vdu_channel_process_t *)optval;
	tmp_qt_svg_channel = (cp_qt_svg_channel_t *)tmp_vdu_channel_process->channel;

	tmp_vdu_channel_process->index = tmp_qt_svg_channel->channel.index;

	return 0;
}

/*��ȡͨ���ĸ���Ȥ����*/
cp_int32_t cp_qt_svg_codec_get_option_channel_get_roi(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, cp_void_t* optval)
{
	cp_int32_t					tmp_ret_int = 0;
	cp_qt_svg_channel_t			*tmp_qt_svg_channel = CP_NULL;
	cp_vdu_channel_process_t	*tmp_vdu_channel_process = CP_NULL;



	if (!qt_svg_codec || !qt_svg_codec->svg_process || !optval) {
		return cp_vdu_status_null_pointer;
	}
	tmp_vdu_channel_process = (cp_vdu_channel_process_t *)optval;
	tmp_qt_svg_channel = (cp_qt_svg_channel_t *)tmp_vdu_channel_process->channel;

	//����roi����
	tmp_ret_int = qt_svg_channel_get_roi(tmp_qt_svg_channel,
		&(tmp_vdu_channel_process->vdu_rect));
	if (tmp_ret_int) {
		return tmp_ret_int;
	}

	return 0;
}

/*��ȡͨ���ĸ���Ȥ�����ͼ������*/
cp_int32_t cp_qt_svg_codec_get_option_channel_get_roi_pixel(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, cp_void_t* optval)
{
	cp_int32_t					tmp_ret_int = 0;
	cp_qt_svg_channel_t			*tmp_qt_svg_channel = CP_NULL;
	cp_vdu_channel_process_t	*tmp_vdu_channel_process = CP_NULL;



	if (!qt_svg_codec || !qt_svg_codec->svg_process || !optval) {
		return cp_vdu_status_null_pointer;
	}
	tmp_vdu_channel_process = (cp_vdu_channel_process_t *)optval;
	tmp_qt_svg_channel = (cp_qt_svg_channel_t *)tmp_vdu_channel_process->channel;

	//����svg �ļ�������
	tmp_ret_int = qt_svg_channel_get_roi_pixel(tmp_qt_svg_channel,
		(cp_uchar_t *)(tmp_vdu_channel_process->buf),
		tmp_vdu_channel_process->buf_length,
		tmp_vdu_channel_process->pixel_format,
		CP_NULL);
	if (tmp_ret_int <= 0) {
		return tmp_ret_int;
	}
	tmp_vdu_channel_process->image_length = tmp_ret_int;

	return 0;
}

/*��ȡͨ����ָ�������ͼ������*/
cp_int32_t cp_qt_svg_codec_get_option_channel_get_rect_pixel(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, cp_void_t* optval)
{
	cp_int32_t					tmp_ret_int = 0;
	cp_qt_svg_channel_t			*tmp_qt_svg_channel = CP_NULL;
	cp_vdu_channel_process_t	*tmp_vdu_channel_process = CP_NULL;



	if (!qt_svg_codec || !qt_svg_codec->svg_process || !optval) {
		return cp_vdu_status_null_pointer;
	}
	tmp_vdu_channel_process = (cp_vdu_channel_process_t *)optval;
	tmp_qt_svg_channel = (cp_qt_svg_channel_t *)tmp_vdu_channel_process->channel;

	//����svg �ļ�������
	tmp_ret_int = qt_svg_channel_get_rect_pixel(tmp_qt_svg_channel,
		(cp_uchar_t *)(tmp_vdu_channel_process->buf),
		tmp_vdu_channel_process->buf_length,
		tmp_vdu_channel_process->pixel_format,
		tmp_vdu_channel_process->vdu_rect,
		CP_NULL);
	if (tmp_ret_int <= 0) {
		return tmp_ret_int;
	}
	tmp_vdu_channel_process->image_length = tmp_ret_int;

	return 0;
}

/*��ȡͨ����״̬��*/
cp_int32_t cp_qt_svg_codec_get_option_channel_get_status(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, cp_void_t* optval)
{
	cp_int32_t					tmp_ret_int = 0;
	cp_qt_svg_channel_t			*tmp_qt_svg_channel = CP_NULL;
	cp_vdu_channel_process_t	*tmp_vdu_channel_process = CP_NULL;



	if (!qt_svg_codec || !qt_svg_codec->svg_process || !optval) {
		return cp_vdu_status_null_pointer;
	}

	tmp_vdu_channel_process = (cp_vdu_channel_process_t *)optval;
	tmp_qt_svg_channel = (cp_qt_svg_channel_t *)tmp_vdu_channel_process->channel;

	tmp_vdu_channel_process->error_no = tmp_qt_svg_channel->error_no;

	return 0;
}





