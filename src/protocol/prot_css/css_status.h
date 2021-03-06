/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2014-2-11

Description:status defined

**************************************************************************/



#ifndef	_PROT_CSS_STATUS_H_
#define _PROT_CSS_STATUS_H_






typedef enum css_status_enum
{
	css_status_null = 0,
	css_status_normal = 1,
	css_status_warning = 2,
	css_status_error = 3,
	css_status_critical = 4,
}css_status;







#define			css_is_null_status(s)					(s >= 0 && s <= 199)
#define			css_is_normal_status(s)					(s >= 200 && s <= 299)
#define			css_is_warning_status(s)				(s >= 300 && s <= 399)
#define			css_is_error_status(s)					(s >= 400 && s <= 499)
#define			css_is_critical_status(s)				(s >= 500 && s <= 599)






///////////////////////////////////////////��״̬��0--199��//////////////////////////////////////
/*=============================================================================================*/
#define			CSS_NULL_STATUS_0									0












/////////////////////////////////////////����״̬��200--299��////////////////////////////////////
/*=============================================================================================*/
#define			CSS_NORMAL_STATUS_200								200













/////////////////////////////////////////�澯״̬��300--399��////////////////////////////////////
/*=============================================================================================*/
#define			CSS_WARNING_STATUS_300								300











/////////////////////////////////////////����״̬��400--499��////////////////////////////////////
/*=============================================================================================*/
#define			CSS_ERROR_STATUS_400								400











/////////////////////////////////////////���ش���״̬��500--599��////////////////////////////////////
/*=============================================================================================*/
#define			CSS_CRITICAL_STATUS_500								500





////////////////////////////////////////���紫��״̬(600-699)///////////////////////////////////////////////////
/*=============================================================================================*/
#define			CSS_NETWORK_STATUS_600								600
#define			CSS_NETWORK_STATUS_601								601
#define			CSS_NETWORK_STATUS_602								602
#define			CSS_NETWORK_STATUS_603								603
#define			CSS_NETWORK_STATUS_604								604





/////////////////////////////////////////�豸״̬�루800--899��//////////////////////////////////////
/*=============================================================================================*/
#define			CSS_DEVICE_STATUS_STOP								800								//��ʾ�豸ͣ��״̬
#define			CSS_DEVICE_STATUS_UNREGISTER						801								//��ʾ�豸δע��״̬














#endif



















