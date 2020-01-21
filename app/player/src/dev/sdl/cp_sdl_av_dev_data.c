/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-20

Description:

**************************************************************************/
#include "cp_sdl_av_dev_data.h"



/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: create_sdl_av_dev_data_element
*
* 函数说明: 创建data element
*
* 参    数: cp_pool_t * pool						[in]参数说明
*
* 返 回 值: cp_sdl_av_dev_data_element_t *
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-12-20 10:14:54
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
* 版权所有: fz & novigo
*
* 函数名称: create_sdl_av_dev_data_element_and_buufer
*
* 函数说明: 创建data element 和 data 中的 buffer
*
* 参    数: cp_pool_t * pool						[in]参数说明
* 参    数: cp_int32_t buf_size						[in]参数说明
*
* 返 回 值: cp_sdl_av_dev_data_element_t *
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-12-20 10:17:50
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
* 版权所有: fz & novigo
*
* 函数名称: destroy_sdl_av_dev_data_element
*
* 函数说明: 消毁data element
*
* 参    数: cp_pool_t * pool						[in]参数说明
* 参    数: cp_sdl_av_dev_data_element_t * elem						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-12-20 10:14:51
******************************************************************************************************/
cp_int32_t destroy_sdl_av_dev_data_element(cp_pool_t *pool, cp_sdl_av_dev_data_element_t *elem)
{
	if (!pool || !elem) {
		return -1;
	}
	cp_pfree(pool, elem);
	return 0;
}


