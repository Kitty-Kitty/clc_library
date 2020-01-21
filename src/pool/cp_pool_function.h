/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2017-03-26

Description:

**************************************************************************/

#ifndef _CP_POOL_FUNCTION_INCLUDE_H_
#define _CP_POOL_FUNCTION_INCLUDE_H_


typedef struct cp_pool_info_s					cp_pool_info_t;
//typedef	struct cp_pool_s						cp_pool_t;
typedef	struct cp_pool_handles_s				cp_pool_handles_t;
typedef	struct cp_pool_manager_handles_s		cp_pool_manager_handles_t;



//����һ���ڴ�أ�Ĭ����ʹ�ñ�׼�ڴ���ڴ�أ���mem_pool
cp_pool_t* cp_create_pool(const cp_app_t *app);
//����ָ�����͵��ڴ�أ�������info�е�type������ѡ����Ҫ�������ڴ��
cp_pool_t* cp_create_pool_ex(const cp_app_t *app, const cp_pool_info_t *info);
//����ָ�����ڴ��
cp_void_t cp_destroy_pool(const cp_pool_t *pool);
//�����ڴ�أ���Ҫ��ʵ�ֲ����ڴ���ͷ�
cp_void_t cp_reset_pool(const cp_pool_t *pool);

//�ڴ����루���룩
cp_void_t* cp_palloc(const cp_pool_t *pool, const size_t size);
//�ڴ����루�����룩
// cp_void_t *cp_pnalloc(cp_pool_t *pool, size_t size);
//�ڴ����루��գ�
cp_void_t* cp_pcalloc(const cp_pool_t *pool, const size_t size);
// cp_void_t *cp_pmemalign(cp_pool_t *pool, size_t size, size_t alignment);
cp_int32_t cp_pfree(const cp_pool_t *pool, const cp_void_t *p);



#endif