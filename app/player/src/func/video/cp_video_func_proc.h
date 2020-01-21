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

void video_func_thread_cb_proc(cp_video_func_t *video_func);
void video_func_decode_thread_cb_proc(cp_video_func_t *video_func);
void video_func_merge_thread_cb_proc(cp_video_func_t *video_func);

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: set_video_multicast_data_filter
*
* ����˵��: ����multicast socket
*
* ��    ��: cp_video_func_t * video_func			[in]����˵��
* ��    ��: cp_char_t * buf						[in]����˵��
* ��    ��: cp_int32_t len						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-11-25 15:31:55
******************************************************************************************************/
cp_int32_t set_video_multicast_data_filter(cp_video_func_t *video_func, cp_char_t *buf, cp_int32_t len);

//�ر���Ƶ socket
cp_int32_t close_video_multicast_socket(cp_video_func_t *video_func);

//����memh��socket����
cp_int32_t set_video_memh_socket_data(cp_video_func_t *video_func, cp_char_t *buf, cp_int32_t len);

//����memh socket����
cp_int32_t unset_video_memh_socket_data(cp_video_func_t *video_func);

//�򿪲����ļ�
cp_bool_t open_video_test_file(cp_video_func_t *video_func);

//�رղ����ļ�
cp_bool_t close_video_test_file(cp_video_func_t *video_func);

//У�������Ƿ��
cp_inline cp_bool_t check_video_is_end(cp_buf_t *buf);

//���ý�������Ϣ
cp_inline cp_int32_t set_video_codec_info(cp_video_func_t *video_func, cp_array_t *ary);

//������Ƶ�����ز�����Ϣ
cp_int32_t set_video_codec_convert_info(cp_video_func_t *video_func);

//У��ý��������Ϣ
cp_bool_t check_video_media_type(cp_video_func_t *video_func, cp_int32_t type);

//�ر���Ƶ��������Ϣ
cp_int32_t close_video_codec_info(cp_video_func_t *video_func);

//������Ƶ��������Ϣ
cp_int32_t unset_video_codec_info(cp_video_func_t *video_func);

//���ò�����Ϣ
cp_int32_t set_video_dev_info(cp_video_func_t *video_func, cp_video_description_t *ad);

//������Ƶ������Ϣ
cp_int32_t unset_video_dev_info(cp_video_func_t *video_func);

//����ý������
cp_inline cp_media_packet_t* merge_video_media_data(cp_video_func_t *video_func, cp_array_t *ary);

//��ȡһ֡��
cp_inline cp_int32_t get_a_video_frame_data(cp_video_func_t *video_func, cp_array_t *ary);

//����ý������
cp_inline cp_int32_t decode_video_media_data(cp_video_func_t *video_func, cp_media_packet_t	*mp);

//��ý������
cp_inline cp_int32_t play_video_media_data(cp_video_func_t *video_func, cp_media_packet_t	*mp);

//ֹͣһ��ý�岥��
cp_int32_t stop_video_func_media_play(cp_video_func_t *video_func, cp_media_channel_info_t *mci);

//���ý��ͨ��
cp_int32_t insert_video_media_channel_info(cp_video_func_t *video_func, cp_media_channel_info_t *mci);

//����֡������Ϣ
cp_int32_t set_video_frame_by_media_channel_info(cp_video_func_frame_process_t *vffp, cp_media_channel_info_t *mci);

//����һ��ý�岥��
cp_int32_t update_video_func_media_play(cp_video_func_t *video_func, cp_media_channel_info_t *mci);

//ɾ��ý��ͨ��
cp_int32_t remove_video_media_channel_info(cp_video_func_t *video_func, cp_media_channel_info_t *mci);

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

//����һ��media_packet
cp_static cp_media_packet_t *create_a_video_media_packet(cp_video_func_t *video_func, cp_int32_t len);

//����һ��media_packet
cp_static cp_int32_t destroy_a_video_media_packet(cp_video_func_t *video_func, cp_media_packet_t *mp);

//���������߳�
cp_int32_t start_video_thread_process(cp_video_func_t *video_func);

//���������߳�
cp_int32_t start_video_single_thread_process(cp_video_func_t *video_func);

//���������߳�
cp_int32_t start_video_multi_thread_process(cp_video_func_t *video_func);

//���������߳�
cp_int32_t start_video_merge_thread_process(cp_video_func_t *video_func);

//���������߳�
cp_int32_t start_video_decode_thread_process(cp_video_func_t *video_func);




//ֹͣ�����߳�
cp_int32_t stop_video_thread_process(cp_video_func_t *video_func);

//ֹͣ�����߳�
cp_int32_t stop_video_single_thread_process(cp_video_func_t *video_func);

//ֹͣ�����߳�
cp_int32_t stop_video_decode_thread_process(cp_video_func_t *video_func);

//ֹͣ�����߳�
cp_int32_t stop_video_multi_thread_process(cp_video_func_t *video_func);

//ֹͣ�����߳�
cp_int32_t stop_video_merge_thread_process(cp_video_func_t *video_func);

//��ӡʱ�������
cp_char_t* format_video_frame_timestamp(cp_char_t *buf, cp_int32_t len);




#endif