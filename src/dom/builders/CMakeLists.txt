#######################################
#  DOT Messages builders sources      #
#######################################

add_subdirectory(nisx)
add_subdirectory(linx)

set(SOURCES ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/nisxparser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/linxparser.cpp
    PARENT_SCOPE
    )

set(HEADERS ${HEADERS}
    PARENT_SCOPE
    )

