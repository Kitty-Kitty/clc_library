#set src files list
#set session directory
SET(CP_PLAYER_SRC_CODEC_FFMEPG_AV_DIR ${CP_PLAYER_SRC_CODECS_DIR}/ffmpeg)



#add session source directory
AUX_SOURCE_DIRECTORY(${CP_PLAYER_SRC_CODEC_FFMEPG_AV_DIR} CP_PLAYER_SRC_CODEC_FFMEPG_AV_FILES_LIST)



#add source file list
SET(CP_PLAYER_SRC_CODECS_PLAYER_FILES_LIST 
	${CP_PLAYER_SRC_CODECS_PLAYER_FILES_LIST} 
	${CP_PLAYER_SRC_CODEC_FFMEPG_AV_FILES_LIST} 
	
	PARENT_SCOPE
	)


#add include dir
SET(CP_PLAYER_INCLUDE_DIR
    ${CP_PLAYER_INCLUDE_DIR} 
    ${CP_PLAYER_SRC_CODEC_FFMEPG_AV_DIR}
	
	PARENT_SCOPE
	)