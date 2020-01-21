/**************************************************************************

* Copyright: novigo

* Author: tianhuiming@novigo.com.cn

* Date：2016-5-12
        
* Description:

**************************************************************************/


#ifndef _CP_DEFINE_FUNC_INCLUDE_H_
#define _CP_DEFINE_FUNC_INCLUDE_H_



#define cp_malloc(size)								malloc(size)
#define cp_memcpy									memcpy
#define	cp_memset									memset
#define cp_free(p)									free(p)

#define	cp_sizeof									sizeof
#define cp_strlen									strlen
#define cp_atoi(p)									atoi(p)
#define cp_atof(p)									atof(p)

#define	cp_strcmp									strcmp
#define	cp_strncmp									strncmp
#define	cp_strcpy									strcpy
#define	cp_strncpy									strncpy

#define  cp_printf(fmt, ...)						printf((fmt), __VA_ARGS__)
#define	 cp_ary_size(ary)							(cp_sizeof(ary) / cp_sizeof((ary)[0]))


# ifdef WIN32

#define		cp_snprintf								_snprintf
#define		cp_sprintf								sprintf
#define		cp_sleep_msec(msec)						Sleep(msec)						//毫秒单位
#define		cp_srand()								srand((uint32_t)time(NULL));

#else

#define		cp_snprintf								snprintf
#define		cp_sprintf								sprintf
#define		cp_rand									rand
#define		cp_srand()								srand(time(NULL));
#define		cp_sleep_msec(msec)						usleep((msec) * 1000)			//毫秒单位

# endif


#define		cp_nbufstrncpy(dest, dest_buf_len, srcs, len) do {		\
		if ((dest_buf_len) > (len))	{								\
			if ((len) > 0)	{										\
				cp_strncpy((dest), (srcs), (len));					\
			}														\
		} else {													\
			cp_strncpy((dest), (srcs), (dest_buf_len));				\
		}															\
	}while(0);														\



#define	cp_abs(a, b)												(((a) > (b) ? ((a) - (b)) : ((b) - (a))))
#define cp_large(a, b)												(((a) > (b) ? (a) : (b)))
#define cp_small(a, b)												(((a) < (b) ? (a) : (b)))


#endif

