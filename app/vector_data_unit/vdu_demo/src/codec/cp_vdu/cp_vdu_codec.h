/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_VDU_CODEC_INCLUDE_H_
#define _CP_VDU_CODEC_INCLUDE_H_

#include "cp_vdu_codec_core.h"



//typedef struct cp_vdu_codec_s					cp_vdu_codec_t;




#pragma pack(1)


#define CP_VDU_CODEC_FIELDS																	\
		CP_VDU_DEMO_CODEC_FIELDS																			\



/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_vdu_codec_s {
	CP_VDU_CODEC_FIELDS									/*��ʾʱ��ģ����Ϣ*/

#if defined(CP_VDU_CODEC_FILE_DEBUG)
		FILE											*file;	/*ý���ļ�*/
#endif

};


#pragma pack()



cp_vdu_codec_t* create_vdu_codec(cp_module_register_t *register_info, cp_codec_manager_t *manager, cp_vdu_codec_info_t *info);
cp_int32_t destroy_vdu_codec(cp_codec_manager_t *manager, cp_vdu_codec_t* vdu_codec);

#endif


