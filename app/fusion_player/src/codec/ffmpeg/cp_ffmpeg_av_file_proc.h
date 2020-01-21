/*******************************************************************************
*
*Copyright:novigo
*
*File name: cp_ffmpeg_av_file_proc.h
*
*Author:fangzhenmu@novigo.com.cn
*
*Version: 1.0
*
*Date:2017/08/06
*
*Description: create (cp_ffmpeg_av_file_proc.h)
*
*Others:
*
*History:
*******************************************************************************/

#ifndef _CP_FFMPEG_AV_FILE_PROC_H_
#define _CP_FFMPEG_AV_FILE_PROC_H_



#include "cp_ffmpeg_av_codec_core.h"
#include "cp_ffmpeg_av_file_conf.h"



#define	CP_FFMPEG_AV_FILE_SQ_DEFAULT_CACHE_SIZE				64											//��ʾĬ�ϵĻ���������
#define CP_FFMPEG_AV_FILE_SQ_DEFAULT_SLEEP_INTERVAL			1000000										//Ĭ�ϵ����߼��ʱ�䣬��λ����


typedef struct cp_ffmpeg_av_file_info_s						cp_ffmpeg_av_file_info_t;



/************************************************************************/
/* ffmpeg �ļ���Ϣ                                                       */
/************************************************************************/
struct cp_ffmpeg_av_file_info_s
{
	cp_ffmpeg_av_codec_t									*ffmpeg_av_codec;							//������Ϣ
	cp_int32_t												max_cache_size;								//��ʾ��󻺴�����
	cp_int32_t												min_cache_size;								//��ʾ��С��������
	cp_safe_queue_t											*data_sq;									//��ʾ������ý������
	cp_thread_status_e										decode_thread_status;						//��ʾ�����߳�״̬
	cp_thread_t												*decode_thread;								//��ʾ�����߳�
};


//����file info��Ϣ
cp_int32_t create_ffmpeg_av_file_info(cp_ffmpeg_av_codec_t *ffmpeg_av_codec);

//��ʼ��file info��Ϣ
cp_int32_t init_ffmpeg_av_file_info(cp_ffmpeg_av_codec_t *ffmpeg_av_codec);

//��file info��Ϣ
cp_int32_t open_ffmpeg_av_file_info(cp_ffmpeg_av_codec_t *ffmpeg_av_codec, cp_media_description_t *md);

//��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��
cp_int32_t read_ffmpeg_av_file_data(cp_ffmpeg_av_codec_t *ffmpeg_av_codec,
	cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);

//дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��
cp_int32_t write_ffmpeg_av_file_data(cp_ffmpeg_av_codec_t *ffmpeg_av_codec,
	const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);

//�ر�file info��Ϣ
cp_int32_t close_ffmpeg_av_file_info(cp_ffmpeg_av_codec_t *ffmpeg_av_codec);

//�˳�file info��Ϣ
cp_int32_t exit_ffmpeg_av_file_info(cp_ffmpeg_av_codec_t *ffmpeg_av_codec);

//����file info
cp_int32_t destroy_ffmpeg_av_file_info(cp_ffmpeg_av_codec_t *ffmpeg_av_codec);

/*��urlָ����ý��Դ��Ϣ*/
cp_int32_t open_ffmpeg_av_file_stream(cp_ffmpeg_av_codec_t *ffmpeg_av_codec, cp_media_description_t *md);

/*�ر�urlָ����ý��Դ��Ϣ*/
cp_int32_t close_ffmpeg_av_file_stream(cp_ffmpeg_av_codec_t *ffmpeg_av_codec);




//���������߳�
cp_int32_t start_ffmpeg_av_decode_thread_process(cp_ffmpeg_av_codec_t *ffmpeg_av_codec);

//ֹͣ�����߳�
cp_int32_t stop_ffmpeg_av_decode_thread_process(cp_ffmpeg_av_codec_t *ffmpeg_av_codec);

//�����̴߳���
void ffmpeg_av_decode_thread_cb_proc(cp_ffmpeg_av_codec_t *ffmpeg_av_codec);







#endif //_CP_FFMPEG_AV_FILE_PROC_H_




