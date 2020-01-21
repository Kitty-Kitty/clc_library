/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-11-21

Description:

**************************************************************************/
#include "cp_semh_parse_gmf.h"



cp_play_channel_info_t* get_semh_play_info(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg, cp_char_t *buf, cp_int32_t len)
{
	cp_bool_t							tmp_bool = cp_false;
	cp_int32_t							tmp_size = 0;
	cp_char_t							tmp_buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };
	cp_play_channel_info_t				*tmp_pc_info = CP_NULL;
	gmp_gmf_t							*gmf = session->gmf;
	cp_void_t							*tmp_p = CP_NULL;



	cp_memset(buf, 0, len);
	tmp_pc_info = (cp_play_channel_info_t *)cp_palloc(session->pool, cp_sizeof(cp_play_channel_info_t));
	if (!tmp_pc_info) {
		cp_snprintf(buf, len, "mpalloc(cp_play_channel_info_t) size[%d] failed!", 
			cp_sizeof(cp_play_channel_info_t));
		return CP_NULL;
	}
	else {
		cp_memset(tmp_pc_info, 0, cp_sizeof(cp_play_channel_info_t));
	}

	//获取媒体信息列表数量
	tmp_size = get_gmf_play_meida_channel_size(gmf, buf, CP_APP_DEFAULT_BUFFER_LENGTH);
	if (tmp_size <= 0) {
		cp_snprintf(buf, len, "get_gmf_play_meida_channel_size() error! size[%d]", tmp_size);
		return CP_NULL;
	}

	//声请内存空间
	tmp_p = cp_palloc(session->pool, cp_sizeof(cp_media_channel_info_t) * tmp_size);
	if (!tmp_p) {
		cp_snprintf(buf, len, "mpalloc() media_channel_info array failed! size[%d] failed!", 
			cp_sizeof(cp_media_channel_info_t) * tmp_size);
		return CP_NULL;
	}
	else {
		cp_memset(tmp_p, 0, cp_sizeof(cp_media_channel_info_t) * tmp_size);
	}

	//初始化媒体信息数组
	cp_array_init(&tmp_pc_info->mci_array, tmp_p, cp_sizeof(cp_media_channel_info_t), tmp_size);
	
	//获取时间戳信息
	tmp_bool = get_gmf_play_cmd_info(gmf, tmp_pc_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH);
	if (!tmp_bool) {
// 		cp_pfree(session->pool, tmp_p);
// 		cp_snprintf(buf, len, "get_gmf_play_cmd_info() error. reason:%s", tmp_buf);
// 		return CP_NULL;
	}

	//获取媒体通道信息
	if (!get_gmf_play_media_channel_array(gmf, &tmp_pc_info->mci_array, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH)) {
		cp_pfree(session->pool, tmp_p);
		cp_snprintf(buf, len, "get_gmf_play_media_channel_array() error. reason:%s", tmp_buf);
		return CP_NULL;
	}

	return tmp_pc_info;
}

cp_play_channel_info_t* get_semh_play_information_play_info(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg, cp_char_t *buf, cp_int32_t len)
{
	gmp_gmdu_t							*gmdu = CP_NULL;
	gmp_gmdt_t							*gmdt = CP_NULL;
	gmp_gmf_t							*gmf = session->gmf;
	cp_char_t							tmp_buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };
	cp_play_channel_info_t				*tmp_pc_info = CP_NULL;


	
	//查找PlayInformation节点
	gmdt = gmp_create_gmdt(gmf, "%T%p%d", GMP_GMDT_ST, CP_APP_STR_PLAY_INFORMATION, cp_strlen(CP_APP_STR_PLAY_INFORMATION));
	gmdu = gmp_find_gmdu(gmf, gmdt);
	if (!gmdu) {
		//清空缓存
		cp_memset(buf, 0, len);
		cp_snprintf(buf, len, "get gmf play media channel info error. not "CP_APP_STR_PLAY_INFORMATION" element error.");
		return CP_NULL;
	}

	//进入PlayInformation
	gmp_reset_gmdu(gmf, gmdu);
	gmp_into_gmdu(gmf);

	//获取需要的媒体信息
	tmp_pc_info = get_semh_play_info(hook, session, arg, tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
	if (!tmp_pc_info) {
		cp_semh_hook_log(warn, hook, session, "get_semh_play_info() error. reason: [%s]", tmp_buf);
		return CP_NULL;
	}

	return tmp_pc_info;
}

cp_int32_t destroy_play_info(cp_semh_session_t *session, cp_play_channel_info_t *pc_info)
{
	if (!session || !pc_info) {
		return -1;
	}

	if (pc_info->mci_array.elts) {
		cp_pfree(session->pool, pc_info->mci_array.elts);
	}

	cp_pfree(session->pool, pc_info);
	return 0;
}