


#set src files list
#set log directory
SET(CP_SRC_LOG_ZLOG_DIR ${CP_SRC_LOG_DIR}/zlog)





#add log source directory
AUX_SOURCE_DIRECTORY(${CP_SRC_LOG_ZLOG_DIR} CP_SRC_LOG_ZLOG_FILES_LIST)







#add source file list
SET(CP_SRC_LOG_FILES_LIST 
	${CP_SRC_LOG_FILES_LIST} 
	${CP_SRC_LOG_ZLOG_FILES_LIST} 
	
	PARENT_SCOPE
	)

#add include dir
SET(CP_SRC_LOG_DIR 
	${CP_SRC_LOG_DIR} 
	${CP_SRC_LOG_ZLOG_DIR}
	
	PARENT_SCOPE
	)

	