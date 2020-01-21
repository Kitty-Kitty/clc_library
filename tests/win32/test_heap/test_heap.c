/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/



#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include "cp_min_heap.h"






struct cp_min_heap				m_min_heap;


struct cp_min_heap_data_struct
{
	struct cp_min_heap_node			node;
	int							index;
	int							value;
};





int value_compare_fn(const struct cp_min_heap_node* a, const struct cp_min_heap_node* b)
{
	struct cp_min_heap_data_struct					*tmp_a;
	struct cp_min_heap_data_struct					*tmp_b;


	tmp_a = cp_min_heap_data(a, struct cp_min_heap_data_struct, node);
	tmp_b = cp_min_heap_data(b, struct cp_min_heap_data_struct, node);

	if (tmp_a->index < tmp_b->index)
	{
		return 1;
	}

	return 0;
}

int main(int argc, char** argv) 
{
	struct cp_min_heap_data_struct				*new_data;


	cp_min_heap_init(&m_min_heap);
	srand(time(0));

	printf("------------------insert node data--------------------------------\r\n");
	for (int i = 0; i < 30; i++)
	{
		new_data = (struct cp_min_heap_data_struct*)malloc(sizeof(struct cp_min_heap_data_struct));
		memset(new_data, 0, sizeof(struct cp_min_heap_data_struct));
		new_data->index = rand() % 100;
		new_data->value = rand() % 100;

		cp_min_heap_insert(&m_min_heap, &new_data->node, value_compare_fn);
		printf("%d : %d\r\n", new_data->index, new_data->value);
	}

	printf("\r\n\r\n------------------printf node data--------------------------------\r\n");
	for (int i = 0; i < 30; i++)
	{
		new_data = cp_min_heap_min(&m_min_heap);
		if (new_data)
		{
			printf("%d : %d\r\n", new_data->index, new_data->value);
			cp_min_heap_remove(&m_min_heap, new_data, value_compare_fn);
		}
	}
	return 0;
}
