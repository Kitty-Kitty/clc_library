


#set src files list
#set app directory


#add app source directory
AUX_SOURCE_DIRECTORY(${CP_VDU_DEMO_SRC_APP_DIR} CP_VDU_DEMO_SRC_APP_FILES_LIST)



#add source file list
SET(CP_VDU_DEMO_EXECUTABLE_FILES_LIST 
	${CP_VDU_DEMO_EXECUTABLE_FILES_LIST} 
	${CP_VDU_DEMO_SRC_APP_FILES_LIST} 

	PARENT_SCOPE
	)

#add include dir
SET(CP_VDU_DEMO_INCLUDE_DIR ${CP_VDU_DEMO_INCLUDE_DIR} 
	${CP_VDU_DEMO_SRC_APP_DIR}

	PARENT_SCOPE
	)


	
	