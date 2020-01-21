#set src files list
#set ipc hook directory

#add ipc HOOK source directory
AUX_SOURCE_DIRECTORY(${CP_IPC_SRC_HOOK_DIR} CP_IPC_SRC_HOOK_FILES_LIST)



	
	
#set hook rtp directory
SET(CP_IPC_SRC_HOOK_RTP_DIR ${CP_IPC_SRC_HOOK_DIR}/rtp)

#add core source directory
ADD_SUBDIRECTORY(${CP_IPC_SRC_HOOK_RTP_DIR})



#add source file list
SET(CP_IPC_EXECUTABLE_FILES_LIST 
	${CP_IPC_EXECUTABLE_FILES_LIST} 
	${CP_IPC_SRC_HOOK_FILES_LIST} 

	PARENT_SCOPE
	)

#add include dir
SET(CP_IPC_INCLUDE_DIR 
    ${CP_IPC_INCLUDE_DIR} 
	${CP_IPC_SRC_HOOK_DIR}

	PARENT_SCOPE
	)