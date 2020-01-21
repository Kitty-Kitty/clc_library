/*******************************************************************************
*
*Copyright:novigo
*
*File name: cp_media_surface.h
*
*Author:fangzhenmu@novigo.com.cn
*
*Version: 1.0
*
*Date:2017/08/20
*
*Description: create (cp_media_surface.h)
*
*Others:
*
*History:
*******************************************************************************/

#ifndef _CP_MEDIA_SURFACE_H_
#define _CP_MEDIA_SURFACE_H_



#include "cp_media_core.h"



//typedef		enum cp_media_surface_type_enum				cp_media_surface_type_e;
//typedef		struct cp_media_surface_s					cp_media_surface_t;




#pragma pack(1)


/************************************************************************/
/* ��ʾmedia surface ������Ϣ                                            */
/************************************************************************/
typedef enum cp_media_surface_type_enum
{
	cp_media_surface_type_none,								//��ʾ����δ����
	cp_media_surface_type_video,							//��ʾ��Ƶ����
	cp_media_surface_type_audio,							//��ʾ��Ƶ����
}cp_media_surface_type_e;


/************************************************************************/
/* ��ʾmedia surface ��Ա����                                            */
/************************************************************************/
#define CP_MEDIA_SURFACE_FIELDS																					\
		cp_media_surface_type_e							type;				/*��ʾý��surface��������Ϣ*/			\
		cp_media_description_t							*md;				/*��ʾý�������Ϣ*/					\



/************************************************************************/
/* ��ʾ���յ�������ݽṹ                                                 */
/************************************************************************/
struct cp_media_surface_s
{
	CP_MEDIA_SURFACE_FIELDS
};

#pragma pack()


#endif //_CP_MEDIA_SURFACE_H_


