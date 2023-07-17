########################################
#      NisX Object parsers sources     #
########################################

add_subdirectory(datasources)

set(SOURCES ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/objectparser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/textparser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/textparser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/fontparser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/barcodeparser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/primitiveparser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/imageparser.cpp
    PARENT_SCOPE
    )

set(HEADERS ${HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/objectparser.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/textparser.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/fontparser.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/barcodeparser.hpp   
    ${CMAKE_CURRENT_SOURCE_DIR}/primitiveparser.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/imageparser.hpp
    PARENT_SCOPE
    )
