/*******************************************************************************
*
*Copyright:novigo
*
*File name: cp_video_surface.h
*
*Author:fangzhenmu@novigo.com.cn
*
*Version: 1.0
*
*Date:2017/08/20
*
*Description: create (cp_video_surface.h)
*
*Others:
*
*History:
*******************************************************************************/

#ifndef _CP_VIDEO_SURFACE_H_
#define _CP_VIDEO_SURFACE_H_



//#include "cp_media_core.h"
#include "cp_media_surface.h"




//typedef		struct cp_video_surface_s					cp_video_surface_t;




#pragma pack(1)




/************************************************************************/
/* ��ʾ���յ����ͼƬ                                                    */
/************************************************************************/
struct cp_video_surface_s
{
	CP_MEDIA_SURFACE_FIELDS												//��ʾý�������Ϣ

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

};

#pragma pack()


#endif //_CP_VIDEO_SURFACE_H_


