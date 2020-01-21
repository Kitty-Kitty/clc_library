/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_PLAYER_PROC_INCLUDE_H_
#define _CP_PLAYER_PROC_INCLUDE_H_


#include "cp_player_core.h"



cp_int32_t init_player_other(cp_player_t *player, cp_app_info_t *app_info);
cp_int32_t start_player_other(cp_player_t *player, cp_app_info_t *app_info);
cp_int32_t stop_player_other(cp_player_t *player, cp_app_info_t *app_info);


/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: select_device_info_index
*
* 函数说明: 判断设备信息是否已经存在
*
* 参    数: cp_player_t * player							[in]需要处理的player信息
* 参    数: cp_device_info_t ** di_ary					[in]需要被遍历的设备列表信息
* 参    数: cp_int32_t di_ary_size						[in]需要被遍历的设备列表长度
* 参    数: cp_int32_t * ret_index						[out]返回所有列表的索引位置
* 参    数: cp_char_t * id								[in]需要查找的设备id
*
* 返 回 值: cp_int32_t
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-09-18 18:27:51
******************************************************************************************************/
cp_int32_t select_device_info_index(cp_player_t *player, cp_device_info_t **di_ary,
	cp_int32_t di_ary_size, cp_int32_t *ret_index, cp_char_t *id);

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: select_index_device_info
*
* 函数说明: 查询设备信息
*
* 参    数: cp_player_t * player						[in]参数说明
* 参    数: cp_device_info_t * * di_ary				[in]参数说明
* 参    数: cp_int32_t di_ary_size					[in]参数说明
* 参    数: cp_int32_t index							[in]参数说明
*
* 返 回 值: cp_device_info_t *
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-11-19 13:41:40
******************************************************************************************************/
cp_device_info_t *select_index_device_info(cp_player_t *player, cp_device_info_t **di_ary,
	cp_int32_t di_ary_size, cp_int32_t index);

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: select_device_heartbeat
*
* 函数说明: 查找一个设备心跳信息
*
* 参    数: cp_player_t * player						[in]参数说明
* 参    数: cp_int32_t * ret_index						[in]表示返回的设备心跳索引信息
* 参    数: cp_char_t * id						[in]参数说明
* 参    数: cp_int32_t type						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-09-19 10:48:53
******************************************************************************************************/
cp_int32_t select_device_heartbeat(cp_player_t *player, cp_int32_t *ret_index, cp_char_t *id, cp_int32_t type);

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: select_a_used_interface
*
* 函数说明: 从设备的网卡信息中查找一个可用的网络信息
*
* 参    数: cp_player_t * player						[in]参数说明
*
* 返 回 值: cp_interface_t *
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-09-19 11:07:52
******************************************************************************************************/
cp_interface_t *select_a_used_interface(cp_player_t *player);

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: insert_new_device_info
*
* 函数说明: 插入一个新的设备信息
*
* 参    数: cp_player_t * player							[in]需要处理的player信息
* 参    数: cp_device_info_t ** di_ary					[in]需要被遍历的设备列表信息
* 参    数: cp_int32_t di_ary_size						[in]需要被遍历的设备列表长度
* 参    数: cp_device_info_t *src_di						[in]需要插入的源设备信息
*
* 返 回 值: cp_int32_t
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-09-18 18:42:02
******************************************************************************************************/
cp_int32_t insert_new_device_info(cp_player_t *player, cp_device_info_t **di_ary,
	cp_int32_t di_ary_size, cp_device_info_t *src_di);

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: insert_new_device_heartbeat
*
* 函数说明: 添加一个设备心跳信息
*
* 参    数: cp_player_t * player						[in]参数说明
* 参    数: cp_device_info_t * di						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-09-19 11:11:49
******************************************************************************************************/
cp_int32_t insert_new_device_heartbeat(cp_player_t *player, cp_device_info_t *di);

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: update_a_device_heartbeat
*
* 函数说明: 更新心跳信息
*
* 参    数: cp_player_t * player							[in]参数说明
* 参    数: cp_device_info_t * di						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-09-19 10:45:04
******************************************************************************************************/
cp_int32_t update_a_device_heartbeat(cp_player_t *player, cp_device_info_t *di);

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: create_device_heartbeat_info
*
* 函数说明: 创建一个心跳信息
*
* 参    数: cp_heartbeat_manager_t * hm						[in]参数说明
* 参    数: cp_device_info_t * di						[in]参数说明
*
* 返 回 值: cp_device_heartbeat_t*
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-11-04 14:02:52
******************************************************************************************************/
cp_device_heartbeat_t* create_device_heartbeat_info(cp_heartbeat_manager_t *hm, cp_device_info_t *di);

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: update_position_device_info
*
* 函数说明: 在更新指定位置的设备信息
*
* 参    数: cp_player_t * player							[in]需要处理的player信息
* 参    数: cp_device_info_t ** di_ary					[in]需要被遍历的设备列表信息
* 参    数: cp_int32_t di_ary_size						[in]需要被遍历的设备列表长度
* 参    数: cp_int32_t pos							[in]需要被更新的设备列表位置
* 参    数: cp_device_info_t *src_di						[in]需要更新的源设备信息
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-09-18 18:39:42
******************************************************************************************************/
cp_int32_t update_position_device_info(cp_player_t *player, cp_device_info_t **di_ary,
	cp_int32_t di_ary_size, cp_int32_t pos, cp_device_info_t *src_di);

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: update_dest_device_info
*
* 函数说明: 更新一个设备信息
*
* 参    数: cp_player_t * player						[in]参数说明
* 参    数: cp_device_info_t * * di_ary						[in]参数说明
* 参    数: cp_int32_t di_ary_size						[in]参数说明
* 参    数: cp_device_info_t * src_di						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-09-18 18:54:00
******************************************************************************************************/
cp_int32_t update_dest_device_info(cp_player_t *player, cp_device_info_t **di_ary,
	cp_int32_t di_ary_size, cp_device_info_t *src_di);

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: update_media_server_other_info
*
* 函数说明: 媒体服务器其他信息
*
* 参    数: cp_player_t * player						[in]参数说明
* 参    数: cp_device_info_t * di						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-11-19 13:56:47
******************************************************************************************************/
cp_int32_t update_media_server_other_info(cp_player_t *player, cp_device_info_t *di);

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: update_device_info
*
* 函数说明: 更新player中的设备信息
*
* 参    数: cp_player_t * player									[in]需要被更新的app信息
* 参    数: cp_array_t * device_info_array						[in]当前获取的设备列表
*
* 返 回 值: cp_int32_t
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-09-18 17:05:05
******************************************************************************************************/
cp_int32_t update_device_info(cp_player_t *player, cp_array_t *device_info_array);

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: update_a_device_info
*
* 函数说明: 更新一个设备信息
*
* 参    数: cp_player_t * player						[in]参数说明
* 参    数: cp_device_info_t * di						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-11-07 14:33:27
******************************************************************************************************/
cp_int32_t update_a_device_info(cp_player_t *player, cp_device_info_t *di);

cp_int32_t update_center_server_info(cp_player_t *player, cp_device_info_t *di);
cp_int32_t update_media_server_info(cp_player_t *player, cp_device_info_t *di);
cp_int32_t update_access_server_info(cp_player_t *player, cp_device_info_t *di);
cp_int32_t update_player_background_server_info(cp_player_t *player, cp_device_info_t *di);
cp_int32_t update_client_background_server_info(cp_player_t *player, cp_device_info_t *di);
cp_int32_t update_other_player_info(cp_player_t *player, cp_device_info_t *di);


/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: remove_a_device_heartbeat
*
* 函数说明: 删除一个已经存在的设备心跳信息
*
* 参    数: cp_player_t * player						[in]参数说明
* 参    数: cp_device_info_t * di						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-09-19 10:21:25
******************************************************************************************************/
cp_int32_t remove_a_device_heartbeat(cp_player_t *player, cp_device_info_t *di);

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: remove_a_device_info
*
* 函数说明: 删除一个设备信息
*
* 参    数: cp_player_t * player							[in]需要被删除操作的app信息
* 参    数: cp_device_info_t * * di_ary					[in]被操作的数据数组列表
* 参    数: cp_int32_t di_ary_size						[in]被操作的数组列表长度
* 参    数: cp_device_info_t * di						[in]需要被删除的信息
*
* 返 回 值: cp_int32_t
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-09-19 10:11:21
******************************************************************************************************/
cp_int32_t remove_a_device_info(cp_player_t *player, cp_device_info_t **di_ary,
	cp_int32_t di_ary_size, cp_device_info_t *di);

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: remove_device_info
*
* 函数说明: 删除一个设备信息
*
* 参    数: cp_player_t * player						[in]参数说明
* 参    数: cp_char_t * id						[in]参数说明
* 参    数: cp_int32_t type						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-09-18 17:45:19
******************************************************************************************************/
cp_int32_t remove_device_info(cp_player_t *player, cp_char_t *id, cp_int32_t type);

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: remove_all_device_info
*
* 函数说明: 删除所有设备信息
*
* 参    数: cp_player_t * player						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-06-22 16:01:46
******************************************************************************************************/
cp_int32_t remove_all_device_info(cp_player_t *player);

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: remove_media_server_other_info
*
* 函数说明: 删除媒体服务器信息
*
* 参    数: cp_player_t * player						[in]参数说明
* 参    数: cp_device_info_t * di						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-11-19 16:48:20
******************************************************************************************************/
cp_int32_t remove_media_server_other_info(cp_player_t *player, cp_device_info_t *di);

cp_int32_t remove_center_server_info(cp_player_t *player, cp_char_t *id, cp_int32_t type);
cp_int32_t remove_media_server_info(cp_player_t *player, cp_char_t *id, cp_int32_t type);
cp_int32_t remove_access_server_info(cp_player_t *player, cp_char_t *id, cp_int32_t type);
cp_int32_t remove_player_background_server_info(cp_player_t *player, cp_char_t *id, cp_int32_t type);
cp_int32_t remove_client_background_server_info(cp_player_t *player, cp_char_t *id, cp_int32_t type);

cp_char_t* printf_device_info(cp_player_t *player, cp_device_info_t *di, cp_char_t *buf, cp_int32_t len);



#endif


