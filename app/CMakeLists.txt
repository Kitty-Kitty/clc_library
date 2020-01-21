#set app player directory
SET(CP_APP_PLAYER_DIR ${CP_APP_DIR}/player)
#set app ipc directory
SET(CP_APP_IPC_DIR ${CP_APP_DIR}/ipc360)
#set app ecam directory
SET(CP_APP_ECAM_DIR ${CP_APP_DIR}/enforce_camera)
#set app test_cp_lib directory
SET(CP_APP_TEST_CP_LIB_DIR ${CP_APP_DIR}/test_cp_lib)
#set app console directory
SET(CP_APP_CONSOLE_DIR ${CP_APP_DIR}/console)

#set app css_encrypt directory
SET(CP_APP_CSS_ENCRYPT_DIR ${CP_APP_DIR}/css_encrypt)

#set app test directory
SET(CP_APP_TEST_DIR ${CP_APP_DIR}/test)

#set app vector_data_unit directory
SET(CP_APP_VECTOR_DATA_UNIT_DIR ${CP_APP_DIR}/vector_data_unit)


#set hisiv500 platform
IF(${CP_PLATFORM} STREQUAL "hisiv500")
	#add app ipc directory
	ADD_SUBDIRECTORY(${CP_APP_IPC_DIR})
	#add app ecam directory
	ADD_SUBDIRECTORY(${CP_APP_ECAM_DIR})
ELSEIF(${CP_PLATFORM} STREQUAL "hisiv600")
	#add app ipc directory
	ADD_SUBDIRECTORY(${CP_APP_IPC_DIR})
ELSEIF(${CP_PLATFORM} STREQUAL "hisiv400")
	#add app player directory [hisiv400]
	#ADD_SUBDIRECTORY(${CP_APP_CSS_ENCRYPT_DIR})

	#add app player directory [hisiv400]
	#ADD_SUBDIRECTORY(${CP_APP_PLAYER_DIR})

	#add app vector_data_unit directory [hisiv400]
	ADD_SUBDIRECTORY(${CP_APP_VECTOR_DATA_UNIT_DIR})
ELSE()
	#add app player directory [x86 / hisiv100 / raspberry_pi3]
	ADD_SUBDIRECTORY(${CP_APP_PLAYER_DIR})

	#add app console directory
	ADD_SUBDIRECTORY(${CP_APP_CONSOLE_DIR})
ENDIF()



#add app test_cp_lib directory
#ADD_SUBDIRECTORY(${CP_APP_TEST_CP_LIB_DIR})
#add app test directory
#ADD_SUBDIRECTORY(${CP_APP_TEST_DIR})