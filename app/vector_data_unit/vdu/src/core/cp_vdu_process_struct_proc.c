/*******************************************************************************
*
*Copyright:novigo
*
*File name: cp_vdu_process_struct.c
*
*Author:fangzhenmu@novigo.com.cn
*
*Version: 1.0
*
*Date:2018/02/02
*
*Description: create (cp_vdu_process_struct.c)
*
*Others:
*
*History:
*******************************************************************************/
#include "cp_vdu_process_struct_proc.h"




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
cp_int32_t fill_vdu_to_process_struct(cp_vdu_process_t *process_struct, cp_vdu_t *vdu)
{
	if (!process_struct) {
		return -1;
	}

	cp_memset(process_struct, 0, cp_sizeof(cp_vdu_process_t));
	process_struct->type = cp_vdu_process_struct_type_process;
	process_struct->vdu = vdu;

	return 0;
}

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
cp_int32_t fill_process_struct_to_vdu(cp_vdu_t *vdu, cp_vdu_process_t *process_struct)
{
	return 0;
}










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
	cp_vdu_channel_process_t *channel_process_struct, cp_vdu_channel_t *vdu_channel)
{
	if (!channel_process_struct || !vdu_channel) {
		return -1;
	}

	cp_memset(channel_process_struct, 0, cp_sizeof(cp_vdu_channel_process_t));
	channel_process_struct->type = cp_vdu_process_struct_type_channel;
	channel_process_struct->index = vdu_channel->index;
	channel_process_struct->channel = vdu_channel->channel;

	return 0;
}

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
	cp_vdu_channel_t *vdu_channel, cp_vdu_channel_process_t *channel_process_struct)
{
	return 0;
}

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
cp_int32_t fill_process_struct_set_image_rect(cp_vdu_channel_process_t *channel_process_struct, cp_vdu_rect_t *image_rect)
{
	convert_vdu_rect_to_cp_rect(&channel_process_struct->image_rect, image_rect);
	return 0;
}

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
cp_void_t convert_vdu_rect_to_cp_rect(cp_rect_t *cp_rect, cp_vdu_rect_t *vdu_rect)
{
	cp_rect->left = vdu_rect->x;
	cp_rect->top = vdu_rect->y;
	cp_rect->right = vdu_rect->x + vdu_rect->width;
	cp_rect->bottom = vdu_rect->y + vdu_rect->height;
}

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
cp_void_t convert_cp_rect_to_vdu_rect(cp_vdu_rect_t *vdu_rect, cp_rect_t *cp_rect)
{
	vdu_rect->x = cp_rect->left;
	vdu_rect->y = cp_rect->top;
	vdu_rect->width = cp_rect->right - cp_rect->left;
	vdu_rect->height = cp_rect->bottom - cp_rect->top;
}

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
cp_codec_pixel_format_e convert_vdu_pf_to_cp_pf(cp_vdu_pixel_format_e vpf)
{
	switch (vpf)
	{
	case cp_vdu_pixel_format_argb8888:
	{
		return cp_codec_pixel_format_argb;
	}
	break;
	case cp_vdu_pixel_format_rgba8888:
	{
		return cp_codec_pixel_format_rgba;
	}
	break;
	default:
	{
		return cp_codec_pixel_format_none;
	}
	break;
	}

	return cp_codec_pixel_format_none;
}