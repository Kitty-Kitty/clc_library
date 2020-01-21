/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_ENV_INCLUDE_H_
#define _CP_ENV_INCLUDE_H_


#include <stdio.h>
#include<stdlib.h>



#ifdef WIN32
int cp_setenv(const char *name, const char * value, int overwrite);
#else
#define	cp_setenv							setenv
#endif



 
#endif