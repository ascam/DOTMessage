##################################
#    DOT Messages Unit Tests     #
##################################

#add_subdirectory(builders)
 
set(SRC_TEST ${SRC_TEST}
    ${CMAKE_CURRENT_SOURCE_DIR}/objectparser_ut.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/datasourceparser_ut.cpp
	PARENT_SCOPE
    )

set(HDRS_TEST ${HDRS_TEST}
	PARENT_SCOPE
    )
