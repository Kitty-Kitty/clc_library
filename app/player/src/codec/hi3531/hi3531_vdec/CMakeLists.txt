#set src files list

SET(CP_PLAYER_SRC_CODEC_HI3531_VDEC_DIR ${CP_PLAYER_SRC_CODEC_HI3531_DIR}/hi3531_vdec)


#add session source directory
AUX_SOURCE_DIRECTORY(${CP_PLAYER_SRC_CODEC_HI3531_VDEC_DIR} CP_PLAYER_SRC_CODEC_HI3531_VDEC_FILES_LIST)




#add source file list
SET(CP_PLAYER_SRC_CODEC_HI3531_FILES_LIST 
	${CP_PLAYER_SRC_CODEC_HI3531_FILES_LIST} 
	${CP_PLAYER_SRC_CODEC_HI3531_VDEC_FILES_LIST} 
	
	PARENT_SCOPE
	)
