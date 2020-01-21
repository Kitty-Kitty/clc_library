/*******************************************************************************
*
*Copyright:novigo
*
*File name: cp_hi3536_dev_conf.h
*
*Author:fangzhenmu@novigo.com.cn
*
*Version: 1.0
*
*Date:2017/08/17
*
*Description: create (cp_hi3536_dev_conf.h)
*
*Others:
*
*History:
*******************************************************************************/

#ifndef _CP_HI3536_DEV_CONF_H_
#define _CP_HI3536_DEV_CONF_H_



#include "cp_core.h"
#include "cp_module_core.h"
#include "cp_hi3536_dev_conf_string.h"



#define CP_HI3536_DEV_ENCRYPT_KEY_LENGTH					128						//��ʾ��Կ�ĳ���


typedef struct cp_hi3536_dev_configure_s					cp_hi3536_dev_configure_t;



#pragma pack(1)

/************************************************************************/
/* hi3536�������                                                      */
/************************************************************************/
struct cp_hi3536_dev_configure_s
{
	cp_char_t						key[CP_HI3536_DEV_ENCRYPT_KEY_LENGTH];			//��ʾ������Կ
	cp_char_t						iv[CP_HI3536_DEV_ENCRYPT_KEY_LENGTH];			//��ʾ��ʼ����
	cp_int32_t						alg;											//��ʾ�����㷨,ȡֵ[0, 2]
	cp_int32_t						bit_width;										//��ʾ���ܻ���ܵ�λ��,ȡֵ[0, 3]
	cp_int32_t						work_mode;										//��ʾ����ģʽ,ȡֵ[0, 5]
	cp_int32_t						key_length;										//��ʾ��Կ����,ȡֵ[0, 4]
	cp_int32_t						change_flag_iv;									//��ʾ�������,ȡֵ[0, 1]
};

#pragma pack()



/************************************************************************/
/*���������ļ�                                                           */
/************************************************************************/
cp_int32_t	hi3536_dev_parse_configure(cp_module_t *module, cp_hi3536_dev_configure_t *hdc);




#endif //_CP_HI3536_DEV_CONF_H_


