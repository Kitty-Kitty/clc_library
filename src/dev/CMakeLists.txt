


#set src files list
#set dev directory
SET(CP_SRC_DEV_DIR ${CP_SRC_DIR}/dev)





#add dev source directory
AUX_SOURCE_DIRECTORY(${CP_SRC_DEV_DIR} CP_SRC_DEV_FILES_LIST)





#add source file list
SET(CP_EXECUTABLE_FILES_LIST 
	${CP_EXECUTABLE_FILES_LIST} 
	${CP_SRC_DEV_FILES_LIST} 
	
	PARENT_SCOPE
	)


#add include dir
SET(CP_INCLUDE_DIR
	${CP_INCLUDE_DIR} 
	${CP_SRC_DEV_DIR}
	
	PARENT_SCOPE
	)
