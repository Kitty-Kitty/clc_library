#include "uv.h"

int main() {

	
	char buf[512];
	uv_interface_address_t *info;
	int count, i;

	uv_interface_addresses(&info, &count);
	i = count;

	printf("Number of interfaces: %d\n", count);
	while (i--) {
		uv_interface_address_t inte = info[i];

		printf("Name: %s\n", inte.name);
		printf("Internal? %s\n", inte.is_internal ? "Yes" : "No");

		if (inte.address.address4.sin_family == AF_INET) {
			uv_ip4_name(&inte.address.address4, buf, sizeof(buf));
			printf("IPv4 address: %s\n", buf);
		}
		else if (inte.address.address4.sin_family == AF_INET6) {
			uv_ip6_name(&inte.address.address6, buf, sizeof(buf));
			printf("IPv6 address: %s\n", buf);
		}

		printf("\n");
	}

	uv_free_interface_addresses(info, count);
	

	/*
	cp_socket_manager_t			sm = UV_SOCKET_MANAGER_MODULE;
	cp_socket_t					*s = NULL;
	cp_socket_t					*udp_s = NULL;
	cp_sockaddr_in				addr;
	cp_sockaddr_in				udp_addr;


	sm.handlers.init(&sm);


	s = sm.handlers.create(&sm, cp_socket_type_tcp);
	set_funs_handlers(s);
	cp_ip4_addr("192.168.1.67", 9213, &addr);
	s->handlers.listen(s, &addr);


	udp_s = sm.handlers.create(&sm, cp_socket_type_udp);
	set_funs_handlers(udp_s);
	cp_ip4_addr("192.168.1.67", 9214, &udp_addr);
	udp_s->handlers.listen(udp_s, &udp_addr);


	sm.handlers.start(&sm);
	*/

	return 0;
}
