#set src files list
#set player hook directory

#add player HOOK source directory
AUX_SOURCE_DIRECTORY(${CP_PLAYER_SRC_EXTEND_DIR} CP_PLAYER_SRC_EXTEND_FILES_LIST)



#add source file list
SET(CP_PLAYER_EXECUTABLE_FILES_LIST 
	${CP_PLAYER_EXECUTABLE_FILES_LIST} 
	${CP_PLAYER_SRC_EXTEND_FILES_LIST} 

	PARENT_SCOPE
	)

#add include dir
SET(CP_PLAYER_INCLUDE_DIR 
    ${CP_PLAYER_INCLUDE_DIR} 
	${CP_PLAYER_SRC_EXTEND_DIR}

	PARENT_SCOPE
	)
