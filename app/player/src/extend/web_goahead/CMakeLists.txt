#set src files list
#set session directory
SET(CP_PLAYER_SRC_EXTEND_WEB_GOAHEAD_DIR ${CP_PLAYER_SRC_EXTEND_DIR}/web_goahead)




#add session source directory
AUX_SOURCE_DIRECTORY(${CP_PLAYER_SRC_EXTEND_WEB_GOAHEAD_DIR} CP_PLAYER_SRC_EXTEND_WEB_GOAHEAD_FILES_LIST)




#add source file list
SET(CP_PLAYER_SRC_EXTEND_FILES_LIST 
	${CP_PLAYER_SRC_EXTEND_FILES_LIST} 
	${CP_PLAYER_SRC_EXTEND_WEB_GOAHEAD_FILES_LIST} 
	
	PARENT_SCOPE
	)


#add include dir
SET(CP_PLAYER_INCLUDE_DIR
    ${CP_PLAYER_INCLUDE_DIR} 
    ${CP_PLAYER_SRC_EXTEND_WEB_GOAHEAD_DIR}
	
	PARENT_SCOPE
	)