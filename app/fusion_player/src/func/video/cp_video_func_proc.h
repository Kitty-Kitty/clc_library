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

void video_func_merge_process_thread_cb_proc(cp_video_func_t *video_func);
void video_func_check_thread_cb_proc(cp_video_func_t *video_func);
void video_func_merge_thread_cb_proc(cp_video_func_t *video_func);


//打开测试文件
cp_bool_t open_video_test_file(cp_video_func_t *video_func);

//关闭测试文件
cp_bool_t close_video_test_file(cp_video_func_t *video_func);

//校验数据是否结
cp_inline cp_bool_t check_video_is_end(cp_buf_t *buf);

//设置解码器信息
cp_int32_t create_video_codecs(cp_video_func_t *video_func, cp_video_func_configure_t *afc);

//消毁视频解码器信息
cp_int32_t destroy_video_codecs(cp_video_func_t *video_func);

//停止一个媒体播放
cp_int32_t stop_video_func_media_play(cp_video_func_t *video_func, cp_media_channel_info_t *mci);

//更新一个媒体播放
cp_int32_t update_video_func_media_play(cp_video_func_t *video_func, cp_media_channel_info_t *mci);

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




//启动处理线程
cp_int32_t start_video_thread_process(cp_video_func_t *video_func);

//启动处理线程
cp_int32_t start_video_single_thread_process(cp_video_func_t *video_func);

//启动处理线程
cp_int32_t start_video_multi_thread_process(cp_video_func_t *video_func);

//启动播放线程
cp_int32_t start_video_merge_thread_process(cp_video_func_t *video_func);

//启动处理线程
cp_int32_t start_video_check_thread_process(cp_video_func_t *video_func);




//停止处理线程
cp_int32_t stop_video_thread_process(cp_video_func_t *video_func);

//停止处理线程
cp_int32_t stop_video_single_thread_process(cp_video_func_t *video_func);

//停止处理线程
cp_int32_t stop_video_check_thread_process(cp_video_func_t *video_func);

//停止处理线程
cp_int32_t stop_video_multi_thread_process(cp_video_func_t *video_func);

//停止播放线程
cp_int32_t stop_video_merge_thread_process(cp_video_func_t *video_func);

//打印时间戳数据
cp_char_t* format_video_frame_timestamp(cp_char_t *buf, cp_int32_t len);




#endif