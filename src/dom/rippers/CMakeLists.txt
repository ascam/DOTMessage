#####################################
#    DOM message rippers sources    #
#####################################

set(SOURCES ${SOURCES}
	${CMAKE_CURRENT_SOURCE_DIR}/ripper.cpp	
	PARENT_SCOPE
    )

set(HEADERS ${HEADERS}
	${CMAKE_CURRENT_SOURCE_DIR}/bitmapgenerator.hpp
	PARENT_SCOPE
    )
    
set(INCLUDES ${INCLUDES}
	${CMAKE_CURRENT_SOURCE_DIR}
	PARENT_SCOPE
)    
