/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_func.h"



cp_func_t *cp_func_create();
/*ģ�鴴���ӿڣ���ʾ����һ��ģ��*/
cp_int32_t init_func(cp_func_t *func, const cp_func_info_t *func_info);
/*ģ������нӿڣ���ģ��init֮�󣬻ᱻ����*/
cp_int32_t open_func(cp_func_t *func, const cp_func_info_t *func_info);
/*��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t read_func(cp_func_t *func, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t write_func(cp_func_t *func, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*�ر�ģ��*/
cp_int32_t close_func(cp_func_t *func);
/*�˳�ģ��*/
cp_int32_t exit_func(cp_func_t *func);
/*����ģ�����*/
cp_int32_t set_option_func(cp_func_t *func, cp_int32_t optname, const cp_void_t* optval);
cp_int32_t get_option_func(cp_func_t *func, cp_int32_t optname, cp_void_t* optval);




/*ģ�鴴���ӿڣ���ʾ����һ��ģ��*/
cp_int32_t init_func(cp_func_t *func, const cp_func_info_t *func_info)
{
	return 0;
}
/*ģ������нӿڣ���ģ��init֮�󣬻ᱻ����*/
cp_int32_t open_func(cp_func_t *func, const cp_func_info_t *func_info)
{
	return 0;
}
/*��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t read_func(cp_func_t *func, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}
/*дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t write_func(cp_func_t *func, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}
/*�ر�ģ��*/
cp_int32_t close_func(cp_func_t *func)
{
	return 0;
}
/*�˳�ģ��*/
cp_int32_t exit_func(cp_func_t *func)
{
	return 0;
}
/*����ģ�����*/
cp_int32_t set_option_func(cp_func_t *func, cp_int32_t optname, const cp_void_t* optval)
{
	return 0;
}
cp_int32_t get_option_func(cp_func_t *func, cp_int32_t optname, cp_void_t* optval)
{
	return 0;
}







