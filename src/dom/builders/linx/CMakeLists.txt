#################################
#      Linx parser Sources      #
#################################

add_subdirectory(objects)

set(SOURCES ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/documentparser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/docproperties.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/linxparsercontext.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/offsetdateparser.cpp
    PARENT_SCOPE
    )

set(HEADERS ${HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/documentparser.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/docproperties.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/offsetdate.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/linxparsercontext.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/offsetdateparser.hpp
    PARENT_SCOPE
    )
