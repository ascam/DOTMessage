#####################################
#  DOT Messages components Sources  #
#####################################

add_subdirectory(datasources)
add_subdirectory(symbologies)

set(SOURCES ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/color.cpp
    PARENT_SCOPE
    )

set(HEADERS ${HEADERS}
    PARENT_SCOPE
    )
    
set(INCLUDES ${INCLUDES}
	${CMAKE_CURRENT_SOURCE_DIR}
	PARENT_SCOPE
)     

