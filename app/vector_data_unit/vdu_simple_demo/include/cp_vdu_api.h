/*******************************************************************************
*
*Copyright:novigo
*
*File name: cp_vdu_api.h
*
*Author:fangzhenmu@novigo.com.cn
*
*Version: 1.0
*
*Date:2018/02/05
*
*Description: create (cp_vdu_api.h)
*
*Others:
*
*History:
*******************************************************************************/

#ifndef _CP_VDU_API_H_
#define _CP_VDU_API_H_



#include "cp_vdu.h"
#include "cp_vdu_status.h"



#ifdef __cplusplus
extern "C" {
#endif

	//cp_vdu������
	///////////////////////////////////////////////////////////////////////////////

	/*******************************************************************************
	* ��Ȩ����: fz & novigo
	*
	* ��������: cp_vdu_create
	*
	* ����ȫ��: cp_vdu_create
	*
	* ��������: public
	*
	* ����˵��: ����һ��cp_vdu_t����
	*
	*
	* �� �� ֵ: cp_vdu_t *
	*         ��NULL: �ɹ�
	*         NULL  : ʧ��
	*
	* ��    ע:��
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@novigo.com.cn
	* �������ڣ�2018-2-2 15:10:45
	********************************************************************************/
	cp_extern cp_vdu_t *cp_vdu_create();

	/*******************************************************************************
	* ��Ȩ����: fz & novigo
	*
	* ��������: cp_vdu_destroy
	*
	* ����ȫ��: cp_vdu_destroy
	*
	* ��������: public
	*
	* ����˵��: ����cp_vdu����
	*
	* ��    ��: cp_vdu_t       *vdu    [in]�������vdu����ָ��
	*
	* �� �� ֵ: int
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@novigo.com.cn
	* �������ڣ�2018-2-3 10:56:18
	********************************************************************************/
	cp_extern int cp_vdu_destroy(cp_vdu_t *vdu);

	/*******************************************************************************
	* ��Ȩ����: fz & novigo
	*
	* ��������: cp_vdu_get_version
	*
	* ����ȫ��: cp_vdu_get_version
	*
	* ��������: public
	*
	* ����˵��: ��ȡ�汾��Ϣ
	*
	* ��    ��: cp_vdu_t * vdu			[in]�������vdu����ָ��
	*
	* �� �� ֵ: cp_vdu_version_t
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@novigo.com.cn
	* �������ڣ�2018-2-5 16:53:47
	********************************************************************************/
	cp_vdu_version_t cp_vdu_get_version(cp_vdu_t *vdu);

	/*******************************************************************************
	* ��Ȩ����: fz & novigo
	*
	* ��������: cp_vdu_get_status
	*
	* ����ȫ��: cp_vdu_get_status
	*
	* ��������: public
	*
	* ����˵��: ��ʾ��ȡ��ǰ��״̬��
	*
	* ��    ��: cp_vdu_t * vdu						[in]����˵��
	*
	* �� �� ֵ: cp_vdu_status_e
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@novigo.com.cn
	* �������ڣ�2018-2-5 17:10:50
	********************************************************************************/
	cp_vdu_status_e cp_vdu_get_status(cp_vdu_t *vdu);

	/*******************************************************************************
	* ��Ȩ����: fz & novigo
	*
	* ��������: cp_vdu_set_coordinate
	*
	* ����ȫ��: cp_vdu_set_coordinate
	*
	* ��������: public
	*
	* ����˵��: ����������Ϣ,������Ϊģ��������ϵ�е�ԭ�����ꡣ
	*
	* ��    ��: cp_vdu_t				*vdu			[in]�������vdu����ָ��
	* ��    ��: cp_vdu_coordinate_t coordinate		[in]��ʼ������Ϣ
	*
	* �� �� ֵ: int
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:
	*			1���ýӿڿ��Բ�ʹ��ʱ��Ĭ��λ��Ϊ(0, 0, 0)
	*			2�����ʹ�øýӿڣ������е�roi��rect��ʹ���Դ�Ϊԭ�����������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@novigo.com.cn
	* �������ڣ�2018-2-3 10:57:24
	********************************************************************************/
	cp_extern int cp_vdu_set_coordinate(cp_vdu_t *vdu, cp_vdu_coordinate_t coordinate);

	/*******************************************************************************
	* ��Ȩ����: fz & novigo
	*
	* ��������: cp_vdu_get_coordinate
	*
	* ����ȫ��: cp_vdu_get_coordinate
	*
	* ��������: public
	*
	* ����˵��: ��ȡ��ʼ������Ϣ
	*
	* ��    ��: cp_vdu_t				*vdu			[in]�������vdu����ָ��
	* ��    ��: cp_vdu_coordinate_t *coordinate		[out]�������������
	*
	* �� �� ֵ: int
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@novigo.com.cn
	* �������ڣ�2018-2-3 10:57:32
	********************************************************************************/
	cp_extern int cp_vdu_get_coordinate(cp_vdu_t *vdu, cp_vdu_coordinate_t *coordinate);

	/*******************************************************************************
	* ��Ȩ����: fz & novigo
	*
	* ��������: cp_vdu_open_debug_mode
	*
	* ����ȫ��: cp_vdu_open_debug_mode
	*
	* ��������: public 
	*
	* ����˵��: ��ʾ�Ƿ���������ģʽ
	*
	* ��    ��: cp_vdu_t		* vdu						[in]�������vdu����ָ��
	* ��    ��: char			* path						[in]��ʾ����ģʽ�±�����Ϣ��Ŀ¼��ַ
	*
	* �� �� ֵ: cp_extern int
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@novigo.com.cn
	* �������ڣ�2018-2-28 17:21:57
	********************************************************************************/
	cp_extern int cp_vdu_open_debug_mode(cp_vdu_t *vdu, char *path);

	/*******************************************************************************
	* ��Ȩ����: fz & novigo
	*
	* ��������: cp_vdu_close_debug_mode
	*
	* ����ȫ��: cp_vdu_close_debug_mode
	*
	* ��������: public 
	*
	* ����˵��: ��ʾ�رյ���ģʽ
	*
	* ��    ��: cp_vdu_t * vdu							[in]�������vdu����ָ��
	*
	* �� �� ֵ: cp_extern int
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@novigo.com.cn
	* �������ڣ�2018-2-28 17:22:20
	********************************************************************************/
	cp_extern int cp_vdu_close_debug_mode(cp_vdu_t *vdu);

	/*******************************************************************************
	* ��Ȩ����: fz & novigo
	*
	* ��������: cp_vdu_set_type
	*
	* ����ȫ��: cp_vdu_set_type
	*
	* ��������: public
	*
	* ����˵��: �豸vdu������
	*
	* ��    ��: cp_vdu_t * vdu							[in]�������vdu����ָ��
	* ��    ��: cp_vdu_type_e type						[in]vdu���������
	*
	* �� �� ֵ: int
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@novigo.com.cn
	* �������ڣ�2018-2-5 11:17:07
	********************************************************************************/
	cp_extern int cp_vdu_set_type(cp_vdu_t *vdu, cp_vdu_type_e type);

	/*******************************************************************************
	* ��Ȩ����: fz & novigo
	*
	* ��������: cp_vdu_get_type
	*
	* ����ȫ��: cp_vdu_get_type
	*
	* ��������: public
	*
	* ����˵��: ��ȡvdu������
	*
	* ��    ��: cp_vdu_t * vdu						[in]�������vdu����ָ��
	*
	* �� �� ֵ: cp_vdu_type_e
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@novigo.com.cn
	* �������ڣ�2018-2-5 11:17:28
	********************************************************************************/
	cp_vdu_type_e cp_vdu_get_type(cp_vdu_t *vdu);

	/*******************************************************************************
	* ��Ȩ����: fz & novigo
	*
	* ��������: cp_vdu_set_roi
	*
	* ����ȫ��: cp_vdu_set_roi
	*
	* ��������: public
	*
	* ����˵��: ����vdu������ĸ���Ȥ����
	*
	* ��    ��: cp_vdu_t       *vdu					[in]�������vdu����ָ��
	* ��    ��: cp_vdu_rect_t	rect				[in]���ø���Ȥ����λ����Ϣ
	*
	* �� �� ֵ: int
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@novigo.com.cn
	* �������ڣ�2018-2-3 10:57:35
	********************************************************************************/
	cp_extern int cp_vdu_set_roi(cp_vdu_t *vdu, cp_vdu_rect_t rect);

	/*******************************************************************************
	* ��Ȩ����: fz & novigo
	*
	* ��������: cp_vdu_set_roi_parameters
	*
	* ����ȫ��: cp_vdu_set_roi_parameters
	*
	* ��������: public 
	*
	* ����˵��: ����vdu������ĸ���Ȥ�������ϸ����
	*
	* ��    ��: cp_vdu_t * vdu						[in]�������vdu����ָ��
	* ��    ��: int x								[in]���ø���Ȥ����λ����Ϣ x ֵ
	* ��    ��: int y								[in]���ø���Ȥ����λ����Ϣ y ֵ
	* ��    ��: int width							[in]���ø���Ȥ����Ŀ��
	* ��    ��: int height							[in]���ø���Ȥ����ĸ߶�
	*
	* �� �� ֵ: cp_extern int
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@novigo.com.cn
	* �������ڣ�2018-2-26 14:19:59
	********************************************************************************/
	cp_extern int cp_vdu_set_roi_parameters(cp_vdu_t *vdu, int x, int y, int width, int height);

	/*******************************************************************************
	* ��Ȩ����: fz & novigo
	*
	* ��������: cp_vdu_get_roi
	*
	* ����ȫ��: cp_vdu_get_roi
	*
	* ��������: public
	*
	* ����˵��: ��ȡ����Ȥ����
	*
	* ��    ��: cp_vdu_t       *vdu             [in]�������vdu����ָ��
	* ��    ��: cp_vdu_rect_t *rect             [out]�����ȡ�ĸ���Ȥ����λ����Ϣ
	*
	* �� �� ֵ: int
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@novigo.com.cn
	* �������ڣ�2018-2-3 10:57:40
	********************************************************************************/
	cp_extern int cp_vdu_get_roi(cp_vdu_t *vdu, cp_vdu_rect_t *rect);

	/*******************************************************************************
	* ��Ȩ����: fz & novigo
	*
	* ��������: cp_vdu_clear_roi
	*
	* ����ȫ��: cp_vdu_clear_roi
	*
	* ��������: public
	*
	* ����˵��: �������Ȥ����
	*
	* ��    ��: cp_vdu_t       *vdu             [in]�������vdu����ָ��
	*
	* �� �� ֵ: int
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@novigo.com.cn
	* �������ڣ�2018-2-3 10:58:00
	********************************************************************************/
	cp_extern int cp_vdu_clear_roi(cp_vdu_t *vdu);

	/*******************************************************************************
	* ��Ȩ����: fz & novigo
	*
	* ��������: cp_vdu_get_roi_pixel
	*
	* ����ȫ��: cp_vdu_get_roi_pixel
	*
	* ��������: public
	*
	* ����˵��: ��ȡ����Ȥ�����λͼ��
	*
	* ��    ��: cp_vdu_t       *vdu             [in]�������vdu����ָ��
	* ��    ��: char * buf						[out]���淵��λͼ���ݵ����ݵ�ַ
	* ��    ��: int len							[in]���淵��λͼ���ݵ����ݵ�ַ�ĳ���
	* ��    ��: cp_vdu_pixel_format_e vpf		[in]����λͼ���ݵı��뷽ʽ
	* ��    ��: cp_vdu_rect_t *scale_rect		[in]ָ������λͼ���ݵĳߴ�
	*
	* �� �� ֵ: int
	*       <= 0  : ʧ��
	*         >0  : ��ʾ����λͼ���ݵ�ʵ�ʳ���
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@novigo.com.cn
	* �������ڣ�2018-2-3 10:58:05
	********************************************************************************/
	cp_extern int cp_vdu_get_roi_pixel(cp_vdu_t *vdu,
		char *buf, int len,
		cp_vdu_pixel_format_e vpf,
		cp_vdu_rect_t *scale_rect);

	/*******************************************************************************
	* ��Ȩ����: fz & novigo
	*
	* ��������: cp_vdu_get_rect_pixel
	*
	* ����ȫ��: cp_vdu_get_rect_pixel
	*
	* ��������: public
	*
	* ����˵��: ��ȡָ�������λͼ��
	*
	* ��    ��: cp_vdu_t       *vdu             [in]�������vdu����ָ��
	* ��    ��: char * buf						[out]���淵��λͼ���ݵ����ݵ�ַ
	* ��    ��: int len							[in]���淵��λͼ���ݵ����ݵ�ַ�ĳ���
	* ��    ��: cp_vdu_pixel_format_e vpf		[in]����λͼ���ݵı��뷽ʽ
	* ��    ��: cp_vdu_rect_t rect				[in]����ָ���������ֵ
	* ��    ��: cp_vdu_rect_t *scale_rect		[in]ָ������λͼ���ݵĳߴ�
	*
	* �� �� ֵ: int
	*       <= 0  : ʧ��
	*         >0  : ��ʾ����λͼ���ݵ�ʵ�ʳ���
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@novigo.com.cn
	* �������ڣ�2018-2-3 10:58:14
	********************************************************************************/
	cp_extern int cp_vdu_get_rect_pixel(cp_vdu_t *vdu,
		char *buf, int len,
		cp_vdu_pixel_format_e vpf,
		cp_vdu_rect_t rect,
		cp_vdu_rect_t *scale_rect);






	//cp_vdu_channel������
	///////////////////////////////////////////////////////////////////////////////

	/*******************************************************************************
	* ��Ȩ����: fz & novigo
	*
	* ��������: cp_vdu_create_channel
	*
	* ����ȫ��: cp_vdu_create_channel
	*
	* ��������: public
	*
	* ����˵��: ��vdu�д���һ��ָ�����͵�ͨ����
	*		 * �´�����ͨ��������vdu�������߼���ϵ�����洦�������ϵ�����Բ���vdu������ʾ����
	*		 * ������vdu������ʾ���������cp_vdu_insert_channel ����
	*
	* ��    ��: cp_vdu_t       *vdu								 [in]�������vdu����ָ��
	* ��    ��: cp_vdu_channel_type_e channel_type               [in]������ͨ������
	*
	* �� �� ֵ: cp_vdu_channel_t*
	*         ��NULL  : �ɹ�
	*         NULL  : ʧ��
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@novigo.com.cn
	* �������ڣ�2018-2-3 10:58:17
	********************************************************************************/
	cp_vdu_channel_t* cp_vdu_create_channel(cp_vdu_t *vdu, cp_vdu_channel_type_e channel_type);

	/*******************************************************************************
	* ��Ȩ����: fz & novigo
	*
	* ��������: cp_vdu_destroy_all_channels
	*
	* ����ȫ��: cp_vdu_destroy_all_channels
	*
	* ��������: public
	*
	* ����˵��: ����vdu�������Ѿ�������ͨ��
	*
	* ��    ��: cp_vdu_t       *vdu             [in]�������vdu����ָ��
	*
	* �� �� ֵ: int
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@novigo.com.cn
	* �������ڣ�2018-2-3 10:58:23
	********************************************************************************/
	cp_extern int cp_vdu_destroy_all_channels(cp_vdu_t *vdu);

	/*******************************************************************************
	* ��Ȩ����: fz & novigo
	*
	* ��������: cp_vdu_destroy_channel
	*
	* ����ȫ��: cp_vdu_destroy_channel
	*
	* ��������: public
	*
	* ����˵��: ����vdu��ָ����ͨ��
	*
	* ��    ��: cp_vdu_channel_t * vdu_channel						[in]��ʾ��Ҫ�����ͨ��
	*
	* �� �� ֵ: int
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@novigo.com.cn
	* �������ڣ�2018-2-3 10:58:28
	********************************************************************************/
	cp_extern int cp_vdu_destroy_channel(cp_vdu_channel_t *vdu_channel);

	/*******************************************************************************
	* ��Ȩ����: fz & novigo
	*
	* ��������: cp_vdu_channel_get_status
	*
	* ����ȫ��: cp_vdu_channel_get_status
	*
	* ��������: public
	*
	* ����˵��: ��ʾ��ȡ��ǰ��״̬��
	*
	* ��    ��: cp_vdu_t * vdu						[in]��ʾ��Ҫ�����ͨ��
	*
	* �� �� ֵ: cp_vdu_status_e
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@novigo.com.cn
	* �������ڣ�2018-2-5 17:13:32
	********************************************************************************/
	cp_extern cp_vdu_status_e cp_vdu_channel_get_status(cp_vdu_channel_t *vdu_channel);

	/*******************************************************************************
	* ��Ȩ����: fz & novigo
	*
	* ��������: cp_vdu_insert_channel
	*
	* ����ȫ��: cp_vdu_insert_channel
	*
	* ��������: public
	*
	* ����˵��: ��������ͨ�����뵽vdu�����д���
	*
	* ��    ��: cp_vdu_t				*vdu               [in]�������vdu����ָ��
	* ��    ��: cp_vdu_channel_t		* vdu_channel      [in]��ʾ��Ҫ�����ͨ��
	*
	* �� �� ֵ: int
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:��ϸ���ݿ��Խ��cp_vdu_create_channel�ӿ�������Ϣ
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@novigo.com.cn
	* �������ڣ�2018-2-3 10:58:34
	********************************************************************************/
	cp_extern int cp_vdu_insert_channel(cp_vdu_t *vdu, cp_vdu_channel_t *vdu_channel);

	/*******************************************************************************
	* ��Ȩ����: fz & novigo
	*
	* ��������: cp_vdu_remove_channel
	*
	* ����ȫ��: cp_vdu_remove_channel
	*
	* ��������: public
	*
	* ����˵��: ��ͨ����vdu�������Ƴ������ָ�����ԭʼ�ĳ�ʼ��ϵ��
	*
	* ��    ��: cp_vdu_t       *vdu             [in]�������vdu����ָ��
	* ��    ��: cp_vdu_channel_t * vdu_channel      [in]��ʾ��Ҫ�����ͨ��
	*
	* �� �� ֵ: int
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:��ϸ���ݿ��Խ��cp_vdu_create_channel��cp_vdu_insert_channel�Ľӿ�������Ϣ
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@novigo.com.cn
	* �������ڣ�2018-2-3 10:58:39
	********************************************************************************/
	cp_extern int cp_vdu_remove_channel(cp_vdu_t *vdu, cp_vdu_channel_t *vdu_channel);

	/*******************************************************************************
	* ��Ȩ����: fz & novigo
	*
	* ��������: cp_vdu_channel_set_index
	*
	* ����ȫ��: cp_vdu_channel_set_index
	*
	* ��������: public
	*
	* ����˵��: �ú�����Ҫ�����豸ͨ�������ţ���Ҫʵ��ͼ���λ�õ���
	*
	* ��    ��: cp_vdu_channel_t * vdu_channel      [in]��ʾ��Ҫ�����ͨ��
	* ��    ��: const int index						[in]��ʾͼ��������
	*
	* �� �� ֵ: int
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:
	*			1��ͨ�������ţ���ʾͨ����cp_vdu�еĲ�ι�ϵ��������Խ��Խ�����ϲ㡣
	*			2��ͨ��������ȡֵ��[0, 65535)
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@novigo.com.cn
	* �������ڣ�2018-2-3 10:58:42
	********************************************************************************/
	cp_extern int cp_vdu_channel_set_index(cp_vdu_channel_t *vdu_channel, const int index);

	/*******************************************************************************
	* ��Ȩ����: fz & novigo
	*
	* ��������: cp_vdu_channel_get_index
	*
	* ����ȫ��: cp_vdu_channel_get_index
	*
	* ��������: public
	*
	* ����˵��: ��ȡͨ����������Ϣ
	*
	* ��    ��: cp_vdu_channel_t * vdu_channel      [in]��ʾ��Ҫ�����ͨ��
	*
	* �� �� ֵ: int
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@novigo.com.cn
	* �������ڣ�2018-2-5 11:07:16
	********************************************************************************/
	cp_extern int cp_vdu_channel_get_index(cp_vdu_channel_t *vdu_channel);

	/*******************************************************************************
	* ��Ȩ����: fz & novigo
	*
	* ��������: cp_vdu_channel_set_vector_stream
	*
	* ����ȫ��: cp_vdu_channel_set_vector_stream
	*
	* ��������: public
	*
	* ����˵��: ����ͨ����Ҫ�����ʸ��������
	*
	* ��    ��: cp_vdu_channel_t * vdu_channel      [in]��ʾ��Ҫ�����ͨ��
	* ��    ��: cp_vdu_vector_stream_type_e vs_type	[in]��ʾʸ����������������
	* ��    ��: const char * buf						[in]��ʾʸ���������ĵ�ַָ��
	* ��    ��: const int len						[in]��ʾʸ�������������ݳ���
	*
	* �� �� ֵ: int
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@novigo.com.cn
	* �������ڣ�2018-2-5 11:14:51
	********************************************************************************/
	cp_extern int cp_vdu_channel_set_vector_stream(cp_vdu_channel_t *vdu_channel,
		cp_vdu_vector_stream_type_e vs_type, const char *buf, const int len);

	/*******************************************************************************
	* ��Ȩ����: fz & novigo
	*
	* ��������: cp_vdu_channel_set_roi
	*
	* ����ȫ��: cp_vdu_channel_set_roi
	*
	* ��������: public
	*
	* ����˵��: ����ͨ��������ĸ���Ȥ����
	*
	* ��    ��: cp_vdu_channel_t * vdu_channel			[in]��ʾ��Ҫ�����ͨ��
	* ��    ��: cp_vdu_rect_t rect						[in]���ø���Ȥ����λ����Ϣ
	*
	* �� �� ֵ: int
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@novigo.com.cn
	* �������ڣ�2018-2-3 10:58:51
	********************************************************************************/
	cp_extern int cp_vdu_channel_set_roi(cp_vdu_channel_t *vdu_channel, cp_vdu_rect_t rect);

	/*******************************************************************************
	* ��Ȩ����: fz & novigo
	*
	* ��������: cp_vdu_channel_set_roi_parameters
	*
	* ����ȫ��: cp_vdu_channel_set_roi_parameters
	*
	* ��������: public 
	*
	* ����˵��: ����˵��
	*
	* ��    ��: cp_vdu_channel_t *vdu_channel		[in]��ʾ��Ҫ�����ͨ��
	* ��    ��: int x								[in]���ø���Ȥ����λ����Ϣ x ֵ
	* ��    ��: int y								[in]���ø���Ȥ����λ����Ϣ y ֵ
	* ��    ��: int width							[in]���ø���Ȥ����Ŀ��
	* ��    ��: int height							[in]���ø���Ȥ����ĸ߶�
	*
	* �� �� ֵ: cp_extern int
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@novigo.com.cn
	* �������ڣ�2018-2-26 14:22:23
	********************************************************************************/
	cp_extern int cp_vdu_channel_set_roi_parameters(cp_vdu_channel_t *vdu_channel, int x, int y, int width, int height);

	/*******************************************************************************
	* ��Ȩ����: fz & novigo
	*
	* ��������: cp_vdu_channel_get_roi
	*
	* ����ȫ��: cp_vdu_channel_get_roi
	*
	* ��������: public
	*
	* ����˵��: ��ȡ����Ȥ����
	*
	* ��    ��: cp_vdu_channel_t * vdu_channel      [in]��ʾ��Ҫ�����ͨ��
	* ��    ��: cp_vdu_rect_t *roi_rect				[out]�����ȡ�ĸ���Ȥ����λ����Ϣ
	*
	* �� �� ֵ: cp_vdu_rect_t
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@novigo.com.cn
	* �������ڣ�2018-2-3 10:58:56
	********************************************************************************/
	cp_extern int cp_vdu_channel_get_roi(cp_vdu_channel_t *vdu_channel, cp_vdu_rect_t *roi_rect);

	/*******************************************************************************
	* ��Ȩ����: fz & novigo
	*
	* ��������: cp_vdu_channel_clear_roi
	*
	* ����ȫ��: cp_vdu_channel_clear_roi
	*
	* ��������: public
	*
	* ����˵��: �������Ȥ����
	*
	* ��    ��: cp_vdu_channel_t * vdu_channel      [in]��ʾ��Ҫ�����ͨ��
	*
	* �� �� ֵ: int
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@novigo.com.cn
	* �������ڣ�2018-2-3 10:59:01
	********************************************************************************/
	cp_extern int cp_vdu_channel_clear_roi(cp_vdu_channel_t *vdu_channel);

	/*******************************************************************************
	* ��Ȩ����: fz & novigo
	*
	* ��������: cp_vdu_channel_get_roi_pixel
	*
	* ����ȫ��: cp_vdu_channel_get_roi_pixel
	*
	* ��������: public
	*
	* ����˵��: ��ȡ����Ȥ�����λͼ��
	*
	* ��    ��: cp_vdu_channel_t * vdu_channel	[in]��ʾ��Ҫ�����ͨ��
	* ��    ��: char * buf						[out]���淵��λͼ���ݵ����ݵ�ַ
	* ��    ��: int len							[in]���淵��λͼ���ݵ����ݵ�ַ�ĳ���
	* ��    ��: cp_vdu_pixel_format_e vpf		[in]����λͼ���ݵı��뷽ʽ
	* ��    ��: cp_vdu_rect_t *scale_rect		[in]ָ������λͼ���ݵĳߴ�
	*
	* �� �� ֵ: int
	*       <= 0  : ʧ��
	*         >0  : ��ʾ����λͼ���ݵ�ʵ�ʳ���
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@novigo.com.cn
	* �������ڣ�2018-2-3 10:59:06
	********************************************************************************/
	cp_extern int cp_vdu_channel_get_roi_pixel(cp_vdu_channel_t *vdu_channel,
		char *buf, int len,
		cp_vdu_pixel_format_e vpf,
		cp_vdu_rect_t *scale_rect);

	/*******************************************************************************
	* ��Ȩ����: fz & novigo
	*
	* ��������: cp_vdu_channel_get_roi_pixel_by_image_info
	*
	* ����ȫ��: cp_vdu_channel_get_roi_pixel_by_image_info
	*
	* ��������: public
	*
	* ����˵��: ����image info������Ȥ����ͼ������imageͼƬ
	*
	* ��    ��: cp_vdu_channel_t * vdu_channel      [in]��ʾ��Ҫ�����ͨ��
	* ��    ��: cp_vdu_image_info_t *image_info		[out]���淵��λͼ���ݵ�����
	*
	* �� �� ֵ: int
	*       <= 0  : ʧ��
	*         >0  : ��ʾ����λͼ���ݵ�ʵ�ʳ���
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@novigo.com.cn
	* �������ڣ�2018-2-3 10:59:06
	********************************************************************************/
	cp_extern int cp_vdu_channel_get_roi_pixel_by_image_info(
		cp_vdu_channel_t *vdu_channel,
		cp_vdu_image_info_t *image_info);

	/*******************************************************************************
	* ��Ȩ����: fz & novigo
	*
	* ��������: cp_vdu_channel_get_rect_pixel
	*
	* ����ȫ��: cp_vdu_channel_get_rect_pixel
	*
	* ��������: public
	*
	* ����˵��: ��ȡָ�������λͼ��
	*
	* ��    ��: cp_vdu_channel_t * vdu_channel	[in]��ʾ��Ҫ�����ͨ��
	* ��    ��: char * buf						[out]���淵��λͼ���ݵ����ݵ�ַ
	* ��    ��: int len							[in]���淵��λͼ���ݵ����ݵ�ַ�ĳ���
	* ��    ��: cp_vdu_pixel_format_e vpf		[in]����λͼ���ݵı��뷽ʽ
	* ��    ��: cp_vdu_rect_t rect				[in]����ָ���������ֵ
	* ��    ��: cp_vdu_rect_t *scale_rect		[in]ָ������λͼ���ݵĳߴ�
	*
	* �� �� ֵ: int
	*       <= 0  : ʧ��
	*         >0  : ��ʾ����λͼ���ݵ�ʵ�ʳ���
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@novigo.com.cn
	* �������ڣ�2018-2-3 10:59:09
	********************************************************************************/
	cp_extern int cp_vdu_channel_get_rect_pixel(cp_vdu_channel_t *vdu_channel,
		char *buf, int len,
		cp_vdu_pixel_format_e vpf,
		cp_vdu_rect_t rect,
		cp_vdu_rect_t *scale_rect);

	/*******************************************************************************
	* ��Ȩ����: fz & novigo
	*
	* ��������: cp_vdu_channel_get_rect_pixel_by_image_info
	*
	* ����ȫ��: cp_vdu_channel_get_rect_pixel_by_image_info
	*
	* ��������: public
	*
	* ����˵��: ����image info��rectָ��������ͼ������imageͼƬ
	*
	* ��    ��: cp_vdu_channel_t * vdu_channel      [in]��ʾ��Ҫ�����ͨ��
	* ��    ��: cp_vdu_image_info_t *image_info		[out]���淵��λͼ���ݵ�����
	*
	* �� �� ֵ: int
	*       <= 0  : ʧ��
	*         >0  : ��ʾ����λͼ���ݵ�ʵ�ʳ���
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@novigo.com.cn
	* �������ڣ�2018-2-3 10:59:06
	********************************************************************************/
	cp_extern int cp_vdu_channel_get_rect_pixel_by_image_info(
		cp_vdu_channel_t *vdu_channel,
		cp_vdu_image_info_t *image_info);




	//cp_vdu_media_info������
	///////////////////////////////////////////////////////////////////////////////

	/*******************************************************************************
	* ��Ȩ����: fz & novigo
	*
	* ��������: cp_vdu_image_info_clear
	*
	* ����ȫ��: cp_vdu_image_info_clear
	*
	* ��������: public 
	*
	* ����˵��: ���image info��Ϣ
	*
	* ��    ��: cp_vdu_image_info_t * vdu_image      [out]��ʾͼ��������Ϣ
	*
	* �� �� ֵ: cp_extern int
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@novigo.com.cn
	* �������ڣ�2018-2-25 11:31:47
	********************************************************************************/
	cp_extern int cp_vdu_image_info_clear(cp_vdu_image_info_t *vdu_image);

	/*******************************************************************************
	* ��Ȩ����: fz & novigo
	*
	* ��������: cp_vdu_image_info_set_pixel_format
	*
	* ����ȫ��: cp_vdu_image_info_set_pixel_format
	*
	* ��������: public 
	*
	* ����˵��: ����ͼ��ɫ�ʿռ�
	*
	* ��    ��: cp_vdu_image_info_t * vdu_image      [out]��ʾͼ��������Ϣ
	* ��    ��: cp_vdu_pixel_format_e vpf			 [in]λͼ���ݵı��뷽ʽ
	*
	* �� �� ֵ: cp_extern int
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@novigo.com.cn
	* �������ڣ�2018-2-25 11:32:10
	********************************************************************************/
	cp_extern int cp_vdu_image_info_set_pixel_format(cp_vdu_image_info_t *vdu_image, cp_vdu_pixel_format_e vpf);

	/*******************************************************************************
	* ��Ȩ����: fz & novigo
	*
	* ��������: cp_vdu_image_info_get_pixel_format
	*
	* ����ȫ��: cp_vdu_image_info_get_pixel_format
	*
	* ��������: public 
	*
	* ����˵��: ��ȡͼ��ɫ�ʿռ�
	*
	* ��    ��: cp_vdu_image_info_t * vdu_image      [in]��ʾͼ��������Ϣ
	*
	* �� �� ֵ: cp_extern cp_vdu_pixel_format_e
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@novigo.com.cn
	* �������ڣ�2018-2-25 11:33:23
	********************************************************************************/
	cp_extern cp_vdu_pixel_format_e cp_vdu_image_info_get_pixel_format(cp_vdu_image_info_t *vdu_image);

	/*******************************************************************************
	* ��Ȩ����: fz & novigo
	*
	* ��������: cp_vdu_image_info_set_vdu_rect
	*
	* ����ȫ��: cp_vdu_image_info_set_vdu_rect
	*
	* ��������: public 
	*
	* ����˵��: ������Ҫ��ȡ��vduͼ��λ��
	*
	* ��    ��: cp_vdu_image_info_t * vdu_image      [out]��ʾͼ��������Ϣ
	* ��    ��: cp_vdu_rect_t rect					[in]����ָ���������ֵ
	*
	* �� �� ֵ: cp_extern int
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@novigo.com.cn
	* �������ڣ�2018-2-25 11:33:31
	********************************************************************************/
	cp_extern int cp_vdu_image_info_set_vdu_rect(cp_vdu_image_info_t *vdu_image, cp_vdu_rect_t vdu_rect);

	/*******************************************************************************
	* ��Ȩ����: fz & novigo
	*
	* ��������: cp_vdu_image_info_set_vdu_rect_parameters
	*
	* ����ȫ��: cp_vdu_image_info_set_vdu_rect_parameters
	*
	* ��������: public 
	*
	* ����˵��: ������Ҫ��ȡ��vduͼ��λ�õ���ϸ
	*
	* ��    ��: cp_vdu_image_info_t * vdu_image      [out]��ʾͼ��������Ϣ
	* ��    ��: int x								[in]��������λ����Ϣ x ֵ
	* ��    ��: int y								[in]��������λ����Ϣ y ֵ
	* ��    ��: int width							[in]��������Ŀ��
	* ��    ��: int height							[in]��������ĸ߶�
	*
	* �� �� ֵ: cp_extern int
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@novigo.com.cn
	* �������ڣ�2018-2-25 11:34:06
	********************************************************************************/
	cp_extern int cp_vdu_image_info_set_vdu_rect_parameters(cp_vdu_image_info_t *vdu_image, int x, int y, int width, int height);

	/*******************************************************************************
	* ��Ȩ����: fz & novigo
	*
	* ��������: cp_vdu_image_info_get_vdu_rect
	*
	* ����ȫ��: cp_vdu_image_info_get_vdu_rect
	*
	* ��������: public 
	*
	* ����˵��: ��ȡ��Ҫ��ȡ��vduͼ��λ��
	*
	* ��    ��: cp_vdu_image_info_t * vdu_image      [out]��ʾͼ��������Ϣ
	*
	* �� �� ֵ: cp_extern cp_vdu_rect_t
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@novigo.com.cn
	* �������ڣ�2018-2-25 11:34:29
	********************************************************************************/
	cp_extern cp_vdu_rect_t cp_vdu_image_info_get_vdu_rect(cp_vdu_image_info_t *vdu_image);

	/*******************************************************************************
	* ��Ȩ����: fz & novigo
	*
	* ��������: cp_vdu_image_info_set_image_size
	*
	* ����ȫ��: cp_vdu_image_info_set_image_size
	*
	* ��������: public 
	*
	* ����˵��: ��������������ͼ��ߴ���Ϣ
	*
	* ��    ��: cp_vdu_image_info_t * vdu_image      [out]��ʾͼ��������Ϣ
	* ��    ��: int width							[in]ָ������λͼ���ݵĿ��
	* ��    ��: int height							[in]ָ������λͼ���ݵĸ߶�
	*
	* �� �� ֵ: cp_extern int
	*           0  : �ɹ�
	*         ��0  : ʧ��
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@novigo.com.cn
	* �������ڣ�2018-2-25 11:37:05
	********************************************************************************/
	cp_extern int cp_vdu_image_info_set_image_size(cp_vdu_image_info_t *vdu_image, int width, int height);

	/*******************************************************************************
	* ��Ȩ����: fz & novigo
	*
	* ��������: cp_vdu_image_info_get_image_rect
	*
	* ����ȫ��: cp_vdu_image_info_get_image_rect
	*
	* ��������: public 
	*
	* ����˵��: ��ȡ����������ͼ��ߴ���Ϣ
	*
	* ��    ��: cp_vdu_image_info_t * vdu_image      [out]��ʾͼ��������Ϣ
	*
	* �� �� ֵ: cp_extern cp_vdu_rect_t
	*
	* ��    ע:����˵������
	*
	* ��    �ߣ�fz
	* �������䣺 fangzhenmu@novigo.com.cn
	* �������ڣ�2018-2-25 11:37:12
	********************************************************************************/
	cp_extern cp_vdu_rect_t cp_vdu_image_info_get_image_rect(cp_vdu_image_info_t *vdu_image);



#ifdef __cplusplus
}
#endif


#endif //_CP_VDU_API_H_


