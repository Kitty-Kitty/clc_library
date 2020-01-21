


#set src files list
#set pool directory
SET(CP_SRC_POOL_DIR ${CP_SRC_DIR}/pool)




#add pool source directory
AUX_SOURCE_DIRECTORY(${CP_SRC_POOL_DIR} CP_SRC_POOL_FILES_LIST)


#build sub directory
ADD_SUBDIRECTORY(${CP_SRC_POOL_DIR}/memory)


#add source file list
SET(CP_EXECUTABLE_FILES_LIST 
	${CP_EXECUTABLE_FILES_LIST} 
	${CP_SRC_POOL_FILES_LIST} 
	
	PARENT_SCOPE
	)

#add include dir
SET(CP_INCLUDE_DIR ${CP_INCLUDE_DIR} 
	${CP_SRC_POOL_DIR}
	
	PARENT_SCOPE
	)


	