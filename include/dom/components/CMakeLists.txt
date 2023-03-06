###############################
#    DOM component headers    #
###############################

add_subdirectory(datasources)

set(SOURCES ${SOURCES}
    PARENT_SCOPE
    )

set(HEADERS ${HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/alignment.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/barcodesymbologies.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/color.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/font.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/geometry.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/pen.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/textboxproperties.hpp
    PARENT_SCOPE
    )

set(INCLUDES ${INCLUDES}
	${CMAKE_CURRENT_SOURCE_DIR}
	PARENT_SCOPE
)
