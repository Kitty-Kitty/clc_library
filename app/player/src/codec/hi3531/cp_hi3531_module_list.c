/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-09-18

Description:

**************************************************************************/

#include "cp_hi3531_module_list.h"





cp_module_register_t  hi3531_codec_module_list[] = {
	CP_MODULE_REGISTER(cp_player_module_type_hi3531_dec_codec,
	1, "hi3531_dec_av_codec", "hi3531_dec_av_codec", create_hi3531_vdec_codec, destroy_hi3531_vdec_codec)
};

cp_int32_t hi3531_codec_module_list_size = cp_ary_size(hi3531_codec_module_list);








