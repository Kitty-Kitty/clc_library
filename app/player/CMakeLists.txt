

#set css_player executable name
SET(CP_PLAYER_EXECUTABLE_NAME cp_player)

#set css_player root directory
SET(CP_PLAYER_PROJECT_SOURCE_DIR ${CP_APP_PLAYER_DIR})


#set src directory
SET(CP_PLAYER_SRC_DIR ${CP_PLAYER_PROJECT_SOURCE_DIR}/src)
#set include directory
SET(CP_PLAYER_INCLUDE_DIR ${CP_PLAYER_PROJECT_SOURCE_DIR}/include)
#set lib directory
SET(CP_PLAYER_LIBRARY_DIR ${CP_PLAYER_PROJECT_SOURCE_DIR}/lib)



#get file list
AUX_SOURCE_DIRECTORY(${CP_PLAYER_SRC_DIR} CP_PLAYER_EXECUTABLE_FILES_LIST)

#add all subdirectory
ADD_SUBDIRECTORY(${CP_PLAYER_SRC_DIR})

#MESSAGE(STATUS "CP_PLAYER_EXECUTABLE_FILES_LIST : "${CP_PLAYER_EXECUTABLE_FILES_LIST})

#set x86 platform
IF(${CP_PLATFORM} STREQUAL "hisiv100")
	#set hi3519 mode
	ADD_DEFINITIONS(-DCP_HI3531_VDEC_MODE=1)
	ADD_DEFINITIONS(-DCP_HI3531_DEV_MODE=1)
	
	#set hi3531 include directory
	SET(CP_PLAYER_SRC_HI3531_VDEC_INCLUDE_DIR 
			${CP_THIRD_PARTY_DIR}/src/hi/hi3531/mpp/include
			)
		
	#set hi3531 lib directory
	SET(CP_PLAYER_SRC_HI3531_VDEC_LIB_DIR 
			${CP_THIRD_PARTY_DIR}/src/hi/hi3531/mpp/lib
			)

	SET(CP_PLAYER_LINK_LIBRARIES
		${CP_PROJECT_LIBRARY_STATIC_NAME}
		
		libmpi.a
		libaec.a
		libmem.a
		libhdmi.a
		libjpeg.a
		libanr.a
		libpciv.a
		libresampler.a
		libtde.a
		libVoiceEngine.a
		
		libSDL2.a
		
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
ENDIF()

IF(${CP_PLATFORM} STREQUAL "x86")
	SET(SYSTEM_USR_I686_INCLUDE_DIR /usr/lib/i686-redhat-linux6E/include/)
	SET(SYSTEM_USR_I686_LIB_DIR /usr/lib/i686-redhat-linux6E/lib/)

	#add system include direntories
	INCLUDE_DIRECTORIES(
    	${SYSTEM_USR_I686_INCLUDE_DIR}
    )

	#add system library directories 
	LINK_DIRECTORIES(
    ${SYSTEM_USR_I686_LIB_DIR}
    )
    
  SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lbz2")
  
  SET(CP_PLAYER_LINK_LIBRARIES
		${CP_PROJECT_LIBRARY_STATIC_NAME}
		
		libavformat.a
		libavdevice.a
		libavcodec.a
		libavfilter.a
		libavutil.a
		libswscale.a
		libswresample.a
		libSDL2.a
		libx264.a
		
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
	
ENDIF()

IF(${CP_PLATFORM} STREQUAL "raspberry_pi3")  
  SET(CP_PLAYER_LINK_LIBRARIES
		${CP_PROJECT_LIBRARY_STATIC_NAME}
		
		libavformat.a
		libavdevice.a
		libavcodec.a
		libavfilter.a
		libavutil.a
		libswscale.a
		libswresample.a
		libSDL2.a
		libx264.a
		
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
	
ENDIF()

#add player include direntories
INCLUDE_DIRECTORIES(
    ${CP_PLAYER_INCLUDE_DIR}
    ${CP_PLAYER_SRC_HI3531_VDEC_INCLUDE_DIR}
    )

#add player library directories 
LINK_DIRECTORIES(
    ${CP_PLAYER_LIBRARY_DIR}
    ${CP_PLAYER_SRC_HI3531_VDEC_LIB_DIR}
    )
#MESSAGE(STATUS "CP_PLAYER_LIBRARY_DIR : "${CP_PLAYER_LIBRARY_DIR})


#add targe
SET(EXECUTABLE_OUTPUT_PATH ${CP_PROJECT_OUTPUT_TOP_DIR}/${CP_PLAYER_EXECUTABLE_NAME})

MESSAGE(STATUS " ")
MESSAGE(STATUS " ")
MESSAGE(STATUS "-----------------build project:[ ${CP_PLAYER_EXECUTABLE_NAME} ]-----------------")
MESSAGE(STATUS "c compiler:[ ${CMAKE_C_COMPILER} ] cxx compiler:[ ${CMAKE_CXX_COMPILER} ]")
MESSAGE(STATUS "project:[ ${CP_PLAYER_EXECUTABLE_NAME} ] path  : [ ${CP_PLAYER_PROJECT_SOURCE_DIR} ]")
MESSAGE(STATUS "project:[ ${CP_PLAYER_EXECUTABLE_NAME} ] output: [ ${EXECUTABLE_OUTPUT_PATH} ]")


#SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pie")
#SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -pie")


#MESSAGE(STATUS "project[" ${CP_PLAYER_EXECUTABLE_NAME} "] libraries: "${CP_PLAYER_LINK_LIBRARIES})

ADD_EXECUTABLE(${CP_PLAYER_EXECUTABLE_NAME} ${CP_PLAYER_EXECUTABLE_FILES_LIST})
TARGET_LINK_LIBRARIES(${CP_PLAYER_EXECUTABLE_NAME}
      ${CP_PLAYER_LINK_LIBRARIES}
		)
		
MESSAGE(STATUS "executable:[${CP_PLAYER_EXECUTABLE_NAME}]")



