/*******************************************************************************
*
*Copyright:novigo
*
*File name: cp_video_frame_packet.h
*
*Author:fangzhenmu@novigo.com.cn
*
*Version: 1.0
*
*Date:2017/08/12
*
*Description: create (cp_video_frame_packet.h)
*
*Others:
*
*History:
*******************************************************************************/

#ifndef _CP_VIDEO_FRAME_PACKET_H_
#define _CP_VIDEO_FRAME_PACKET_H_



#include "cp_media_packet.h"




typedef struct cp_video_frame_play_position_s		cp_video_frame_play_position_t;
typedef struct cp_video_frame_packet_s				cp_video_frame_packet_t;



#pragma pack(1)




/************************************************************************/
/* ��Ƶ֡����λ����Ϣ                                                    */
/************************************************************************/
struct cp_video_frame_play_position_s
{
	//fpp��ʾý����������Ҫ������ĺ��λ����Ϣ��
	//����source��ʾý�屾���ȫͼλ����Ϣ��dest��ʾ��Ҫ���ڴ����ͼ��������ˣ�source��������ʾ���������dest����������ʾ������
	/************************************************************************/
	/* fpp����ʹ��˵��                                                       */
	/*        .      __________________________________       .             */
	/*        .     | xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx |      .             */
	/*        .     | xxxxxxxx  fpp->source  xxxxxxxxx |      .             */
	/*        .     | xxxxxxx ________________ xxxxxxx |      .             */
	/*        .     | xxxxxx |                | xxxxxx |      .             */
	/*        .     | xxxxxx |   fpp->dest    | xxxxxx |      .             */
	/*        .     | xxxxxx |________________| xxxxxx |      .             */
	/*        .     | xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx |      .             */
	/*        .     | xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx |      .             */
	/*        .     | ________________________________ |      .             */
	/*                                                                      */
	/************************************************************************/
	cp_frame_play_position_t				fpp;				//��ʾý�������
	cp_int32_t								layer;				//��ʾ�����Ϣ��ȡֵ[0, (cp_int32_t -1)]����ֵԽ��Խ�����㡣
	//cp_media_packet_buf_t					mp_buf;				//ý������buf����
	cp_queue_t								queue;				//��ʾ��Ƶ֡����λ���б�
};


/************************************************************************/
/* ��Ƶ֡���ݰ�                                                          */
/************************************************************************/
struct cp_video_frame_packet_s
{
	CP_MEDIA_PACKET_FIELDS										//��ʾý�������

	//fpp��ʾý����������Ҫ������ĺ��λ����Ϣ��
	//����source��ʾý�屾���ȫͼλ����Ϣ��dest��ʾ��Ҫ���ڴ����ͼ��������ˣ�source��������ʾ���������dest����������ʾ������
	/************************************************************************/
	/* fpp����ʹ��˵��                                                       */
	/*        .      __________________________________       .             */
	/*        .     | xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx |      .             */
	/*        .     | xxxxxxxx  fpp->source  xxxxxxxxx |      .             */
	/*        .     | xxxxxxx ________________ xxxxxxx |      .             */
	/*        .     | xxxxxx |                | xxxxxx |      .             */
	/*        .     | xxxxxx |   fpp->dest    | xxxxxx |      .             */
	/*        .     | xxxxxx |________________| xxxxxx |      .             */
	/*        .     | xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx |      .             */
	/*        .     | xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx |      .             */
	/*        .     | ________________________________ |      .             */
	/*                                                                      */
	/************************************************************************/
	cp_frame_play_position_t				fpp;
	cp_queue_t								queue;				//��ʾ��Ƶ֡���ݶ���,��Ҫ��cp_video_frame_process_t�ṹʹ��
	cp_queue_t								vfpp_queue;			//��ʾ��Ƶ֡����λ����Ϣ����cp_video_frame_play_position_tλ������
};




#pragma pack()




#endif //_CP_VIDEO_FRAME_PACKET_H_


