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
* ��Ȩ����: fz & novigo
*
* ��������: select_device_info_index
*
* ����˵��: �ж��豸��Ϣ�Ƿ��Ѿ�����
*
* ��    ��: cp_player_t * player							[in]��Ҫ�����player��Ϣ
* ��    ��: cp_device_info_t ** di_ary					[in]��Ҫ���������豸�б���Ϣ
* ��    ��: cp_int32_t di_ary_size						[in]��Ҫ���������豸�б���
* ��    ��: cp_int32_t * ret_index						[out]���������б������λ��
* ��    ��: cp_char_t * id								[in]��Ҫ���ҵ��豸id
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-09-18 18:27:51
******************************************************************************************************/
cp_int32_t select_device_info_index(cp_player_t *player, cp_device_info_t **di_ary,
	cp_int32_t di_ary_size, cp_int32_t *ret_index, cp_char_t *id);

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: select_index_device_info
*
* ����˵��: ��ѯ�豸��Ϣ
*
* ��    ��: cp_player_t * player						[in]����˵��
* ��    ��: cp_device_info_t * * di_ary				[in]����˵��
* ��    ��: cp_int32_t di_ary_size					[in]����˵��
* ��    ��: cp_int32_t index							[in]����˵��
*
* �� �� ֵ: cp_device_info_t *
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-11-19 13:41:40
******************************************************************************************************/
cp_device_info_t *select_index_device_info(cp_player_t *player, cp_device_info_t **di_ary,
	cp_int32_t di_ary_size, cp_int32_t index);

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: select_device_heartbeat
*
* ����˵��: ����һ���豸������Ϣ
*
* ��    ��: cp_player_t * player						[in]����˵��
* ��    ��: cp_int32_t * ret_index						[in]��ʾ���ص��豸����������Ϣ
* ��    ��: cp_char_t * id						[in]����˵��
* ��    ��: cp_int32_t type						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-09-19 10:48:53
******************************************************************************************************/
cp_int32_t select_device_heartbeat(cp_player_t *player, cp_int32_t *ret_index, cp_char_t *id, cp_int32_t type);

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: select_a_used_interface
*
* ����˵��: ���豸��������Ϣ�в���һ�����õ�������Ϣ
*
* ��    ��: cp_player_t * player						[in]����˵��
*
* �� �� ֵ: cp_interface_t *
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-09-19 11:07:52
******************************************************************************************************/
cp_interface_t *select_a_used_interface(cp_player_t *player);

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: insert_new_device_info
*
* ����˵��: ����һ���µ��豸��Ϣ
*
* ��    ��: cp_player_t * player							[in]��Ҫ�����player��Ϣ
* ��    ��: cp_device_info_t ** di_ary					[in]��Ҫ���������豸�б���Ϣ
* ��    ��: cp_int32_t di_ary_size						[in]��Ҫ���������豸�б���
* ��    ��: cp_device_info_t *src_di						[in]��Ҫ�����Դ�豸��Ϣ
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-09-18 18:42:02
******************************************************************************************************/
cp_int32_t insert_new_device_info(cp_player_t *player, cp_device_info_t **di_ary,
	cp_int32_t di_ary_size, cp_device_info_t *src_di);

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: insert_new_device_heartbeat
*
* ����˵��: ���һ���豸������Ϣ
*
* ��    ��: cp_player_t * player						[in]����˵��
* ��    ��: cp_device_info_t * di						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-09-19 11:11:49
******************************************************************************************************/
cp_int32_t insert_new_device_heartbeat(cp_player_t *player, cp_device_info_t *di);

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: update_a_device_heartbeat
*
* ����˵��: ����������Ϣ
*
* ��    ��: cp_player_t * player							[in]����˵��
* ��    ��: cp_device_info_t * di						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-09-19 10:45:04
******************************************************************************************************/
cp_int32_t update_a_device_heartbeat(cp_player_t *player, cp_device_info_t *di);

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: create_device_heartbeat_info
*
* ����˵��: ����һ��������Ϣ
*
* ��    ��: cp_heartbeat_manager_t * hm						[in]����˵��
* ��    ��: cp_device_info_t * di						[in]����˵��
*
* �� �� ֵ: cp_device_heartbeat_t*
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-11-04 14:02:52
******************************************************************************************************/
cp_device_heartbeat_t* create_device_heartbeat_info(cp_heartbeat_manager_t *hm, cp_device_info_t *di);

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: update_position_device_info
*
* ����˵��: �ڸ���ָ��λ�õ��豸��Ϣ
*
* ��    ��: cp_player_t * player							[in]��Ҫ�����player��Ϣ
* ��    ��: cp_device_info_t ** di_ary					[in]��Ҫ���������豸�б���Ϣ
* ��    ��: cp_int32_t di_ary_size						[in]��Ҫ���������豸�б���
* ��    ��: cp_int32_t pos							[in]��Ҫ�����µ��豸�б�λ��
* ��    ��: cp_device_info_t *src_di						[in]��Ҫ���µ�Դ�豸��Ϣ
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-09-18 18:39:42
******************************************************************************************************/
cp_int32_t update_position_device_info(cp_player_t *player, cp_device_info_t **di_ary,
	cp_int32_t di_ary_size, cp_int32_t pos, cp_device_info_t *src_di);

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: update_dest_device_info
*
* ����˵��: ����һ���豸��Ϣ
*
* ��    ��: cp_player_t * player						[in]����˵��
* ��    ��: cp_device_info_t * * di_ary						[in]����˵��
* ��    ��: cp_int32_t di_ary_size						[in]����˵��
* ��    ��: cp_device_info_t * src_di						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-09-18 18:54:00
******************************************************************************************************/
cp_int32_t update_dest_device_info(cp_player_t *player, cp_device_info_t **di_ary,
	cp_int32_t di_ary_size, cp_device_info_t *src_di);

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: update_media_server_other_info
*
* ����˵��: ý�������������Ϣ
*
* ��    ��: cp_player_t * player						[in]����˵��
* ��    ��: cp_device_info_t * di						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-11-19 13:56:47
******************************************************************************************************/
cp_int32_t update_media_server_other_info(cp_player_t *player, cp_device_info_t *di);

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: update_device_info
*
* ����˵��: ����player�е��豸��Ϣ
*
* ��    ��: cp_player_t * player									[in]��Ҫ�����µ�app��Ϣ
* ��    ��: cp_array_t * device_info_array						[in]��ǰ��ȡ���豸�б�
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-09-18 17:05:05
******************************************************************************************************/
cp_int32_t update_device_info(cp_player_t *player, cp_array_t *device_info_array);

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: update_a_device_info
*
* ����˵��: ����һ���豸��Ϣ
*
* ��    ��: cp_player_t * player						[in]����˵��
* ��    ��: cp_device_info_t * di						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-11-07 14:33:27
******************************************************************************************************/
cp_int32_t update_a_device_info(cp_player_t *player, cp_device_info_t *di);

cp_int32_t update_center_server_info(cp_player_t *player, cp_device_info_t *di);
cp_int32_t update_media_server_info(cp_player_t *player, cp_device_info_t *di);
cp_int32_t update_access_server_info(cp_player_t *player, cp_device_info_t *di);
cp_int32_t update_player_background_server_info(cp_player_t *player, cp_device_info_t *di);
cp_int32_t update_client_background_server_info(cp_player_t *player, cp_device_info_t *di);
cp_int32_t update_other_player_info(cp_player_t *player, cp_device_info_t *di);


/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: remove_a_device_heartbeat
*
* ����˵��: ɾ��һ���Ѿ����ڵ��豸������Ϣ
*
* ��    ��: cp_player_t * player						[in]����˵��
* ��    ��: cp_device_info_t * di						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-09-19 10:21:25
******************************************************************************************************/
cp_int32_t remove_a_device_heartbeat(cp_player_t *player, cp_device_info_t *di);

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: remove_a_device_info
*
* ����˵��: ɾ��һ���豸��Ϣ
*
* ��    ��: cp_player_t * player							[in]��Ҫ��ɾ��������app��Ϣ
* ��    ��: cp_device_info_t * * di_ary					[in]�����������������б�
* ��    ��: cp_int32_t di_ary_size						[in]�������������б���
* ��    ��: cp_device_info_t * di						[in]��Ҫ��ɾ������Ϣ
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-09-19 10:11:21
******************************************************************************************************/
cp_int32_t remove_a_device_info(cp_player_t *player, cp_device_info_t **di_ary,
	cp_int32_t di_ary_size, cp_device_info_t *di);

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: remove_device_info
*
* ����˵��: ɾ��һ���豸��Ϣ
*
* ��    ��: cp_player_t * player						[in]����˵��
* ��    ��: cp_char_t * id						[in]����˵��
* ��    ��: cp_int32_t type						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-09-18 17:45:19
******************************************************************************************************/
cp_int32_t remove_device_info(cp_player_t *player, cp_char_t *id, cp_int32_t type);

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: remove_all_device_info
*
* ����˵��: ɾ�������豸��Ϣ
*
* ��    ��: cp_player_t * player						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-06-22 16:01:46
******************************************************************************************************/
cp_int32_t remove_all_device_info(cp_player_t *player);

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: remove_media_server_other_info
*
* ����˵��: ɾ��ý���������Ϣ
*
* ��    ��: cp_player_t * player						[in]����˵��
* ��    ��: cp_device_info_t * di						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-11-19 16:48:20
******************************************************************************************************/
cp_int32_t remove_media_server_other_info(cp_player_t *player, cp_device_info_t *di);

cp_int32_t remove_center_server_info(cp_player_t *player, cp_char_t *id, cp_int32_t type);
cp_int32_t remove_media_server_info(cp_player_t *player, cp_char_t *id, cp_int32_t type);
cp_int32_t remove_access_server_info(cp_player_t *player, cp_char_t *id, cp_int32_t type);
cp_int32_t remove_player_background_server_info(cp_player_t *player, cp_char_t *id, cp_int32_t type);
cp_int32_t remove_client_background_server_info(cp_player_t *player, cp_char_t *id, cp_int32_t type);

cp_char_t* printf_device_info(cp_player_t *player, cp_device_info_t *di, cp_char_t *buf, cp_int32_t len);



#endif


