
CMAKE_MINIMUM_REQUIRED(VERSION 2.8 FATAL_ERROR)


#project name 
PROJECT(CP_PROJECT C CXX ASM)


# this one is important
SET(CMAKE_SYSTEM_NAME Linux)


#set library name
SET(CP_PROJECT_NAME cp_lib)
SET(CP_PROJECT_LIBRARY_STATIC_NAME lib${CP_PROJECT_NAME}.a)
SET(CP_PROJECT_LIBRARY_SHARED_NAME lib${CP_PROJECT_NAME}.so)
#set cp source directory
SET(CP_PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR})



#grep "\"V" /opt/Project/hi3536/cp_player/include/cp_version.h -m 1 | awk "{print $3}"|awk -F "\"" "{print $2}" | awk -F "V" "{print $2}"
EXECUTE_PROCESS(
    COMMAND grep "\"V" ${CP_PROJECT_SOURCE_DIR}/include/cp_version.h -m 1 
    COMMAND awk "{print $3}"
    COMMAND awk -F "\"" "{print $2}"
    COMMAND awk -F "V" "{print $2}"
    OUTPUT_VARIABLE CP_PROJECT_LIBRARY_VERSION
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

IF( CP_PROJECT_LIBRARY_VERSION )
    SET(CP_PROJECT_LIBRARY_STATIC_NAME lib${CP_PROJECT_NAME}-${CP_PROJECT_LIBRARY_VERSION}.a)
    SET(CP_PROJECT_LIBRARY_SHARED_NAME lib${CP_PROJECT_NAME}-${CP_PROJECT_LIBRARY_VERSION}.so)
ENDIF()



#set system support platform
SET(CP_PLATFORM_LIST "x86" "hisiv100" "hisiv400" "hisiv500" "hisiv600" "raspberry_pi3" "cpptestscan")
SET(CP_PLATFORM, "x86")
SET(CP_THIRD_PARTY_PLATFORM_NAME "x86")



IF(NOT DEFINED PLATFORM)
	MESSAGE(WARNING "set platform warning. parameter[PLATFORM] not defined. used default [PLATFORM = x86]")
	MESSAGE(STATUS "[ctrl + c] to stop; usage: [cmake PLATFORM=x86 ../] ; wait [5] seconds for you ...")
	#CTEST_SLEEP(5)
ELSE()
	MESSAGE(STATUS "set parameter[PLATFORM = ${PLATFORM}] ")
	SET(CP_PLATFORM ${PLATFORM})
ENDIF()


LIST(FIND CP_PLATFORM_LIST ${CP_PLATFORM} FIND_LIST_RETURN)
IF(${FIND_LIST_RETURN} EQUAL -1)
	MESSAGE(STATUS "usage: [cmake CP_PLATFORM=x86 ../] " "  ${FIND_LIST_RETURN}")
	MESSAGE(FATAL_ERROR "system usupport[CP_PLATFORM = ${CP_PLATFORM}] support system list[${CP_PLATFORM_LIST}]")
ENDIF()



#set compiler
#set general compiler
SET(CMAKE_ASM_NASM_COMPILER "as")
SET(CMAKE_C_COMPILER "gcc")
SET(CMAKE_CXX_COMPILER "g++")
SET(CMAKE_CXX_COMPILER_FULLPATH "/usr/bin/g++")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wwrite-strings -Wl,-Bsymbolic")


SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lpthread  -ldl -lrt -lc")
SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -lpthread -ldl -lrt -lc")


#select a mode
IF(DEBUG_MODE)        #cmake -D DEBUG_MODE=ON ../
		SET(CMAKE_BUILD_TYPE Debug)
    #set cp output debug directory
    SET(CP_PROJECT_OUTPUT_TOP_DIR ${PROJECT_BINARY_DIR}/debug)
    SET(CMAKE_C_FLAGS_DEBUG "$ENV{CFLAGS} ${CMAKE_C_FLAGS_DEBUG} -ggdb3 -lpthread_nonshared -lrt")
    SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -ggdb3 -lpthread -lrt")
    MESSAGE(STATUS "use the [debug] mode! output_path: [ ${CP_PROJECT_OUTPUT_TOP_DIR} ]" )
ELSE()
    SET(CMAKE_BUILD_TYPE Release)
    #set cp output release directory
    SET(CP_PROJECT_OUTPUT_TOP_DIR ${PROJECT_BINARY_DIR}/release)
    SET(CMAKE_C_FLAGS_RELEASE "$ENV{CFLAGS} ${CMAKE_C_FLAGS_RELEASE} -pipe -lpthread_nonshared -lrt")
		SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} ${CMAKE_CXX_FLAGS_RELEASE} -pipe -lpthread -lrt")
    MESSAGE(STATUS "use the [release] mode! output_path: [ ${CP_PROJECT_OUTPUT_TOP_DIR} ]" )
ENDIF()


IF(BUILD_NULL_LOG)                        #cmake -D BUILD_NULL_LOG=ON ../
  ADD_DEFINITIONS(-DCP_LOG_USED_NULL)
  MESSAGE(STATUS "set [BUILD_NULL_LOG] mode, log type [CP_LOG_USED_NULL]" )
ELSEIF(BUILD_FILE_LOG)                   #cmake -D BUILD_FILE_LOG=ON ../
  ADD_DEFINITIONS(-DCP_LOG_USED_FILE)
  MESSAGE(STATUS "set [BUILD_FILE_LOG] mode, log type [CP_LOG_USED_FILE]" )
ELSE()
  MESSAGE(STATUS "not set log mode, log type system print" )
ENDIF()

#SET(SYSTEM_USR_INCLUDE_DIR /usr/include/)
#SET(SYSTEM_USR_LOCAL_INCLUDE_DIR /usr/local/include/)
#SET(SYSTEM_USR_LIBRARY_DIR /usr/lib/)
#SET(SYSTEM_USR_LOCAL_LIBRARY_DIR /usr/local/lib/)

#set hisiv100 platform
IF(${CP_PLATFORM} STREQUAL "hisiv100")
	SET(CMAKE_ASM_NASM_COMPILER "as")
  SET(CMAKE_C_COMPILER "arm-hisiv100nptl-linux-gcc")
  SET(CMAKE_CXX_COMPILER "arm-hisiv100nptl-linux-g++")
  SET(CMAKE_CXX_COMPILER_FULLPATH "/opt/hisi-linux-nptl/arm-hisiv100-linux/target/bin/arm-hisiv100-linux-gcc")
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wwrite-strings -Wl,-Bsymbolic")
  
  SET(CMAKE_C_FLAGS_DEBUG "$ENV{CFLAGS} ${CMAKE_C_FLAGS_DEBUG} -ggdb3 -lpthread -lrt")
	SET(CMAKE_C_FLAGS_RELEASE "$ENV{CFLAGS} ${CMAKE_C_FLAGS_RELEASE} -pipe -lpthread -lrt")
  
	SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -ggdb3 -lpthread -lrt")
	SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} ${CMAKE_CXX_FLAGS_RELEASE} -pipe -lpthread -lrt")
  
  SET(SYSTEM_USR_INCLUDE_DIR /opt/hisi-linux-nptl/arm-hisiv100-linux/target/usr/include)
	SET(SYSTEM_USR_LIBRARY_DIR /opt/hisi-linux-nptl/arm-hisiv100-linux/target/usr/lib/)
	
  SET(CP_THIRD_PARTY_PLATFORM_NAME "arm-hisiv100nptl")
  ADD_DEFINITIONS(-DPLATFORM_HISIV100)
  
  
ENDIF()

#set hisiv400 platform
IF(${CP_PLATFORM} STREQUAL "hisiv400")
	SET(CMAKE_ASM_NASM_COMPILER "as")
  SET(CMAKE_C_COMPILER "arm-hisiv400-linux-gcc")
  SET(CMAKE_CXX_COMPILER "arm-hisiv400-linux-g++")
  SET(CMAKE_CXX_COMPILER_FULLPATH "/opt/hisi-linux/x86-arm/arm-hisiv400-linux/target/bin/arm-hisiv400-linux-gcc")
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wwrite-strings -Wl,-Bsymbolic")
  
  SET(CMAKE_C_FLAGS_DEBUG "$ENV{CFLAGS} ${CMAKE_C_FLAGS_DEBUG} -ggdb3 -lpthread -ldl -lrt")
	SET(CMAKE_C_FLAGS_RELEASE "$ENV{CFLAGS} ${CMAKE_C_FLAGS_RELEASE} -pipe -lpthread -ldl -lrt")
  
	SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -ggdb3 -lpthread -ldl -lrt")
	SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} ${CMAKE_CXX_FLAGS_RELEASE} -pipe -lpthread -ldl -lrt")
  
  SET(SYSTEM_USR_INCLUDE_DIR /opt/hisi-linux/x86-arm/arm-hisiv400-linux/target/usr/include)
	SET(SYSTEM_USR_LIBRARY_DIR /opt/hisi-linux/x86-arm/arm-hisiv400-linux/target/usr/lib)

  SET(CP_THIRD_PARTY_PLATFORM_NAME "arm-hisiv400")
  
  
ENDIF()


#set hisiv500 platform
IF(${CP_PLATFORM} STREQUAL "hisiv500")
	SET(CMAKE_ASM_NASM_COMPILER "as")
  SET(CMAKE_C_COMPILER "arm-hisiv500-linux-gcc")
  SET(CMAKE_CXX_COMPILER "arm-hisiv500-linux-g++")
  SET(CMAKE_CXX_COMPILER_FULLPATH "/opt/hisi-linux/x86-arm/arm-hisiv500-linux/target/bin/arm-hisiv500-linux-gcc")
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wwrite-strings -Wl,-Bsymbolic")
  
  SET(CMAKE_C_FLAGS_DEBUG "$ENV{CFLAGS} ${CMAKE_C_FLAGS_DEBUG} -ggdb3 -lpthread -lrt")
	SET(CMAKE_C_FLAGS_RELEASE "$ENV{CFLAGS} ${CMAKE_C_FLAGS_RELEASE} -pipe -lpthread -lrt")
  
	SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -ggdb3 -lpthread -lrt")
	SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} ${CMAKE_CXX_FLAGS_RELEASE} -pipe -lpthread -lrt")
  
  SET(SYSTEM_USR_INCLUDE_DIR /opt/hisi-linux/x86-arm/arm-hisiv500-linux/target/usr/include)
	SET(SYSTEM_USR_LIBRARY_DIR /opt/hisi-linux/x86-arm/arm-hisiv500-linux/target/usr/lib)

  SET(CP_THIRD_PARTY_PLATFORM_NAME "arm-hisiv500")
  
  
ENDIF()


#set hisiv600 platform
IF(${CP_PLATFORM} STREQUAL "hisiv600")
	SET(CMAKE_ASM_NASM_COMPILER "as")
  SET(CMAKE_C_COMPILER "arm-hisiv600-linux-gcc")
  SET(CMAKE_CXX_COMPILER "arm-hisiv600-linux-g++")
  SET(CMAKE_CXX_COMPILER_FULLPATH "/opt/hisi-linux/x86-arm/arm-hisiv600-linux/target/bin/arm-hisiv600-linux-gcc")
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wwrite-strings -Wl,-Bsymbolic")
  
  SET(CMAKE_C_FLAGS_DEBUG "$ENV{CFLAGS} ${CMAKE_C_FLAGS_DEBUG} -ggdb3 -lpthread -lrt")
	SET(CMAKE_C_FLAGS_RELEASE "$ENV{CFLAGS} ${CMAKE_C_FLAGS_RELEASE} -pipe -lpthread -lrt")
  
	SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -ggdb3 -lpthread -lrt")
	SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} ${CMAKE_CXX_FLAGS_RELEASE} -pipe -lpthread -lrt")
  
  SET(SYSTEM_USR_INCLUDE_DIR /opt/hisi-linux/x86-arm/arm-hisiv600-linux/target/usr/include)
	SET(SYSTEM_USR_LIBRARY_DIR /opt/hisi-linux/x86-arm/arm-hisiv600-linux/target/usr/lib)

  SET(CP_THIRD_PARTY_PLATFORM_NAME "arm-hisiv600")
  
  
ENDIF()


#set raspberry_pi3 platform
IF(${CP_PLATFORM} STREQUAL "raspberry_pi3")

	SET(CMAKE_ASM_NASM_COMPILER "arm-linux-gnueabihf-as")
  SET(CMAKE_C_COMPILER "arm-linux-gnueabihf-gcc")
  SET(CMAKE_CXX_COMPILER "arm-linux-gnueabihf-g++")
  SET(CMAKE_CXX_COMPILER_FULLPATH "/opt/raspberry_pi3_toolschain/arm-bcm2708/arm-rpi-4.9.3-linux-gnueabihf/bin/arm-linux-gnueabihf-g++")
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wwrite-strings -Wl,-Bsymbolic")
  
  SET(CP_THIRD_PARTY_PLATFORM_NAME "raspberry_pi3_gcc4.9.2" )
  
  SET(SYSTEM_USR_INCLUDE_DIR /usr/include/)
	SET(SYSTEM_USR_LOCAL_INCLUDE_DIR /usr/local/include/)
	SET(SYSTEM_USR_LIBRARY_DIR /usr/lib/)
	SET(SYSTEM_USR_LOCAL_LIBRARY_DIR /usr/local/lib/)

  
ENDIF()

#set x86 platform
IF(${CP_PLATFORM} STREQUAL "x86")
	SET(SYSTEM_USR_INCLUDE_DIR /usr/include/)
	SET(SYSTEM_USR_LOCAL_INCLUDE_DIR /usr/local/include/)
	SET(SYSTEM_USR_LIBRARY_DIR /usr/lib/)
	SET(SYSTEM_USR_LOCAL_LIBRARY_DIR /usr/local/lib/)
ENDIF()

#set cpptestscan platform
IF(${CP_PLATFORM} STREQUAL "cpptestscan")
	SET(CMAKE_ASM_NASM_COMPILER "as")
	SET(CMAKE_C_COMPILER "cpptestscan")
	SET(CMAKE_CXX_COMPILER "cpptestscan")
	SET(CMAKE_CXX_COMPILER_FULLPATH "/root/Project/Parasoft/parasoft/cpptest/9.0")
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --cpptestscanOutputFile=/home/CpptestProject/MyProject.bdf --cpptestscanProjectName=MyProject g++ -Wwrite-strings")
	SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --cpptestscanOutputFile=/home/CpptestProject/MyProject.bdf --cpptestscanProjectName=MyProject gcc")
  
  SET(CP_THIRD_PARTY_PLATFORM_NAME "cpptestscan" )
ENDIF()

MESSAGE(STATUS "set SYSTEM_USR_INCLUDE_DIR[ ${SYSTEM_USR_INCLUDE_DIR} ]")
MESSAGE(STATUS "set SYSTEM_USR_LIBRARY_DIR[ ${SYSTEM_USR_LIBRARY_DIR} ]")

MESSAGE(STATUS "set SYSTEM_USR_LOCAL_INCLUDE_DIR[ ${SYSTEM_USR_LOCAL_INCLUDE_DIR} ]")
MESSAGE(STATUS "set SYSTEM_USR_LOCAL_LIBRARY_DIR[ ${SYSTEM_USR_LOCAL_LIBRARY_DIR} ]")

MESSAGE(STATUS "system platform[${CP_PLATFORM}] used third library [${CP_THIRD_PARTY_PLATFORM_NAME}]")




#set x86_64 flag
IF( CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" )
	ADD_DEFINITIONS(-fPIC)
ENDIF( CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" )

#set include directory
SET(CP_INCLUDE_DIR ${CP_PROJECT_SOURCE_DIR}/include)
#set src directory
SET(CP_SRC_DIR ${CP_PROJECT_SOURCE_DIR}/src)
#set tests directory
SET(CP_TESTS_DIR ${CP_PROJECT_SOURCE_DIR}/tests)
#set third_party directory
SET(CP_THIRD_PARTY_DIR ${CP_PROJECT_SOURCE_DIR}/third-party)
#set app directory
SET(CP_APP_DIR ${CP_PROJECT_SOURCE_DIR}/app)
#set library directory
SET(CP_LIBRARY_DIR ${CP_PROJECT_OUTPUT_TOP_DIR})

#add system include direntories
INCLUDE_DIRECTORIES(
    ${SYSTEM_USR_INCLUDE_DIR}
    ${SYSTEM_USR_LOCAL_INCLUDE_DIR}
    ${CP_INCLUDE_DIR}
    )


#add system library directories 
LINK_DIRECTORIES(
    ${SYSTEM_USR_LIBRARY_DIR}
    ${SYSTEM_USR_LOCAL_LIBRARY_DIR}
    ${CP_PROJECT_OUTPUT_TOP_DIR}
    )

#print message
MESSAGE(STATUS " ")
MESSAGE(STATUS " ")
MESSAGE(STATUS "-----------------build project:[ ${CP_PROJECT_NAME} ]-----------------")
MESSAGE(STATUS "c compiler:[ ${CMAKE_C_COMPILER} ] cxx compiler:[ ${CMAKE_CXX_COMPILER} ]")
MESSAGE(STATUS "project:[ ${CP_PROJECT_NAME} ] path  : [ ${CP_PROJECT_SOURCE_DIR} ]")
MESSAGE(STATUS "project:[ ${CP_PROJECT_NAME} ] output: [ ${CP_PROJECT_OUTPUT_TOP_DIR} ]")


#set third-party directory
ADD_SUBDIRECTORY(${CP_THIRD_PARTY_DIR})

#build sub directory
ADD_SUBDIRECTORY(${CP_SRC_DIR})


#add include direntories
#MESSAGE(STATUS "update include path : "${CP_INCLUDE_DIR})
INCLUDE_DIRECTORIES(
    ${CP_INCLUDE_DIR}
    )
#add library directories 
LINK_DIRECTORIES(
    ${CP_LIBRARY_DIR}
    )
#MESSAGE(STATUS "library directories: "${CP_LIBRARY_DIR})
#MESSAGE(STATUS "${CP_LIBRARY_DIR}")
    
    
#build app directory
ADD_SUBDIRECTORY(${CP_APP_DIR})
#build tests directory
ADD_SUBDIRECTORY(${CP_TESTS_DIR})




