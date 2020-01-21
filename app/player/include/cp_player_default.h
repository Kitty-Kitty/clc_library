/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-09-18

Description:

**************************************************************************/

#ifndef _CP_PLAYER_DEFINED_INCLUDE_H_
#define _CP_PLAYER_DEFINED_INCLUDE_H_



#define		CP_PLAYER_MAX_CENTER_SERVER_NUMBER				8					/*表示最大支持中心数量*/
#define		CP_PLAYER_MAX_CLIENT_SERVER_NUMBER				16					/*表示最大支持回显服务器数量*/
#define		CP_PLAYER_MAX_PLAYER_SERVER_NUMBER				8					/*表示最大支持背景服务器数量*/
#define		CP_PLAYER_MAX_MEDIA_SERVER_NUMBER				128					/*表示最大支持媒体服务器数量*/
/*表示所有心跳的设备数量*/
#define		CP_PLAYER_MAX_DEVICE_NUMBER						\
		(CP_PLAYER_MAX_CENTER_SERVER_NUMBER +				\
			CP_PLAYER_MAX_CLIENT_SERVER_NUMBER +			\
			CP_PLAYER_MAX_PLAYER_SERVER_NUMBER +			\
			CP_PLAYER_MAX_MEDIA_SERVER_NUMBER				\
		)



#define		CP_PLAYER_MAX_HEARTBEAT_LOST_TIMES				3					/*表示最大的心跳丢失次数*/

#define		CP_PLAYER_HEARTBEAT_DEFAULT_BUFFER_LENGTH		256					/*表示设备的心跳信息描述字符串*/

#define		CP_PLAYER_HEARTBEAT_DEFAULT_DATA_LENGTH			1024				/*表示设备默认的心跳缓存大小*/

#endif