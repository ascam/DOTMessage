##################################
#      DOT Messages Sources      #
##################################

add_subdirectory(factories)
#add_subdirectory(datasources)

set(SOURCES ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/document.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/object.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/text.cpp
 #   ${CMAKE_CURRENT_SOURCE_DIR}/barcode.cpp
 #   ${CMAKE_CURRENT_SOURCE_DIR}/image.cpp
 #   ${CMAKE_CURRENT_SOURCE_DIR}/primitive.cpp
 #   ${CMAKE_CURRENT_SOURCE_DIR}/diamond.cpp
 #   ${CMAKE_CURRENT_SOURCE_DIR}/ellipse.cpp
 #   ${CMAKE_CURRENT_SOURCE_DIR}/line.cpp
 #   ${CMAKE_CURRENT_SOURCE_DIR}/rectangle.cpp
    PARENT_SCOPE
    )

set(HEADERS ${HEADERS}
    PARENT_SCOPE
    )

