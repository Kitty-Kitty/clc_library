


#set src files list
#set protocol directory
SET(CP_SRC_PROTOCOL_DIR ${CP_SRC_DIR}/protocol)




#add protocol source directory
AUX_SOURCE_DIRECTORY(${CP_SRC_PROTOCOL_DIR} CP_SRC_PROTOCOL_FILES_LIST)



#build sub directory
ADD_SUBDIRECTORY(${CP_SRC_PROTOCOL_DIR}/prot_css)



#add source file list
SET(CP_EXECUTABLE_FILES_LIST 
	${CP_EXECUTABLE_FILES_LIST} 
	${CP_SRC_PROTOCOL_FILES_LIST} 
	
	PARENT_SCOPE
	)


#add include dir
SET(CP_INCLUDE_DIR
	${CP_INCLUDE_DIR} 
	${CP_SRC_PROTOCOL_DIR}
	
	PARENT_SCOPE
	)



	