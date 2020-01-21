/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-11-24

Description:

**************************************************************************/

#ifndef _CP_CSS_STD_INCLUDE_H_
#define _CP_CSS_STD_INCLUDE_H_


#include "cp_core.h"
#include "prot_gmp_core.h"
#include "css_media_info.h"



/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: cp_std_convert_position
*
* ����˵��: ת��λ����Ϣ
*
* ��    ��: gmdt_rectpair_p_t *gmdt_rp						[in]����˵��
* ��    ��: cp_play_position_t * pp						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-11-24 14:06:30
******************************************************************************************************/
cp_int32_t	cp_std_convert_position(gmdt_rectpair_p_t *gmdt_rp, cp_play_position_t *pp);

#endif