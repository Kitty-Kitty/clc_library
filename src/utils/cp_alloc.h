/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2014-2-11

Description:alloc defined

**************************************************************************/

#ifndef _CP_ALLOC_H_
#define _CP_ALLOC_H_





#include <stddef.h>
#include "cp_core.h"





#if defined(WIN32)

#define		cp_align_ptr(p, a)                                                   \
	(unsigned char *) (((uintptr_t) (p) + ((uintptr_t) a - 1)) & ~((uintptr_t) a - 1))

#else


//������Ҫע��32λ��64λ���������32λ��int �� long����32Ϊ���ȣ������64λ��long��64λ������ת��Ϊ���ֽ��м���ʱҲҪע��������
#define		cp_align_ptr(p, a)                                                   \
	(unsigned char *) (((unsigned long) (p) + ((unsigned long) a - 1)) & ~((unsigned long) a - 1))

#endif
#define		CP_ALIGNMENT   sizeof(unsigned long)






#if defined(__cplusplus)
extern "C"{
#endif


void *cp_memalign(size_t alignment, size_t size);
void *cp_alloc(size_t size);


#if defined(__cplusplus)
};
#endif





#endif /* _CP_PALLOC_H_ */










