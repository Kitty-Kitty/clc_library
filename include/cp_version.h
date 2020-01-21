/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-08-30

Description:

**************************************************************************/

#ifndef _CP_VERSION_INCLUDE_H_
#define _CP_VERSION_INCLUDE_H_


#include <stdio.h>



#define		cp_version								200
#define		CP_VERSION								"V0.2.0"
#define		CP_VER									"cp_lib/" CP_VERSION
#define		CP_VAR									"cp_lib"





#define		CP_VERSION_BUFFER_LENGTH				128
#define		CP_VERSION_HOST_BUFFER_LENGTH			256


typedef	struct cp_version_s							cp_version_t;
/************************************************************************/
/*主要描述当前的版本信息                                                  */
/************************************************************************/
struct cp_version_s {
	int						serial;									/*表示当前版本序列号数值，V0.1.0对应100*/
	char					version[CP_VERSION_BUFFER_LENGTH];		/*表示当前版本字符串内容，例如V0.1.0*/
	char					ver[CP_VERSION_BUFFER_LENGTH];			/*表示当前完整的版本字符串内容，例如cp_lib/V0.1.0*/
	char					name[CP_VERSION_BUFFER_LENGTH];			/*表示当前库的名称，例如cp_lib*/
	char					build_date[CP_VERSION_BUFFER_LENGTH];	/*表示当前库的编译时间，例如2016-08-30 16:49:00*/
	char					compiler[CP_VERSION_BUFFER_LENGTH];		/*表示当前编译器版本信息，例如gcc 4.8.5*/
	char					host[CP_VERSION_HOST_BUFFER_LENGTH];	/*表示当前编译主机的信息，例如Red Hat 4.8.5-4*/
};



/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: cp_get_version
*
* 函数说明: 获取当前编译的版本信息
*
* 参    数: cp_version_t * version						[in]参数说明
*
* 返 回 值: int
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-08-30 16:40:14
******************************************************************************************************/
int cp_get_version(cp_version_t *version);

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: cp_get_format_version
*
* 函数说明: 获取版本信息字符串
*
* 参    数: char * buf					[out]保存格式化版本信息的输入缓存
* 参    数: int len						[in]参数说明
*
* 返 回 值: char*
*           0  : 失败 
*         非 0  :成功
*
* 备    注:返回的地址为信息字符串的起始地址
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-08-31 14:50:27
******************************************************************************************************/
char* cp_get_format_version(char *buf, int len);


/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: cp_version_itoa
*
* 函数说明: 将版本号从十进制转换为点分十进制表示
*
* 参    数: int version					[in]表示当前的版本号
* 参    数: char * buf					[out]表示格式化输出
* 参    数: int len						[in]参数说明
*
* 返 回 值: char*
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-08-31 15:50:26
******************************************************************************************************/
char* cp_version_itoa(int version, char *buf, int len);

#endif