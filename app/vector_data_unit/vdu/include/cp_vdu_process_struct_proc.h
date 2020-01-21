/*******************************************************************************
*
*Copyright:novigo
*
*File name: cp_vdu_process_struct_proc.h
*
*Author:fangzhenmu@novigo.com.cn
*
*Version: 1.0
*
*Date:2018/02/17
*
*Description: create (cp_vdu_process_struct_proc.h)
*
*Others:
*
*History:
*******************************************************************************/

#ifndef _CP_VDU_PROCESS_STRUCT_PROC_H_
#define _CP_VDU_PROCESS_STRUCT_PROC_H_



#include "cp_vdu.h"
#include "cp_vdu_process_struct.h"



//����process struct������
#define cp_vdu_process_struct_set_type(ps)					((ps)->type = cp_vdu_process_struct_type_process);

//����channel process struct������
#define cp_vdu_channel_process_struct_set_type(ps)			((ps)->type = cp_vdu_process_struct_type_channel);




/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: fill_vdu_to_process_struct
*
* ����˵��: ��ʼ��vdu process����
*
* ��    ��: cp_vdu_process_t *process_struct					[in]����˵��
*
* �� �� ֵ: cp_extern cp_int32_t
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-03-26 14:07:54
******************************************************************************************************/
cp_int32_t fill_vdu_to_process_struct(cp_vdu_process_t *process_struct, cp_vdu_t *vdu);

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: fill_process_struct_to_vdu
*
* ����˵��: ��ʼ��vdu process����
*
* ��    ��: cp_vdu_process_t *process_struct					[in]����˵��
*
* �� �� ֵ: cp_extern cp_int32_t
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-03-26 14:07:54
******************************************************************************************************/
cp_int32_t fill_process_struct_to_vdu(cp_vdu_t *vdu, cp_vdu_process_t *process_struct);





/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: fill_vdu_channel_to_process_struct
*
* ����˵��: ��ʼ��channel process struct����
*
* ��    ��: cp_vdu_channel_process_t *channel_process_struct					[in]����˵��
*
* �� �� ֵ: cp_extern cp_int32_t
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-03-26 14:07:54
******************************************************************************************************/
cp_int32_t fill_vdu_channel_to_process_struct(
	cp_vdu_channel_process_t *channel_process_struct, cp_vdu_channel_t *vdu_channel);

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: fill_vdu_channel_to_process_struct
*
* ����˵��: ��ʼ��channel process struct����
*
* ��    ��: cp_vdu_channel_process_t *channel_process_struct					[in]����˵��
*
* �� �� ֵ: cp_extern cp_int32_t
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-03-26 14:07:54
******************************************************************************************************/
cp_int32_t fill_process_struct_to_vdu_channel(
	cp_vdu_channel_t *vdu_channel, cp_vdu_channel_process_t *channel_process_struct);


//����channel process struct��image rect
/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: fill_process_struct_set_image_rect
*
* ����˵��: ����image rect
*
* ��    ��: cp_vdu_channel_process_t		*channel_process_struct					[in]����˵��
* ��    ��: cp_vdu_rect_t				*image_rect								[in]����˵��
*
* �� �� ֵ: cp_extern cp_int32_t
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-03-26 14:07:54
******************************************************************************************************/
cp_int32_t fill_process_struct_set_image_rect(
	cp_vdu_channel_process_t *channel_process_struct, cp_vdu_rect_t *image_rect);

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: convert_vdu_rect_to_cp_rect
*
* ����˵��: ��vdu_rectת��Ϊcp_rect
*
* ��    ��: cp_rect_t *cp_rect				[out]����˵��
* ��    ��: cp_vdu_rect_t *vdu_rect			[in]����˵��
*
* �� �� ֵ: cp_extern cp_int32_t
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-03-26 14:07:54
******************************************************************************************************/
cp_void_t convert_vdu_rect_to_cp_rect(cp_rect_t *cp_rect, cp_vdu_rect_t *vdu_rect);

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: fill_vdu_channel_to_process_struct
*
* ����˵��: ��cp_rectת��Ϊvdu_rect
*
* ��    ��: cp_vdu_rect_t *vdu_rect			[out]����˵��
* ��    ��: cp_rect_t *cp_rect				[in]����˵��
*
* �� �� ֵ: cp_extern cp_int32_t
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-03-26 14:07:54
******************************************************************************************************/
cp_void_t convert_cp_rect_to_vdu_rect(cp_vdu_rect_t *vdu_rect, cp_rect_t *cp_rect);

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: convert_vdu_pf_to_cp_pf
*
* ����˵��: ��vdu_pfת��Ϊcp_pf
*
* ��    ��: cp_vdu_pixel_format_e vpf			[out]����˵��
*
* �� �� ֵ: cp_codec_pixel_format_e
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-03-26 14:07:54
******************************************************************************************************/
cp_codec_pixel_format_e convert_vdu_pf_to_cp_pf(cp_vdu_pixel_format_e vpf);


#endif