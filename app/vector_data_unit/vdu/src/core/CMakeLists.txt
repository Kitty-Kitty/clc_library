


#set src files list
#set core directory


#add core source directory
AUX_SOURCE_DIRECTORY(${CP_VDU_SRC_CORE_DIR} CP_VDU_SRC_CORE_FILES_LIST)



#add source file list
SET(CP_VDU_LIBRARY_FILES_LIST 
	${CP_VDU_LIBRARY_FILES_LIST} 
	${CP_VDU_SRC_CORE_FILES_LIST} 

	PARENT_SCOPE
	)

#add include dir
SET(CP_VDU_INCLUDE_DIR ${CP_VDU_INCLUDE_DIR} 
	${CP_VDU_SRC_CORE_DIR}

	PARENT_SCOPE
	)


	
	