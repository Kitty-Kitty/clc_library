/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-09-18

Description:

**************************************************************************/


#include <stdio.h>
#include <string.h>
#include "cp_safe_queue.h"
#include "cp_core.h"



#define		TEST_BUFFER_LENGTH								128
#define		TEST_PRODUCER_DATA_NUMBER						5000
#define		TEST_COMSUMER_THREAD_NUMBER						1



typedef struct test_data_info_struct					test_data_info_t;


struct test_data_info_struct
{
	int					key;
	char				buf[TEST_BUFFER_LENGTH];
};




int producer_proc(cp_safe_queue_t *tmp_sq);
int consumer_proc(cp_safe_queue_t *tmp_sq);


#ifdef WIN32
#include <windows.h>


#define		cp_sleep(ms)			Sleep(ms)



DWORD WINAPI ProducerThreadProc(LPVOID lpParam)
{
	return producer_proc((cp_safe_queue_t*)(lpParam));
}

DWORD WINAPI ConsumerThreadProc(LPVOID lpParam)
{
	return consumer_proc((cp_safe_queue_t*)(lpParam));
}

void startThreads(cp_safe_queue_t *tmp_sq)
{
	DWORD			ProducerThreadId;
	DWORD			ConsumerThreadId[TEST_COMSUMER_THREAD_NUMBER];
	HANDLE			ProducerThreadHandle;
	HANDLE			ConsumerThreadHandle[TEST_COMSUMER_THREAD_NUMBER];
	int				i = 0;


	ProducerThreadHandle = CreateThread(NULL, 0, ProducerThreadProc, tmp_sq, 0, &ProducerThreadId);


	for (i = 0; i < TEST_COMSUMER_THREAD_NUMBER; i++) {
		ConsumerThreadHandle[i] =
			CreateThread(NULL, 0, ConsumerThreadProc, tmp_sq, 0, &ConsumerThreadId[i]);
	}
}

int cp_thread_self()
{
	return GetCurrentThreadId();
}

#else

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define		cp_sleep(ms)			usleep(ms * 1000)


int cp_thread_self()
{
	return pthread_self();
}

void *producer_thrd_func(void *arg)
{
	producer_proc((cp_safe_queue_t *)arg);
}

void *consumer_thrd_func(void *arg)
{
	consumer_proc((cp_safe_queue_t *)arg);
}

void startThreads(void *arg)
{
	pthread_t		producer_tid;
	pthread_t		consumer_tid[TEST_COMSUMER_THREAD_NUMBER];
	int				i = 0;


	if (pthread_create(&producer_tid, NULL, producer_thrd_func, arg) != 0) {
		printf("create producer_thrd_func thread error!\n");
		exit(1);
	}

	for (i = 0; i < TEST_COMSUMER_THREAD_NUMBER; i++) {

		if (pthread_create(&consumer_tid[i], NULL, consumer_thrd_func, arg) != 0) {
			printf("create consumer_thrd_func thread error!\n");
		}
	}
}

#endif



int producer_proc(cp_safe_queue_t *tmp_sq)
{
	cp_timeval					tmp_tv = { 0, };
	test_data_info_t			*tmp_data_info = NULL;
	int							i = 0;



	for (i = 0; i < TEST_PRODUCER_DATA_NUMBER; i++)
	{
		tmp_data_info = (test_data_info_t*)malloc(sizeof(test_data_info_t));

		if (!tmp_data_info) {
			continue;
		}

		cp_gettimeofday(&tmp_tv, NULL);
		memset(tmp_data_info, 0, sizeof(test_data_info_t));
		tmp_data_info->key = i;
		sprintf(tmp_data_info->buf, "test buffer %d : %d\t%d", i, tmp_tv.tv_sec, tmp_tv.tv_usec);
		cp_safe_queue_push(tmp_sq, tmp_data_info);

		printf("push buffer: %d", i);
// 		if (!(i % 100)) {
// 			Sleep(100);
// 		}
	}
	return 0;
}

int consumer_proc(cp_safe_queue_t *tmp_sq)
{
	cp_timeval					tmp_tv = { 0, };
	test_data_info_t			*tmp_data_info = NULL;
	int							tmp_tid = 0;
	char						tmp_buf[TEST_BUFFER_LENGTH] = { 0, };



	tmp_tid = cp_thread_self();
	while (1)
	{
		tmp_data_info = cp_safe_queue_pop(tmp_sq);
		if (!tmp_data_info) {
			//Sleep(10);
			continue;
		}

		cp_gettimeofday(&tmp_tv, NULL);
		memset(tmp_buf, 0, TEST_BUFFER_LENGTH);
		sprintf(tmp_buf, "%d-->%d  %s : %d\t%d\r\n", 
			tmp_tid, tmp_data_info->key, tmp_data_info->buf, tmp_tv.tv_sec, tmp_tv.tv_usec);
		//OutputDebugString(tmp_data_info);
		printf("%s", tmp_buf);
		free(tmp_data_info);
	}
	return 0;
}



int main(int argc, char**argv)
{
	int								queue_bound_size = 6000;
	cp_safe_queue_t					*tmp_sq;


	tmp_sq = cp_create_general_safe_queue(cp_safe_queue_mode_qbss, queue_bound_size);
	if (!tmp_sq) {
		printf("cp_create_general_safe_queue() failed!\r\n");
		return -1;
	}
	startThreads(tmp_sq);

	while (1)
	{
		cp_sleep(10000);
	}
	return 0;
}