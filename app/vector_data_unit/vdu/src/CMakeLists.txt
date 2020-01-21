
#set core vdu src files list
#set core directory
SET(CP_VDU_SRC_CORE_DIR ${CP_VDU_SRC_DIR}/core)
#set codec directory
SET(CP_VDU_SRC_CODEC_DIR ${CP_VDU_SRC_DIR}/codec)
#set dev directory
SET(CP_VDU_SRC_DEV_DIR ${CP_VDU_SRC_DIR}/dev)
#set func directory
SET(CP_VDU_SRC_FUNC_DIR ${CP_VDU_SRC_DIR}/func)



#add core source directory
ADD_SUBDIRECTORY(${CP_VDU_SRC_CORE_DIR})
#add codec source directory
ADD_SUBDIRECTORY(${CP_VDU_SRC_CODEC_DIR})
#add dev source directory
ADD_SUBDIRECTORY(${CP_VDU_SRC_DEV_DIR})
#add func source directory
ADD_SUBDIRECTORY(${CP_VDU_SRC_FUNC_DIR})



#add source file list
SET(CP_VDU_LIBRARY_FILES_LIST 
	${CP_VDU_LIBRARY_FILES_LIST} 

	PARENT_SCOPE
	)

#add include dir
SET(CP_VDU_INCLUDE_DIR
    ${CP_VDU_INCLUDE_DIR}
	${CP_VDU_SRC_CORE_DIR}
	${CP_VDU_SRC_CODEC_DIR}
	${CP_VDU_SRC_DEV_DIR}
	${CP_VDU_SRC_FUNC_DIR}

	PARENT_SCOPE
	)
	
	
#MESSAGE(STATUS "vdu file list:" ${CP_VDU_LIBRARY_FILES_LIST})
	
	