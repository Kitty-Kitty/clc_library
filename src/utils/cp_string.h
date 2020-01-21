/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-06-22

Description:

**************************************************************************/

#ifndef _CP_STRING_INCLUDE_H_
#define _CP_STRING_INCLUDE_H_



#include <stdio.h>



typedef struct cp_str_s						cp_str_t;





struct cp_str_s{
	size_t				len;
	unsigned char     *data;
};



#ifndef cp_snprintf
	int	cp_snprintf(unsigned char *buf, int len, const char *fmt, ...);
#endif











#endif





