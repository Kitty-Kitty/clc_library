
#include <stdio.h>
#include <string.h>


#ifdef WIN32
#include <winsock.h>
#else
#include <netinet/in.h>
#endif

int cp_ip4_addr(const char* ip, int port, struct sockaddr_in* addr) {
	memset(addr, 0, sizeof(*addr));
	addr->sin_family = AF_INET;
	addr->sin_port = htons(port);
	addr->sin_addr.s_addr = inet_addr(ip);
	if (INADDR_NONE == addr->sin_addr.s_addr) {
		return -1;
	}
	return 0;
}

int cp_any_addr(struct sockaddr_in* addr){
	memset(addr, 0, sizeof(*addr));
	addr->sin_family = AF_INET;
	addr->sin_port = 0;
	addr->sin_addr.s_addr = INADDR_ANY;
	return 0;
}

