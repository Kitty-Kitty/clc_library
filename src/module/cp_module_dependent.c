/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-08-09

Description:

**************************************************************************/


#include "cp_include.h"
#include "cp_module_dependent.h"





/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: cp_add_root_manager_dependent
*
* ����˵��: ���������������
*
* ��    ��: cp_module_manager_t * app						[in]����˵��
* ��    ��: cp_uint32_t register_struct_size						[in]����˵��
* ��    ��: cp_module_manager_register_t * module_manager_register						[in]����˵��
*
* �� �� ֵ: cp_module_manager_register_t*
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-08-16 14:52:29
******************************************************************************************************/
cp_module_manager_register_t* cp_add_root_manager_dependent
	(cp_app_t *app, cp_module_manager_register_t* module_manager_register, cp_uint32_t register_struct_size) {
	cp_int32_t										ret_int = 0;
	cp_module_manager_register_t					*tmp_mmr = CP_NULL;




	//�ж����ݺϷ���
	if (!app || !register_struct_size || !module_manager_register) {
		return CP_NULL;
	}
	//����һ����������ע����
	ret_int = cp_manager_set_root_manager_register(app, module_manager_register, register_struct_size);
	if (ret_int) {
		return CP_NULL;
	}
	return (cp_module_manager_register_t*)cp_manager_get_root_manager_register(app, module_manager_register->type);
}


/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: cp_add_sub_manager_dependent
*
* ����˵��: �����ӹ���������
*
* ��    ��: cp_module_manager_t * app						[in]����˵��
* ��    ��: cp_uint32_t register_struct_size						[in]����˵��
* ��    ��: cp_module_manager_register_t * module_manager_register						[in]����˵��
*
* �� �� ֵ: cp_module_manager_register_t*
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-08-16 14:52:44
******************************************************************************************************/
cp_module_manager_register_t* cp_add_sub_manager_dependent
	(cp_app_t *app, cp_module_manager_register_t* module_manager_register, cp_uint32_t register_struct_size) {
	cp_int32_t										ret_int = 0;
	cp_module_manager_t								*tmp_root_manager = CP_NULL;
	cp_module_manager_register_t					*tmp_mmr = CP_NULL;
	cp_char_t										tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };




	//�ж����ݺϷ���
	if (!app || !register_struct_size || !module_manager_register) {
		return CP_NULL;
	}
	tmp_root_manager = cp_manager_get_root_manager(app, module_manager_register->type);
	if (!tmp_root_manager) {
		cp_app_log(error, app, "cp_add_sub_manager_dependent() error. not found root manager of [%s] register_struct_size[%d].",
			cp_print_manager_register_info(module_manager_register, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH),
			register_struct_size);
		return CP_NULL;
	}
	//����һ����������ע����
	ret_int = cp_manager_set_sub_manager_register(tmp_root_manager, module_manager_register, 1, register_struct_size);
	if (ret_int) {
		cp_app_log(error, app, "cp_add_sub_manager_dependent() error. set_sub_manager_register() error of [%s] register_struct_size[%d].",
			cp_print_manager_register_info(module_manager_register, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH),
			register_struct_size);
		return CP_NULL;
	}
	return (cp_module_manager_register_t*)cp_manager_get_sub_manager_register(tmp_root_manager, module_manager_register->type);
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: cp_add_module_dependent
*
* ����˵��: ���ģ��������Ϣ
*
* ��    ��: cp_module_manager_t * app						[in]��ʾ��Ҫ��ӵ�ģ�������
* ��    ��: cp_uint32_t register_struct_size						[in]��ʾע�����Ĵ�С
* ��    ��: cp_module_manager_register_t * module_manager_register				[in]��ʾ��Ҫ��ӵ�ע����
*
* �� �� ֵ: cp_module_manager_register_t*
*           0  : ʧ��
*         �� 0  :�ɹ� 
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-08-09 15:45:57
******************************************************************************************************/
cp_module_register_t* cp_add_module_dependent(cp_app_t *app, 
	cp_int32_t manager_type, cp_module_register_t* module_register, cp_uint32_t register_struct_size) {
	cp_int32_t										ret_int = 0;
	cp_module_manager_info_t						tmp_module_manager_info;
	cp_module_manager_t								*tmp_module_manager = CP_NULL;




	//�ж����ݺϷ���
	if (!app || !register_struct_size || !module_register) {
		return CP_NULL;
	}
	//��ȡģ�������
	CP_MODULE_MANAGER_INFO_SET_TYPE(&tmp_module_manager_info, manager_type);
	tmp_module_manager = cp_get_manager(app, &tmp_module_manager_info);
	if (!tmp_module_manager) {
		return CP_NULL;
	}
	//����һ��ģ��ע����
	ret_int = cp_manager_set_module_register(tmp_module_manager, module_register, 1, register_struct_size);
	if (ret_int) {
		return CP_NULL;
	}
	return (cp_module_register_t*)cp_manager_get_module_register(tmp_module_manager, module_register->type);
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: cp_add_manager_dependent_callback_null_handle
*
* ����˵��: һ���յ������ص�����
*
* ��    ��: cp_module_manager_t * app												[in]����˵��
* ��    ��: cp_uint32_t register_struct_size											[in]����˵��
* ��    ��: cp_module_manager_register_t * module_manager_register					[in]����˵��
*
* �� �� ֵ: cp_module_manager_register_t*
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-08-16 15:30:17
******************************************************************************************************/
cp_module_manager_register_t* cp_add_manager_dependent_callback_null_handle(cp_app_t *app, 
	cp_module_manager_register_t* module_manager_register, cp_uint32_t register_struct_size) {
	return module_manager_register;
}


/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: cp_add_module_dependent_callback_null_handle
*
* ����˵��: ���������Ĺ�����Ϣ
*
* ��    ��: cp_app_t * app										[in]��Ҫ�������app
* ��    ��: cp_int32_t manager_type								[in]����˵��
* ��    ��: cp_module_register_t * module_register				[in]����˵��
* ��    ��: cp_uint32_t register_struct_size						[in]����˵��
*
* �� �� ֵ: cp_module_register_t*
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-08-16 17:00:50
******************************************************************************************************/
cp_module_register_t* cp_add_module_dependent_callback_null_handle
(cp_app_t *app, cp_int32_t manager_type, cp_module_register_t* module_register, cp_uint32_t register_struct_size) {
	return module_register;
}