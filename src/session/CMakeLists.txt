


#set src files list
#set session directory
SET(CP_SRC_SESSION_DIR ${CP_SRC_DIR}/session)





#add session source directory
AUX_SOURCE_DIRECTORY(${CP_SRC_SESSION_DIR} CP_SRC_SESSION_FILES_LIST)




#add source file list
SET(CP_EXECUTABLE_FILES_LIST 
	${CP_EXECUTABLE_FILES_LIST} 
	${CP_SRC_SESSION_FILES_LIST} 
	
	PARENT_SCOPE
	)


#add include dir
SET(CP_INCLUDE_DIR 
	${CP_INCLUDE_DIR} 
	${CP_SRC_SESSION_DIR}
	
	PARENT_SCOPE
	)

	
	