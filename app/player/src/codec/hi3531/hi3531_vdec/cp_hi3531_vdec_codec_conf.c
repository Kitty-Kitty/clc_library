/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-20

Description:

**************************************************************************/
#include "cp_log.h"
#include "cp_conf.h"
#include "cp_hi3531_vdec_codec_conf.h"



cp_inline cp_static cp_bool_t get_module_conf_xml_int_prop(cp_int32_t *dest, cp_module_t *module,
	cp_conf_t *conf, const char *context, const char *key, int def)
{
	cp_int32_t							tmp_value = 0;



	if (!conf || !module) {
		return cp_false;
	}
	tmp_value = cp_conf_xml_getint(conf->conf_xml, context, key, def);
	if (tmp_value < 0) {
		cp_module_log(notice, module, "get [%s:%s] warning!", context, key);
		//return cp_false;
	}
	*dest = tmp_value;
	return cp_true;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: hi3531_vdec_codec_parse_configure
*
* ����˵��: ���������ļ�
*
* ��    ��: cp_module_t * module						[in]����˵��
* ��    ��: cp_hi3531_vdec_codec_configure_t * hacc						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-12-20 15:14:47
******************************************************************************************************/
cp_int32_t	hi3531_vdec_codec_parse_configure(cp_module_t *module, cp_hi3531_vdec_codec_configure_t *hacc)
{
	cp_int32_t						tmp_value = 0;
	cp_int32_t						tmp_ret_int = 0;



	if (!module || !hacc) {
		return -1;
	}

	//����vdec ����video �����ļ�
	tmp_ret_int = hi3531_vdec_codec_parse_video_configure(module, hacc);
	if (tmp_ret_int) {
		cp_module_log(error, module, "hi3531_vdec_codec_parse_video_configure() error.");
		return -1;
	}

	//�������ͨ������
	tmp_ret_int = hi3531_vdec_codec_parse_channel_param(module, hacc);
	if (tmp_ret_int) {
		cp_module_log(error, module, "hi3531_vdec_codec_parse_channel_param() error.");
		return -1;
	}

	//������Э����ص��ڴ�������
	tmp_ret_int = hi3531_vdec_codec_parse_prtcl_param(module, hacc);
	if (tmp_ret_int) {
		cp_module_log(error, module, "hi3531_vdec_codec_parse_prtcl_param() error.");
		return -1;
	}
	
	return 0;
}


/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: hi3531_vdec_codec_parse_video_configure
*
* ����˵��: ����vdec ����video �����ļ�
*
* ��    ��: cp_module_t *module						[in]����˵��
* ��    ��: cp_hi3531_configure_t * hacc						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-07-01 11:26:11
******************************************************************************************************/
cp_int32_t	hi3531_vdec_codec_parse_video_configure(cp_module_t *module, cp_hi3531_vdec_codec_configure_t *hacc)
{
	cp_int32_t						tmp_value = 0;
	cp_int32_t						tmp_ret_int = 0;



	if (!module || !hacc) {
		return -1;
	}

	//����vdec_max_width
	if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
		CP_HI3531_VIDEO_VDEC_CONF_STRING_VDEC_VIDEO_ATTR, CP_HI3531_VIDEO_VDEC_CONF_STRING_VDEC_MAX_WIDTH, 0)) {
		return -1;
	}
	hacc->vdec_video_conf.vdec_max_width = tmp_value;

	//����vdec_max_height
	if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
		CP_HI3531_VIDEO_VDEC_CONF_STRING_VDEC_VIDEO_ATTR, CP_HI3531_VIDEO_VDEC_CONF_STRING_VDEC_MAX_HEIGHT, 0)) {
		return -1;
	}
	hacc->vdec_video_conf.vdec_max_height = tmp_value;

	//����vdec_ref_frame_number
	if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
		CP_HI3531_VIDEO_VDEC_CONF_STRING_VDEC_VIDEO_ATTR, CP_HI3531_VIDEO_VDEC_CONF_STRING_VDEC_REF_FRAME_NUMBER, 0)) {
		return -1;
	}
	hacc->vdec_video_conf.vdec_ref_frame_number = tmp_value;

	//����vdec_stream_mode
	if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
		CP_HI3531_VIDEO_VDEC_CONF_STRING_VDEC_VIDEO_ATTR, CP_HI3531_VIDEO_VDEC_CONF_STRING_VDEC_STREAM_MODE, 0)) {
		return -1;
	}
	hacc->vdec_video_conf.vdec_stream_mode = tmp_value;

	//����vdec_support_bframe
	if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
		CP_HI3531_VIDEO_VDEC_CONF_STRING_VDEC_VIDEO_ATTR, CP_HI3531_VIDEO_VDEC_CONF_STRING_VDEC_SUPPORT_BFRAME, 0)) {
		return -1;
	}
	hacc->vdec_video_conf.vdec_support_bframe = tmp_value;

	//����vdec_default_priority
	if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
		CP_HI3531_VIDEO_VDEC_CONF_STRING_VDEC_VIDEO_ATTR, CP_HI3531_VIDEO_VDEC_CONF_STRING_VDEC_DEFAULT_PRIORITY, 0)) {
		return -1;
	} else {
		if (tmp_value < CP_HI3531_VIDEO_VDEC_CONF_VDEC_DEFAULT_PRIORITY_MIN_VALUE || 
			tmp_value > CP_HI3531_VIDEO_VDEC_CONF_VDEC_DEFAULT_PRIORITY_MAX_VALUE) {
			cp_module_log(error, module,
				"hi3531 xml configure[%s:%s] value[%d] invalid error. value must into[%d, %d]",
				CP_HI3531_VIDEO_VDEC_CONF_STRING_VDEC_VIDEO_ATTR,
				CP_HI3531_VIDEO_VDEC_CONF_STRING_VDEC_DEFAULT_PRIORITY,
				tmp_value,
				CP_HI3531_VIDEO_VDEC_CONF_VDEC_DEFAULT_PRIORITY_MIN_VALUE,
				CP_HI3531_VIDEO_VDEC_CONF_VDEC_DEFAULT_PRIORITY_MAX_VALUE);
			return -4;
		}

		hacc->vdec_video_conf.vdec_default_priority = tmp_value;
	}
	

	return 0;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: hi3531_vdec_codec_parse_channel_param
*
* ����˵��: �������ͨ������
*
* ��    ��: cp_module_t * module						[in]����˵��
* ��    ��: cp_hi3531_vdec_codec_configure_t * hacc						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-07-01 12:29:14
******************************************************************************************************/
cp_int32_t	hi3531_vdec_codec_parse_channel_param(cp_module_t *module, cp_hi3531_vdec_codec_configure_t *hacc)
{
	cp_int32_t						tmp_value = 0;
	cp_int32_t						tmp_ret_int = 0;



	if (!module || !hacc) {
		return -1;
	}

	//����channel_err_thr
	if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
		CP_HI3531_VIDEO_VDEC_CONF_STRING_VDEC_VIDEO_CHANNEL_PRARAM, CP_HI3531_VIDEO_VDEC_CONF_STRING_CHANNEL_ERR_THR, 0)) {
		return -1;
	}
	hacc->vdec_channle_param.channel_err_thr = tmp_value;

	//����channel_stream_of_thr
	if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
		CP_HI3531_VIDEO_VDEC_CONF_STRING_VDEC_VIDEO_CHANNEL_PRARAM, CP_HI3531_VIDEO_VDEC_CONF_STRING_CHANNEL_STREAM_OF_THR, 0)) {
		return -1;
	}
	hacc->vdec_channle_param.channel_stream_of_thr = tmp_value;

	//����decode_mode
	if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
		CP_HI3531_VIDEO_VDEC_CONF_STRING_VDEC_VIDEO_CHANNEL_PRARAM, CP_HI3531_VIDEO_VDEC_CONF_STRING_DECODE_MODE, 0)) {
		return -1;
	}
	hacc->vdec_channle_param.decode_mode = tmp_value;

	//����decode_order_output
	if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
		CP_HI3531_VIDEO_VDEC_CONF_STRING_VDEC_VIDEO_CHANNEL_PRARAM, CP_HI3531_VIDEO_VDEC_CONF_STRING_DECODE_ORDER_OUTPUT, 0)) {
		return -1;
	}
	hacc->vdec_channle_param.decode_order_output = tmp_value;

	return 0;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: hi3531_vdec_codec_parse_prtcl_param
*
* ����˵��: ������Э����ص��ڴ�������
*
* ��    ��: cp_module_t * module						[in]����˵��
* ��    ��: cp_hi3531_vdec_codec_configure_t * hacc						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-07-01 12:44:26
******************************************************************************************************/
cp_int32_t	hi3531_vdec_codec_parse_prtcl_param(cp_module_t *module, cp_hi3531_vdec_codec_configure_t *hacc)
{
	cp_int32_t						tmp_value = 0;
	cp_int32_t						tmp_ret_int = 0;



	if (!module || !hacc) {
		return -1;
	}

	//����max_slice_number
	if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
		CP_HI3531_VIDEO_VDEC_CONF_STRING_VDEC_VIDEO_PRTCL_PRARAM, CP_HI3531_VIDEO_VDEC_CONF_STRING_MAX_SLICE_NUMBER, 0)) {
		return -1;
	}
	hacc->vdec_prtcl_param.max_slice_number = tmp_value;

	//����max_sps_number
	if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
		CP_HI3531_VIDEO_VDEC_CONF_STRING_VDEC_VIDEO_PRTCL_PRARAM, CP_HI3531_VIDEO_VDEC_CONF_STRING_MAX_SPS_NUMBER, 0)) {
		return -1;
	}
	hacc->vdec_prtcl_param.max_sps_number = tmp_value;

	//����max_pps_number
	if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
		CP_HI3531_VIDEO_VDEC_CONF_STRING_VDEC_VIDEO_PRTCL_PRARAM, CP_HI3531_VIDEO_VDEC_CONF_STRING_MAX_PPS_NUMBER, 0)) {
		return -1;
	}
	hacc->vdec_prtcl_param.max_pps_number = tmp_value;

	//����scd_buffer_size
	if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
		CP_HI3531_VIDEO_VDEC_CONF_STRING_VDEC_VIDEO_PRTCL_PRARAM, CP_HI3531_VIDEO_VDEC_CONF_STRING_SCD_BUFFER_SIZE, 0)) {
		return -1;
	}
	hacc->vdec_prtcl_param.scd_buffer_size = tmp_value;

	//����display_frame_number
	if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
		CP_HI3531_VIDEO_VDEC_CONF_STRING_VDEC_VIDEO_PRTCL_PRARAM, CP_HI3531_VIDEO_VDEC_CONF_STRING_DISPLAY_FRAME_NUMBER, 0)) {
		return -1;
	}
	hacc->vdec_prtcl_param.display_frame_number = tmp_value;


	return 0;
}