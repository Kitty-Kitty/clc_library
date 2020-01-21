/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-09-18

Description:

**************************************************************************/

#ifndef _CP_PLAYER_DEFINED_INCLUDE_H_
#define _CP_PLAYER_DEFINED_INCLUDE_H_



#define		CP_PLAYER_MAX_CENTER_SERVER_NUMBER				8					/*��ʾ���֧����������*/
#define		CP_PLAYER_MAX_CLIENT_SERVER_NUMBER				16					/*��ʾ���֧�ֻ��Է���������*/
#define		CP_PLAYER_MAX_PLAYER_SERVER_NUMBER				8					/*��ʾ���֧�ֱ�������������*/
#define		CP_PLAYER_MAX_MEDIA_SERVER_NUMBER				128					/*��ʾ���֧��ý�����������*/
/*��ʾ�����������豸����*/
#define		CP_PLAYER_MAX_DEVICE_NUMBER						\
		(CP_PLAYER_MAX_CENTER_SERVER_NUMBER +				\
			CP_PLAYER_MAX_CLIENT_SERVER_NUMBER +			\
			CP_PLAYER_MAX_PLAYER_SERVER_NUMBER +			\
			CP_PLAYER_MAX_MEDIA_SERVER_NUMBER				\
		)



#define		CP_PLAYER_MAX_HEARTBEAT_LOST_TIMES				3					/*��ʾ����������ʧ����*/

#define		CP_PLAYER_HEARTBEAT_DEFAULT_BUFFER_LENGTH		256					/*��ʾ�豸��������Ϣ�����ַ���*/

#define		CP_PLAYER_HEARTBEAT_DEFAULT_DATA_LENGTH			1024				/*��ʾ�豸Ĭ�ϵ����������С*/

#endif