#set src files list
#set session directory
#SET(CP_PLAYER_SRC_DEV_HI3531_DEV_SDL_DIR ${CP_PLAYER_SRC_DEV_HI3531_DEV_DIR}/hi3531_sdl)

#add session source directory
AUX_SOURCE_DIRECTORY(${CP_PLAYER_SRC_DEV_HI3531_DEV_SDL_DIR} CP_IPC_SRC_DEV_HI3531_DEV_SDL_FILES_LIST)






#SET(CP_IPC_SRC_HI3531_DEC_COMMON_FILES_LIST
#		${CP_THIRD_PARTY_DIR}/src/hi/hi3531/mpp_big-little/sample/common/sample_comm_isp.c
#		${CP_THIRD_PARTY_DIR}/src/hi/hi3531/mpp_big-little/sample/common/sample_comm_sys.c
#		${CP_THIRD_PARTY_DIR}/src/hi/hi3531/mpp_big-little/sample/common/sample_comm_venc.c
#		${CP_THIRD_PARTY_DIR}/src/hi/hi3531/mpp_big-little/sample/common/sample_comm_vi.c
#		${CP_THIRD_PARTY_DIR}/src/hi/hi3531/mpp_big-little/sample/common/sample_comm_vpss.c
#	)



#add source file list
SET(CP_PLAYER_SRC_DEV_HI3531_DEV_FILES_LIST 
	${CP_PLAYER_SRC_DEV_HI3531_DEV_FILES_LIST} 
	${CP_IPC_SRC_DEV_HI3531_DEV_SDL_FILES_LIST} 
	
	PARENT_SCOPE
	)


#add include dir
SET(CP_PLAYER_SRC_DEV_HI3531_DEV_DIR
    ${CP_PLAYER_SRC_DEV_HI3531_DEV_DIR} 
    ${CP_PLAYER_SRC_DEV_HI3531_DEV_SDL_DIR}
	
	PARENT_SCOPE
	)