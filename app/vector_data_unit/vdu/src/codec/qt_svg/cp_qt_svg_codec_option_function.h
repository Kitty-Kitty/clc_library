/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-08-09

Description:

**************************************************************************/

#ifndef _CP_QT_SVG_CODEC_OPTION_FUNCTION_INCLUDE_H_
#define _CP_QT_SVG_CODEC_OPTION_FUNCTION_INCLUDE_H_



#include "cp_qt_svg_codec_core.h"


#ifdef __cplusplus
extern "C" {
#endif

//��ʼ��option handle��������
cp_int32_t cp_qt_svg_codec_create_option_handle(cp_qt_svg_codec_t *codec);
cp_int32_t cp_qt_svg_codec_destroy_option_handle(cp_qt_svg_codec_t *codec);





/*ѡ���ģ�����*/
cp_int32_t cp_qt_svg_codec_set_option_process(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, const cp_void_t* optval);
cp_int32_t cp_qt_svg_codec_get_option_process(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, cp_void_t* optval);

//����status״̬��Ϣ
cp_int32_t cp_qt_svg_codec_update_status(cp_qt_svg_codec_t *qt_svg_codec,
	cp_int32_t optname, const cp_void_t* optval, cp_int32_t status);
cp_int32_t cp_qt_svg_codec_update_process_status(cp_vdu_process_t *vdu_process, cp_int32_t status);
cp_int32_t cp_qt_svg_codec_update_channel_process_status(cp_vdu_channel_process_t *vdu_channel_process, cp_int32_t status);


/*����ģ�����*/
cp_int32_t cp_qt_svg_codec_set_option_process_create_channel(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, const cp_void_t* optval);

/*����channel��ͨ��������*/
cp_int32_t cp_qt_svg_codec_set_option_process_set_channel_index(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, const cp_void_t* optval);

/*����ģ��*/
cp_int32_t cp_qt_svg_codec_set_option_process_destroy_channel(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, const cp_void_t* optval);

/*��������ģ��*/
cp_int32_t cp_qt_svg_codec_set_option_process_destroy_all_channel(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, const cp_void_t* optval);

/*����ģ��ĸ���Ȥ����*/
cp_int32_t cp_qt_svg_codec_set_option_process_set_roi(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, const cp_void_t* optval);

/*���ģ��ĸ���Ȥ����*/
cp_int32_t cp_qt_svg_codec_set_option_process_clear_roi(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, const cp_void_t* optval);

/*����ģ�������ռ�*/
cp_int32_t cp_qt_svg_codec_set_option_process_set_coordinate(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, const cp_void_t* optval);

/*����debug��Ϣ*/
cp_int32_t cp_qt_svg_codec_set_option_process_set_debug_info(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, const cp_void_t* optval);


/*����ͨ��*/
cp_int32_t cp_qt_svg_codec_set_option_channel_set_insert_channel(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, const cp_void_t* optval);

/*ɾ��ͨ��*/
cp_int32_t cp_qt_svg_codec_set_option_channel_set_remove_channel(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, const cp_void_t* optval);

/*����ͨ���ĸ���Ȥ����*/
cp_int32_t cp_qt_svg_codec_set_option_channel_set_roi(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, const cp_void_t* optval);

/*���ͨ���ĸ���Ȥ����*/
cp_int32_t cp_qt_svg_codec_set_option_channel_clear_roi(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, const cp_void_t* optval);

/*����ʸ��������*/
cp_int32_t cp_qt_svg_codec_set_option_channel_set_vector_stream(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, const cp_void_t* optval);






/*��ȡģ��ĸ���Ȥ����*/
cp_int32_t cp_qt_svg_codec_set_option_process_get_roi(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, cp_void_t* optval);

/*��ȡģ��ĸ���Ȥ�����ͼ������*/
cp_int32_t cp_qt_svg_codec_set_option_process_get_roi_pixel(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, cp_void_t* optval);

/*��ȡģ���ָ�������ͼ������*/
cp_int32_t cp_qt_svg_codec_set_option_process_get_rect_pixel(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, cp_void_t* optval);

/*��ȡģ���״̬��*/
cp_int32_t cp_qt_svg_codec_set_option_process_get_status(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, cp_void_t* optval);

/*��ȡģ�������ռ���Ϣ*/
cp_int32_t cp_qt_svg_codec_set_option_process_get_coordinate(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, cp_void_t* optval);





/*��ȡͨ����������*/
cp_int32_t cp_qt_svg_codec_get_option_channel_get_channel_index(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, cp_void_t* optval);

/*��ȡͨ���ĸ���Ȥ����*/
cp_int32_t cp_qt_svg_codec_get_option_channel_get_roi(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, cp_void_t* optval);

/*��ȡͨ���ĸ���Ȥ�����ͼ������*/
cp_int32_t cp_qt_svg_codec_get_option_channel_get_roi_pixel(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, cp_void_t* optval);

/*��ȡͨ����ָ�������ͼ������*/
cp_int32_t cp_qt_svg_codec_get_option_channel_get_rect_pixel(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, cp_void_t* optval);

/*��ȡͨ����״̬��*/
cp_int32_t cp_qt_svg_codec_get_option_channel_get_status(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, cp_void_t* optval);





#ifdef __cplusplus
}
#endif

#endif