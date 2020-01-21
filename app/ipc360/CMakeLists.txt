

#set css_ipc executable name
SET(CP_IPC_EXECUTABLE_NAME cp_ipc360)

#set css_ipc root directory
SET(CP_IPC_PROJECT_SOURCE_DIR ${CP_APP_IPC_DIR})

SET(CP_IPC_HISIV_INCLUDE_DIR "")
SET(CP_IPC_HISIV_LIB_DIR "")


IF(${CP_PLATFORM} STREQUAL "hisiv500")
		#set hi3519 mode
		ADD_DEFINITIONS(-DCP_HI3519_MODE=1)
		ADD_DEFINITIONS(-DSENSOR_TYPE=OMNIVISION_OV4689_MIPI_1080P_30FPS)
		#ADD_DEFINITIONS(-DSENSOR_TYPE=OMNIVISION_OV4689_MIPI_4M_30FPS)
		ADD_DEFINITIONS(-DSNS_OV4689_1080P_DOUBLE)
		ADD_DEFINITIONS(-DHI_MIPI_ENABLE)
		#SENSOR_TYPE = OMNIVISION_OV4689_MIPI_1080P_30FPS
		#CFLAGS += -DSNS_OV4689_1080P_DOUBLE
		#CFLAGS += -DHI_MIPI_ENABLE
		
		#set hi3519 include directory
		SET(CP_IPC_HISIV_INCLUDE_DIR 
				${CP_THIRD_PARTY_DIR}/src/hi/hi3519/mpp_big-little/include
				${CP_THIRD_PARTY_DIR}/src/hi/hi3519/mpp_big-little/sample/common
				)
		
		#set hi3519 lib directory
		SET(CP_IPC_HISIV_LIB_DIR 
				${CP_THIRD_PARTY_DIR}/src/hi/hi3519/mpp_big-little/lib
				)
				
		#set hi3519 depends libraries
		SET(CP_IPC_HISIV_LIBRARIES
				libisp.a
				libsns_ov4689_slave.a
				lib_cmoscfg.a
				lib_hiae.a
				lib_hiawb.a
				lib_hiaf.a
				lib_hidefog.a
				libmpi.a
				libupvqe.a
				lib_cmoscfg.a
				libdnvqe.a
				lib_hiae.a
				lib_hiaf.a
				lib_hiawb.a
				lib_hidefog.a
				libhistitch.a
				libisp.a
				libive.a
				libmd.a
				libmpi.a
				libsns_ov4689_slave.a
				libtde.a
				libupvqe.a
				libVoiceEngine.a
				)
		
ENDIF()


IF(${CP_PLATFORM} STREQUAL "hisiv600")
		#set hi3559 mode
		ADD_DEFINITIONS(-DCP_HI3559_MODE=1)
		ADD_DEFINITIONS(-DSENSOR_TYPE=cp_hi_vi_mode_omnivision_ov4689_mipi_1080p_30fps)
		#ADD_DEFINITIONS(-DSENSOR_TYPE=cp_hi_vi_mode_omnivision_ov4689_mipi_4m_30fps)
		ADD_DEFINITIONS(-DSNS_OV4689_1080P_DOUBLE)
		ADD_DEFINITIONS(-DHI_MIPI_ENABLE)
		#SENSOR_TYPE = OMNIVISION_OV4689_MIPI_1080P_30FPS
		#CFLAGS += -DSNS_OV4689_1080P_DOUBLE
		#CFLAGS += -DHI_MIPI_ENABLE
		
		#set hi3559 include directory
		SET(CP_IPC_HISIV_INCLUDE_DIR 
				${CP_THIRD_PARTY_DIR}/src/hi/hi3559/mpp/out/slave/include
				${CP_THIRD_PARTY_DIR}/src/hi/hi3559/mpp/sample/common
				)
		
		#set hi3559 lib directory
		SET(CP_IPC_HISIV_LIB_DIR 
				${CP_THIRD_PARTY_DIR}/src/hi/hi3559/mpp/out/slave/lib/release
				${CP_THIRD_PARTY_DIR}/lib/arm-hisiv600/ortp-0.24.0/lib/
				)
				
		#set hi3559 depends libraries
		SET(CP_IPC_HISIV_LIBRARIES
				libisp.a
				libupvqe.a
				libdnvqe.a
				lib_hiae.a
				lib_hiaf.a
				lib_hiawb_dv.a
				lib_hidefog.a
				libhistitch.a
				libive.a
				libmd.a
				libupvqe.a
				libVoiceEngine.a
				libmpi.a
				libhi_osal.a
				libhidis.a
				libupvqe.a
				)
ENDIF()
      

#set src directory
SET(CP_IPC_SRC_DIR ${CP_IPC_PROJECT_SOURCE_DIR}/src)
#set include directory
SET(CP_IPC_INCLUDE_DIR ${CP_IPC_PROJECT_SOURCE_DIR}/include)
#set lib directory
SET(CP_IPC_LIBRARY_DIR ${CP_IPC_PROJECT_SOURCE_DIR}/lib)



		


#get file list
AUX_SOURCE_DIRECTORY(${CP_IPC_SRC_DIR} CP_IPC_EXECUTABLE_FILES_LIST)

#add all subdirectory
ADD_SUBDIRECTORY(${CP_IPC_SRC_DIR})

#MESSAGE(STATUS "CP_IPC_EXECUTABLE_FILES_LIST : "${CP_IPC_EXECUTABLE_FILES_LIST})

#add ipc include direntories
INCLUDE_DIRECTORIES(
    ${CP_IPC_INCLUDE_DIR}
    ${CP_IPC_HISIV_INCLUDE_DIR}
    )


#add ipc library directories 
LINK_DIRECTORIES(
    ${CP_IPC_LIBRARY_DIR}
    ${CP_IPC_HISIV_LIB_DIR}
    )
    
    
#MESSAGE(STATUS "CP_IPC_LIBRARY_DIR : "${CP_IPC_LIBRARY_DIR})


#add targe
SET(EXECUTABLE_OUTPUT_PATH ${CP_PROJECT_OUTPUT_TOP_DIR}/${CP_IPC_EXECUTABLE_NAME})

MESSAGE(STATUS " ")
MESSAGE(STATUS " ")
MESSAGE(STATUS "-----------------build project:[ ${CP_IPC_EXECUTABLE_NAME} ]-----------------")
MESSAGE(STATUS "c compiler:[ ${CMAKE_C_COMPILER} ] cxx compiler:[ ${CMAKE_CXX_COMPILER} ]")
MESSAGE(STATUS "project:[ ${CP_IPC_EXECUTABLE_NAME} ] path  : [ ${CP_IPC_PROJECT_SOURCE_DIR} ]")
MESSAGE(STATUS "project:[ ${CP_IPC_EXECUTABLE_NAME} ] output: [ ${EXECUTABLE_OUTPUT_PATH} ]")
MESSAGE(STATUS "project:[ ${CP_IPC_EXECUTABLE_NAME} ] include path  : [ ${CP_IPC_HISIV_INCLUDE_DIR} ]")
MESSAGE(STATUS "project:[ ${CP_IPC_EXECUTABLE_NAME} ] library path: [ ${CP_IPC_HISIV_LIB_DIR} ]")

ADD_EXECUTABLE(${CP_IPC_EXECUTABLE_NAME} ${CP_IPC_EXECUTABLE_FILES_LIST})
TARGET_LINK_LIBRARIES(${CP_IPC_EXECUTABLE_NAME}
    ${CP_PROJECT_LIBRARY_STATIC_NAME}
		${CP_IPC_HISIV_LIBRARIES}
	
		libortp.a
		libxml2.a
		libuv.a
		libzlog.a
		libiniparser.a
		libgmf_parser.a
		libuuid.a
		
		libz.a
		liblzma.a
		libcharset.a
		libiconv.a
		liblfds710.a
		librt.a
		libm.a
		)
		
		
MESSAGE(STATUS "executable:[${CP_IPC_EXECUTABLE_NAME}]")



