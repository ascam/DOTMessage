######################################
#      DOT Messages datasources      #
######################################

set(SOURCES ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compositedatasource.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/counterdatasource.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/databasedatasource.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/datetimedatasource.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/userinputdatasource.cpp
    PARENT_SCOPE
    )

set(HEADERS ${HEADERS}
    PARENT_SCOPE
    )

