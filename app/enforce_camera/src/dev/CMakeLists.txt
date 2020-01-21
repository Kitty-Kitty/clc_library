#set src files list
#set ecam codecs directory


#add ecam codecs source directory
AUX_SOURCE_DIRECTORY(${CP_ECAM_SRC_DEV_DIR} CP_ECAM_SRC_DEV_ECAM_FILES_LIST)


#set hook rtp directory
SET(CP_ECAM_SRC_DEV_HI3519_DIR ${CP_ECAM_SRC_DEV_DIR}/hi3516c)

#add core source directory
ADD_SUBDIRECTORY(${CP_ECAM_SRC_DEV_HI3519_DIR})



#add source file list
SET(CP_ECAM_EXECUTABLE_FILES_LIST 
	${CP_ECAM_EXECUTABLE_FILES_LIST} 
	${CP_ECAM_SRC_DEV_ECAM_FILES_LIST} 

	PARENT_SCOPE
	)

#add include dir
SET(CP_ECAM_INCLUDE_DIR ${CP_ECAM_INCLUDE_DIR} 
	${CP_ECAM_SRC_DEV_DIR}

	PARENT_SCOPE
	)