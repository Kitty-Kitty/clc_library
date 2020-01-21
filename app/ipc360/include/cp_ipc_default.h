/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-09-18

Description:

**************************************************************************/

#ifndef _CP_IPC_DEFINED_INCLUDE_H_
#define _CP_IPC_DEFINED_INCLUDE_H_



#define		CP_IPC_MAX_CENTER_SERVER_NUMBER				2					/*��ʾ���֧����������*/
#define		CP_IPC_MAX_CLIENT_SERVER_NUMBER				2					/*��ʾ���֧�ֻ��Է���������*/
#define		CP_IPC_MAX_IPC_SERVER_NUMBER				2					/*��ʾ���֧�ֱ�������������*/
#define		CP_IPC_MAX_MEDIA_SERVER_NUMBER				2					/*��ʾ���֧��ý�����������*/
/*��ʾ�����������豸����*/
#define		CP_IPC_MAX_DEVICE_NUMBER					\
		(CP_IPC_MAX_CENTER_SERVER_NUMBER +				\
			CP_IPC_MAX_CLIENT_SERVER_NUMBER +			\
			CP_IPC_MAX_IPC_SERVER_NUMBER +				\
			CP_IPC_MAX_MEDIA_SERVER_NUMBER				\
		)



#define		CP_IPC_MAX_HEARTBEAT_LOST_TIMES				3					/*��ʾ����������ʧ����*/

#define		CP_IPC_HEARTBEAT_DEFAULT_BUFFER_LENGTH		2					/*��ʾ�豸��������Ϣ�����ַ���*/

#define		CP_IPC_HEARTBEAT_DEFAULT_DATA_LENGTH		2					/*��ʾ�豸Ĭ�ϵ����������С*/

#endif