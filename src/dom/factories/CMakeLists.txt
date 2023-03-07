############################################
#      DOT Messages factories sources      #
############################################

set(SOURCES ${SOURCES}
    PARENT_SCOPE
    )

set(HEADERS ${HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/abstractobjectfactory.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/barcodesymbologyfactory.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/datasourcefactory.hpp
    PARENT_SCOPE
    )
    
set(INCLUDES ${INCLUDES}
	${CMAKE_CURRENT_SOURCE_DIR}
	PARENT_SCOPE
)     

