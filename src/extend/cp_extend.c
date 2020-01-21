/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_extend.h"
#include "cp_include.h"



/*ģ�鴴���ӿڣ���ʾ����һ��ģ��*/
cp_int32_t init_extend(cp_extend_t *extend, const cp_extend_info_t *extend_info);
/*ģ������нӿڣ���ģ��init֮�󣬻ᱻ����*/
cp_int32_t open_extend(cp_extend_t *extend, const cp_extend_info_t *extend_info);
/*��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t read_extend(cp_extend_t *extend, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t write_extend(cp_extend_t *extend, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*�ر�ģ��*/
cp_int32_t close_extend(cp_extend_t *extend);
/*�˳�ģ��*/
cp_int32_t exit_extend(cp_extend_t *extend);
/*����ģ�����*/
cp_int32_t set_option_extend(cp_extend_t *extend, cp_int32_t optname, const cp_void_t* optval);
cp_int32_t get_option_extend(cp_extend_t *extend, cp_int32_t optname, cp_void_t* optval);



/*ģ�鴴���ӿڣ���ʾ����һ��ģ��*/
cp_int32_t init_extend(cp_extend_t *extend, const cp_extend_info_t *extend_info)
{
	return 0;
}
/*ģ������нӿڣ���ģ��init֮�󣬻ᱻ����*/
cp_int32_t open_extend(cp_extend_t *extend, const cp_extend_info_t *extend_info)
{
	return 0;
}
/*��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t read_extend(cp_extend_t *extend, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}
/*дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t write_extend(cp_extend_t *extend, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}
/*�ر�ģ��*/
cp_int32_t close_extend(cp_extend_t *extend)
{
	return 0;
}
/*�˳�ģ��*/
cp_int32_t exit_extend(cp_extend_t *extend)
{
	return 0;
}
/*����ģ�����*/
cp_int32_t set_option_extend(cp_extend_t *extend, cp_int32_t optname, const cp_void_t* optval)
{
	return 0;
}
cp_int32_t get_option_extend(cp_extend_t *extend, cp_int32_t optname, cp_void_t* optval)
{
	return 0;
}


