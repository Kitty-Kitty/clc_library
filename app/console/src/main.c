/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-23

Description:

**************************************************************************/
#include "cp_core.h"
#include "cp_app.h"
#include "cp_include.h"
#include "cp_console.h"




int main(int argc, char** argv) {
	//cp_log_printf("Hello World!\r\n");
	printf("Hello World!\r\n");

	cp_app_register(0, "cp_console", 1, "cp console", CP_NULL, CP_NULL);
	return 0;
}