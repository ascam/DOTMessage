##################################
#      DOT Messages Sources      #
##################################

#add_subdirectory(datasources)

set(SOURCES ${SOURCES}
    PARENT_SCOPE
    )

set(HEADERS ${HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/document.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/geometry.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/color.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/font.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/object.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/objecttype.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/refreshpolicy.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/textboxproperties.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/alignment.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/text.hpp
#    ${CMAKE_CURRENT_SOURCE_DIR}/barcode.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/image.hpp
#    ${CMAKE_CURRENT_SOURCE_DIR}/primitives.hpp
    PARENT_SCOPE
    )

