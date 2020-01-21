

/*******************************************************************************
*
*Copyright:novigo
*
*File name: cp_vdu.h
*
*Author:fangzhenmu@novigo.com.cn
*
*Version: 1.0
*
*Date:2018/01/01
*
*Description: create (cp_vdu.h)
*1�����ģ����Ҫ����ʸ�������ݵĴ�������ͨ��ģ�鷽ʽ����֧�ֶ�������
*2��ģ����Ҫ����˼��Ϊ����cp_app��һ�������װ����app��װΪһ��codec��ģ��
*3��ģ���ʹ�÷��������֣�
*			1���ⲿʹ�á�����cp_vdu.hͷ�ļ����������еĽӿں���
*			2���ڲ�ʹ�á�������ʹ��1��������Ҳ����ֱ�Ӽ������е�ģ��
*Others:
*
*History:
*******************************************************************************/

#ifndef _CP_VDU_H_
#define _CP_VDU_H_



#include <stdio.h>
#include <stdlib.h>
#include "cp_vdu_type.h"
#include "cp_vdu_vector_stream_type.h"
#include "cp_vdu_rect.h"
#include "cp_vdu_pixel.h"



//����ӿڵĵ�����ʽ
#ifndef cp_extern
#define cp_extern
#endif



//��ʾĬ�ϵĻ�������С
#define CP_VDU_DEFAULT_BUFFER_LENGTH			32




typedef  struct cp_vdu_s						cp_vdu_t;
typedef  struct cp_vdu_channel_s				cp_vdu_channel_t;
typedef  struct cp_vdu_info_s					cp_vdu_info_t;
typedef	 struct cp_vdu_version_s				cp_vdu_version_t;
typedef  struct cp_vdu_image_info_s				cp_vdu_image_info_t;




#pragma pack(1)


/************************************************************************/
/*����һ��vdu����															*/
/************************************************************************/
struct cp_vdu_s {
	void										*app;					/*��������app��Ϣ�ṹ��Ϣ�����ڼ���cp_app����*/
	void										*process;				/*��ʾ����Ԫ��ַ*/
	cp_vdu_type_e								type;					/*��ʾvdu����*/

};


/************************************************************************/
/*����һ��vdu channel����													*/
/************************************************************************/
struct cp_vdu_channel_s {
	void										*app;					/*��������app��Ϣ�ṹ��Ϣ�����ڼ���cp_app����*/
	cp_vdu_t									*vdu;					/*��ʾ�䷢չ��vdu����*/
	void										*channel;				/*��ʾ����channel����Ϣ����*/
	cp_vdu_channel_type_e						type;					/*��ʾvdu channelͨ��������*/
	int											index;					/*��ʾͨ����������*/
};



/************************************************************************/
/*����һ��vdu����															*/
/************************************************************************/
struct cp_vdu_info_s {
	int											type;					/*��ʾ������Ϣ*/
};



/************************************************************************/
/*����һ��vdu����															*/
/************************************************************************/
struct cp_vdu_version_s {
	char										name[CP_VDU_DEFAULT_BUFFER_LENGTH];					/*��ʾ��������,����:"cp_vdu"*/
	int											version;											/*��ʾ�汾��,����:100*/
	char										str_version[CP_VDU_DEFAULT_BUFFER_LENGTH];			/*��ʾ�汾�ַ���,����:"V0.1.0"*/
	char										description[CP_VDU_DEFAULT_BUFFER_LENGTH];			/*��ʾ����������Ϣ,����:"cp_vdu/V0.1.0"*/
};


/************************************************************************/
/*����һ��vdu ͼƬ��Ϣ����													*/
/************************************************************************/
struct cp_vdu_image_info_s {
	char										*buf;												/*��ʾ�����ͼƬλͼ������ڴ�λ��*/
	int											buf_length;											/*��ʾ�����ͼƬλͼ������ڴ泤��*/
	cp_vdu_pixel_format_e						vpf;												/*��ʾͼƬ�ĸ�ʽ*/
	cp_vdu_rect_t								vdu_rect;											/*��ʾvdu��ͼƬ����*/
	cp_vdu_rect_t								image_rect;											/*��ʾvduͼƬ�������Ŀ��ͼƬ��С��Ҳ�������ŵĲ���*/
	int											image_length;										/*��ʾͼƬλͼ����ʵ�ʳ���*/
};



#pragma pack()



#include "cp_vdu_api.h"




#endif //_CP_VDU_H_


