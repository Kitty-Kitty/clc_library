/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2017-01-12

Description:

**************************************************************************/

#ifndef _CP_VIDEO_FUNC_PROC_INCLUDE_H_
#define _CP_VIDEO_FUNC_PROC_INCLUDE_H_


#include "cp_video_func_core.h"



#define		CP_VIDEO_FUNC_PROC_MERGE_SLEEP_INTERVAL						1000000					//Ĭ�ϵ����߼��ʱ�䣬��λ����



cp_int32_t video_func_data_integrity
(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status);

cp_int32_t video_func_process_socket_data(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status);

void video_func_merge_process_thread_cb_proc(cp_video_func_t *video_func);
void video_func_check_thread_cb_proc(cp_video_func_t *video_func);
void video_func_merge_thread_cb_proc(cp_video_func_t *video_func);


//�򿪲����ļ�
cp_bool_t open_video_test_file(cp_video_func_t *video_func);

//�رղ����ļ�
cp_bool_t close_video_test_file(cp_video_func_t *video_func);

//У�������Ƿ��
cp_inline cp_bool_t check_video_is_end(cp_buf_t *buf);

//���ý�������Ϣ
cp_int32_t create_video_codecs(cp_video_func_t *video_func, cp_video_func_configure_t *afc);

//������Ƶ��������Ϣ
cp_int32_t destroy_video_codecs(cp_video_func_t *video_func);

//ֹͣһ��ý�岥��
cp_int32_t stop_video_func_media_play(cp_video_func_t *video_func, cp_media_channel_info_t *mci);

//����һ��ý�岥��
cp_int32_t update_video_func_media_play(cp_video_func_t *video_func, cp_media_channel_info_t *mci);

//������������
cp_inline cp_int32_t destroy_video_tmp_data(cp_video_func_t *video_func, cp_array_t *ary);

//��ʼ��ý����Ϣ
cp_int32_t init_video_media_description_info(cp_video_func_t *video_func);

//��ʼ��������Ϣ
cp_int32_t init_video_codec_callback_info(cp_video_func_t *video_func);

//��ʼ��merge
cp_int32_t init_video_merge_safe_queue(cp_video_func_t *video_func);

//����merge
cp_int32_t destory_video_merge_safe_queue(cp_video_func_t *video_func);




//���������߳�
cp_int32_t start_video_thread_process(cp_video_func_t *video_func);

//���������߳�
cp_int32_t start_video_single_thread_process(cp_video_func_t *video_func);

//���������߳�
cp_int32_t start_video_multi_thread_process(cp_video_func_t *video_func);

//���������߳�
cp_int32_t start_video_merge_thread_process(cp_video_func_t *video_func);

//���������߳�
cp_int32_t start_video_check_thread_process(cp_video_func_t *video_func);




//ֹͣ�����߳�
cp_int32_t stop_video_thread_process(cp_video_func_t *video_func);

//ֹͣ�����߳�
cp_int32_t stop_video_single_thread_process(cp_video_func_t *video_func);

//ֹͣ�����߳�
cp_int32_t stop_video_check_thread_process(cp_video_func_t *video_func);

//ֹͣ�����߳�
cp_int32_t stop_video_multi_thread_process(cp_video_func_t *video_func);

//ֹͣ�����߳�
cp_int32_t stop_video_merge_thread_process(cp_video_func_t *video_func);

//��ӡʱ�������
cp_char_t* format_video_frame_timestamp(cp_char_t *buf, cp_int32_t len);




#endif