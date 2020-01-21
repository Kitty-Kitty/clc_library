#set src files list
#set vdu func directory


#add vdu func source directory
AUX_SOURCE_DIRECTORY(${CP_VDU_SRC_FUNC_DIR} CP_VDU_SRC_FUNC_FILES_LIST)


#build sub directory
ADD_SUBDIRECTORY(${CP_VDU_SRC_FUNC_DIR}/vdu)


#add source file list
SET(CP_VDU_LIBRARY_FILES_LIST 
	${CP_VDU_LIBRARY_FILES_LIST} 
	${CP_VDU_SRC_FUNC_FILES_LIST} 

	PARENT_SCOPE
	)

#add include dir
SET(CP_VDU_INCLUDE_DIR ${CP_VDU_INCLUDE_DIR} 
	${CP_VDU_SRC_FUNC_DIR}

	PARENT_SCOPE
	)