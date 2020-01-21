/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_HI3531_TDE_INCLUDE_H_
#define _CP_HI3531_TDE_INCLUDE_H_

#include "cp_hi3531_tde_core.h"






#pragma pack(1)


#define CP_HI3531_TDE_FIELDS																		\
		CP_PLAYER_DEV_FIELDS																		\



/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_hi3531_tde_s {
	CP_HI3531_TDE_FIELDS														/*��ʾʱ��ģ����Ϣ*/

#if defined(CP_HI3531_DEV_MODE)
	TDE_HANDLE													tde_handle;		/*vo mppͨ����Ϣ*/
#endif

	cp_hi3531_tde_configure_t									hacc;			/*��ʾ��ǰ�ı�����������Ϣ*/

};


#pragma pack()



cp_hi3531_tde_t* create_hi3531_tde(cp_module_register_t *register_info, cp_codec_manager_t *manager, cp_hi3531_tde_info_t *info);
cp_int32_t destroy_hi3531_tde(cp_codec_manager_t *manager, cp_hi3531_tde_t* hi3531_tde);

#endif


