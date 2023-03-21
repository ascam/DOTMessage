##################################
#    DOT Messages Unit Tests     #
##################################

# add_subdirectory(components)
# add_subdirectory(writers)
# add_subdirectory(builders)
# add_subdirectory(rippers)
 
set(SRC_TEST ${SRC_TEST}
	${CMAKE_CURRENT_SOURCE_DIR}/document_ut.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/variableobject_ut.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/barcode_ut.cpp
	PARENT_SCOPE
    )

set(HDRS_TEST ${HDRS_TEST}
	${CMAKE_CURRENT_SOURCE_DIR}/mockvariableobject.hpp
	PARENT_SCOPE
    )
