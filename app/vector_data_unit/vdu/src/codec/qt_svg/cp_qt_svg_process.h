/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_QT_SVG_PROCESS_INCLUDE_H_
#define _CP_QT_SVG_PROCESS_INCLUDE_H_

#include "cp_qt_svg_include.h"




#pragma pack(1)



/************************************************************************/
/* ���ﶨ��һ��ͼ�δ���������ʾһ��ͼ�δ��������                          */
/************************************************************************/
struct cp_qt_svg_process_debug_info_s {
	cp_bool_t								is_save_file;								//��ʾ�Ƿ񱣴��ļ�
	cp_char_t								path[CP_APP_DEFAULT_STRING_LENGTH];			//��ʾ�����ļ���Ŀ¼
};




/************************************************************************/
/* ���ﶨ��һ��ͼ�δ���������ʾһ��ͼ�δ��������                          */
/************************************************************************/
struct cp_qt_svg_process_info_s {
	cp_int32_t								type;
	cp_rect_t								rect;
};




/************************************************************************/
/* ���ﶨ��һ��ͼ�δ���������ʾһ��ͼ�δ��������                          */
/************************************************************************/
struct cp_qt_svg_process_s {
	cp_qt_svg_codec_t						*codec;						//��ʾ��ǰ�Ľ�����
	cp_qt_svg_process_info_t				info;						//��ʾ������Ϣ
	cp_qt_svg_process_debug_info_t			debug_info;					//��ʾdebug��Ϣ
	QApplication							*qt_app;					//��ʾqt��application
	QGraphicsView							*view;						//��ʾͼ�ε���ͼ����
	QGraphicsScene							*scene;						//��ʾͼ�γ���
	cp_channel_manager_t					channel_manager;			//��ʾͨ��������
	CP_MODULE_ERROR_FIELDS												//��ʾ�������
};





#pragma pack()


#ifdef __cplusplus
extern "C" {
#endif


	/*����qt_svg_process ��Ϣ*/
	cp_qt_svg_process_t* create_qt_svg_process(cp_qt_svg_codec_t *codec, cp_qt_svg_process_info_t *info);

	/*����qt_svg_process ��Ϣ*/
	cp_int32_t destroy_svg_process(cp_qt_svg_process_t *process);





	/*��ʼ��qt_svg_process ��Ϣ*/
	cp_int32_t init_qt_svg_process(cp_qt_svg_process_t *process, cp_qt_svg_process_info_t *info);




	/*����qt_svg_process ��Ϣ*/
	cp_int32_t start_qt_svg_process(cp_qt_svg_process_t *process, cp_qt_svg_process_info_t *info);

	//����svg������Դ
	cp_int32_t qt_svg_process_create_source(cp_qt_svg_process_t *process, cp_qt_svg_process_info_t *info);

	//����svg������Դ
	cp_int32_t qt_svg_process_destroy_source(cp_qt_svg_process_t *process);

	//У���Ƿ��Ѿ�׼����
	cp_int32_t qt_svg_process_check_ready(cp_qt_svg_process_t *process);


	//�ж�channel index�Ƿ����
	cp_bool_t qt_svg_process_check_svg_channel_index_is_exist(
		cp_qt_svg_process_t *process,
		cp_int32_t index);

	//����channel
	cp_qt_svg_channel_t* qt_svg_process_create_svg_channel(
		cp_qt_svg_process_t *process,
		cp_int32_t index);

	//��������channelͨ��
	cp_qt_svg_channel_t* qt_svg_process_create_max_svg_channel(
		cp_qt_svg_process_t *process);

	//����channel
	cp_int32_t qt_svg_process_destroy_svg_channel(
		cp_qt_svg_process_t *process,
		cp_qt_svg_channel_t *svg_channel);

	//ͨ��index����channel
	cp_int32_t qt_svg_process_destroy_svg_channel_by_index(
		cp_qt_svg_process_t *process,
		cp_int32_t index);

	//����all_channel
	cp_int32_t qt_svg_process_destroy_all_svg_channel(cp_qt_svg_process_t *process);
	int qt_svg_process_remove_svg_channel_callback(
		cp_channel_manager_t *cm,
		cp_void_t *arg,
		cp_channel_t *channel);

	//����coordinate��ֵ
	cp_int32_t qt_svg_process_set_coordinate(cp_qt_svg_process_t *process, 
		cp_coordinate_t coordinate);

	//��ȡcoordinate��ֵ
	cp_int32_t qt_svg_process_get_coordinate(cp_qt_svg_process_t *process,
		cp_coordinate_t *coordinate);

	//����debug info��ֵ
	cp_int32_t qt_svg_process_set_debug_info(cp_qt_svg_process_t *process,
		cp_qt_svg_process_debug_info_t debug_info);

	//���ñ����ļ���Ϣ
	cp_int32_t qt_svg_process_save_file(cp_qt_svg_process_t *process, QImage *image);

	/*���svgͼƬ�ĸ���Ȥ��������*/
	cp_int32_t qt_svg_process_clear_roi(cp_qt_svg_process_t *process);
	/*����svgͼƬ�ĸ���Ȥ��������*/
	cp_int32_t qt_svg_process_set_roi(cp_qt_svg_process_t *process, cp_rect_t rect);
	/*��ȡsvgͼƬ�ĸ���Ȥ��������*/
	cp_int32_t qt_svg_process_get_roi(
		cp_qt_svg_process_t *process,
		cp_rect_t *dest_rect);

	/*��ȡsvg����Ȥ�������ݵ�ͼƬ����*/
	cp_int32_t qt_svg_process_get_roi_pixel(cp_qt_svg_process_t *process,
		cp_uchar_t *dest_buf,
		cp_uint32_t buf_len,
		cp_codec_pixel_format_e cpf,
		cp_rect_t *image_rect);


	/*��ȡsvgָ�������ͼƬ����*/
	cp_int32_t qt_svg_process_get_rect_pixel(
		cp_qt_svg_process_t *process,
		cp_uchar_t *dest_buf,
		cp_uint32_t buf_len,
		cp_codec_pixel_format_e cpf,
		cp_rect_t rect,
		cp_rect_t *image_rect);

	/*��ʾ���볡��*/
	cp_int32_t qt_svg_process_insert_svg_channel(
		cp_qt_svg_process_t *process,
		cp_qt_svg_channel_t *channel,
		cp_rect_t rect);
	/*��ʾ�˳�����*/
	cp_int32_t qt_svg_process_remove_svg_channel(
		cp_qt_svg_process_t *process,
		cp_qt_svg_channel_t *channel);

	/*��ʾ�޸�ͨ����index����ͼ������*/
	cp_int32_t qt_svg_process_update_svg_channel_index(
		cp_qt_svg_process_t *process,
		cp_qt_svg_channel_t *channel,
		cp_int32_t index);





	/*ֹͣqt_svg_process ��Ϣ*/
	cp_int32_t stop_qt_svg_process(cp_qt_svg_process_t *process);

#ifdef __cplusplus
};
#endif



#endif


