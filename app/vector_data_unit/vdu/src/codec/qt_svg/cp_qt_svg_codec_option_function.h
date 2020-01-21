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

//初始化option handle部分内容
cp_int32_t cp_qt_svg_codec_create_option_handle(cp_qt_svg_codec_t *codec);
cp_int32_t cp_qt_svg_codec_destroy_option_handle(cp_qt_svg_codec_t *codec);





/*选项处理模块参数*/
cp_int32_t cp_qt_svg_codec_set_option_process(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, const cp_void_t* optval);
cp_int32_t cp_qt_svg_codec_get_option_process(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, cp_void_t* optval);

//更新status状态信息
cp_int32_t cp_qt_svg_codec_update_status(cp_qt_svg_codec_t *qt_svg_codec,
	cp_int32_t optname, const cp_void_t* optval, cp_int32_t status);
cp_int32_t cp_qt_svg_codec_update_process_status(cp_vdu_process_t *vdu_process, cp_int32_t status);
cp_int32_t cp_qt_svg_codec_update_channel_process_status(cp_vdu_channel_process_t *vdu_channel_process, cp_int32_t status);


/*设置模块参数*/
cp_int32_t cp_qt_svg_codec_set_option_process_create_channel(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, const cp_void_t* optval);

/*设置channel的通道索引号*/
cp_int32_t cp_qt_svg_codec_set_option_process_set_channel_index(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, const cp_void_t* optval);

/*销毁模块*/
cp_int32_t cp_qt_svg_codec_set_option_process_destroy_channel(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, const cp_void_t* optval);

/*销毁所有模块*/
cp_int32_t cp_qt_svg_codec_set_option_process_destroy_all_channel(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, const cp_void_t* optval);

/*设置模块的感兴趣区域*/
cp_int32_t cp_qt_svg_codec_set_option_process_set_roi(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, const cp_void_t* optval);

/*清除模块的感兴趣区域*/
cp_int32_t cp_qt_svg_codec_set_option_process_clear_roi(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, const cp_void_t* optval);

/*设置模块的坐标空间*/
cp_int32_t cp_qt_svg_codec_set_option_process_set_coordinate(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, const cp_void_t* optval);

/*设置debug信息*/
cp_int32_t cp_qt_svg_codec_set_option_process_set_debug_info(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, const cp_void_t* optval);


/*插入通道*/
cp_int32_t cp_qt_svg_codec_set_option_channel_set_insert_channel(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, const cp_void_t* optval);

/*删除通道*/
cp_int32_t cp_qt_svg_codec_set_option_channel_set_remove_channel(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, const cp_void_t* optval);

/*设置通道的感兴趣区域*/
cp_int32_t cp_qt_svg_codec_set_option_channel_set_roi(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, const cp_void_t* optval);

/*清除通道的感兴趣区域*/
cp_int32_t cp_qt_svg_codec_set_option_channel_clear_roi(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, const cp_void_t* optval);

/*解析矢量数据流*/
cp_int32_t cp_qt_svg_codec_set_option_channel_set_vector_stream(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, const cp_void_t* optval);






/*获取模块的感兴趣区域*/
cp_int32_t cp_qt_svg_codec_set_option_process_get_roi(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, cp_void_t* optval);

/*获取模块的感兴趣区域的图像内容*/
cp_int32_t cp_qt_svg_codec_set_option_process_get_roi_pixel(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, cp_void_t* optval);

/*获取模块的指定区域的图像内容*/
cp_int32_t cp_qt_svg_codec_set_option_process_get_rect_pixel(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, cp_void_t* optval);

/*获取模块的状态码*/
cp_int32_t cp_qt_svg_codec_set_option_process_get_status(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, cp_void_t* optval);

/*获取模块的坐标空间信息*/
cp_int32_t cp_qt_svg_codec_set_option_process_get_coordinate(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, cp_void_t* optval);





/*获取通道的索引号*/
cp_int32_t cp_qt_svg_codec_get_option_channel_get_channel_index(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, cp_void_t* optval);

/*获取通道的感兴趣区域*/
cp_int32_t cp_qt_svg_codec_get_option_channel_get_roi(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, cp_void_t* optval);

/*获取通道的感兴趣区域的图像内容*/
cp_int32_t cp_qt_svg_codec_get_option_channel_get_roi_pixel(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, cp_void_t* optval);

/*获取通道的指定区域的图像内容*/
cp_int32_t cp_qt_svg_codec_get_option_channel_get_rect_pixel(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, cp_void_t* optval);

/*获取通道的状态码*/
cp_int32_t cp_qt_svg_codec_get_option_channel_get_status(
	cp_qt_svg_codec_t *qt_svg_codec, cp_int32_t optname, cp_void_t* optval);





#ifdef __cplusplus
}
#endif

#endif