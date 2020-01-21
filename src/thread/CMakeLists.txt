


#set src files list
#set thread directory
SET(CP_SRC_THREAD_DIR ${CP_SRC_DIR}/thread)




#add thread source directory
AUX_SOURCE_DIRECTORY(${CP_SRC_THREAD_DIR} CP_SRC_THREAD_FILES_LIST)




#build sub directory
ADD_SUBDIRECTORY(${CP_SRC_THREAD_DIR}/libuv_thread)




#add source file list
SET(CP_EXECUTABLE_FILES_LIST 
	${CP_EXECUTABLE_FILES_LIST} 
	${CP_SRC_THREAD_FILES_LIST} 
	
	PARENT_SCOPE
	)

#add include dir
SET(CP_INCLUDE_DIR ${CP_INCLUDE_DIR} 
	${CP_SRC_THREAD_DIR}
	
	PARENT_SCOPE
	)


	