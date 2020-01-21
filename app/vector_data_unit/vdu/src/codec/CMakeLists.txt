#set src files list
#set vdu codecs directory


#add vdu codecs source directory
AUX_SOURCE_DIRECTORY(${CP_VDU_SRC_CODEC_DIR} CP_VDU_SRC_CODEC_VDU_FILES_LIST)


#build sub directory
ADD_SUBDIRECTORY(${CP_VDU_SRC_CODEC_DIR}/qt_svg)

#add source file list
SET(CP_VDU_LIBRARY_FILES_LIST 
	${CP_VDU_LIBRARY_FILES_LIST} 
	${CP_VDU_SRC_CODEC_VDU_FILES_LIST} 

	PARENT_SCOPE
	)

#add include dir
SET(CP_VDU_INCLUDE_DIR ${CP_VDU_INCLUDE_DIR} 
	${CP_VDU_SRC_CODEC_DIR}

	PARENT_SCOPE
	)