/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2017-01-12

Description:

**************************************************************************/

#ifndef _CP_AUDIO_FUNC_PROC_INCLUDE_H_
#define _CP_AUDIO_FUNC_PROC_INCLUDE_H_


#include "cp_audio_func_core.h"



#define		CP_AUDIO_FUNC_PROC_MERGE_SLEEP_INTERVAL						1000000					//Ĭ�ϵ����߼��ʱ�䣬��λ����



cp_int32_t audio_func_data_integrity
(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status);

cp_int32_t audio_func_process_socket_data(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status);

void audio_func_thread_cb_proc(cp_audio_func_t *audio_func);
void audio_func_decode_thread_cb_proc(cp_audio_func_t *audio_func);
void audio_func_merge_thread_cb_proc(cp_audio_func_t *audio_func);

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: set_audio_multicast_data_filter
*
* ����˵��: ����multicast socket
*
* ��    ��: cp_audio_func_t * audio_func			[in]����˵��
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
cp_int32_t set_audio_multicast_data_filter(cp_audio_func_t *audio_func, cp_char_t *buf, cp_int32_t len);

//�ر���Ƶ socket
cp_int32_t close_audio_multicast_socket(cp_audio_func_t *audio_func);

//����memh��socket����
cp_int32_t set_audio_memh_socket_data(cp_audio_func_t *audio_func, cp_char_t *buf, cp_int32_t len);

//����memh socket����
cp_int32_t unset_audio_memh_socket_data(cp_audio_func_t *audio_func);

//�򿪲����ļ�
cp_bool_t open_audio_test_file(cp_audio_func_t *audio_func);

//�رղ����ļ�
cp_bool_t close_audio_test_file(cp_audio_func_t *audio_func);

//У�������Ƿ��
cp_inline cp_bool_t check_audio_is_end(cp_buf_t *buf);

//���ý�������Ϣ
cp_inline cp_int32_t set_audio_codec_info(cp_audio_func_t *audio_func, cp_array_t *ary);

//������Ƶ�����ز�����Ϣ
cp_int32_t set_audio_codec_convert_info(cp_audio_func_t *audio_func);

//У��ý��������Ϣ
cp_bool_t check_audio_media_type(cp_audio_func_t *audio_func, cp_int32_t type);

//�ر���Ƶ��������Ϣ
cp_int32_t close_audio_codec_info(cp_audio_func_t *audio_func);

//������Ƶ��������Ϣ
cp_int32_t unset_audio_codec_info(cp_audio_func_t *audio_func);

//���ò�����Ϣ
cp_int32_t set_audio_dev_info(cp_audio_func_t *audio_func, cp_audio_description_t *ad);

//������Ƶ������Ϣ
cp_int32_t unset_audio_dev_info(cp_audio_func_t *audio_func);

//����ý������
cp_inline cp_media_packet_t* merge_audio_media_data(cp_audio_func_t *audio_func, cp_array_t *ary);

//��ȡһ֡��
cp_inline cp_int32_t get_a_audio_frame_data(cp_audio_func_t *audio_func, cp_array_t *ary);

//����ý������
cp_inline cp_int32_t decode_audio_media_data(cp_audio_func_t *audio_func, cp_media_packet_t	*mp);

//��ý������
cp_inline cp_int32_t play_audio_media_data(cp_audio_func_t *audio_func, cp_media_packet_t	*mp);

//ֹͣһ��ý�岥��
cp_int32_t stop_audio_func_media_play(cp_audio_func_t *audio_func, cp_media_channel_info_t *mci);

//���ý��ͨ��
cp_int32_t insert_audio_media_channel_info(cp_audio_func_t *audio_func, cp_media_channel_info_t *mci);

//����һ��ý�岥��
cp_int32_t update_audio_func_media_play(cp_audio_func_t *audio_func, cp_media_channel_info_t *mci);

//ɾ��ý��ͨ��
cp_int32_t remove_audio_media_channel_info(cp_audio_func_t *audio_func, cp_media_channel_info_t *mci);

//������������
cp_inline cp_int32_t destroy_audio_tmp_data(cp_audio_func_t *audio_func, cp_array_t *ary);

//��ʼ��ý����Ϣ
cp_int32_t init_audio_media_description_info(cp_audio_func_t *audio_func);

//��ʼ��������Ϣ
cp_int32_t init_audio_codec_callback_info(cp_audio_func_t *audio_func);

//��ʼ��merge
cp_int32_t init_audio_merge_safe_queue(cp_audio_func_t *audio_func);

//����merge
cp_int32_t destory_audio_merge_safe_queue(cp_audio_func_t *audio_func);

//����һ��media_packet
cp_static cp_media_packet_t *create_a_audio_media_packet(cp_audio_func_t *audio_func, cp_int32_t len);

//����һ��media_packet
cp_static cp_int32_t destroy_a_audio_media_packet(cp_audio_func_t *audio_func, cp_media_packet_t *mp);

//���������߳�
cp_int32_t start_audio_thread_process(cp_audio_func_t *audio_func);

//���������߳�
cp_int32_t start_audio_single_thread_process(cp_audio_func_t *audio_func);

//���������߳�
cp_int32_t start_audio_multi_thread_process(cp_audio_func_t *audio_func);

//���������߳�
cp_int32_t start_audio_merge_thread_process(cp_audio_func_t *audio_func);

//���������߳�
cp_int32_t start_audio_decode_thread_process(cp_audio_func_t *audio_func);




//ֹͣ�����߳�
cp_int32_t stop_audio_thread_process(cp_audio_func_t *audio_func);

//ֹͣ�����߳�
cp_int32_t stop_audio_single_thread_process(cp_audio_func_t *audio_func);

//ֹͣ�����߳�
cp_int32_t stop_audio_decode_thread_process(cp_audio_func_t *audio_func);

//ֹͣ�����߳�
cp_int32_t stop_audio_multi_thread_process(cp_audio_func_t *audio_func);

//ֹͣ�����߳�
cp_int32_t stop_audio_merge_thread_process(cp_audio_func_t *audio_func);

//��ӡʱ�������
cp_char_t* format_audio_frame_timestamp(cp_char_t *buf, cp_int32_t len);




//����ɾ����Ϣ
cp_int32_t send_remove_module_message(cp_audio_func_t *audio_func);






#endif