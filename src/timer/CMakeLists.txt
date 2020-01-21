


#set src files list
#set timer directory
SET(CP_SRC_TIMER_DIR ${CP_SRC_DIR}/timer)





#add timer source directory
AUX_SOURCE_DIRECTORY(${CP_SRC_TIMER_DIR} CP_SRC_TIMER_FILES_LIST)



#build sub directory
ADD_SUBDIRECTORY(${CP_SRC_TIMER_DIR}/libuv_timer)




#add source file list
SET(CP_EXECUTABLE_FILES_LIST 
	${CP_EXECUTABLE_FILES_LIST} 
	${CP_SRC_TIMER_FILES_LIST} 
	
	PARENT_SCOPE
	)

#add include dir
SET(CP_INCLUDE_DIR ${CP_INCLUDE_DIR} 
	${CP_SRC_TIMER_DIR}
	
	PARENT_SCOPE
	)


	