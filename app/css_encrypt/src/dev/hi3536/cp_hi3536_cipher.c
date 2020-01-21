/*******************************************************************************
*
*Copyright:novigo
*
*File name: cp_hi3536_cipher.c
*
*Author:fangzhenmu@novigo.com.cn
*
*Version: 1.0
*
*Date:2017/08/18
*
*Description: create (cp_hi3536_cipher.c)
*
*Others:
*
*History:
*******************************************************************************/

#include "cp_hi3536_cipher.h"


/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: cp_hi3536_cipher_create
*
* ����ȫ��: cp_hi3536_cipher_create
*
* ��������: public 
*
* ����˵��: ����cipher
*
* ��    ��: cp_hi3536_dev_t * hi3536_dev						[in/out]����˵��
* ��    ��: cp_hi3536_dev_configure_t * hdc						[in/out]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-8-18 16:13:04
********************************************************************************/
cp_int32_t cp_hi3536_cipher_create(cp_hi3536_dev_t *hi3536_dev, cp_hi3536_dev_configure_t *hdc)
{
	if (!hi3536_dev || !hdc) {
		return -1;
	}

	hi3536_dev->hcc = cp_palloc(hi3536_dev->pool, cp_sizeof(cp_hi3536_cipher_configure_t));
	if (!hi3536_dev->hcc) {
		return -2;
	}
	else {
		cp_memset(hi3536_dev->hcc, 0, cp_sizeof(cp_hi3536_cipher_configure_t));
		hi3536_dev->hcc->hi3536_dev = hi3536_dev;
	}


	return 0;
}

/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: cp_hi3536_cipher_destroy
*
* ����ȫ��: cp_hi3536_cipher_destroy
*
* ��������: public 
*
* ����˵��: ����cipher
*
* ��    ��: cp_hi3536_dev_t * hi3536_dev						[in/out]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-8-18 16:13:14
********************************************************************************/
cp_int32_t cp_hi3536_cipher_destroy(cp_hi3536_dev_t *hi3536_dev)
{
	if (!hi3536_dev || !hi3536_dev->hcc) {
		return -1;
	}

	cp_pfree(hi3536_dev->pool, hi3536_dev->hcc);
	return 0;
}

/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: cp_hi3536_cipher_init
*
* ����ȫ��: cp_hi3536_cipher_init
*
* ��������: public 
*
* ����˵��: ��ʼ��cipher
*
* ��    ��: cp_hi3536_dev_t * hi3536_dev						[in/out]����˵��
* ��    ��: cp_hi3536_dev_configure_t * hdc						[in/out]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-8-18 16:13:24
********************************************************************************/
cp_int32_t cp_hi3536_cipher_init(cp_hi3536_dev_t *hi3536_dev, cp_hi3536_dev_configure_t *hdc)
{

#if defined(CP_HI3536_CIPHER_MODULE)

	hi3536_dev->hcc->ctrl.enAlg = hdc->alg;
	hi3536_dev->hcc->ctrl.enWorkMode = hdc->work_mode;
	hi3536_dev->hcc->ctrl.enBitWidth = hdc->bit_width;
	hi3536_dev->hcc->ctrl.enKeyLen = hdc->key_length;
	if (hi3536_dev->hcc->ctrl.enWorkMode != HI_UNF_CIPHER_WORK_MODE_ECB) {
		hi3536_dev->hcc->ctrl.stChangeFlags.bit1IV = 1;  //must set for CBC , CFB mode
		//memcpy(hi3536_dev->hcc->ctrl.u32IV, u8IVBuf, 16);
	}

// 	if (HI_FALSE == isKeyByCA)
// 	{
// 		memcpy(hi3536_dev->hcc->ctrl.u32Key, u8KeyBuf, 16);
// 	}

#endif
	return 0;
}

/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: cp_hi3536_cipher_open
*
* ����ȫ��: cp_hi3536_cipher_open
*
* ��������: public 
*
* ����˵��: ��cipher
*
* ��    ��: cp_hi3536_dev_t * hi3536_dev						[in/out]����˵��
* ��    ��: cp_hi3536_cipher_configure_t * hcc						[in/out]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-8-18 16:13:33
********************************************************************************/
cp_int32_t cp_hi3536_cipher_open(cp_hi3536_dev_t *hi3536_dev, cp_hi3536_cipher_configure_t *hcc)
{
	cp_int32_t					tmp_ret_int = 0;
	cp_int32_t					tmp_int_input_addr_phy = 0;
	cp_int32_t					tmp_int_output_addr_phy = 0;
	cp_int32_t					tmp_int_test_data_length = 32;
	cp_int32_t					tmp_int_test_cached = 0;
	cp_char_t					*tmp_input_addr_vir = CP_NULL;
	cp_char_t					*tmp_output_addr_vir = CP_NULL;


	if (!hi3536_dev || !hcc) {
		return -1;
	}

#if defined(CP_HI3536_CIPHER_MODULE)
	tmp_ret_int = HI_UNF_CIPHER_Init();
	if (HI_SUCCESS != tmp_ret_int) {
		cp_module_log(error, hi3536_dev,
			"HI_UNF_CIPHER_Init() error. code[0x%x]", tmp_ret_int);
		return -2;
	}

	tmp_ret_int = HI_UNF_CIPHER_CreateHandle(&hi3536_dev->hcc->handle);
	if (HI_SUCCESS != tmp_ret_int) {
		HI_UNF_CIPHER_DeInit();

		cp_module_log(error, hi3536_dev,
			"HI_UNF_CIPHER_CreateHandle() error. code[0x%x]", tmp_ret_int);
		return -3;
	}

	tmp_int_input_addr_phy = (HI_U32)HI_MMZ_New(tmp_int_test_data_length, 0, NULL, "CIPHER_BufIn");
	if (!tmp_int_input_addr_phy) {
		HI_UNF_CIPHER_DestroyHandle(hi3536_dev->hcc->handle);
		HI_UNF_CIPHER_DeInit();
		return -4;
	}
	tmp_input_addr_vir = HI_MMZ_Map(tmp_int_input_addr_phy, tmp_int_test_cached);
	tmp_int_output_addr_phy = (HI_U32)HI_MMZ_New(tmp_int_test_data_length, 0, NULL, "CIPHER_BufOut");
	if (!tmp_int_output_addr_phy) {
		HI_UNF_CIPHER_DestroyHandle(hi3536_dev->hcc->handle);
		HI_UNF_CIPHER_DeInit();
		return -5;
	}
	tmp_output_addr_vir = HI_MMZ_Map(tmp_int_output_addr_phy, tmp_int_test_cached);

#endif

	return 0;
}

/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: cp_hi3536_cipher_encrypt
*
* ����ȫ��: cp_hi3536_cipher_encrypt
*
* ��������: public 
*
* ����˵��: ��ʼ����
*
* ��    ��: cp_hi3536_dev_t * hi3536_dev						[in/out]����˵��
* ��    ��: cp_hi3536_cipher_configure_t * hcc						[in/out]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-8-18 16:13:42
********************************************************************************/
cp_int32_t cp_hi3536_cipher_encrypt(cp_hi3536_dev_t *hi3536_dev, cp_hi3536_cipher_configure_t *hcc)
{
	return 0;
}

/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: cp_hi3536_cipher_close
*
* ����ȫ��: cp_hi3536_cipher_close
*
* ��������: public 
*
* ����˵��: �ر�cipher
*
* ��    ��: cp_hi3536_dev_t * hi3536_dev						[in/out]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-8-18 16:13:50
********************************************************************************/
cp_int32_t cp_hi3536_cipher_close(cp_hi3536_dev_t *hi3536_dev)
{
	return 0;
}