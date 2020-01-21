
/*
 * Copyright (C) Igor Sysoev
 * Copyright (C) Nginx, Inc.
 */


#include "cp_array.h"


//��ʼ������
cp_int32_t cp_array_init(cp_array_t *ary, void *buffer, size_t size, size_t count)
{
	ary->elts = buffer;
	ary->nelts = 0;
	ary->size = size;
	ary->nalloc = count;

	return 0;
}
//�����ռ��ʼ������
cp_int32_t cp_array_malloc_init(cp_array_t *ary, size_t size, size_t count)
{
	void					*buffer = NULL;

	buffer = malloc(size * count);
	if (!buffer) {
		return -1;
	}
	memset(buffer, 0, size * count);
	return cp_array_init(ary, buffer, size, count);
}

//��ʾ��indexλ�ò���elts��ָ����ڴ�����
cp_int32_t cp_array_set(cp_array_t *ary, void *elts, size_t index)
{
	char			*tmp_elts;



	if (index > (ary->nalloc - 1)) {
		return -1;
	}

	tmp_elts = (char*)(ary->elts) + (index * ary->size);
	memcpy(tmp_elts, elts, ary->size);
	++(ary->nelts);
	return 0;
}

//��ʾ��ȡָ��λ�õ�ָ
void *cp_array_get(const cp_array_t *ary, size_t index)
{
	if (index > (ary->nalloc - 1)) {
		return NULL;
	}

	return (char*)(ary->elts) + (index * ary->size);
}

//ɾ��һ��ָ���ڵ�����
cp_int32_t cp_array_remove(cp_array_t *ary, size_t index)
{
	char			*tmp_elts;



	if (index > (ary->nalloc - 1)) {
		return -1;
	}

	tmp_elts = (char*)(ary->elts) + (index * ary->size);
	memset(tmp_elts, 0, ary->size);
	--(ary->nelts);
	return 0;
}

//������нڵ�����
cp_int32_t cp_array_clear(cp_array_t *ary)
{
	memset(ary->elts, 0, ary->nalloc * ary->size);
	ary->nelts = 0;
	return 0;
}

//�ͷŷ���Ŀռ�
cp_int32_t cp_array_malloc_destroy(cp_array_t *ary)
{
	if (!ary || !ary->elts) {
		return -1;
	}

	free(ary->elts);
	return 0;
}