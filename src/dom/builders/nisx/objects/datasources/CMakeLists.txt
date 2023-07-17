#############################################
#      NisX Datasources parsers sources     #
#############################################

set(SOURCES ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compositeparser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/counterparser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/databaseparser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/datetimeparser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/userinputparser.cpp
    PARENT_SCOPE
    )

set(HEADERS ${HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/compositeparser.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/counterparser.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/databaseparser.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/datasourceparser.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/datetimeparser.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/userinputparser.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/datasourceparsersfactory.hpp
    PARENT_SCOPE
    )

