#set src files list
#set ipc hook directory

#add ipc HOOK source directory
AUX_SOURCE_DIRECTORY(${CP_IPC_SRC_FILTER_DIR} CP_IPC_SRC_FILTER_FILES_LIST)


#set func ipc directory
SET(CP_IPC_SRC_FILTER_RTP_DIR ${CP_IPC_SRC_FILTER_DIR}/rtp)

#add core source directory
ADD_SUBDIRECTORY(${CP_IPC_SRC_FILTER_RTP_DIR})


#add source file list
SET(CP_IPC_EXECUTABLE_FILES_LIST 
	${CP_IPC_EXECUTABLE_FILES_LIST} 
	${CP_IPC_SRC_FILTER_FILES_LIST} 

	PARENT_SCOPE
	)

#add include dir
SET(CP_IPC_INCLUDE_DIR 
    ${CP_IPC_INCLUDE_DIR} 
	${CP_IPC_SRC_FILTER_DIR}

	PARENT_SCOPE
	)
