/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-24

Description:

**************************************************************************/

#ifndef _CP_HI3519_INCLUDE_INCLUDE_H_
#define _CP_HI3519_INCLUDE_INCLUDE_H_



//#define		CP_HI3519_MODE				1
//#define		CP_HI3519_PRINT_LOG			1

#if defined(__linux__)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/ioctl.h>
#endif


#if defined(CP_HI3519_MODE)
#include "sample_comm.h"

#endif

#endif