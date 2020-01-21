/*******************************************************************************
*
*Copyright:novigo
*
*File name: cp_ffmpeg_av_data_proc.h
*
*Author:fangzhenmu@novigo.com.cn
*
*Version: 1.0
*
*Date:2017/08/06
*
*Description: create (cp_ffmpeg_av_data_proc.h)
*
*Others:
*
*History:
*******************************************************************************/

#ifndef _CP_FFMPEG_AV_DATA_PROC_H_
#define _CP_FFMPEG_AV_DATA_PROC_H_



#include "cp_ffmpeg_av_codec_core.h"



//����file info��Ϣ
cp_int32_t create_ffmpeg_av_data_proc(cp_ffmpeg_av_codec_t *ffmpeg_av_codec);

//��ʼ��file info��Ϣ
cp_int32_t init_ffmpeg_av_data_proc(cp_ffmpeg_av_codec_t *ffmpeg_av_codec);

//��file info��Ϣ
cp_int32_t open_ffmpeg_av_data_proc(cp_ffmpeg_av_codec_t *ffmpeg_av_codec, cp_media_description_t *md);

//��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��
cp_int32_t read_ffmpeg_av_data_stream(cp_ffmpeg_av_codec_t *ffmpeg_av_codec,
	cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);

//дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��
cp_int32_t write_ffmpeg_av_data_stream(cp_ffmpeg_av_codec_t *ffmpeg_av_codec,
	const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);

//�ر�file info��Ϣ
cp_int32_t close_ffmpeg_av_data_proc(cp_ffmpeg_av_codec_t *ffmpeg_av_codec);

//�˳�file info��Ϣ
cp_int32_t exit_ffmpeg_av_data_proc(cp_ffmpeg_av_codec_t *ffmpeg_av_codec);

//����file info
cp_int32_t destroy_ffmpeg_av_data_proc(cp_ffmpeg_av_codec_t *ffmpeg_av_codec);




/*�򿪽�������Ϣ*/
cp_int32_t open_ffmpeg_av_codec_data(cp_ffmpeg_av_codec_t *ffmpeg_av_codec, cp_media_description_t *md);

/*�رս�������Ϣ*/
cp_int32_t close_ffmpeg_av_codec_data(cp_ffmpeg_av_codec_t *ffmpeg_av_codec);




//�򿪲����ļ�
cp_bool_t open_test_file(cp_ffmpeg_av_codec_t *ffmpeg_av_codec);

//�رղ����ļ�
cp_bool_t close_test_file(cp_ffmpeg_av_codec_t *ffmpeg_av_codec);




#endif //_CP_FFMPEG_AV_DATA_PROC_H_


