/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/


#ifndef	_CP_INET_INCLUDE_H_
#define _CP_INET_INCLUDE_H_

int cp_ip4_addr(const char* ip, int port, struct sockaddr_in* addr);
int cp_any_addr(struct sockaddr_in* addr);

#endif

