/*******************************************************************************
*
*Copyright:novigo
*
*File name: cp_media_canvas.h
*
*Author:fangzhenmu@novigo.com.cn
*
*Version: 1.0
*
*Date:2017/08/20
*
*Description: create (cp_media_canvas.h)
*
*Others:
*
*History:
*******************************************************************************/

#ifndef _CP_MEDIA_CANVAS_H_
#define _CP_MEDIA_CANVAS_H_



#include "cp_media_core.h"



//typedef		enum cp_media_canvas_type_enum				cp_media_canvas_type_e;
//typedef		struct cp_media_canvas_s					cp_media_canvas_t;




#pragma pack(1)


/************************************************************************/
/* ��ʾmedia canvas ������Ϣ                                            */
/************************************************************************/
typedef enum cp_media_canvas_type_enum
{
	cp_media_canvas_type_none,								//��ʾ����δ����
	cp_media_canvas_type_video,								//��ʾ��Ƶ����
	cp_media_canvas_type_audio,								//��ʾ��Ƶ����
}cp_media_canvas_type_e;


/************************************************************************/
/* ��ʾmedia canvas ��Ա����                                            */
/************************************************************************/
#define CP_MEDIA_CANVAS_FIELDS																					\
		cp_media_canvas_type_e							type;				/*��ʾý��canvas��������Ϣ*/			\
		cp_media_description_t							*md;				/*��ʾý�������Ϣ*/					\



/************************************************************************/
/* ��ʾ���յ�������ݽṹ                                                 */
/************************************************************************/
struct cp_media_canvas_s
{
	CP_MEDIA_CANVAS_FIELDS
};

#pragma pack()


#endif //_CP_MEDIA_CANVAS_H_


