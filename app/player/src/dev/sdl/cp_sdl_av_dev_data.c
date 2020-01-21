/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-20

Description:

**************************************************************************/
#include "cp_sdl_av_dev_data.h"



/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: create_sdl_av_dev_data_element
*
* ����˵��: ����data element
*
* ��    ��: cp_pool_t * pool						[in]����˵��
*
* �� �� ֵ: cp_sdl_av_dev_data_element_t *
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-12-20 10:14:54
******************************************************************************************************/
cp_sdl_av_dev_data_element_t *create_sdl_av_dev_data_element(cp_pool_t *pool)
{
	cp_void_t					*sadd_elem = CP_NULL;



	if (!pool) {
		return CP_NULL;
	}
	sadd_elem = cp_palloc(pool, cp_sizeof(cp_sdl_av_dev_data_element_t));
	if (sadd_elem) {
		cp_memset(sadd_elem, 0, cp_sizeof(cp_sdl_av_dev_data_element_t));
		return (cp_sdl_av_dev_data_element_t*)sadd_elem;
	}
	return CP_NULL;
}


/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: create_sdl_av_dev_data_element_and_buufer
*
* ����˵��: ����data element �� data �е� buffer
*
* ��    ��: cp_pool_t * pool						[in]����˵��
* ��    ��: cp_int32_t buf_size						[in]����˵��
*
* �� �� ֵ: cp_sdl_av_dev_data_element_t *
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-12-20 10:17:50
******************************************************************************************************/
cp_sdl_av_dev_data_element_t *create_sdl_av_dev_data_element_and_buufer(cp_pool_t *pool, cp_int32_t buf_size)
{
	cp_sdl_av_dev_data_element_t					*sadd_elem = CP_NULL;



	if (!pool) {
		return CP_NULL;
	}

	sadd_elem = cp_palloc(pool, cp_sizeof(cp_sdl_av_dev_data_element_t) + buf_size);
	if (!sadd_elem) {
		return CP_NULL;
	}

	cp_memset(sadd_elem, 0, cp_sizeof(cp_sdl_av_dev_data_element_t) + buf_size);

	cp_set_sdl_av_dev_data(&sadd_elem->data, 0, 0, 0,
		(cp_uchar_t*)sadd_elem + cp_sizeof(cp_sdl_av_dev_data_element_t),
		buf_size);

	return sadd_elem;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: destroy_sdl_av_dev_data_element
*
* ����˵��: ����data element
*
* ��    ��: cp_pool_t * pool						[in]����˵��
* ��    ��: cp_sdl_av_dev_data_element_t * elem						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-12-20 10:14:51
******************************************************************************************************/
cp_int32_t destroy_sdl_av_dev_data_element(cp_pool_t *pool, cp_sdl_av_dev_data_element_t *elem)
{
	if (!pool || !elem) {
		return -1;
	}
	cp_pfree(pool, elem);
	return 0;
}


