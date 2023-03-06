##################################
#      DOT Messages Sources      #
##################################

add_subdirectory(dom)

set(SOURCES ${SOURCES}
    PARENT_SCOPE
    )

set(HEADERS ${HEADERS}
    PARENT_SCOPE
    )
    
set(INCLUDES ${INCLUDES}
	${CMAKE_CURRENT_SOURCE_DIR}
	PARENT_SCOPE
)    

