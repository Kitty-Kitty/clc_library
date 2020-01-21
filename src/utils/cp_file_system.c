/*******************************************************************************
*
*Copyright:novigo
*
*File name: cp_file_system.c
*
*Author:fangzhenmu@novigo.com.cn
*
*Version: 1.0
*
*Date:2017/08/21
*
*Description: create (cp_file_system.c)
*
*Others:
*
*History:
*******************************************************************************/

#if defined(WIN32)

//  
// _WIN32_WINNT version constants  
//  
// #define _WIN32_WINNT_NT4                    0x0400 // Windows NT 4.0  
// #define _WIN32_WINNT_WIN2K                  0x0500 // Windows 2000  
// #define _WIN32_WINNT_WINXP                  0x0501 // Windows XP  
// #define _WIN32_WINNT_WS03                   0x0502 // Windows Server 2003  
// #define _WIN32_WINNT_WIN6                   0x0600 // Windows Vista  
// #define _WIN32_WINNT_VISTA                  0x0600 // Windows Vista  
// #define _WIN32_WINNT_WS08                   0x0600 // Windows Server 2008  
// #define _WIN32_WINNT_LONGHORN               0x0600 // Windows Vista  
// #define _WIN32_WINNT_WIN7                   0x0601 // Windows 7  
// #define _WIN32_WINNT_WIN8                   0x0602 // Windows 8  
// #define _WIN32_WINNT_WINBLUE                0x0603 // Windows 8.1  
// #define _WIN32_WINNT_WINTHRESHOLD           0x0A00 // Windows 10  
// #define _WIN32_WINNT_WIN10                  0x0A00 // Windows 10 

#ifdef _WIN32_WINNT
#undef _WIN32_WINNT
#endif
#define _WIN32_WINNT			0x0502
#define WIN32_LEAN_AND_MEAN     // Exclude rarely-used stuff from Windows headers
#include <windows.h>
#include <strsafe.h>
#include <WinBase.h>
#include <Psapi.h>
#include <direct.h>
#include <io.h>

#define CP_FS_ACCESS				_access  
#define CP_FS_MKDIR(a)				_mkdir((a))
#define CP_FS_STRDUP(a)				_strdup((a))

#else

#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/timex.h>
#include <sys/reboot.h>
#include <sys/types.h>
#include <sys/stat.h>

#define CP_FS_ACCESS				access
#define CP_FS_MKDIR(a)				mkdir((a),0755)
#define CP_FS_STRDUP(a)				strdup((a))

#endif


#include "cp_file_system.h"



char *cp_get_exe_path(char *buf, int count)
{
#if defined(WIN32)
	if (!GetModuleFileName(NULL, buf, count)) {
		TCHAR buffer[1024] = { 0, };
		DWORD dwErrorCode = GetLastError();

		FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			0,
			dwErrorCode,
			0,
			buffer,
			1024,
			0);
		//cp_printf("get GetModuleFileName() error. reason:[ %d: %s]", dwErrorCode, buffer);
	}
#else

	int i;
	int rslt = readlink("/proc/self/exe", buf, count - 1);
	if (rslt < 0 || (rslt >= count - 1))
	{
		return NULL;
	}

	buf[rslt] = '\0';
	for (i = rslt; i >= 0; i--)
	{
		if (buf[i] == '/')
		{
			buf[i + 1] = '\0';
			break;
		}
	}

#endif

	return buf;
}

//get current working directory
char *cp_get_work_dir(char *buf, int count)
{
#if defined(WIN32)

	if (!GetCurrentDirectory(count, buf)) {
		TCHAR buffer[1024] = { 0, };
		DWORD dwErrorCode = GetLastError();

		FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			0,
			dwErrorCode,
			0,
			buffer,
			1024,
			0);
		//cp_printf("get GetCurrentDirectory() error. reason:[ %d: %s]", dwErrorCode, buffer);
	}

#else

	getcwd(buf, count);

#endif

	return buf;
}

//set current working directory
int cp_set_work_dir(const char *buf)
{
	int				tmp_ret_int = 0;


#if defined(WIN32)
	//设置dll目录
	if (!SetDllDirectory((LPCSTR)buf)) {
		TCHAR buffer[1024] = { 0, };
		DWORD dwErrorCode = GetLastError();

		FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			0,
			dwErrorCode,
			0,
			buffer,
			1024,
			0);
		//cp_printf("set SetDllDirectory() error. reason:[ %d: %s]", dwErrorCode, buffer);
		//return -1;
		tmp_ret_int = -1;
	}

	//设置工作目录
	if (!SetCurrentDirectory(TEXT(buf))) {
		TCHAR buffer[1024] = { 0, };
		DWORD dwErrorCode = GetLastError();

		FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			0,
			dwErrorCode,
			0,
			buffer,
			1024,
			0);
		//cp_printf("set SetCurrentDirectory() error. reason:[ %d: %s]", dwErrorCode, buffer);
		tmp_ret_int = -2;
	}

#else

	tmp_ret_int = chdir(buf);

#endif

	return tmp_ret_int;
}

int cp_mkdir_simple(const char *dir)
{
	int				i = 0;
	int				tmp_ret_int = 0;
	int				tmp_int_length = 0;
	char			*tmp_psz_dir = NULL;

	if (NULL == dir) {
		return 0;
	}

	tmp_psz_dir = CP_FS_STRDUP(dir);
	if (!tmp_psz_dir) {
		return 0;
	}
	tmp_int_length = strlen(tmp_psz_dir);

	// 创建中间目录
	for (i = 0; i < tmp_int_length; i++)
	{
		if (tmp_psz_dir[i] == '\\' || tmp_psz_dir[i] == '/')
		{
			tmp_psz_dir[i] = '\0';

			//如果不存在,创建
			tmp_ret_int = CP_FS_ACCESS(tmp_psz_dir, 0);
			if (tmp_ret_int != 0)
			{
				tmp_ret_int = CP_FS_MKDIR(tmp_psz_dir);
				if (tmp_ret_int != 0)
				{
					return -1;
				}
			}
			//支持linux,将所有\换成/
			tmp_psz_dir[i] = '/';
		}
	}

	tmp_ret_int = CP_FS_MKDIR(tmp_psz_dir);
	free(tmp_psz_dir);

	return tmp_ret_int;
}




