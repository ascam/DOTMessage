##################################
#      DOT Messages Sources      #
##################################

add_subdirectory(datasources)

set(SOURCES ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/color.cpp
    PARENT_SCOPE
    )

set(HEADERS ${HEADERS}
    PARENT_SCOPE
    )

