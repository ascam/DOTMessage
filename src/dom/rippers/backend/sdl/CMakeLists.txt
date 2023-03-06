##########################
#  SDL backend sources	  #
##########################

set(SOURCES ${SOURCES}
	${CMAKE_CURRENT_SOURCE_DIR}/sdlgenerator.cpp
	PARENT_SCOPE
	)

set(HEADERS ${HEADERS}
	${CMAKE_CURRENT_SOURCE_DIR}/sdlgenerator.hpp
	PARENT_SCOPE
	)
	
set(INCLUDES ${INCLUDES}
	${CMAKE_CURRENT_SOURCE_DIR}
	PARENT_SCOPE
)	
