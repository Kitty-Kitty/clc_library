#set cp_vdu name
SET(CP_VDU_LIBRARY_PROJECT_NAME cp_vdu)
SET(CP_VDU_LIBRARY_LIBRARY_STATIC_NAME lib${CP_VDU_LIBRARY_PROJECT_NAME}.a)
SET(CP_VDU_LIBRARY_LIBRARY_SHARED_NAME lib${CP_VDU_LIBRARY_PROJECT_NAME}.so)

#set app vdu directory
SET(CP_APP_VDU_DIR ${CP_APP_VECTOR_DATA_UNIT_DIR}/vdu)

#set app vdu_demo directory
SET(CP_APP_VDU_DEMO_DIR ${CP_APP_VECTOR_DATA_UNIT_DIR}/vdu_demo)

#set app vdu_simple_demo directory
SET(CP_APP_VDU_SIMPLE_DEMO_DIR ${CP_APP_VECTOR_DATA_UNIT_DIR}/vdu_simple_demo)


#grep "\"V" /opt/Project/hi3536/cp_player/app/vector_data_unit/vdu/include/cp_vdu_version.h -m 1 | awk "{print $3}"|awk -F "\"" "{print $2}" | awk -F "V" "{print $2}"
EXECUTE_PROCESS(
    COMMAND grep "\"V" ${CP_APP_VDU_DIR}/include/cp_vdu_version.h -m 1 
    COMMAND awk "{print $3}"
    COMMAND awk -F "\"" "{print $2}"
    COMMAND awk -F "V" "{print $2}"
    OUTPUT_VARIABLE CP_APP_VDU_VERSION
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

IF( CP_APP_VDU_VERSION )
    SET(CP_VDU_LIBRARY_LIBRARY_STATIC_NAME lib${CP_VDU_LIBRARY_PROJECT_NAME}-${CP_APP_VDU_VERSION}.a)
    SET(CP_VDU_LIBRARY_LIBRARY_SHARED_NAME lib${CP_VDU_LIBRARY_PROJECT_NAME}-${CP_APP_VDU_VERSION}.so)
ENDIF()



#add app vdu directory
ADD_SUBDIRECTORY(${CP_APP_VDU_DIR})
#add app vdu_demo directory
#ADD_SUBDIRECTORY(${CP_APP_VDU_DEMO_DIR})
#add app vdu_simple_demo directory
ADD_SUBDIRECTORY(${CP_APP_VDU_SIMPLE_DEMO_DIR})