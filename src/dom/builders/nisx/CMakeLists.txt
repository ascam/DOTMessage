#################################
#      NisX parser Sources      #
#################################

add_subdirectory(objects)

set(SOURCES ${SOURCES}
	${CMAKE_CURRENT_SOURCE_DIR}/documentparser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/docproperties.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/doccolors.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/fieldsparser.cpp
    PARENT_SCOPE
    )

set(HEADERS ${HEADERS}
	${CMAKE_CURRENT_SOURCE_DIR}/documentparser.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/docproperties.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/doccolors.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/fieldsparser.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/nisxcommonnames.hpp
    PARENT_SCOPE
    )
    
set(INCLUDES ${INCLUDES}
	${CMAKE_CURRENT_SOURCE_DIR}
	PARENT_SCOPE
)     
