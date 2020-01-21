/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-05

Description:

**************************************************************************/

#ifndef _CP_VDU_CODEC_MODULE_OPTION_INCLUDE_H_
#define _CP_VDU_CODEC_MODULE_OPTION_INCLUDE_H_


#include "cp_module_option.h"
#include "cp_bit.h"




//typedef enum cp_vdu_codec_option_enum		cp_vdu_codec_option_e;



/************************************************************************/
/* 定义module的设置属性                                                  */
/************************************************************************/
typedef enum cp_vdu_codec_option_enum
{
	///设置选项
	//1、process操作
	cp_qt_svg_process_option_create_channel			= CP_MODULE_OPTION_MAKE_SET_FLAG(B16(00000000, 00000001)),
	cp_qt_svg_process_option_destroy_channel,
	cp_qt_svg_process_option_destroy_all_channel,
	cp_qt_svg_process_option_set_roi,
	cp_qt_svg_process_option_clear_roi,
	cp_qt_svg_process_option_set_coordinate,
	cp_qt_svg_process_option_set_debug_info,
	//2、channel操作
	cp_qt_svg_channel_option_set_channel_index,
	cp_qt_svg_channel_option_set_insert_channel,
	cp_qt_svg_channel_option_set_remove_channel,
	cp_qt_svg_channel_option_set_roi,
	cp_qt_svg_channel_option_clear_roi,
	cp_qt_svg_channel_option_set_vector_stream,

	//获取选项
	//1、process操作
	cp_qt_svg_process_option_get_roi				= CP_MODULE_OPTION_MAKE_GET_FLAG(B16(00000000, 00000001)),
	cp_qt_svg_process_option_get_roi_pixel,
	cp_qt_svg_process_option_get_rect_pixel,
	cp_qt_svg_process_option_get_status,
	cp_qt_svg_process_option_get_coordinate,
	//2、channel通道操作
	cp_qt_svg_channel_option_get_channel_index,
	cp_qt_svg_channel_option_get_roi,
	cp_qt_svg_channel_option_get_roi_pixel,
	cp_qt_svg_channel_option_get_rect_pixel,
	cp_qt_svg_channel_option_get_status,

}cp_vdu_codec_option_e;



#endif