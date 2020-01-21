/*******************************************************************************
*
*Copyright:novigo
*
*File name: cp_hi3536_cipher.h
*
*Author:fangzhenmu@novigo.com.cn
*
*Version: 1.0
*
*Date:2017/08/18
*
*Description: create (cp_hi3536_cipher.h)
*
*Others:
*
*History:
*******************************************************************************/

#ifndef _CP_HI3536_CIPHER_H_
#define _CP_HI3536_CIPHER_H_



#include "cp_hi3536_dev_core.h"



//#define	CP_HI3536_CIPHER_MODULE		1
//typedef struct cp_hi3536_cipher_configure_s					cp_hi3536_cipher_configure_t;


#if defined(CP_HI3536_CIPHER_MODULE)
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <linux/fb.h>

#include "hi_type.h"
#include "hi_unf_cipher.h"
#include "hi_mmz_api.h"
#endif




#pragma pack(1)

/************************************************************************/
/* hi3536�������                                                      */
/************************************************************************/
struct cp_hi3536_cipher_configure_s
{
	cp_module_t						*hi3536_dev;									//��ʾhi3536�豸
#if defined(CP_HI3536_CIPHER_MODULE)
	HI_HANDLE						handle;											//��ʾ��ȡCIPHER ���
	HI_UNF_CIPHER_CTRL_S			ctrl;											//��ʾCIPHER ������Ϣ�ṹ��
#endif
};

#pragma pack()

//����cipher
cp_int32_t cp_hi3536_cipher_create(cp_hi3536_dev_t *hi3536_dev, cp_hi3536_dev_configure_t *hdc);

//����cipher
cp_int32_t cp_hi3536_cipher_destroy(cp_hi3536_dev_t *hi3536_dev);

//��ʼ��cipher
cp_int32_t cp_hi3536_cipher_init(cp_hi3536_dev_t *hi3536_dev, cp_hi3536_dev_configure_t *hdc);

//��cipher
cp_int32_t cp_hi3536_cipher_open(cp_hi3536_dev_t *hi3536_dev, cp_hi3536_cipher_configure_t *hcc);

//��ʼ����
cp_int32_t cp_hi3536_cipher_encrypt(cp_hi3536_dev_t *hi3536_dev, cp_hi3536_cipher_configure_t *hcc);

//�ر�cipher
cp_int32_t cp_hi3536_cipher_close(cp_hi3536_dev_t *hi3536_dev);


#endif //_CP_HI3536_CRYPT_H_


