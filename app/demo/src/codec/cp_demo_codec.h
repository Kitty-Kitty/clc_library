/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_DEMO_CODEC_INCLUDE_H_
#define _CP_DEMO_CODEC_INCLUDE_H_

#include <stddef.h>
#include "uv.h"
#include "cp_demo_codec_core.h"



//typedef struct cp_demo_codec_s				cp_demo_codec_t;





#pragma pack(1)


#define CP_DEMO_CODEC_FIELDS											\
		CP_CODEC_FIELDS													\
		cp_int32_t						css_av_type;	/*css ý������*/	\
		cp_media_channel_info_t			*mci;		/*ý��ͨ����Ϣ*/		\


/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_demo_codec_s {
	CP_DEMO_CODEC_FIELDS												/*��ʾʱ��ģ����Ϣ*/
};

#pragma pack()




cp_demo_codec_t* create_demo_codec(cp_module_register_t *register_info, cp_codec_manager_t *manager, cp_demo_codec_info_t *info);
cp_int32_t destroy_demo_codec(cp_codec_manager_t *manager, cp_demo_codec_t* demo_codec);



/************************************************************************/
/* ���ý��������													    */
/************************************************************************/
#define CP_DEMO_CODEC_SET_MEDIA_CHANNEL_INFO(codec, in_mci)	do {	\
		(codec)->mci = (cp_media_channel_info_t*)(in_mci);				\
	}while(0);															\


#endif


