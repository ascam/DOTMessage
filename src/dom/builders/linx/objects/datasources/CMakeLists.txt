#############################################
#      NisX Datasources parsers sources     #
#############################################

set(SOURCES ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/dataparser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/userinputdataparser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/counterdataparser.cpp
    PARENT_SCOPE
    )

set(HEADERS ${HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/dataparser.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/userinputdataparser.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/counterdataparser.hpp
    PARENT_SCOPE
    )

