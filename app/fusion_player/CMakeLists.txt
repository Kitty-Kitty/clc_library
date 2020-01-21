

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
ENDIF()

#add player include direntories
INCLUDE_DIRECTORIES(
    ${CP_PLAYER_INCLUDE_DIR}
    )


#add player library directories 
LINK_DIRECTORIES(
    ${CP_PLAYER_LIBRARY_DIR}
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


ADD_EXECUTABLE(${CP_PLAYER_EXECUTABLE_NAME} ${CP_PLAYER_EXECUTABLE_FILES_LIST})
TARGET_LINK_LIBRARIES(${CP_PLAYER_EXECUTABLE_NAME}
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
		
MESSAGE(STATUS "executable:[${CP_PLAYER_EXECUTABLE_NAME}]")



