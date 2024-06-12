##############################################
#    DOT Messages DOM datasources headers    #
##############################################

set(SOURCES ${SOURCES}
    PARENT_SCOPE
    )

set(HEADERS ${HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/datasource.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/compositedatasource.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/counterdatasource.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/databasedatasource.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/datetimedatasource.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/datetimesource.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/offsettime.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/userinputdatasource.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/roundingdatepolicy.hpp
    PARENT_SCOPE
    )

