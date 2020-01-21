/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2017-01-12

Description:

**************************************************************************/

#ifndef _CP_AUDIO_FUNC_PROC_INCLUDE_H_
#define _CP_AUDIO_FUNC_PROC_INCLUDE_H_


#include "cp_audio_func_core.h"



#define		CP_AUDIO_FUNC_PROC_MERGE_SLEEP_INTERVAL						1000000					//默认的休眠间隔时间，单位纳秒



cp_int32_t audio_func_data_integrity
(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status);

cp_int32_t audio_func_process_socket_data(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status);

void audio_func_thread_cb_proc(cp_audio_func_t *audio_func);
void audio_func_decode_thread_cb_proc(cp_audio_func_t *audio_func);
void audio_func_merge_thread_cb_proc(cp_audio_func_t *audio_func);

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: set_audio_multicast_data_filter
*
* 函数说明: 设置multicast socket
*
* 参    数: cp_audio_func_t * audio_func			[in]参数说明
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
cp_int32_t set_audio_multicast_data_filter(cp_audio_func_t *audio_func, cp_char_t *buf, cp_int32_t len);

//关闭视频 socket
cp_int32_t close_audio_multicast_socket(cp_audio_func_t *audio_func);

//设置memh的socket数据
cp_int32_t set_audio_memh_socket_data(cp_audio_func_t *audio_func, cp_char_t *buf, cp_int32_t len);

//消毁memh socket数据
cp_int32_t unset_audio_memh_socket_data(cp_audio_func_t *audio_func);

//打开测试文件
cp_bool_t open_audio_test_file(cp_audio_func_t *audio_func);

//关闭测试文件
cp_bool_t close_audio_test_file(cp_audio_func_t *audio_func);

//校验数据是否结
cp_inline cp_bool_t check_audio_is_end(cp_buf_t *buf);

//设置解码器信息
cp_inline cp_int32_t set_audio_codec_info(cp_audio_func_t *audio_func, cp_array_t *ary);

//设置音频解码重采样信息
cp_int32_t set_audio_codec_convert_info(cp_audio_func_t *audio_func);

//校验媒体类型信息
cp_bool_t check_audio_media_type(cp_audio_func_t *audio_func, cp_int32_t type);

//关闭音频解码器信息
cp_int32_t close_audio_codec_info(cp_audio_func_t *audio_func);

//消毁视频解码器信息
cp_int32_t unset_audio_codec_info(cp_audio_func_t *audio_func);

//设置播放信息
cp_int32_t set_audio_dev_info(cp_audio_func_t *audio_func, cp_audio_description_t *ad);

//消毁视频显视信息
cp_int32_t unset_audio_dev_info(cp_audio_func_t *audio_func);

//解码媒体数据
cp_inline cp_media_packet_t* merge_audio_media_data(cp_audio_func_t *audio_func, cp_array_t *ary);

//获取一帧数
cp_inline cp_int32_t get_a_audio_frame_data(cp_audio_func_t *audio_func, cp_array_t *ary);

//解码媒体数据
cp_inline cp_int32_t decode_audio_media_data(cp_audio_func_t *audio_func, cp_media_packet_t	*mp);

//播媒体数据
cp_inline cp_int32_t play_audio_media_data(cp_audio_func_t *audio_func, cp_media_packet_t	*mp);

//停止一个媒体播放
cp_int32_t stop_audio_func_media_play(cp_audio_func_t *audio_func, cp_media_channel_info_t *mci);

//添加媒体通道
cp_int32_t insert_audio_media_channel_info(cp_audio_func_t *audio_func, cp_media_channel_info_t *mci);

//更新一个媒体播放
cp_int32_t update_audio_func_media_play(cp_audio_func_t *audio_func, cp_media_channel_info_t *mci);

//删除媒体通道
cp_int32_t remove_audio_media_channel_info(cp_audio_func_t *audio_func, cp_media_channel_info_t *mci);

//消毁所有数据
cp_inline cp_int32_t destroy_audio_tmp_data(cp_audio_func_t *audio_func, cp_array_t *ary);

//初始化媒体信息
cp_int32_t init_audio_media_description_info(cp_audio_func_t *audio_func);

//初始化解码信息
cp_int32_t init_audio_codec_callback_info(cp_audio_func_t *audio_func);

//初始化merge
cp_int32_t init_audio_merge_safe_queue(cp_audio_func_t *audio_func);

//消毁merge
cp_int32_t destory_audio_merge_safe_queue(cp_audio_func_t *audio_func);

//创建一个media_packet
cp_static cp_media_packet_t *create_a_audio_media_packet(cp_audio_func_t *audio_func, cp_int32_t len);

//消毁一个media_packet
cp_static cp_int32_t destroy_a_audio_media_packet(cp_audio_func_t *audio_func, cp_media_packet_t *mp);

//启动处理线程
cp_int32_t start_audio_thread_process(cp_audio_func_t *audio_func);

//启动处理线程
cp_int32_t start_audio_single_thread_process(cp_audio_func_t *audio_func);

//启动处理线程
cp_int32_t start_audio_multi_thread_process(cp_audio_func_t *audio_func);

//启动播放线程
cp_int32_t start_audio_merge_thread_process(cp_audio_func_t *audio_func);

//启动处理线程
cp_int32_t start_audio_decode_thread_process(cp_audio_func_t *audio_func);




//停止处理线程
cp_int32_t stop_audio_thread_process(cp_audio_func_t *audio_func);

//停止处理线程
cp_int32_t stop_audio_single_thread_process(cp_audio_func_t *audio_func);

//停止处理线程
cp_int32_t stop_audio_decode_thread_process(cp_audio_func_t *audio_func);

//停止处理线程
cp_int32_t stop_audio_multi_thread_process(cp_audio_func_t *audio_func);

//停止播放线程
cp_int32_t stop_audio_merge_thread_process(cp_audio_func_t *audio_func);

//打印时间戳数据
cp_char_t* format_audio_frame_timestamp(cp_char_t *buf, cp_int32_t len);




//发送删除消息
cp_int32_t send_remove_module_message(cp_audio_func_t *audio_func);






#endif