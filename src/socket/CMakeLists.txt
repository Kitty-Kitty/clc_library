


#set src files list
#set socket directory
SET(CP_SRC_SOCKET_DIR ${CP_SRC_DIR}/socket)





#add socket source directory
AUX_SOURCE_DIRECTORY(${CP_SRC_SOCKET_DIR} CP_SRC_SOCKET_FILES_LIST)




#build sub directory
ADD_SUBDIRECTORY(${CP_SRC_SOCKET_DIR}/libuv_socket)


#add source file list
SET(CP_EXECUTABLE_FILES_LIST 
	${CP_EXECUTABLE_FILES_LIST} 
	${CP_SRC_SOCKET_FILES_LIST} 
	
	PARENT_SCOPE
	)

#add include dir
SET(CP_INCLUDE_DIR ${CP_INCLUDE_DIR} 
	${CP_SRC_SOCKET_DIR}
	
	PARENT_SCOPE
	)


	