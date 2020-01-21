#set src files list
#set ecam hook directory

#add ecam HOOK source directory
AUX_SOURCE_DIRECTORY(${CP_ECAM_SRC_HOOK_DIR} CP_ECAM_SRC_HOOK_FILES_LIST)



	
	
#set hook rtp directory
SET(CP_ECAM_SRC_HOOK_RTP_DIR ${CP_ECAM_SRC_HOOK_DIR}/rtp)

#add core source directory
ADD_SUBDIRECTORY(${CP_ECAM_SRC_HOOK_RTP_DIR})



#add source file list
SET(CP_ECAM_EXECUTABLE_FILES_LIST 
	${CP_ECAM_EXECUTABLE_FILES_LIST} 
	${CP_ECAM_SRC_HOOK_FILES_LIST} 

	PARENT_SCOPE
	)

#add include dir
SET(CP_ECAM_INCLUDE_DIR 
    ${CP_ECAM_INCLUDE_DIR} 
	${CP_ECAM_SRC_HOOK_DIR}

	PARENT_SCOPE
	)