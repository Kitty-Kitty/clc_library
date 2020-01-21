/**************************************************************************

* Copyright: tianhuiming@novigo.com.cn

* Author£ºtianhuiming@novigo.com.cn

* Date£º2016-4-21 15:59:42

* Description: cp defined

**************************************************************************/
#ifndef _CP_DEFINE_INCLUDE_H_
#define _CP_DEFINE_INCLUDE_H_




#if defined(WIN32)
	#define		cp_inline					__inline

	/* Windows - set up dll import/export decorators. */
	# if defined(BUILDING_CP_LIB_SHARED)
		/* Building shared library. */
		#define cp_extern __declspec(dllexport)
	# elif defined(USING_CP_LIB_SHARED)
		/* Using shared library. */
		#define cp_extern __declspec(dllimport)
	# else
		/* Building static library. */
		#ifndef cp_extern
			#define cp_extern /* nothing */
		#endif
	# endif

#else 

	#define		cp_inline					inline

	#if __GNUC__ >= 4
		#define cp_extern __attribute__((visibility("default")))
	#else
		#define cp_extern /* nothing */
	#endif

#endif //WIN32



#define		cp_static					static
#define		cp_offsetof					offsetof



#ifndef		__GNUC__
#define     __attribute__(x)			/*NOTHING*/
#endif



#define		CP_ERROR					0
#define		CP_OK						1



#endif



