/*******************************************************************************
*
*Copyright:novigo
*
*File name: cp_media_process.h
*
*Author:fangzhenmu@novigo.com.cn
*
*Version: 1.0
*
*Date:2017/08/20
*
*Description: create (cp_media_process.h)
*
*Others:
*
*History:
*******************************************************************************/

#ifndef _CP_MEDIA_PROCESS_H_
#define _CP_MEDIA_PROCESS_H_



#include "cp_media_core.h"



//typedef struct cp_media_process_s			cp_media_process_t;



#pragma pack(1)



/************************************************************************/
/* ��ʾmedia process ��Ա����                                            */
/************************************************************************/
#define CP_MEDIA_PROCESS_FIELDS																									\
	cp_media_surface_t						*ms;				/*ý��surface����ʾ����������ݡ���������,��Ŀ��ͼƬ*/				\
	cp_media_packet_t						*mp;				/*��ʾý������������Դ����ͼƬ���ݡ�*/							\



/************************************************************************/
/* ý��֡�������ݽṹ                                                    */
/* ��Ҫ�����ǽ�Դ(cp_media_packet_t)����Ŀ�ģ�cp_media_surface_t���У�  */
/*     1��cp_media_surface_t ��������,��Ŀ��ͼƬ                         */
/*     2��cp_media_packet_t ���Դ����ͼƬ����                           */
/************************************************************************/
struct cp_media_process_s
{
	CP_MEDIA_PROCESS_FIELDS
};




#pragma pack()








#endif //_CP_MEDIA_PROCESS_H_


