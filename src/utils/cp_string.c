
/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-06-22

Description:

**************************************************************************/
#include <stdarg.h>
#include "cp_string.h"




#ifndef cp_snprintf
int	cp_snprintf(unsigned char *buf, int len, const char *fmt, ...)
{
	int				ret_int = -1;
	va_list				marker;



	if (len < 3)
	{
		return -1;
	}

	va_start(marker, fmt);
	ret_int = /*_vsnprintf*/vsnprintf(buf, len, fmt, marker);
	if (ret_int < 0)
	{
		buf[len - 4] = '.';
		buf[len - 3] = '.';
		buf[len - 2] = '.';
	}
	buf[len - 1] = 0;

	va_end(marker);
	return 0;
}
#endif


