/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2017-01-12

Description:

**************************************************************************/

#ifndef _CP_VIDEO_FUNC_PROC_INCLUDE_H_
#define _CP_VIDEO_FUNC_PROC_INCLUDE_H_


#include "cp_video_func_core.h"



#define		CP_VIDEO_FUNC_PROC_MERGE_SLEEP_INTERVAL						1000000					//默认的休眠间隔时间，单位纳秒



cp_int32_t video_func_data_integrity
(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status);

cp_int32_t video_func_process_socket_data(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status);

void video_func_thread_cb_proc(cp_video_func_t *video_func);
void video_func_decode_thread_cb_proc(cp_video_func_t *video_func);
void video_func_merge_thread_cb_proc(cp_video_func_t *video_func);

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: set_video_multicast_data_filter
*
* 函数说明: 设置multicast socket
*
* 参    数: cp_video_func_t * video_func			[in]参数说明
* 参    数: cp_char_t * buf						[in]参数说明
* 参    数: cp_int32_t len						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-11-25 15:31:55
******************************************************************************************************/
cp_int32_t set_video_multicast_data_filter(cp_video_func_t *video_func, cp_char_t *buf, cp_int32_t len);

//关闭视频 socket
cp_int32_t close_video_multicast_socket(cp_video_func_t *video_func);

//设置memh的socket数据
cp_int32_t set_video_memh_socket_data(cp_video_func_t *video_func, cp_char_t *buf, cp_int32_t len);

//消毁memh socket数据
cp_int32_t unset_video_memh_socket_data(cp_video_func_t *video_func);

//打开测试文件
cp_bool_t open_video_test_file(cp_video_func_t *video_func);

//关闭测试文件
cp_bool_t close_video_test_file(cp_video_func_t *video_func);

//校验数据是否结
cp_inline cp_bool_t check_video_is_end(cp_buf_t *buf);

//设置解码器信息
cp_inline cp_int32_t set_video_codec_info(cp_video_func_t *video_func, cp_array_t *ary);

//设置视频解码重采样信息
cp_int32_t set_video_codec_convert_info(cp_video_func_t *video_func);

//校验媒体类型信息
cp_bool_t check_video_media_type(cp_video_func_t *video_func, cp_int32_t type);

//关闭视频解码器信息
cp_int32_t close_video_codec_info(cp_video_func_t *video_func);

//消毁视频解码器信息
cp_int32_t unset_video_codec_info(cp_video_func_t *video_func);

//设置播放信息
cp_int32_t set_video_dev_info(cp_video_func_t *video_func, cp_video_description_t *ad);

//消毁视频显视信息
cp_int32_t unset_video_dev_info(cp_video_func_t *video_func);

//解码媒体数据
cp_inline cp_media_packet_t* merge_video_media_data(cp_video_func_t *video_func, cp_array_t *ary);

//获取一帧数
cp_inline cp_int32_t get_a_video_frame_data(cp_video_func_t *video_func, cp_array_t *ary);

//解码媒体数据
cp_inline cp_int32_t decode_video_media_data(cp_video_func_t *video_func, cp_media_packet_t	*mp);

//播媒体数据
cp_inline cp_int32_t play_video_media_data(cp_video_func_t *video_func, cp_media_packet_t	*mp);

//停止一个媒体播放
cp_int32_t stop_video_func_media_play(cp_video_func_t *video_func, cp_media_channel_info_t *mci);

//添加媒体通道
cp_int32_t insert_video_media_channel_info(cp_video_func_t *video_func, cp_media_channel_info_t *mci);

//设置帧处理信息
cp_int32_t set_video_frame_by_media_channel_info(cp_video_func_frame_process_t *vffp, cp_media_channel_info_t *mci);

//更新一个媒体播放
cp_int32_t update_video_func_media_play(cp_video_func_t *video_func, cp_media_channel_info_t *mci);

//删除媒体通道
cp_int32_t remove_video_media_channel_info(cp_video_func_t *video_func, cp_media_channel_info_t *mci);

//消毁所有数据
cp_inline cp_int32_t destroy_video_tmp_data(cp_video_func_t *video_func, cp_array_t *ary);

//初始化媒体信息
cp_int32_t init_video_media_description_info(cp_video_func_t *video_func);

//初始化解码信息
cp_int32_t init_video_codec_callback_info(cp_video_func_t *video_func);

//初始化merge
cp_int32_t init_video_merge_safe_queue(cp_video_func_t *video_func);

//消毁merge
cp_int32_t destory_video_merge_safe_queue(cp_video_func_t *video_func);

//创建一个media_packet
cp_static cp_media_packet_t *create_a_video_media_packet(cp_video_func_t *video_func, cp_int32_t len);

//消毁一个media_packet
cp_static cp_int32_t destroy_a_video_media_packet(cp_video_func_t *video_func, cp_media_packet_t *mp);

//启动处理线程
cp_int32_t start_video_thread_process(cp_video_func_t *video_func);

//启动处理线程
cp_int32_t start_video_single_thread_process(cp_video_func_t *video_func);

//启动处理线程
cp_int32_t start_video_multi_thread_process(cp_video_func_t *video_func);

//启动播放线程
cp_int32_t start_video_merge_thread_process(cp_video_func_t *video_func);

//启动处理线程
cp_int32_t start_video_decode_thread_process(cp_video_func_t *video_func);




//停止处理线程
cp_int32_t stop_video_thread_process(cp_video_func_t *video_func);

//停止处理线程
cp_int32_t stop_video_single_thread_process(cp_video_func_t *video_func);

//停止处理线程
cp_int32_t stop_video_decode_thread_process(cp_video_func_t *video_func);

//停止处理线程
cp_int32_t stop_video_multi_thread_process(cp_video_func_t *video_func);

//停止播放线程
cp_int32_t stop_video_merge_thread_process(cp_video_func_t *video_func);

//打印时间戳数据
cp_char_t* format_video_frame_timestamp(cp_char_t *buf, cp_int32_t len);




#endif