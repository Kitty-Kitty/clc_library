


#set src files list
#set pool directory
SET(CP_SRC_POOL_MEMORY_DIR ${CP_SRC_POOL_DIR}/memory)




#add pool source directory
AUX_SOURCE_DIRECTORY(${CP_SRC_POOL_MEMORY_DIR} CP_SRC_POOL_MEMORY_FILES_LIST)




#add source file list
SET(CP_SRC_POOL_FILES_LIST 
	${CP_SRC_POOL_FILES_LIST} 
	${CP_SRC_POOL_MEMORY_FILES_LIST} 
	
	PARENT_SCOPE
	)

#add include dir
SET(CP_SRC_POOL_DIR 
	${CP_SRC_POOL_DIR} 
	${CP_SRC_POOL_MEMORY_DIR}
	
	PARENT_SCOPE
	)
	