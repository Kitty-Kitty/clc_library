
#set app ecam src files list
#set app directory
SET(CP_ECAM_SRC_APP_DIR ${CP_ECAM_SRC_DIR}/app)
#set codecs directory
SET(CP_ECAM_SRC_CODEC_DIR ${CP_ECAM_SRC_DIR}/codec)
#set dev directory
SET(CP_ECAM_SRC_DEV_DIR ${CP_ECAM_SRC_DIR}/dev)
#set extend directory
SET(CP_ECAM_SRC_EXTEND_DIR ${CP_ECAM_SRC_DIR}/extend)
#set filter directory
SET(CP_ECAM_SRC_FILTER_DIR ${CP_ECAM_SRC_DIR}/filter)
#set func directory
SET(CP_ECAM_SRC_FUNC_DIR ${CP_ECAM_SRC_DIR}/func)
#set hook directory
SET(CP_ECAM_SRC_HOOK_DIR ${CP_ECAM_SRC_DIR}/hook)
#set process directory
SET(CP_ECAM_SRC_PROCESS_DIR ${CP_ECAM_SRC_DIR}/process)
#set session directory
SET(CP_ECAM_SRC_SESSION_DIR ${CP_ECAM_SRC_DIR}/session)



#add app source directory
ADD_SUBDIRECTORY(${CP_ECAM_SRC_APP_DIR})
#add codecs source directory
ADD_SUBDIRECTORY(${CP_ECAM_SRC_CODEC_DIR})
#add dev source directory
ADD_SUBDIRECTORY(${CP_ECAM_SRC_DEV_DIR})
#add extend source directory
ADD_SUBDIRECTORY(${CP_ECAM_SRC_EXTEND_DIR})
#add filter source directory
ADD_SUBDIRECTORY(${CP_ECAM_SRC_FILTER_DIR})
#add func source directory
ADD_SUBDIRECTORY(${CP_ECAM_SRC_FUNC_DIR})
#add hook source directory
ADD_SUBDIRECTORY(${CP_ECAM_SRC_HOOK_DIR})
#add process source directory
ADD_SUBDIRECTORY(${CP_ECAM_SRC_PROCESS_DIR})
#add session source directory
ADD_SUBDIRECTORY(${CP_ECAM_SRC_SESSION_DIR})



#add source file list
SET(CP_ECAM_EXECUTABLE_FILES_LIST 
	${CP_ECAM_EXECUTABLE_FILES_LIST} 

	PARENT_SCOPE
	)

#add include dir
SET(CP_ECAM_INCLUDE_DIR
    ${CP_ECAM_INCLUDE_DIR} 

	PARENT_SCOPE
	)
	
	
#MESSAGE(STATUS "ecam file list:" ${CP_ECAM_EXECUTABLE_FILES_LIST})
	
	