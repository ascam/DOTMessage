##################################
#      DOT Messages Sources      #
##################################

add_subdirectory(components)
add_subdirectory(factories)
add_subdirectory(writers)
add_subdirectory(builders)
add_subdirectory(rippers)
add_subdirectory(visitors)

set(SOURCES ${SOURCES}
	${CMAKE_CURRENT_SOURCE_DIR}/dotmessage.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/document.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/object.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/text.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/barcode.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/image.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/primitives.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/variableobject.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/datecodes.cpp
	PARENT_SCOPE
    )

set(HEADERS ${HEADERS}
	PARENT_SCOPE
    )

