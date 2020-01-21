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
/*��Ҫ������ǰ�İ汾��Ϣ                                                  */
/************************************************************************/
struct cp_version_s {
	int						serial;									/*��ʾ��ǰ�汾���к���ֵ��V0.1.0��Ӧ100*/
	char					version[CP_VERSION_BUFFER_LENGTH];		/*��ʾ��ǰ�汾�ַ������ݣ�����V0.1.0*/
	char					ver[CP_VERSION_BUFFER_LENGTH];			/*��ʾ��ǰ�����İ汾�ַ������ݣ�����cp_lib/V0.1.0*/
	char					name[CP_VERSION_BUFFER_LENGTH];			/*��ʾ��ǰ������ƣ�����cp_lib*/
	char					build_date[CP_VERSION_BUFFER_LENGTH];	/*��ʾ��ǰ��ı���ʱ�䣬����2016-08-30 16:49:00*/
	char					compiler[CP_VERSION_BUFFER_LENGTH];		/*��ʾ��ǰ�������汾��Ϣ������gcc 4.8.5*/
	char					host[CP_VERSION_HOST_BUFFER_LENGTH];	/*��ʾ��ǰ������������Ϣ������Red Hat 4.8.5-4*/
};



/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: cp_get_version
*
* ����˵��: ��ȡ��ǰ����İ汾��Ϣ
*
* ��    ��: cp_version_t * version						[in]����˵��
*
* �� �� ֵ: int
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-08-30 16:40:14
******************************************************************************************************/
int cp_get_version(cp_version_t *version);

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: cp_get_format_version
*
* ����˵��: ��ȡ�汾��Ϣ�ַ���
*
* ��    ��: char * buf					[out]�����ʽ���汾��Ϣ�����뻺��
* ��    ��: int len						[in]����˵��
*
* �� �� ֵ: char*
*           0  : ʧ�� 
*         �� 0  :�ɹ�
*
* ��    ע:���صĵ�ַΪ��Ϣ�ַ�������ʼ��ַ
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-08-31 14:50:27
******************************************************************************************************/
char* cp_get_format_version(char *buf, int len);


/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: cp_version_itoa
*
* ����˵��: ���汾�Ŵ�ʮ����ת��Ϊ���ʮ���Ʊ�ʾ
*
* ��    ��: int version					[in]��ʾ��ǰ�İ汾��
* ��    ��: char * buf					[out]��ʾ��ʽ�����
* ��    ��: int len						[in]����˵��
*
* �� �� ֵ: char*
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-08-31 15:50:26
******************************************************************************************************/
char* cp_version_itoa(int version, char *buf, int len);

#endif