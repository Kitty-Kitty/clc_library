/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_hook.h"



cp_hook_t *cp_hook_create();

/*ģ�鴴���ӿڣ���ʾ����һ��ģ��*/
cp_int32_t init_hook(cp_hook_t *hook, const cp_hook_info_t *hook_info);
/*ģ������нӿڣ���ģ��init֮�󣬻ᱻ����*/
cp_int32_t open_hook(cp_hook_t *hook, const cp_hook_info_t *hook_info);
/*��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t read_hook(cp_hook_t *hook, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t write_hook(cp_hook_t *hook, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*�ر�ģ��*/
cp_int32_t close_hook(cp_hook_t *hook);
/*�˳�ģ��*/
cp_int32_t exit_hook(cp_hook_t *hook);
/*����ģ�����*/
cp_int32_t set_option_hook(cp_hook_t *hook, cp_int32_t optname, const cp_void_t* optval);
cp_int32_t get_option_hook(cp_hook_t *hook, cp_int32_t optname, cp_void_t* optval);




/*ģ�鴴���ӿڣ���ʾ����һ��ģ��*/
cp_int32_t init_hook(cp_hook_t *hook, const cp_hook_info_t *hook_info)
{
	return 0;
}
/*ģ������нӿڣ���ģ��init֮�󣬻ᱻ����*/
cp_int32_t open_hook(cp_hook_t *hook, const cp_hook_info_t *hook_info)
{
	return 0;
}
/*��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t read_hook(cp_hook_t *hook, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}
/*дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t write_hook(cp_hook_t *hook, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}
/*�ر�ģ��*/
cp_int32_t close_hook(cp_hook_t *hook)
{
	return 0;
}
/*�˳�ģ��*/
cp_int32_t exit_hook(cp_hook_t *hook)
{
	return 0;
}
/*����ģ�����*/
cp_int32_t set_option_hook(cp_hook_t *hook, cp_int32_t optname, const cp_void_t* optval)
{
	return 0;
}
cp_int32_t get_option_hook(cp_hook_t *hook, cp_int32_t optname, cp_void_t* optval)
{
	return 0;
}







