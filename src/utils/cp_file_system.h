/*******************************************************************************
*
*Copyright:novigo
*
*File name: cp_file_system.h
*
*Author:fangzhenmu@novigo.com.cn
*
*Version: 1.0
*
*Date:2017/08/21
*
*Description: create (cp_file_system.h)
*
*Others:
*
*History:
*******************************************************************************/

#ifndef _CP_FILE_SYSTEM_H_
#define _CP_FILE_SYSTEM_H_


#include <stdio.h>
#include <string.h>


//define file system diagonal
#ifdef WIN32
	#define cp_dir_diagonal								'\\'
#else
	#define cp_dir_diagonal								'//'
#endif



//获取当前可执行程序的路径
char *cp_get_exe_path(char *buf, int count);

//get current working directory
char *cp_get_work_dir(char *buf, int count);

//set current working directory
int cp_set_work_dir(const char *buf);

//make directory
int cp_mkdir_simple(const char *dir);


#endif //_CP_FILE_SYSTEM_H_


