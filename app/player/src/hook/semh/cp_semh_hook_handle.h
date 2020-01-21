/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_SEMH_HOOK_HANDLE_INCLUDE_H_
#define _CP_SEMH_HOOK_HANDLE_INCLUDE_H_


#include "cp_semh_hook_core.h"


/************************************************************************/
/*中心注册返回															*/
/************************************************************************/
cp_int32_t proc_semh_center_register_return(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg);

/************************************************************************/
/* 取消注册返回                                                         */
/************************************************************************/
cp_int32_t proc_semh_center_cancel_register_return(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg);

/************************************************************************/
/* 中心和其他设备心跳心跳                                                             */
/************************************************************************/
cp_int32_t proc_semh_all_life_heart(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg);
cp_int32_t proc_semh_center_life_heart(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg);
cp_int32_t proc_semh_accessed_server_life_heart(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg);
cp_int32_t proc_semh_media_server_life_heart(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg);
cp_int32_t proc_semh_player_life_heart(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg);
cp_int32_t proc_semh_client_background_server_life_heart(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg);
cp_int32_t proc_semh_player_background_server_life_heart(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg);

/************************************************************************/
/* 服务器心跳返回                                                       */
/************************************************************************/
cp_int32_t proc_semh_player_heart_return(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg);


/************************************************************************/
/* 设备软件更新															*/
/************************************************************************/
cp_int32_t proc_semh_player_software_update(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg);

/************************************************************************/
/* 设备日志接口															*/
/************************************************************************/
cp_int32_t proc_semh_player_set_log(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg);
cp_int32_t proc_semh_player_get_log(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg);
cp_int32_t proc_semh_player_delete_log(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg);
cp_int32_t proc_semh_player_query_log(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg);

/************************************************************************/
/* 设备操作接口                                                         */
/************************************************************************/
cp_int32_t proc_semh_player_get_dev_info(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg);
cp_int32_t proc_semh_player_set_dev_info(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg);
cp_int32_t proc_semh_player_start_dev(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg);
cp_int32_t proc_semh_player_stop_dev(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg);
cp_int32_t proc_semh_player_test_dev(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg);
cp_int32_t proc_semh_player_set_network(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg);
cp_int32_t proc_semh_player_set_focus(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg);

/************************************************************************/
/* 设备背景接口                                                         */
/************************************************************************/
cp_int32_t proc_semh_player_set_background(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg);
cp_int32_t proc_semh_player_clear_background(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg);
cp_int32_t proc_semh_player_reflesh_picture(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg);

/************************************************************************/
/* 设备字幕接口                                                         */
/************************************************************************/
cp_int32_t proc_semh_player_set_word(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg);
cp_int32_t proc_semh_player_clear_word(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg);

/************************************************************************/
/* 设备媒体接口                                                         */
/************************************************************************/
cp_int32_t proc_semh_player_media_play(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg);
cp_int32_t proc_semh_player_media_play_update(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg);
cp_int32_t proc_semh_player_media_layer_update(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg);
cp_int32_t proc_semh_player_media_stop(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg);
cp_int32_t proc_semh_player_media_close(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg);
cp_int32_t proc_semh_player_media_get_channel_info(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg);


/************************************************************************/
/* 音频播放相关                                                          */
/************************************************************************/
cp_int32_t proc_semh_player_audio_play(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg);
cp_int32_t proc_semh_player_audio_play_update(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg);
cp_int32_t proc_semh_player_audio_stop(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg);


/************************************************************************/
/* 离线设置设备接口                                                     */
/************************************************************************/
cp_int32_t proc_semh_player_offline_get_passwd(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg);
cp_int32_t proc_semh_player_offline_set_passwd(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg);
cp_int32_t proc_semh_player_offline_update_passwd(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg);
cp_int32_t proc_semh_player_offline_get_information(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg);
cp_int32_t proc_semh_player_offline_set_information(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg);

/************************************************************************/
/* 中心请求返回接口                                                     */
/************************************************************************/
cp_int32_t send_semh_player_get_dev_info_return(cp_player_t *player, cp_socket_t *s, gmp_gmph_semh_t *semh, cp_request_info_t *request_info,
	cp_sockaddr_in *addr, cp_int32_t flags);
cp_int32_t send_semh_player_get_log_info_return(cp_player_t *player, cp_socket_t *s, gmp_gmph_semh_t *semh, cp_request_info_t *request_info,
	cp_sockaddr_in *addr, cp_int32_t flags);

/************************************************************************/
/* 系统基础函数                                                         */
/************************************************************************/
cp_int32_t func_global(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg);
cp_int32_t func_global_destroy(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg);
cp_int32_t func_check_semh_command(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg);
cp_int32_t func_get_semh_hook(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg);
cp_int32_t func_parse_gmf_data(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg);
cp_int32_t func_gmf_error_data(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg);
cp_int32_t func_error_response(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg, cp_char_t *fmt, ...);

cp_bool_t func_join_media_multicast(cp_player_t *player, const cp_char_t *ip, const cp_int32_t port);

cp_bool_t send_semh_response_data(cp_player_t *player, cp_socket_t *s, const cp_sockaddr_in *remote_addr,
	gmp_gmph_semh_t *semh, gmp_gmf_t *src_gmf, cp_int32_t status, cp_char_t *reason, cp_int32_t nreason);
cp_bool_t send_semh_response(cp_player_t *player, cp_socket_t *s, const cp_sockaddr_in *remote_addr,
	gmp_gmph_semh_t *semh, cp_int32_t status, cp_char_t *reason, cp_int32_t nreason);

/************************************************************************/
/* 数据结构操作接口                                                      */
/************************************************************************/
cp_int32_t cp_list_find_device_info_by_type(list_node *device_node, void *type);
cp_int32_t cp_list_find_device_focus_by_id(list_node *focus_node, char *id);

/************************************************************************/
/* 更新和保存host部分的信息                                                    */
/************************************************************************/
cp_int32_t	cp_update_host_info(cp_host_t *dest, cp_host_t *src);
cp_int32_t	cp_save_host_info(cp_player_t *player, cp_host_t *src);


#endif

