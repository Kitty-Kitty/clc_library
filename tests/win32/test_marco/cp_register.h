/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-08-09

Description:

**************************************************************************/

#ifndef _CP_REGISTER_INCLUDE_H_
#define _CP_REGISTER_INCLUDE_H_



typedef struct cp_test_register_struct
{
	int		a;
	char	*name;
}cp_test_register;



#define		CP_TEST_REGISTER_MARCO(input_a, input_name)			{input_a, input_name},


#endif