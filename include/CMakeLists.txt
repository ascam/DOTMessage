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
    ${CMAKE_CURRENT_SOURCE_DIR}/object.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/objecttype.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/refreshpolicy.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/text.hpp
#    ${CMAKE_CURRENT_SOURCE_DIR}/barcode.hpp
#    ${CMAKE_CURRENT_SOURCE_DIR}/image.hpp
#    ${CMAKE_CURRENT_SOURCE_DIR}/primitive.hpp
#    ${CMAKE_CURRENT_SOURCE_DIR}/diamond.hpp
#    ${CMAKE_CURRENT_SOURCE_DIR}/ellipse.hpp
#    ${CMAKE_CURRENT_SOURCE_DIR}/line.hpp
#    ${CMAKE_CURRENT_SOURCE_DIR}/rectangle.hpp
    PARENT_SCOPE
    )

