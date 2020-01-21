/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef _CP_TYPEDEF_INCLUDE_H_
#define _CP_TYPEDEF_INCLUDE_H_


#include <stdlib.h>


#define CP_NULL					NULL
#define CP_MAX_INT				0X7FFFFFFF


typedef	void					cp_void_t;
typedef	char					cp_int8_t;
typedef unsigned char			cp_uint8_t;
typedef	short					cp_int16_t;
typedef unsigned short			cp_uint16_t;
typedef	int						cp_int32_t;
typedef unsigned int			cp_uint32_t;
typedef	char					cp_char_t;
typedef	unsigned char			cp_uchar_t;
typedef long long				cp_int64_t;
typedef unsigned long long		cp_uint64_t;
//typedef enum cp_bool_e		cp_bool_t;
typedef	float					cp_float_t;
typedef short					cp_short_t;
typedef	double					cp_double_t;

typedef enum cp_bool_enum
{
	cp_false = 0,
	cp_true = 1,
}cp_bool_t;

typedef struct sockaddr_in		cp_sockaddr_in;
typedef struct timeval			cp_timeval;





#endif
