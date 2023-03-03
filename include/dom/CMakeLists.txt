##################################
#    DOT Messages DOM headers    #
##################################

add_subdirectory(datasources)
add_subdirectory(builders)
add_subdirectory(visitors)

set(SOURCES ${SOURCES}
    PARENT_SCOPE
    )

set(HEADERS ${HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/document.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/geometry.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/color.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/font.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/pen.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/object.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/objecttype.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/variableobject.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/refreshpolicy.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/textboxproperties.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/alignment.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/text.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/barcode.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/image.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/primitives.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/barcodesymbologies.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/idocumentbuilder.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/documentvisitor.hpp
    PARENT_SCOPE
    )
