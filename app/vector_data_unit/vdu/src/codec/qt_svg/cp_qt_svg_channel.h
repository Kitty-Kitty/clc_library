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
/*这里定义一个图形层                                                     */
/************************************************************************/
struct cp_qt_svg_channel_info_s {
	cp_int32_t								index;
};


/************************************************************************/
/*这里定义一个图形层                                                     */
/************************************************************************/
struct cp_qt_svg_channel_scene_s {
	cp_qt_svg_process_t						*process;			//表示场景所在的图形处理器
	cp_bool_t								is_render_scene;	//表示是否渲染到场景；cp_true表示渲染；cp_false表示不渲染
	cp_rect_t								rect;				//表示通道相对场景的坐标信息
};


/************************************************************************/
/*这里定义一个图形层                                                     */
/************************************************************************/
struct cp_qt_svg_channel_s {
	cp_qt_svg_process_t						*process;			//表示一个图形处理器
	cp_qt_svg_channel_info_t				info;				//表示通道信息
	cp_qt_svg_channel_scene_t				scene;				//表示通道相对场景的信息
	cp_channel_t							channel;			//表示通道管理信息
	QGraphicsSvgItem						*item;				//表示一个svg图层
	QSvgRenderer							*render;			//表示一个svg render内容
	CP_MODULE_ERROR_FIELDS										//表示错误编码
};




#pragma pack()


#ifdef __cplusplus
extern "C" {
#endif


	/*创建qt_svg_channel 信息*/
	cp_qt_svg_channel_t* create_qt_svg_channel(cp_qt_svg_process_t *process, cp_qt_svg_channel_info_t *info);

	/*销毁qt_svg_channel 信息*/
	cp_int32_t destroy_qt_svg_channel(cp_qt_svg_channel_t *channel);





	/*初始化qt_svg_channel 信息*/
	cp_int32_t init_qt_svg_channel(cp_qt_svg_channel_t *channel, cp_qt_svg_channel_info_t *channel_info);




	/*启动qt_svg_channel 信息*/
	cp_int32_t start_qt_svg_channel(cp_qt_svg_channel_t *channel, cp_qt_svg_channel_info_t *channel_info);

	//创建svg处理资源
	cp_int32_t qt_svg_channel_create_source(cp_qt_svg_channel_t *channel);
	//销毁svg处理资源
	cp_int32_t qt_svg_channel_destroy_source(cp_qt_svg_channel_t *channel);

	//校验是否已经准备好
	cp_int32_t qt_svg_channel_check_ready(cp_qt_svg_channel_t *channel);

	/*处理svg图片数据流*/
	cp_int32_t qt_svg_channel_vector_stream(cp_qt_svg_channel_t *channel, cp_uchar_t *buf, cp_uint32_t len);

	//设置保存文件信息
	cp_int32_t qt_svg_channel_save_file(cp_qt_svg_channel_t *channel, QImage *image);

	/*清除svg图片的感兴趣区域数据*/
	cp_int32_t qt_svg_channel_clear_roi(cp_qt_svg_channel_t *channel);
	/*设置svg图片的感兴趣区域数据*/
	cp_int32_t qt_svg_channel_set_roi(cp_qt_svg_channel_t *channel,
		cp_rect_t rect);
	/*获取svg图片的感兴趣区域数据*/
	cp_int32_t qt_svg_channel_get_roi(cp_qt_svg_channel_t *channel,
		cp_rect_t *dest_rect);

	/*获取svg感兴趣区域数据的图片数据*/
	cp_int32_t qt_svg_channel_get_roi_pixel(cp_qt_svg_channel_t *channel,
		cp_uchar_t *dest_buf,
		cp_uint32_t buf_len,
		cp_codec_pixel_format_e cpf,
		cp_rect_t *image_rect);

	/*获取svg指定区域的图片数据*/
	cp_int32_t qt_svg_channel_get_rect_pixel(cp_qt_svg_channel_t *channel,
		cp_uchar_t *dest_buf,
		cp_uint32_t buf_len,
		cp_codec_pixel_format_e cpf,
		cp_rect_t rect,
		cp_rect_t *image_rect);

	/*表示插入场景*/
	cp_int32_t qt_svg_channel_insert_scene(cp_qt_svg_process_t *process, cp_qt_svg_channel_t *channel, cp_rect_t rect);
	/*表示退出场景*/
	cp_int32_t qt_svg_channel_remove_scene(cp_qt_svg_process_t *process, cp_qt_svg_channel_t *channel);
	/*表示修改通道的index，即图层属性*/
	cp_int32_t qt_svg_channel_update_index(cp_qt_svg_channel_t *channel, cp_int32_t index);


	/*停止qt_svg_channel 信息*/
	cp_int32_t stop_qt_svg_channel(cp_qt_svg_channel_t *channel);


#ifdef __cplusplus
};
#endif


#endif


