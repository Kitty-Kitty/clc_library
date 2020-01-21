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
/* 这里定义一个图形处理器，表示一个图形处理管理器                          */
/************************************************************************/
struct cp_qt_svg_process_debug_info_s {
	cp_bool_t								is_save_file;								//表示是否保存文件
	cp_char_t								path[CP_APP_DEFAULT_STRING_LENGTH];			//表示保存文件的目录
};




/************************************************************************/
/* 这里定义一个图形处理器，表示一个图形处理管理器                          */
/************************************************************************/
struct cp_qt_svg_process_info_s {
	cp_int32_t								type;
	cp_rect_t								rect;
};




/************************************************************************/
/* 这里定义一个图形处理器，表示一个图形处理管理器                          */
/************************************************************************/
struct cp_qt_svg_process_s {
	cp_qt_svg_codec_t						*codec;						//表示当前的解码器
	cp_qt_svg_process_info_t				info;						//表示处理信息
	cp_qt_svg_process_debug_info_t			debug_info;					//表示debug信息
	QApplication							*qt_app;					//表示qt的application
	QGraphicsView							*view;						//表示图形的视图对象
	QGraphicsScene							*scene;						//表示图形场景
	cp_channel_manager_t					channel_manager;			//表示通道管理器
	CP_MODULE_ERROR_FIELDS												//表示错误编码
};





#pragma pack()


#ifdef __cplusplus
extern "C" {
#endif


	/*创建qt_svg_process 信息*/
	cp_qt_svg_process_t* create_qt_svg_process(cp_qt_svg_codec_t *codec, cp_qt_svg_process_info_t *info);

	/*销毁qt_svg_process 信息*/
	cp_int32_t destroy_svg_process(cp_qt_svg_process_t *process);





	/*初始化qt_svg_process 信息*/
	cp_int32_t init_qt_svg_process(cp_qt_svg_process_t *process, cp_qt_svg_process_info_t *info);




	/*启动qt_svg_process 信息*/
	cp_int32_t start_qt_svg_process(cp_qt_svg_process_t *process, cp_qt_svg_process_info_t *info);

	//创建svg处理资源
	cp_int32_t qt_svg_process_create_source(cp_qt_svg_process_t *process, cp_qt_svg_process_info_t *info);

	//销毁svg处理资源
	cp_int32_t qt_svg_process_destroy_source(cp_qt_svg_process_t *process);

	//校验是否已经准备好
	cp_int32_t qt_svg_process_check_ready(cp_qt_svg_process_t *process);


	//判断channel index是否存在
	cp_bool_t qt_svg_process_check_svg_channel_index_is_exist(
		cp_qt_svg_process_t *process,
		cp_int32_t index);

	//创建channel
	cp_qt_svg_channel_t* qt_svg_process_create_svg_channel(
		cp_qt_svg_process_t *process,
		cp_int32_t index);

	//创建最大的channel通道
	cp_qt_svg_channel_t* qt_svg_process_create_max_svg_channel(
		cp_qt_svg_process_t *process);

	//销毁channel
	cp_int32_t qt_svg_process_destroy_svg_channel(
		cp_qt_svg_process_t *process,
		cp_qt_svg_channel_t *svg_channel);

	//通过index销毁channel
	cp_int32_t qt_svg_process_destroy_svg_channel_by_index(
		cp_qt_svg_process_t *process,
		cp_int32_t index);

	//销毁all_channel
	cp_int32_t qt_svg_process_destroy_all_svg_channel(cp_qt_svg_process_t *process);
	int qt_svg_process_remove_svg_channel_callback(
		cp_channel_manager_t *cm,
		cp_void_t *arg,
		cp_channel_t *channel);

	//设置coordinate数值
	cp_int32_t qt_svg_process_set_coordinate(cp_qt_svg_process_t *process, 
		cp_coordinate_t coordinate);

	//获取coordinate数值
	cp_int32_t qt_svg_process_get_coordinate(cp_qt_svg_process_t *process,
		cp_coordinate_t *coordinate);

	//设置debug info数值
	cp_int32_t qt_svg_process_set_debug_info(cp_qt_svg_process_t *process,
		cp_qt_svg_process_debug_info_t debug_info);

	//设置保存文件信息
	cp_int32_t qt_svg_process_save_file(cp_qt_svg_process_t *process, QImage *image);

	/*清除svg图片的感兴趣区域数据*/
	cp_int32_t qt_svg_process_clear_roi(cp_qt_svg_process_t *process);
	/*设置svg图片的感兴趣区域数据*/
	cp_int32_t qt_svg_process_set_roi(cp_qt_svg_process_t *process, cp_rect_t rect);
	/*获取svg图片的感兴趣区域数据*/
	cp_int32_t qt_svg_process_get_roi(
		cp_qt_svg_process_t *process,
		cp_rect_t *dest_rect);

	/*获取svg感兴趣区域数据的图片数据*/
	cp_int32_t qt_svg_process_get_roi_pixel(cp_qt_svg_process_t *process,
		cp_uchar_t *dest_buf,
		cp_uint32_t buf_len,
		cp_codec_pixel_format_e cpf,
		cp_rect_t *image_rect);


	/*获取svg指定区域的图片数据*/
	cp_int32_t qt_svg_process_get_rect_pixel(
		cp_qt_svg_process_t *process,
		cp_uchar_t *dest_buf,
		cp_uint32_t buf_len,
		cp_codec_pixel_format_e cpf,
		cp_rect_t rect,
		cp_rect_t *image_rect);

	/*表示插入场景*/
	cp_int32_t qt_svg_process_insert_svg_channel(
		cp_qt_svg_process_t *process,
		cp_qt_svg_channel_t *channel,
		cp_rect_t rect);
	/*表示退出场景*/
	cp_int32_t qt_svg_process_remove_svg_channel(
		cp_qt_svg_process_t *process,
		cp_qt_svg_channel_t *channel);

	/*表示修改通道的index，即图层属性*/
	cp_int32_t qt_svg_process_update_svg_channel_index(
		cp_qt_svg_process_t *process,
		cp_qt_svg_channel_t *channel,
		cp_int32_t index);





	/*停止qt_svg_process 信息*/
	cp_int32_t stop_qt_svg_process(cp_qt_svg_process_t *process);

#ifdef __cplusplus
};
#endif



#endif


