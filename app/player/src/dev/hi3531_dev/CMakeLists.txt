#set src files list
#set session directory
SET(CP_PLAYER_SRC_DEV_HI3531_DEV_DIR ${CP_PLAYER_SRC_DEV_DIR}/hi3531_dev)



#add session source directory
AUX_SOURCE_DIRECTORY(${CP_PLAYER_SRC_DEV_HI3531_DEV_DIR} CP_PLAYER_SRC_DEV_HI3531_DEV_FILES_LIST)


#IF(${CP_PLATFORM} STREQUAL "hisiv100")

#set directory
SET(CP_PLAYER_SRC_DEV_HI3531_DEV_SDL_DIR ${CP_PLAYER_SRC_DEV_HI3531_DEV_DIR}/hi3531_sdl)
SET(CP_PLAYER_SRC_DEV_HI3531_DEV_TDE_DIR ${CP_PLAYER_SRC_DEV_HI3531_DEV_DIR}/hi3531_tde)
SET(CP_PLAYER_SRC_DEV_HI3531_DEV_VO_DIR ${CP_PLAYER_SRC_DEV_HI3531_DEV_DIR}/hi3531_vo)
SET(CP_PLAYER_SRC_DEV_HI3531_DEV_VPSS_DIR ${CP_PLAYER_SRC_DEV_HI3531_DEV_DIR}/hi3531_vpss)

#build sub directory
ADD_SUBDIRECTORY(${CP_PLAYER_SRC_DEV_HI3531_DEV_SDL_DIR})
ADD_SUBDIRECTORY(${CP_PLAYER_SRC_DEV_HI3531_DEV_TDE_DIR})
ADD_SUBDIRECTORY(${CP_PLAYER_SRC_DEV_HI3531_DEV_VO_DIR})
ADD_SUBDIRECTORY(${CP_PLAYER_SRC_DEV_HI3531_DEV_VPSS_DIR})

#SET(CP_IPC_SRC_HI3531_DEC_COMMON_FILES_LIST
#		${CP_THIRD_PARTY_DIR}/src/hi/hi3531/mpp_big-little/sample/common/sample_comm_isp.c
#		${CP_THIRD_PARTY_DIR}/src/hi/hi3531/mpp_big-little/sample/common/sample_comm_sys.c
#		${CP_THIRD_PARTY_DIR}/src/hi/hi3531/mpp_big-little/sample/common/sample_comm_venc.c
#		${CP_THIRD_PARTY_DIR}/src/hi/hi3531/mpp_big-little/sample/common/sample_comm_vi.c
#		${CP_THIRD_PARTY_DIR}/src/hi/hi3531/mpp_big-little/sample/common/sample_comm_vpss.c
#	)

#ENDIF()


#add source file list
SET(CP_PLAYER_SRC_DEV_PLAYER_FILES_LIST
	${CP_PLAYER_SRC_DEV_PLAYER_FILES_LIST}
	${CP_PLAYER_SRC_DEV_HI3531_DEV_FILES_LIST}
	#${CP_IPC_SRC_HI3531_DEC_COMMON_FILES_LIST}
	
	PARENT_SCOPE
	)


#add include dir
SET(CP_PLAYER_SRC_DEV_DIR
    ${CP_PLAYER_SRC_DEV_DIR} 
    ${CP_PLAYER_SRC_DEV_HI3531_DEV_DIR}
	
	PARENT_SCOPE
	)
	
	
#MESSAGE(STATUS "hi3531---->P_PLAYER_INCLUDE_DIR : "${CP_PLAYER_SRC_DEV_DIR})