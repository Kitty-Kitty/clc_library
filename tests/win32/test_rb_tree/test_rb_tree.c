
/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-13

Description:

**************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "cp_tree_ex.h"



#define				TEST_RB_TREE_MAX_SIZE						2



typedef struct cp_rb_channel_s
{
	int										key;						//key
	int										value;						//key
	CP_RB_ENTRY(cp_rb_channel_s)			tree_entry;
}cp_rb_channel_t;


CP_RB_HEAD(cp_rb_channel_tree_s, cp_rb_channel_s);


static int rb_channel_compare(cp_rb_channel_t* rb_chl1, cp_rb_channel_t* rb_chl2) {
	if (rb_chl1->key < rb_chl2->key) return -1;
	if (rb_chl1->key > rb_chl2->key) return 1;

	return 0;
}

CP_RB_GENERATE_STATIC(cp_rb_channel_tree_s, cp_rb_channel_s, tree_entry, rb_channel_compare);


int main(int argc, char** argv) 
{
	int								i = 0;
	int								min = TEST_RB_TREE_MAX_SIZE;
	int								max = 0;
	struct cp_rb_channel_tree_s		rb_root = CP_RB_INITIALIZER(rb_root);
	struct cp_rb_channel_s			rb_chl[TEST_RB_TREE_MAX_SIZE] = { 0, };
	struct cp_rb_channel_s			*min_rb_chl = NULL;
	struct cp_rb_channel_s			*max_rb_chl = NULL;



	for (i = 0; i < TEST_RB_TREE_MAX_SIZE; i++) {
		//rb_chl[i].key = rand() % TEST_RB_TREE_MAX_SIZE;
		rb_chl[i].key = rand();
		rb_chl[i].value = rb_chl[i].key;
		CP_RB_INSERT(cp_rb_channel_tree_s, &rb_root, &rb_chl[i]);
		printf("insert key[%d]  value[%d]\r\n", rb_chl[i].key, rb_chl[i].value);
		if (min > rb_chl[i].key) {
			min = rb_chl[i].key;
		}

		if (max < rb_chl[i].key) {
			max = rb_chl[i].key;
		}
	}

	printf("min node[%d]  max node[%d]\r\n", min, max);

	min_rb_chl = CP_RB_MIN(cp_rb_channel_tree_s, &rb_root);
	max_rb_chl = CP_RB_MAX(cp_rb_channel_tree_s, &rb_root);

	printf("tree min[%d]  max[%d]\r\n", min_rb_chl->key, max_rb_chl->key);

	CP_RB_REMOVE(cp_rb_channel_tree_s, &rb_root, min_rb_chl);
	CP_RB_REMOVE(cp_rb_channel_tree_s, &rb_root, max_rb_chl);


	min_rb_chl = CP_RB_MIN(cp_rb_channel_tree_s, &rb_root);
	max_rb_chl = CP_RB_MAX(cp_rb_channel_tree_s, &rb_root);

	printf("tree min[%d]  max[%d]\r\n", min_rb_chl->key, max_rb_chl->key);

	CP_RB_REMOVE(cp_rb_channel_tree_s, &rb_root, min_rb_chl);
	CP_RB_REMOVE(cp_rb_channel_tree_s, &rb_root, max_rb_chl);


	min_rb_chl = CP_RB_MIN(cp_rb_channel_tree_s, &rb_root);
	max_rb_chl = CP_RB_MAX(cp_rb_channel_tree_s, &rb_root);

	printf("tree min[%d]  max[%d]\r\n", min_rb_chl->key, max_rb_chl->key);

	return 0;
}

