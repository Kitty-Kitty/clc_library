/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_QT_SVG_CHANNEL_INCLUDE_H_
#define _CP_QT_SVG_CHANNEL_INCLUDE_H_

#include "cp_qt_svg_include.h"




#pragma pack(1)


/************************************************************************/
/*���ﶨ��һ��ͼ�β�                                                     */
/************************************************************************/
struct cp_qt_svg_channel_info_s {
	cp_int32_t								index;
};


/************************************************************************/
/*���ﶨ��һ��ͼ�β�                                                     */
/************************************************************************/
struct cp_qt_svg_channel_scene_s {
	cp_qt_svg_process_t						*process;			//��ʾ�������ڵ�ͼ�δ�����
	cp_bool_t								is_render_scene;	//��ʾ�Ƿ���Ⱦ��������cp_true��ʾ��Ⱦ��cp_false��ʾ����Ⱦ
	cp_rect_t								rect;				//��ʾͨ����Գ�����������Ϣ
};


/************************************************************************/
/*���ﶨ��һ��ͼ�β�                                                     */
/************************************************************************/
struct cp_qt_svg_channel_s {
	cp_qt_svg_process_t						*process;			//��ʾһ��ͼ�δ�����
	cp_qt_svg_channel_info_t				info;				//��ʾͨ����Ϣ
	cp_qt_svg_channel_scene_t				scene;				//��ʾͨ����Գ�������Ϣ
	cp_channel_t							channel;			//��ʾͨ��������Ϣ
	QGraphicsSvgItem						*item;				//��ʾһ��svgͼ��
	QSvgRenderer							*render;			//��ʾһ��svg render����
	CP_MODULE_ERROR_FIELDS										//��ʾ�������
};




#pragma pack()


#ifdef __cplusplus
extern "C" {
#endif


	/*����qt_svg_channel ��Ϣ*/
	cp_qt_svg_channel_t* create_qt_svg_channel(cp_qt_svg_process_t *process, cp_qt_svg_channel_info_t *info);

	/*����qt_svg_channel ��Ϣ*/
	cp_int32_t destroy_qt_svg_channel(cp_qt_svg_channel_t *channel);





	/*��ʼ��qt_svg_channel ��Ϣ*/
	cp_int32_t init_qt_svg_channel(cp_qt_svg_channel_t *channel, cp_qt_svg_channel_info_t *channel_info);




	/*����qt_svg_channel ��Ϣ*/
	cp_int32_t start_qt_svg_channel(cp_qt_svg_channel_t *channel, cp_qt_svg_channel_info_t *channel_info);

	//����svg������Դ
	cp_int32_t qt_svg_channel_create_source(cp_qt_svg_channel_t *channel);
	//����svg������Դ
	cp_int32_t qt_svg_channel_destroy_source(cp_qt_svg_channel_t *channel);

	//У���Ƿ��Ѿ�׼����
	cp_int32_t qt_svg_channel_check_ready(cp_qt_svg_channel_t *channel);

	/*����svgͼƬ������*/
	cp_int32_t qt_svg_channel_vector_stream(cp_qt_svg_channel_t *channel, cp_uchar_t *buf, cp_uint32_t len);

	//���ñ����ļ���Ϣ
	cp_int32_t qt_svg_channel_save_file(cp_qt_svg_channel_t *channel, QImage *image);

	/*���svgͼƬ�ĸ���Ȥ��������*/
	cp_int32_t qt_svg_channel_clear_roi(cp_qt_svg_channel_t *channel);
	/*����svgͼƬ�ĸ���Ȥ��������*/
	cp_int32_t qt_svg_channel_set_roi(cp_qt_svg_channel_t *channel,
		cp_rect_t rect);
	/*��ȡsvgͼƬ�ĸ���Ȥ��������*/
	cp_int32_t qt_svg_channel_get_roi(cp_qt_svg_channel_t *channel,
		cp_rect_t *dest_rect);

	/*��ȡsvg����Ȥ�������ݵ�ͼƬ����*/
	cp_int32_t qt_svg_channel_get_roi_pixel(cp_qt_svg_channel_t *channel,
		cp_uchar_t *dest_buf,
		cp_uint32_t buf_len,
		cp_codec_pixel_format_e cpf,
		cp_rect_t *image_rect);

	/*��ȡsvgָ�������ͼƬ����*/
	cp_int32_t qt_svg_channel_get_rect_pixel(cp_qt_svg_channel_t *channel,
		cp_uchar_t *dest_buf,
		cp_uint32_t buf_len,
		cp_codec_pixel_format_e cpf,
		cp_rect_t rect,
		cp_rect_t *image_rect);

	/*��ʾ���볡��*/
	cp_int32_t qt_svg_channel_insert_scene(cp_qt_svg_process_t *process, cp_qt_svg_channel_t *channel, cp_rect_t rect);
	/*��ʾ�˳�����*/
	cp_int32_t qt_svg_channel_remove_scene(cp_qt_svg_process_t *process, cp_qt_svg_channel_t *channel);
	/*��ʾ�޸�ͨ����index����ͼ������*/
	cp_int32_t qt_svg_channel_update_index(cp_qt_svg_channel_t *channel, cp_int32_t index);


	/*ֹͣqt_svg_channel ��Ϣ*/
	cp_int32_t stop_qt_svg_channel(cp_qt_svg_channel_t *channel);


#ifdef __cplusplus
};
#endif


#endif


