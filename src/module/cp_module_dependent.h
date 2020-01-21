/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-08-09

Description:

**************************************************************************/

#ifndef _CP_MODULE_DEPENDENT_INCLUDE_H_
#define _CP_MODULE_DEPENDENT_INCLUDE_H_



#include "cp_module_core.h"


/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: cp_add_manager_dependent_callback_handle
*
* ����˵��: �������ģ���Ļص�����
*
* ��    ��: cp_app_t *app													[in]��ʾ��ǰ�������app��Ϣ
* ��    ��: cp_module_manager_register_t* module_register					[in]��ʾģ�������ע����
* ��    ��: cp_uint32_t register_struct_size									[in]��ʾģ�������ע�����Ĵ�С
*
* �� �� ֵ: typedef cp_module_manager_register_t* (*
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-08-16 16:34:20
******************************************************************************************************/
typedef cp_module_manager_register_t* (*cp_add_manager_dependent_callback_handle)
	(cp_app_t *app, cp_module_manager_register_t* module_manager_register, cp_uint32_t register_struct_size);


 
 /******************************************************************************************************
 * ��Ȩ����: fz & novigo
 *
 * ��������: cp_add_module_dependent_callback_handle
 *
 * ����˵��: ���������Ĺ�����Ϣ
 *
 * ��    ��: cp_app_t *app													[in]��ʾ��ǰ�������app��Ϣ
 * ��    ��: cp_int32_t manager_type											[in]��ʾ��Ҫ����ӵ�ģ�������������
 * ��    ��: cp_module_register_t* module_register							[in]��ʾģ��ע����
 * ��    ��: cp_uint32_t register_struct_size								[in]��ʾģ��ע�����Ĵ�С
 *
 * �� �� ֵ: typedef cp_module_register_t* (*
 *           0  : �ɹ� 
 *         �� 0  :ʧ��
 *
 * ��    ע:����˵������
 *
 * ��    �ߣ�fz
 * �������䣺 fangzhenmu@novigo.com.cn
 * �������ڣ�2016-08-16 16:45:37
 ******************************************************************************************************/
typedef cp_module_register_t* (*cp_add_module_dependent_callback_handle)
(cp_app_t *app, cp_int32_t manager_type, cp_module_register_t* module_register, cp_uint32_t register_struct_size);



/************************************************************************/
/* ���崦���ģ���������������ں���                                     */
/************************************************************************/
#define CP_ROOT_MODULE_MANAGER_DEPENDENT_FUNCTION(app_flag)										\
	cp_void_t cp_##app_flag##_root_module_manager_dependent(cp_app_t *app);						\


/************************************************************************/
/* ���崦���ģ����������������������ϵ                                  */
/************************************************************************/
#define CP_ROOT_MODULE_MANAGER_DEPENDENT_BEGIN(app_flag)										\
	cp_void_t cp_##app_flag##_root_module_manager_dependent(cp_app_t *app){						\



/************************************************************************/
/* ����ִ�д����ģ�����������			                                */
/************************************************************************/
#define CP_ROOT_MODULE_MANAGER_DEPENDENT(app_flag, app)											\
	cp_##app_flag##_root_module_manager_dependent((cp_app_t*)(app));							\





/************************************************************************/
/* ���崦����ģ���������������ں���                                     */
/************************************************************************/
#define CP_SUB_MODULE_MANAGER_DEPENDENT_FUNCTION(app_flag)										\
	cp_void_t cp_##app_flag##_sub_module_manager_dependent(cp_app_t *app);						\


/************************************************************************/
/* ���崦����ģ����������������������ϵ                                  */
/************************************************************************/
#define CP_SUB_MODULE_MANAGER_DEPENDENT_BEGIN(app_flag)											\
	cp_void_t cp_##app_flag##_sub_module_manager_dependent(cp_app_t *app){						\


/************************************************************************/
/* ����ִ�д�����ģ�����������                                           */
/************************************************************************/
#define CP_SUB_MODULE_MANAGER_DEPENDENT(app_flag, app)											\
	cp_##app_flag##_sub_module_manager_dependent((cp_app_t*)(app));								\



/************************************************************************/
/* ���崦��ģ�麯������ں���                                             */
/************************************************************************/
#define CP_MODULE_DEPENDENT_FUNCTION(app_flag)													\
	cp_void_t cp_##app_flag##_module_dependent(cp_app_t *app);									\



/************************************************************************/
/* ���崦��ģ�麯�������������ϵ                                          */
/************************************************************************/
#define CP_MODULE_DEPENDENT_BEGIN(app_flag)														\
	cp_void_t cp_##app_flag##_module_dependent(cp_app_t *app){									\


/************************************************************************/
/* ����ִ�д���ģ�麯��													*/
/************************************************************************/
#define CP_MODULE_DEPENDENT(app_flag, app)														\
	cp_##app_flag##_module_dependent((cp_app_t*)(app));											\






/************************************************************************/
/* ��ӻ���ģ����������													*/
/* ��    �� : register_struct							[in]��ʾregister_struct,��ǰע��������������				*/
/* ��    �� : add_manager_dependent_handle				[in]��ʾadd_manager_dependent_handle,��ǰ�������ִ�еĺ���ָ��	*/
/* ��    �� : add_module_dependent_callback_handle		[in]��ʾadd_module_dependent_callback_handle,��ǰģ����Ӻ�Ļص�ģ��ע����		*/
/* ��    �� : MODULE_REGISTER_MARCO						[in]��ʾģ��ע�����ĺ�	*/
/************************************************************************/
#define CP_ADD_MANAGER_BASE_DEPENDENT(register_struct, add_manager_dependent_handle,											\
			add_module_dependent_callback_handle, ...)																			\
		do{																														\
				cp_module_manager_register_t *tmp_ret_register = CP_NULL;														\
				register_struct tmp_new_register[] = {__VA_ARGS__};																\
																																\
				if ((cp_add_manager_dependent_callback_handle)add_manager_dependent_handle) {									\
						tmp_ret_register = ((cp_add_manager_dependent_callback_handle)add_manager_dependent_handle)(app,		\
						(cp_module_manager_register_t*)&tmp_new_register[0], sizeof(register_struct));							\
						if ((cp_add_manager_dependent_callback_handle)add_module_dependent_callback_handle){					\
								((cp_add_manager_dependent_callback_handle)add_module_dependent_callback_handle)				\
										(app, tmp_ret_register, sizeof(register_struct));										\
						}																										\
				}																												\
		}while(0);																												\




/************************************************************************/
/* ��ӻ���ģ����������                                                      */
/* ��    �� : register_struct							[in]��ʾregister_struct,��ǰע��������������				*/
/* ��    �� : manager_type								[in]��ʾģ�������Ĺ�����������							*/
/* ��    �� : add_manager_dependent_handle				[in]��ʾadd_manager_dependent_handle,��ǰ�������ִ�еĺ���ָ��	*/
/* ��    �� : add_module_dependent_callback_handle		[in]��ʾadd_module_dependent_callback_handle,��ǰģ����Ӻ�Ļص�ģ��ע����		*/
/* ��    �� : MODULE_REGISTER_MARCO						[in]��ʾģ��ע�����ĺ�	*/
/************************************************************************/
#define CP_ADD_MODULE_BASE_DEPENDENT(register_struct, manager_type, add_module_dependent_handle,								\
			add_module_dependent_callback_handle, ...)																			\
		do {																													\
				cp_module_register_t *tmp_ret_register = CP_NULL;																\
				register_struct tmp_new_register[] = {__VA_ARGS__};																\
																																\
				if ((cp_add_module_dependent_callback_handle)add_module_dependent_handle) {										\
						tmp_ret_register = ((cp_add_module_dependent_callback_handle)add_module_dependent_handle)(app,			\
						manager_type, (cp_module_register_t*)&tmp_new_register[0], sizeof(register_struct));					\
						if ((cp_add_module_dependent_callback_handle)add_module_dependent_callback_handle){						\
								((cp_add_module_dependent_callback_handle)add_module_dependent_callback_handle)					\
										(app, manager_type, tmp_ret_register, sizeof(register_struct));							\
						}																										\
				}																												\
		}while(0);																												\




/************************************************************************/
/* ��Ӹ���������������                                                  */
/* register_struct : ��ʾע����������*/
/************************************************************************/
#define CP_ADD_ROOT_MANAGER_DEPENDENT(register_struct, add_module_dependent_callback_handle, MODULE_REGISTER_MARCO)				\
				CP_ADD_MANAGER_BASE_DEPENDENT(register_struct, cp_add_root_manager_dependent,									\
						add_module_dependent_callback_handle, MODULE_REGISTER_MARCO)											\



/************************************************************************/
/* ����ӹ�������������                                                  */
/************************************************************************/
#define CP_ADD_SUB_MANAGER_DEPENDENT(register_struct, add_module_dependent_callback_handle, MODULE_REGISTER_MARCO)				\
				CP_ADD_MANAGER_BASE_DEPENDENT(register_struct, cp_add_sub_manager_dependent,									\
						add_module_dependent_callback_handle, MODULE_REGISTER_MARCO)											\



/************************************************************************/
/* ���ģ����������                                                      */
/************************************************************************/
#define CP_ADD_MODULE_DEPENDENT(register_struct, manager_type, add_module_dependent_callback_handle, MODULE_REGISTER_MARCO)		\
				CP_ADD_MODULE_BASE_DEPENDENT(register_struct, manager_type, cp_add_module_dependent,							\
						add_module_dependent_callback_handle, MODULE_REGISTER_MARCO)											\



/************************************************************************/
/* ����ģ�����������                                                    */
/************************************************************************/
#define CP_MODULE_MANAGER_DEPENDENT_END()												}



/************************************************************************/
/* ����ģ�����                                                         */
/************************************************************************/
#define CP_MODULE_DEPENDENT_END()														}



/************************************************************************/
/* ���һ���յĹ�����ע������ӻص�����                                    */
/************************************************************************/
#define CP_MANAGER_DEPENDENT_CALLBACK_NULL			cp_add_manager_dependent_callback_null_handle

/************************************************************************/
/* ���һ���յ�ģ��ע������ӻص�����                                     */
/************************************************************************/
#define CP_MODULE_DEPENDENT_CALLBACK_NULL			cp_add_module_dependent_callback_null_handle




/************************************************************************/
/* �����ӡ��̷����������߹�ϵ                                             */
/* 1����                                                                */
/*    1.1��                                                             */
/*		   1.1.1��														*/
/*		       1.1.1...��											    */
/************************************************************************/

/************************************************************************/
/* ���������������                                                      */
/************************************************************************/
cp_module_manager_register_t* cp_add_root_manager_dependent(cp_app_t *app, 
	cp_module_manager_register_t *module_manager_register, cp_uint32_t register_struct_size);

/************************************************************************/
/* �����ӹ���������                                                      */
/************************************************************************/
cp_module_manager_register_t* cp_add_sub_manager_dependent(cp_app_t *app, 
	cp_module_manager_register_t* module_manager_register, cp_uint32_t register_struct_size);

/************************************************************************/
/* ����ģ������                                                          */
/************************************************************************/
cp_module_register_t* cp_add_module_dependent(cp_app_t *app, 
	cp_int32_t manager_type, cp_module_register_t *module_register, cp_uint32_t register_struct_size);





/************************************************************************/
/* �յĹ�����ע����������ӻص�����                                       */
/************************************************************************/
cp_module_manager_register_t* cp_add_manager_dependent_callback_null_handle(cp_app_t *app, 
	cp_module_manager_register_t *module_manager_register, cp_uint32_t register_struct_size);

/************************************************************************/
/* �յ�ģ��ע����������ӻص�����                                         */
/************************************************************************/
cp_module_register_t* cp_add_module_dependent_callback_null_handle
(cp_app_t *app, cp_int32_t manager_type, cp_module_register_t *module_register, cp_uint32_t register_struct_size);


#endif