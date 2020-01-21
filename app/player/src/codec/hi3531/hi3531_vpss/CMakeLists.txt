#set src files list


#add session source directory
AUX_SOURCE_DIRECTORY(${CP_IPC_SRC_CODEC_HI3531_DEC_DIR} CP_IPC_SRC_CODEC_HI3531_DEC_FILES_LIST)




#SET(CP_IPC_SRC_HI3531_DEC_COMMON_DIR /home/f/Project/Hi3519V101_SDK_V1.0.0.1/mpp_big-little/sample/common)
#AUX_SOURCE_DIRECTORY(${CP_IPC_SRC_HI3531_DEC_COMMON_DIR} CP_IPC_SRC_HI3531_DEC_COMMON_FILES_LIST)





SET(CP_IPC_SRC_HI3531_DEC_COMMON_FILES_LIST
		${CP_THIRD_PARTY_DIR}/src/hi/hi3519/mpp_big-little/sample/common/sample_comm_isp.c
		${CP_THIRD_PARTY_DIR}/src/hi/hi3519/mpp_big-little/sample/common/sample_comm_sys.c
		${CP_THIRD_PARTY_DIR}/src/hi/hi3519/mpp_big-little/sample/common/sample_comm_venc.c
		${CP_THIRD_PARTY_DIR}/src/hi/hi3519/mpp_big-little/sample/common/sample_comm_vi.c
		${CP_THIRD_PARTY_DIR}/src/hi/hi3519/mpp_big-little/sample/common/sample_comm_vpss.c
	)



#add source file list
SET(CP_IPC_SRC_CODEC_FILES_LIST 
	${CP_IPC_SRC_CODEC_FILES_LIST} 
	${CP_IPC_SRC_CODEC_HI3531_DEC_FILES_LIST} 
	${CP_IPC_SRC_HI3531_DEC_COMMON_FILES_LIST}
	
	PARENT_SCOPE
	)


#add include dir
SET(CP_IPC_INCLUDE_DIR
    ${CP_IPC_INCLUDE_DIR} 
    ${CP_IPC_SRC_CODEC_HI3531_DEC_DIR}
	
	PARENT_SCOPE
	)