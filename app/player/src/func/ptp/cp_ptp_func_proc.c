/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2017-01-04

Description:

**************************************************************************/
#include "cp_ptp_func_proc.h"




//打开debug 文件
cp_int32_t open_ptp_debug_file(cp_ptp_func_t *ptp_func, cp_int32_t group_id)
{
	cp_char_t				tmp_file_name[CP_PTP_DEFAULT_BUFFER_LENGTH] = { 0, };


	if (!ptp_func || !ptp_func->ptp_conf.is_debug) {
		return 0;
	}

	if (ptp_func->file) {
		return 0;
	}

	cp_snprintf(tmp_file_name, CP_PTP_DEFAULT_BUFFER_LENGTH, 
		"%s/ptp_%d.txt", ptp_func->ptp_conf.debug_path, group_id);
	ptp_func->file = fopen(tmp_file_name, "wb");
	if (!ptp_func->file) {
		cp_module_log(error, ptp_func, "open_ptp_debug_file() [%s] error.", 
			tmp_file_name);
		return -2;
	}

	return 0;
}

//关闭debug 文件
cp_int32_t close_ptp_debug_file(cp_ptp_func_t *ptp_func)
{
	if (ptp_func->file) {
		fclose(ptp_func->file);
		ptp_func->file = CP_NULL;
	}
	return 0;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: print_ptp_debug_info
*
* 函数说明: 打印debug信息
*
* 参    数: cp_ptp_func_t * ptp_func						[in]参数说明
* 参    数: cp_player_timestamp_t * pt						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-01-10 11:24:04
******************************************************************************************************/
cp_int32_t print_ptp_debug_info(cp_ptp_func_t *ptp_func, cp_player_timestamp_t *pt)
{
	if (!ptp_func || !ptp_func->ptp_conf.is_debug || !ptp_func->file) {
		return -1;
	}

#if defined(WIN32)
	fprintf(ptp_func->file, "update ptp: [%d] sys[\t%u\t:\t%u\t] ptp[\t%u\t:\t%u\t]\toffset[\t%lld\t]",
		pt->ptp_timestamp.id,
		pt->system_timestamp.tv_sec,
		(cp_uint32_t)(pt->system_timestamp.tv_usec * CP_TIME_USEC_TO_NSEC),
		pt->ptp_timestamp.time.tv_sec,
		pt->ptp_timestamp.time.tv_nsec,
		pt->offset_ns);
#else
	fprintf(ptp_func->file, "update ptp: [%d] sys[\t%u\t:\t%u\t] ptp[\t%u\t:\t%u\t]\toffset[\t%lld\t]",
		pt->ptp_timestamp.id,
		pt->system_timestamp.tv_sec,
		(cp_uint32_t)(pt->system_timestamp.tv_usec * CP_TIME_USEC_TO_NSEC),
		pt->ptp_timestamp.time.tv_sec,
		pt->ptp_timestamp.time.tv_nsec,
		pt->offset_ns);
#endif

	fflush(ptp_func->file);

	return 0;
}


