/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2017-01-04

Description:

**************************************************************************/
#include "cp_ptp_func_proc.h"




//��debug �ļ�
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

//�ر�debug �ļ�
cp_int32_t close_ptp_debug_file(cp_ptp_func_t *ptp_func)
{
	if (ptp_func->file) {
		fclose(ptp_func->file);
		ptp_func->file = CP_NULL;
	}
	return 0;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: print_ptp_debug_info
*
* ����˵��: ��ӡdebug��Ϣ
*
* ��    ��: cp_ptp_func_t * ptp_func						[in]����˵��
* ��    ��: cp_player_timestamp_t * pt						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-01-10 11:24:04
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


