#set src files list
#set ipc codecs directory


#add ipc codecs source directory
AUX_SOURCE_DIRECTORY(${CP_IPC_SRC_DEV_DIR} CP_IPC_SRC_DEV_IPC_FILES_LIST)


#set hook rtp directory
SET(CP_IPC_SRC_DEV_HI3519_DIR ${CP_IPC_SRC_DEV_DIR}/hi3519)

#add core source directory
ADD_SUBDIRECTORY(${CP_IPC_SRC_DEV_HI3519_DIR})



#add source file list
SET(CP_IPC_EXECUTABLE_FILES_LIST 
	${CP_IPC_EXECUTABLE_FILES_LIST} 
	${CP_IPC_SRC_DEV_IPC_FILES_LIST} 

	PARENT_SCOPE
	)

#add include dir
SET(CP_IPC_INCLUDE_DIR ${CP_IPC_INCLUDE_DIR} 
	${CP_IPC_SRC_DEV_DIR}

	PARENT_SCOPE
	)