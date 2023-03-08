##################################
#      DOM Writers Sources      #
##################################

add_subdirectory(nisx)

set(SOURCES ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/nisxwriter.cpp
    PARENT_SCOPE
    )

set(HEADERS ${HEADERS}
    PARENT_SCOPE
    )

