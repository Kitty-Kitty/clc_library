/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_BUF_INCLUDE_H_
#define _CP_BUF_INCLUDE_H_


#include <stdio.h>
#include <string.h>
#include "cp_typedef.h"




typedef		struct cp_buf_s			 cp_buf_t;



struct cp_buf_s {
	cp_uchar_t				*pos;
	cp_uchar_t				*last;
	cp_uchar_t				*start;         /* start of buffer */
	cp_uchar_t				*end;           /* end of buffer */

};

#define cp_buf_get_start(buf)								((buf)->start)

#define cp_buf_get_pos(buf)									((buf)->pos)

#define cp_buf_get_last(buf)								((buf)->last)

#define cp_buf_get_size(buf)								((buf)->end - (buf)->start)

#define cp_buf_get_free_size(buf)							((buf)->end - (buf)->last)

#define cp_buf_get_length(buf)								((buf)->last - (buf)->pos)

#define cp_buf_memzero(buf)									memset((buf)->start, 0, ((buf)->end - (buf)->start));


#define cp_buf_init(buf)					do {			\
		(buf)->start = NULL;								\
		(buf)->pos = (buf)->start;							\
		(buf)->last = (buf)->start;							\
		(buf)->end = (buf)->start;							\
	} while (/*CONSTCOND*/ 0)								\



#define cp_buf_assemble(buf, mem, size)		do {			\
		(buf)->start = (cp_uchar_t*)(mem);					\
		(buf)->pos = (buf)->start;							\
		(buf)->last = (buf)->start;							\
		(buf)->end = (buf)->start + (size);					\
	} while (/*CONSTCOND*/ 0)								\




#define cp_buf_create(buf, size) do{						\
		(buf) = (cp_buf_t*)cp_malloc(sizeof(cp_buf_t));		\
		(buf)->start = (cp_uchar_t*)cp_malloc(size);		\
		(buf)->pos = (buf)->start;							\
		(buf)->last = (buf)->start;							\
		(buf)->end = (buf)->start + (size);					\
	}while(0);												\


#define cp_buf_clear(buf) do {								\
		(buf)->pos = (buf)->start;							\
		(buf)->last = (buf)->start;							\
	}while(0);												\


#define cp_buf_destroy(buf)  do{if (buf){cp_free(buf);}}while(0)



#define  cp_buf_strcat(dst_buf, data, size) do {			\
		if((data) && (size) > 0 && (size) <= cp_buf_get_free_size(dst_buf)) {							\
			memcpy((dst_buf)->last, (data), (size));		\
			(dst_buf)->last += (size);						\
		}													\
	}while (0)												\



#define cp_buf_position(buf, size) do {						\
		(buf)->last = (buf)->last + (size);					\
	}while(0);												\


#endif