/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-09-18

Description:

**************************************************************************/


#include <stdio.h>
#include <string.h>
#include "cp_lockfree_queue.h"



#define		TEST_BUFFER_LENGTH								128
#define		TEST_PRODUCER_DATA_NUMBER						5000
#define		TEST_COMSUMER_THREAD_NUMBER						1



typedef struct test_data_info_struct					test_data_info_t;


struct test_data_info_struct
{
	int					key;
	char				buf[TEST_BUFFER_LENGTH];
};




int producer_proc(cp_lockfree_queue_t *fl_queue);
int consumer_proc(cp_lockfree_queue_t *fl_queue);


#ifdef WIN32
#include <windows.h>


#define		cp_sleep(ms)			Sleep(ms)



DWORD WINAPI ProducerThreadProc(LPVOID lpParam)
{
	return producer_proc((cp_lockfree_queue_t*)(lpParam));
}

DWORD WINAPI ConsumerThreadProc(LPVOID lpParam)
{
	return consumer_proc((cp_lockfree_queue_t*)(lpParam));
}


void startThreads(cp_lockfree_queue_t *fl_queue)
{
	DWORD			ProducerThreadId;
	DWORD			ConsumerThreadId[TEST_COMSUMER_THREAD_NUMBER];
	HANDLE			ProducerThreadHandle;
	HANDLE			ConsumerThreadHandle[TEST_COMSUMER_THREAD_NUMBER];
	int				i = 0;


	ProducerThreadHandle = CreateThread(NULL, 0, ProducerThreadProc, fl_queue, 0, &ProducerThreadId);


	for (i = 0; i < TEST_COMSUMER_THREAD_NUMBER; i++) {
		ConsumerThreadHandle[i] =
			CreateThread(NULL, 0, ConsumerThreadProc, fl_queue, 0, &ConsumerThreadId[i]);
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
	producer_proc((cp_lockfree_queue_t *)arg);
}

void *consumer_thrd_func(void *arg)
{
	consumer_proc((cp_lockfree_queue_t *)arg);
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



int producer_proc(cp_lockfree_queue_t *fl_queue)
{
	cp_lockfree_queue_t			*tmp_fl_queue = fl_queue;
	cp_lockfree_queue_element_t	*tmp_fl_queue_elem = NULL;
	test_data_info_t			*tmp_data_info = NULL;
	int							i = 0;



	for (i = 0; i < TEST_PRODUCER_DATA_NUMBER; i++)
	{
		tmp_fl_queue_elem =
			(cp_lockfree_queue_element_t*)malloc(sizeof(cp_lockfree_queue_element_t));
		tmp_data_info = (test_data_info_t*)malloc(sizeof(test_data_info_t));

		if (!tmp_fl_queue_elem || !tmp_data_info) {
			continue;
		}

		memset(tmp_data_info, 0, sizeof(test_data_info_t));
		tmp_data_info->key = i;
		sprintf(tmp_data_info->buf, "test buffer %d", i);

		cp_lockfree_queue_element_init(fl_queue, tmp_fl_queue_elem, &tmp_data_info->key, tmp_data_info);
		cp_lockfree_queue_push(tmp_fl_queue, tmp_fl_queue_elem, 0, NULL);
	}
	return 0;
}

int consumer_proc(cp_lockfree_queue_t *fl_queue)
{
	cp_lockfree_queue_t			*tmp_fl_queue = fl_queue;
	cp_lockfree_queue_element_t	*tmp_fl_queue_elem = NULL;
	test_data_info_t			*tmp_data_info = NULL;
	int							tmp_tid = 0;
	char						tmp_buf[TEST_BUFFER_LENGTH] = { 0, };



	tmp_tid = cp_thread_self();
	while (1)
	{
		tmp_fl_queue_elem = NULL;
		tmp_data_info = NULL;
		cp_lockfree_queue_pop(tmp_fl_queue, &tmp_fl_queue_elem);
		if (!tmp_fl_queue_elem) {
			//Sleep(10);
			continue;
		}
		tmp_data_info = (test_data_info_t*)(tmp_fl_queue_elem->value);

		memset(tmp_buf, 0, TEST_BUFFER_LENGTH);
		sprintf(tmp_buf, "%d-->%d  %s \r\n", tmp_tid, tmp_data_info->key, tmp_data_info->buf);
		//OutputDebugString(tmp_data_info);
		printf("%s", tmp_buf);
		free(tmp_data_info);
		free(tmp_fl_queue_elem);
	}
	return 0;
}



int main(int argc, char**argv)
{
	int								queue_bound_size = 6000;
	cp_lockfree_queue_t				tmp_fl_queue;


	//cp_lockfree_queue_init(&tmp_fl_queue, cp_lockfree_queue_mode_qbmm);
	cp_lockfree_queue_init(&tmp_fl_queue, cp_lockfree_queue_mode_qbss);
	cp_lockfree_queue_set_option(&tmp_fl_queue, cp_lockfree_queue_option_bounded, &queue_bound_size);
	cp_lockfree_queue_start(&tmp_fl_queue);
	startThreads(&tmp_fl_queue);

	while (1)
	{
		cp_sleep(10000);
	}
	return 0;
}