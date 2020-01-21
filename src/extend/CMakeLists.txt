


#set src files list
#set extend directory
SET(CP_SRC_EXTEND_DIR ${CP_SRC_DIR}/extend)





#add extend source directory
AUX_SOURCE_DIRECTORY(${CP_SRC_EXTEND_DIR} CP_SRC_EXTEND_FILES_LIST)


#add source file list
SET(CP_EXECUTABLE_FILES_LIST 
	${CP_EXECUTABLE_FILES_LIST} 
	${CP_SRC_EXTEND_FILES_LIST} 
	
	PARENT_SCOPE
	)

#add include dir
SET(CP_INCLUDE_DIR ${CP_INCLUDE_DIR} 
	${CP_SRC_EXTEND_DIR}
	
	PARENT_SCOPE
	)


	