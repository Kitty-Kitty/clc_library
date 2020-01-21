/*******************************************************************************
*
*Copyright:novigo
*
*File name: cp_vdu_status.c
*
*Author:fangzhenmu@novigo.com.cn
*
*Version: 1.0
*
*Date:2018/02/05
*
*Description: create (cp_vdu_status.c)
*
*Others:
*
*History:
*******************************************************************************/
#include "cp_vdu_status.h"



//ªÒ»°vdu status ÷µ
#define CP_VDU_STATUS_NAME_GEN(type, type_name) case cp_vdu_status_name_ ## type: return type_name;
const char* cp_vdu_strstatus(cp_vdu_status_e status)
{
	switch (status)
	{
		CP_VDU_STATUS_NAME_MAP(CP_VDU_STATUS_NAME_GEN);
	}

	return "unknown status";
}
#undef CP_VDU_STATUS_NAME_GEN



