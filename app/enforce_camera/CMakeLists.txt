

#set cp_enforce_camera executable name
SET(CP_ECAM_EXECUTABLE_NAME cp_enforce_camera)

#set cp_enforce_camera root directory
SET(CP_ECAM_PROJECT_SOURCE_DIR ${CP_APP_ECAM_DIR})


IF(${CP_PLATFORM} STREQUAL "hisiv500")
		#set hi3516c mode
		ADD_DEFINITIONS(-DCP_HI3519_MODE=1)
		ADD_DEFINITIONS(-DSENSOR_TYPE=OMNIVISION_OV4689_MIPI_1080P_30FPS)
		#ADD_DEFINITIONS(-DSENSOR_TYPE=OMNIVISION_OV4689_MIPI_4M_30FPS)
		ADD_DEFINITIONS(-DSNS_OV4689_1080P_DOUBLE)
		ADD_DEFINITIONS(-DHI_MIPI_ENABLE)
		#SENSOR_TYPE = OMNIVISION_OV4689_MIPI_1080P_30FPS
		#CFLAGS += -DSNS_OV4689_1080P_DOUBLE
		#CFLAGS += -DHI_MIPI_ENABLE
ENDIF()
      

#set src directory
SET(CP_ECAM_SRC_DIR ${CP_ECAM_PROJECT_SOURCE_DIR}/src)
#set include directory
SET(CP_ECAM_INCLUDE_DIR ${CP_ECAM_PROJECT_SOURCE_DIR}/include)
#set lib directory
SET(CP_ECAM_LIBRARY_DIR ${CP_ECAM_PROJECT_SOURCE_DIR}/lib)
#set hi3516c include directory
SET(CP_ECAM_HI3519V101_INCLUDE_DIR 
		${CP_THIRD_PARTY_DIR}/src/hi/hi3516c/mpp/include
		${CP_THIRD_PARTY_DIR}/src/hi/hi3516c/mpp/sample/common
		)
		
#set hi3516c lib directory
SET(CP_ECAM_HI3519V101_LIB_DIR 
		${CP_THIRD_PARTY_DIR}/src/hi/hi3516c/mpp/lib
		)
		


#get file list
AUX_SOURCE_DIRECTORY(${CP_ECAM_SRC_DIR} CP_ECAM_EXECUTABLE_FILES_LIST)

#add all subdirectory
ADD_SUBDIRECTORY(${CP_ECAM_SRC_DIR})

#MESSAGE(STATUS "CP_ECAM_EXECUTABLE_FILES_LIST : "${CP_ECAM_EXECUTABLE_FILES_LIST})

#add ecam include direntories
INCLUDE_DIRECTORIES(
    ${CP_ECAM_INCLUDE_DIR}
    ${CP_ECAM_HI3519V101_INCLUDE_DIR}
    )


#add ecam library directories 
LINK_DIRECTORIES(
    ${CP_ECAM_LIBRARY_DIR}
    ${CP_ECAM_HI3519V101_LIB_DIR}
    )
    
    
#MESSAGE(STATUS "CP_ECAM_LIBRARY_DIR : "${CP_ECAM_LIBRARY_DIR})


#add targe
SET(EXECUTABLE_OUTPUT_PATH ${CP_PROJECT_OUTPUT_TOP_DIR}/${CP_ECAM_EXECUTABLE_NAME})

MESSAGE(STATUS " ")
MESSAGE(STATUS " ")
MESSAGE(STATUS "-----------------build project:[ ${CP_ECAM_EXECUTABLE_NAME} ]-----------------")
MESSAGE(STATUS "c compiler:[ ${CMAKE_C_COMPILER} ] cxx compiler:[ ${CMAKE_CXX_COMPILER} ]")
MESSAGE(STATUS "project:[ ${CP_ECAM_EXECUTABLE_NAME} ] path  : [ ${CP_ECAM_PROJECT_SOURCE_DIR} ]")
MESSAGE(STATUS "project:[ ${CP_ECAM_EXECUTABLE_NAME} ] output: [ ${EXECUTABLE_OUTPUT_PATH} ]")

ADD_EXECUTABLE(${CP_ECAM_EXECUTABLE_NAME} ${CP_ECAM_EXECUTABLE_FILES_LIST})
TARGET_LINK_LIBRARIES(${CP_ECAM_EXECUTABLE_NAME}
    ${CP_PROJECT_LIBRARY_STATIC_NAME}
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
		
		
MESSAGE(STATUS "executable:[${CP_ECAM_EXECUTABLE_NAME}]")



