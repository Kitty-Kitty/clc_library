


#set src files list
#set module directory
SET(CP_SRC_MODULE_DIR ${CP_SRC_DIR}/module)





#add module source directory
AUX_SOURCE_DIRECTORY(${CP_SRC_MODULE_DIR} CP_SRC_MODULE_FILES_LIST)





#add source file list
SET(CP_EXECUTABLE_FILES_LIST 
	${CP_EXECUTABLE_FILES_LIST} 
	${CP_SRC_MODULE_FILES_LIST} 
	
	PARENT_SCOPE
	)

#add include dir
SET(CP_INCLUDE_DIR ${CP_INCLUDE_DIR} 
	${CP_SRC_MODULE_DIR}
	
	PARENT_SCOPE
	)

	
	