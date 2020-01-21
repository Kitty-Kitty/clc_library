/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-24

Description:

**************************************************************************/

#ifndef _CP_HI3531_DEV_INCLUDE_INCLUDE_H_
#define _CP_HI3531_DEV_INCLUDE_INCLUDE_H_



#include "cp_player_platform_include.h"
//#define			CP_HI3531_DEV_MODE					1
//#define			CP_HI3531_DEV_PRINT_LOG				1
// #ifdef WIN32
//#define			CP_HI3531_DEV_DEBUG			1
// #endif



#if defined(CP_HI3531_DEV_MODE)

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

#include "hi_common.h"
#include "hi_comm_sys.h"
#include "hi_comm_vb.h"
#include "hi_comm_vpss.h"
#include "hi_comm_vdec.h"
#include "hi_comm_vo.h"
#include "hi_defines.h"

#include "mpi_sys.h"
#include "mpi_vb.h"
#include "mpi_vpss.h"
#include "mpi_vdec.h"

#endif


#define CP_ALIGN_BACK(x, a)              ((a) * (((x) / (a))))



#endif
