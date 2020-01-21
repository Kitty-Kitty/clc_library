/**************************************************************************

* Copyright: novigo

* Author: tianhuiming@novigo.com.cn

* Date：2016-4-23
        
* Description:

**************************************************************************/



#ifndef	_CP_CSS_GMF_INCLUDE_H_
#define _CP_CSS_GMF_INCLUDE_H_

// #include "cp_core.h"
// #include "prot_gmp_core.h"
// #include "prot_core.h"
#include "cp_css_hook_core.h"


cp_int32_t make_semh_header(gmp_gmph_semh_t *semh, cp_uint32_t cmd, cp_int32_t len, cp_int32_t p_no, 
	cp_int32_t status, cp_char_t *session_id);
gmp_gmdu_t *make_gmf_host(gmp_gmf_t *gmf, cp_host_t *host);
gmp_gmdu_t *make_gmf_interfaces(gmp_gmf_t *gmf, cp_interface_t *network);
gmp_gmdu_t *make_gmf_serials(gmp_gmf_t *gmf, cp_serial_t *serials);
gmp_gmdu_t *make_gmf_networks(gmp_gmf_t *gmf, cp_interface_t *network);
gmp_gmdu_t *make_gmf_register_information(gmp_gmf_t *gmf, cp_device_info_t *pi);
gmp_gmdu_t *make_gmf_life_heart_information(gmp_gmf_t *gmf, cp_device_info_t *pi);
gmp_gmdu_t *make_gmf_player_information(gmp_gmf_t *gmf, cp_device_info_t *pi, cp_center_addr_t *center_addr);
gmp_gmdu_t *make_gmf_return(gmp_gmf_t *gmf, cp_return_info_t *ret, cp_char_t *buf, cp_int32_t len);
gmp_gmdu_t *make_gmf_sync_information(gmp_gmf_t *gmf, cp_device_info_t *pi);
gmp_gmdu_t *make_gmf_register(gmp_gmf_t *gmf, cp_device_info_t *player_info, cp_char_t *error_buf, cp_int32_t len);
gmp_gmdu_t *make_gmf_life_heart(gmp_gmf_t *gmf, cp_device_info_t *player_info, cp_char_t *error_buf, cp_int32_t len);
gmp_gmdu_t *make_gmf_log_info(gmp_gmf_t *gmf, cp_log_info_t *log_info, cp_char_t *error_buf, cp_int32_t len);
gmp_gmdu_t *make_gmf_exceptions(gmp_gmf_t *gmf, cp_device_info_t *player_info, cp_exception_info_t *ex_info, 
	cp_char_t *error_buf, cp_int32_t len);
gmp_gmdu_t *make_gmf_exception(gmp_gmf_t *gmf, cp_exception_info_t *exp_info, cp_char_t *error_buf, cp_int32_t len);

gmp_gmdu_t *make_gmf_get_dev_info_return(gmp_gmf_t *gmf, cp_device_info_t *player_info, cp_char_t *error_buf, cp_int32_t len);
gmp_gmdu_t *make_gmf_get_log_info_return(gmp_gmf_t *gmf, cp_device_info_t *player_info, cp_log_info_t *log_info, 
	cp_char_t *error_buf, cp_int32_t len);
gmp_gmdu_t *make_gmf_offline_passwd_return(gmp_gmf_t *gmf, cp_device_info_t *player_info, cp_return_info_t *return_info, 
	cp_char_t *error_buf, cp_int32_t len);
gmp_gmdu_t *make_gmf_offline_information_return(gmp_gmf_t *gmf, cp_device_info_t *player_info, cp_return_info_t *return_info, 
	cp_center_addr_t *center_addr, cp_char_t *error_buf, cp_int32_t len);

gmp_gmdu_t *make_gmf_media_info(gmp_gmf_t *gmf, cp_media_info_t *media_info, cp_char_t *error_buf, cp_int32_t len);
gmp_gmdu_t *make_gmf_channel_info(gmp_gmf_t *gmf, cp_channel_info_t *channel_info, cp_char_t *error_buf, cp_int32_t len);

cp_bool_t parse_gmf_return(gmp_gmf_t *gmf, cp_return_info_t *ret, cp_char_t *buf, cp_int32_t len);
cp_bool_t parse_gmf_host(gmp_gmf_t *gmf, cp_host_t *host, cp_char_t *buf, cp_int32_t len);
cp_bool_t parse_gmf_host_network(gmp_gmf_t *gmf, cp_host_t *host, cp_interface_t *network, cp_char_t *buf, cp_int32_t len);
cp_bool_t parse_gmf_device_host(gmp_gmf_t *gmf, cp_host_t *host, cp_char_t *buf, cp_int32_t len);
cp_bool_t parse_gmf_interfaces(gmp_gmf_t *gmf, cp_interface_t *network, cp_char_t *buf, cp_int32_t len);
cp_bool_t parse_gmf_resolution_size(gmp_gmf_t *gmf, cp_uint32_t *resolution_width, cp_uint32_t *resolution_height, cp_char_t *buf, 
	cp_int32_t len);
cp_bool_t parse_gmf_back_size(gmp_gmf_t *gmf, cp_uint32_t *width, cp_uint32_t *height, cp_char_t *buf, cp_int32_t len);

/************************************************************************/
/* 获取播放媒体相关信息(注册返回指令)                                   */
/************************************************************************/
cp_bool_t get_gmf_play_information(gmp_gmf_t *gmf, list_node **media_channel_info_list, cp_char_t *buf, cp_int32_t len);

/************************************************************************/
/*获取软件更新信息(注册返回）											*/
/************************************************************************/
cp_bool_t get_gmf_device_update_info(gmp_gmf_t *gmf, cp_update_info_t *update_info, cp_char_t *buf, cp_int32_t len);

/************************************************************************/
/*获取设备信息链表(注册返回)                                            */
/************************************************************************/
cp_bool_t get_gmf_devices_info(gmp_gmf_t *gmf, list_node **dev_info_list, cp_char_t *buf, cp_int32_t len);
cp_bool_t get_gmf_devices_info_array(gmp_gmf_t *gmf, cp_array_t *dev_info_array, cp_char_t *buf, cp_int32_t len);
cp_int32_t get_gmf_devices_info_size(gmp_gmf_t *gmf, cp_char_t *buf, cp_int32_t len);
cp_bool_t get_gmf_child_device_info(gmp_gmf_t *gmf, cp_device_info_t *dev_info, cp_char_t *buf, cp_int32_t len);
cp_bool_t get_gmf_host_device_info(gmp_gmf_t *gmf, cp_device_info_t *dev_info, cp_char_t *buf, cp_int32_t len);
cp_bool_t get_host_id_detail(cp_host_t *host, cp_char_t *buf, cp_int32_t len);

/************************************************************************/
/*解析同步信息															*/
/************************************************************************/
cp_bool_t get_gmf_sync_info(gmp_gmf_t *gmf, cp_sync_info_t *sync_info, cp_char_t *buf, cp_int32_t len);
cp_bool_t get_gmf_child_sync_info(gmp_gmf_t *gmf, cp_sync_info_t *sync_info, cp_char_t *buf, cp_int32_t len);

/************************************************************************/
/*获取设备信息(设置设备)                                                */
/************************************************************************/
cp_bool_t get_gmf_device_info(gmp_gmf_t *gmf, cp_device_info_t *dev_info, cp_char_t *buf, cp_int32_t len);

cp_bool_t get_gmf_hardware_info(gmp_gmf_t *gmf, cp_host_t *host, cp_hardware_info_t *hardware, cp_char_t *buf, cp_int32_t len);
cp_bool_t get_gmf_multicast_info(gmp_gmf_t *gmf, cp_multicast_addr_t *multicast_addr, cp_char_t *buf, cp_int32_t len);
cp_bool_t get_gmf_play_address_info(gmp_gmf_t *gmf, cp_play_addr_t *play_addr, cp_char_t *buf, cp_int32_t len);
cp_bool_t get_gmf_stream_description(gmp_gmf_t *gmf, cp_stream_description_t *stream_description, cp_char_t *buf, cp_int32_t len);
cp_bool_t get_gmf_device_groups_info(gmp_gmf_t *gmf, cp_host_t *host, cp_char_t *buf, cp_int32_t len);
cp_bool_t get_gmf_chunk_size(gmp_gmf_t *gmf, cp_int32_t *chunk_size, cp_char_t *buf, cp_int32_t len);

/************************************************************************/
/*获取设备信息(离线设置设备信息)										*/
/************************************************************************/
cp_bool_t get_gmf_player_info(gmp_gmf_t *gmf, cp_device_info_t *dev_info, cp_center_addr_t *center_addr, cp_char_t *buf, cp_int32_t len);
cp_bool_t get_gmf_checkcolor_info(gmp_gmf_t *gmf, cp_checkcolor_info_t *check_color, cp_char_t *buf, cp_int32_t len);
cp_bool_t get_gmf_center_info(gmp_gmf_t *gmf, cp_center_addr_t *center_addr, cp_char_t *buf, cp_int32_t len);
cp_bool_t get_gmf_serials_info(gmp_gmf_t *gmf, cp_serial_t *serial_info, cp_char_t *buf, cp_int32_t len);
cp_bool_t get_gmf_serial_info(gmp_gmf_t *gmf, cp_serial_t *serial_info, cp_char_t *buf, cp_int32_t len);
cp_bool_t get_gmf_networks_info(gmp_gmf_t *gmf, cp_interface_t *network_info, cp_char_t *buf, cp_int32_t len);
cp_bool_t get_gmf_network_info(gmp_gmf_t *gmf, cp_interface_t *network_info, cp_char_t *buf, cp_int32_t len);

/************************************************************************/
/* 解析背景字幕信息														*/
/************************************************************************/
cp_bool_t get_gmf_background_player_info(gmp_gmf_t *gmf, cp_player_background_info_t *player_background_info, 
	cp_char_t *buf, cp_int32_t len);
cp_bool_t get_gmf_background_medias_info(gmp_gmf_t *gmf, cp_background_media_info_t *background_meidas_info, 
	cp_char_t *buf, cp_int32_t len);
cp_bool_t get_gmf_background_media_info(gmp_gmf_t *gmf, cp_background_media_info_t *background_meidas_info, 
	cp_char_t *buf, cp_int32_t len);
cp_bool_t get_gmf_background_information(gmp_gmf_t *gmf, cp_player_background_info_t *player_background_info, 
	cp_char_t *buf, cp_int32_t len);

/************************************************************************/
/*字幕背景刷新指令                                                      */
/************************************************************************/
cp_bool_t get_gmf_background_player_reflesh_info(gmp_gmf_t *gmf, cp_player_background_info_t *player_background_info, cp_char_t *buf, cp_int32_t len);
cp_bool_t get_gmf_background_reflesh_info(gmp_gmf_t *gmf, cp_background_reflesh_info_t *reflesh_info, cp_char_t *buf, cp_int32_t len);
cp_bool_t get_gmf_background_child_reflesh_info(gmp_gmf_t *gmf, cp_background_reflesh_info_t *reflesh_media_info, cp_char_t *buf, cp_int32_t len);

/************************************************************************/
/* 获取播放媒体通道相关信息                                             */
/************************************************************************/
cp_int32_t get_gmf_play_meida_channel_size(gmp_gmf_t *gmf, cp_char_t *buf, cp_int32_t len);
cp_bool_t get_gmf_play_media_channel_array(gmp_gmf_t *gmf, cp_array_t *mci_array, cp_char_t *buf, cp_int32_t len);
cp_bool_t get_gmf_play_media_channel_info(gmp_gmf_t *gmf, list_node **media_channel_info_list, cp_char_t *buf, cp_int32_t len);
cp_bool_t get_gmf_play_child_media_channel_info(gmp_gmf_t *gmf, cp_media_channel_info_t *media_channel_info, cp_char_t *buf, cp_int32_t len);
cp_bool_t get_gmf_media_info(gmp_gmf_t *gmf, cp_media_info_t *media_info, cp_char_t *buf, cp_int32_t len);
cp_bool_t get_gmf_video_source(gmp_gmf_t *gmf, cp_media_info_t *media_info, cp_char_t *buf, cp_int32_t len);
cp_bool_t get_gmf_audio_source(gmp_gmf_t *gmf, cp_media_info_t *media_info, cp_char_t *buf, cp_int32_t len);
cp_bool_t get_gmf_channel_info(gmp_gmf_t *gmf, cp_channel_info_t *channel_info, cp_char_t *buf, cp_int32_t len);
cp_bool_t get_gmf_play_information_info(gmp_gmf_t *gmf, list_node **group_list, cp_play_channel_info_t *pc_info,
	cp_char_t *buf, cp_int32_t len);
cp_bool_t get_gmf_play_groups_info(gmp_gmf_t *gmf, list_node **group_list, cp_char_t *buf, cp_int32_t len);
cp_bool_t get_gmf_play_group_info(gmp_gmf_t *gmf, cp_media_group_info_t *group_info, cp_char_t *buf, cp_int32_t len);
cp_bool_t get_gmf_play_channel_stop_info(gmp_gmf_t *gmf, list_node **media_channel_stop_list, cp_char_t *buf, cp_int32_t len);
cp_bool_t get_gmf_play_child_channel_stop_info(gmp_gmf_t *gmf, cp_channel_stop_info_t *media_channel_stop_info, cp_char_t *buf, cp_int32_t len);
cp_bool_t get_gmf_play_cmd_info(gmp_gmf_t *gmf, cp_play_channel_info_t *pc_info, cp_char_t *buf, cp_int32_t len);

/************************************************************************/
/*解析日志信息                                                          */
/************************************************************************/
cp_bool_t get_gmf_log_info_by_id(gmp_gmf_t *gmf, const cp_char_t *id, cp_log_info_t *log_info, cp_char_t *buf, cp_int32_t len);
cp_bool_t get_gmf_log_info(gmp_gmf_t *gmf, cp_log_info_t *log_info, cp_char_t *buf, cp_int32_t len);

/************************************************************************/
/*解析软件更新信息--（软件更新指令）                                    */
/************************************************************************/
cp_bool_t get_gmf_update_info_by_id(gmp_gmf_t *gmf, const cp_char_t *id, cp_update_info_t *update_info, cp_char_t *buf,
	cp_int32_t len);
cp_bool_t get_gmf_chunk_size_by_id(gmp_gmf_t *gmf, const cp_char_t *id, cp_int32_t *chunk_size, cp_char_t *buf, cp_int32_t len);
cp_bool_t get_gmf_devices_id_exist(gmp_gmf_t *gmf, const cp_char_t *id, cp_char_t *buf, cp_int32_t len);


//解析通道信息---未使用接口
cp_bool_t get_gmf_channels(gmp_gmf_t *gmf, list_node *channel_info_list, cp_char_t *buf, cp_int32_t len);
cp_bool_t get_gmf_channel(gmp_gmf_t *gmf, cp_channel_info_t *channel_info, cp_char_t *buf, cp_int32_t len);

cp_bool_t get_gmf_devices_focus_list(gmp_gmf_t *gmf, list_node **device_focus_list, cp_char_t *buf, cp_int32_t len);
cp_bool_t get_gmf_offline_info_list(gmp_gmf_t *gmf, list_node **offline_info_list, cp_char_t *buf, cp_int32_t len);

cp_bool_t get_gmf_element(gmp_gmf_t *gmf, cp_void_t *dest, cp_int32_t dest_len, gmp_gmdt gmdt_type, cp_char_t *name, cp_char_t *buf, 
	cp_int32_t len);
cp_bool_t get_gmf_element_key(gmp_gmf_t *gmf, gmp_gmdu_t *gmdu, cp_void_t *dest, cp_int32_t dest_len, gmp_gmdt gmdt_type, cp_char_t *buf, 
	cp_int32_t len);
cp_bool_t get_gmf_element_str2char(gmp_gmf_t *gmf, cp_char_t *dest_buf, cp_int32_t dest_buf_len, gmp_gmdt gmdt_type, cp_char_t *name, 
	cp_char_t *buf, cp_int32_t len);

/************************************************************************/
/* gmf指令log                                                           */
/************************************************************************/
cp_char_t *print_gmph_emh(cp_void_t *emh, cp_char_t *buf, cp_int32_t len, cp_bool_t is_show_all);
cp_char_t *print_gmf_version(gmp_gmf_t *gmf, cp_char_t *buf, cp_int32_t len);
cp_char_t *print_gmf_reason(gmp_gmf_t *gmf, gmp_gmdu_t *gmdu, cp_char_t *buf, cp_int32_t len);


#endif