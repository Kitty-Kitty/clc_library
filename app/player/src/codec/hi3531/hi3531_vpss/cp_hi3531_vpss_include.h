/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-24

Description:

**************************************************************************/

#ifndef _CP_HI3531_VPSS_INCLUDE_INCLUDE_H_
#define _CP_HI3531_VPSS_INCLUDE_INCLUDE_H_




#if defined(CP_HI3531_VDEC_MODE)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#if defined(__linux__)
#include <pthread.h>
#include <sys/ioctl.h>
#endif

#include "sample_comm.h"

#endif

#endif