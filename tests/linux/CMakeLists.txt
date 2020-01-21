#set tests test_libuv_multicast directory
SET(CP_TESTS_LINUX_LIBUV_MULTICAST_DIR ${CP_TESTS_LINUX_DIR}/test_libuv_multicast)

#set tests test_libuv_tcp directory
SET(CP_TESTS_LINUX_LIBUV_TCP_DIR ${CP_TESTS_LINUX_DIR}/test_libuv_tcp)


#add tests test_libuv_multicast directory
ADD_SUBDIRECTORY(${CP_TESTS_LINUX_LIBUV_MULTICAST_DIR})

#add tests test_libuv_tcp directory
ADD_SUBDIRECTORY(${CP_TESTS_LINUX_LIBUV_TCP_DIR})
