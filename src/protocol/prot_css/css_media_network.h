/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-05

Description:

**************************************************************************/

#ifndef _CSS_MEDIA_NETWORK_INCLUDE_H_
#define _CSS_MEDIA_NETWORK_INCLUDE_H_


/************************************************************************/
/* 媒体网络包类型                                                             */
/************************************************************************/
typedef enum css_media_network_enum
{
	css_media_network_metadata = 0x00,
	css_media_network_metadata_return = 0x01,
	css_media_network_begin = 0x40,
	css_media_network_other = 0x41,
	css_media_network_end = 0x42
}css_media_network;

#endif