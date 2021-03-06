/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-07

Description:

**************************************************************************/
#include "cp_dev_description.h"



/************************************************************************/
/* 创建描述信息                                                          */
/************************************************************************/
cp_dev_description_t	*create_dev_description(cp_pool_t *pool, cp_dev_description_type_e type)
{
	cp_int32_t								desc_len = 0;
	cp_dev_description_t					*tmp_md = CP_NULL;



	if (!pool) {
		return CP_NULL;
	}

	switch (type)
	{
		case cp_dev_description_type_general:
		{
			desc_len = cp_sizeof(cp_dev_description_t);
		}
		break;
		case cp_dev_description_type_video:
		{
			desc_len = cp_sizeof(cp_dev_video_description_t);
		}
		break;
		case cp_dev_description_type_audio:
		{
			desc_len = cp_sizeof(cp_dev_audio_description_t);
		}
		break;
		default:
		{

		}
		break;
	}

	if (desc_len > 0) {
		tmp_md = (cp_dev_description_t*)cp_palloc(pool, desc_len);
		if (tmp_md) {
			tmp_md->type = type;
		}
	}

	return tmp_md;
}

/************************************************************************/
/* 消毁描述信息                                                          */
/************************************************************************/
cp_int32_t destroy_dev_description(cp_pool_t *pool, cp_dev_description_t *md)
{
	if (!pool || !md) {
		return -1;
	}
	cp_pfree(pool, md);
	return 0;
}