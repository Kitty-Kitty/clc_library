/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-20

Description:

**************************************************************************/

#ifndef _CP_VIDEO_FUNC_CONF_INCLUDE_H_
#define _CP_VIDEO_FUNC_CONF_INCLUDE_H_


#include "cp_core.h"
#include "cp_module_core.h"
#include "cp_video_description.h"
#include "cp_video_func_conf_string.h"



#define	CP_VIDEO_SOURCE_URL_LENGTH							512					//��ƵԴ��ַ
#define	CP_VIDEO_SOURCES_MAX_NUMBER							8					//��ƵԴ��ַ


typedef struct cp_video_source_s							cp_video_source_t;
typedef struct cp_video_func_configure_s					cp_video_func_configure_t;



#pragma pack(1)

/************************************************************************/
/* ��ƵԴ��Ϣ                                                            */
/************************************************************************/
struct cp_video_source_s
{
	cp_char_t						url[CP_VIDEO_SOURCE_URL_LENGTH];			//��ʾ�Ƿ������Ƶ�ز�����ȡֵ��0��ʾ���زɣ�1��ʾ�ز�
	cp_bool_t						is_used;									//����Ƿ�ʹ��
};

/************************************************************************/
/* ��Ƶ�����������                                                      */
/************************************************************************/
struct cp_video_func_configure_s
{
	cp_video_source_t				video_sources[CP_VIDEO_SOURCES_MAX_NUMBER];	//��ƵԴ����
	cp_int32_t						buffer_size;								//��ʾ��ǰʹ�õĻ�������
	cp_int32_t						each_buffer_length;							//��ʾ��ǰʹ�õ�ÿ�������С
};

#pragma pack()


/************************************************************************/
/*���������ļ�                                                           */
/************************************************************************/
cp_int32_t	video_func_parse_configure(cp_module_t *module, cp_video_func_configure_t *afc);

/************************************************************************/
/* ����video sources                                                     */
/************************************************************************/
cp_int32_t	video_func_parse_video_sources(const cp_module_t *module, cp_video_func_configure_t *afc);


#endif