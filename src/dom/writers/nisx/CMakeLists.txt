#################################
#      NisX Writer Sources      #
#################################

set(SOURCES ${SOURCES}
	${CMAKE_CURRENT_SOURCE_DIR}/documentvisitor.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/objectvisitor.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/textvisitor.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/barcodevisitor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/imagevisitor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/primitivesvisitor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/variableobjectvisitor.cpp
    PARENT_SCOPE
    )

set(HEADERS ${HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/documentvisitor.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/objectvisitor.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/textvisitor.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/barcodevisitor.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/imagevisitor.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/primitivesvisitor.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/variableobjectvisitor.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/nisxcommonnames.hpp
    PARENT_SCOPE
    )