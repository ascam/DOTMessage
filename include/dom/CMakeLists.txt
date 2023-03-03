##################################
#    DOT Messages DOM headers    #
##################################

add_subdirectory(components)
add_subdirectory(builders)
add_subdirectory(visitors)

set(SOURCES ${SOURCES}
    PARENT_SCOPE
    )

set(HEADERS ${HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/document.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/object.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/objecttype.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/variableobject.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/refreshpolicy.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/text.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/barcode.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/image.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/primitives.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/idocumentbuilder.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/documentvisitor.hpp
    PARENT_SCOPE
    )
