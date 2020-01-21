/*******************************************************************************
*
*Copyright:novigo
*
*File name: cp_status.c
*
*Author:fangzhenmu@novigo.com.cn
*
*Version: 1.0
*
*Date:2018/02/05
*
*Description: create (cp_status.c)
*
*Others:
*
*History:
*******************************************************************************/
#include "cp_status.h"



//ªÒ»°vdu status ÷µ
#define CP_STATUS_NAME_GEN(type, type_name) case cp_status_name_ ## type: return type_name;
const char* cp_strstatus(cp_status_e status)
{
	switch (status)
	{
		CP_STATUS_NAME_MAP(CP_STATUS_NAME_GEN);
	}

	return "unknown status";
}
#undef CP_STATUS_NAME_GEN



