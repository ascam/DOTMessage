#######################################
#  DOT Messages builders sources      #
#######################################

add_subdirectory(nisx)

set(SOURCES ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/nisxparser.cpp
    PARENT_SCOPE
    )

set(HEADERS ${HEADERS}
    PARENT_SCOPE
    )

