
#set app css_encrypt src files list
#set app directory
SET(CP_CSS_ENCRYPT_SRC_APP_DIR ${CP_CSS_ENCRYPT_SRC_DIR}/app)
#set dev directory
SET(CP_CSS_ENCRYPT_SRC_DEV_DIR ${CP_CSS_ENCRYPT_SRC_DIR}/dev)



#add app source directory
ADD_SUBDIRECTORY(${CP_CSS_ENCRYPT_SRC_APP_DIR})
#add dev source directory
ADD_SUBDIRECTORY(${CP_CSS_ENCRYPT_SRC_DEV_DIR})



#add source file list
SET(CP_CSS_ENCRYPT_EXECUTABLE_FILES_LIST 
	${CP_CSS_ENCRYPT_EXECUTABLE_FILES_LIST} 

	PARENT_SCOPE
	)

#add include dir
SET(CP_CSS_ENCRYPT_INCLUDE_DIR
    ${CP_CSS_ENCRYPT_INCLUDE_DIR} 

	PARENT_SCOPE
	)
	
	
#MESSAGE(STATUS "css_encrypt file list:" ${CP_CSS_ENCRYPT_EXECUTABLE_FILES_LIST})
	
	