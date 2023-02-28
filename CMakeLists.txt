#############################
#  DOT Messages DOM Project #
#############################
## Project configuration
cmake_minimum_required(VERSION 3.10)
include_guard(GLOBAL)
cmake_policy(SET CMP0048 NEW)

project(dotmessage VERSION 0.0.0)

set (PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
message("\n## Configuring ${PROJECT_NAME} v${PROJECT_VERSION}")

#####################  VERSION DEFINITION  #############################
add_definitions(-DDOT_MESSAGE_LIB_VERSION_MAJOR=${PROJECT_VERSION_MAJOR})
add_definitions(-DDOT_MESSAGE_LIB_VERSION_MINOR=${PROJECT_VERSION_MINOR})
add_definitions(-DDOT_MESSAGE_LIB_VERSION_BUILD=${PROJECT_VERSION_PATCH})
add_definitions(-DDOT_MESSAGE_LIB_VERSION="${PROJECT_VERSION}")

##################  LOADING MODULES  ###########################
include(${PROJECT_SOURCE_DIR}/cmake/dependencies.cmake)


####################  SOURCES AND HEADERS  #############################
option(BUILD_SHARED_LIBS "Build Shared libraries" ON)

set(SOURCES)
set(HEADERS)

if (${ENABLE_TESTS})
	add_subdirectory(test)
	# Move resource file
	# file(COPY "assets/fonts/*" DESTINATION "${PROJECT_BINARY_DIR}/bin/fonts" FILES_MATCHING PATTERN "*.ttf")
endif()


add_subdirectory(${PROJECT_SOURCE_DIR}/src		${PROJECT_BINARY_DIR}/src)
add_subdirectory(${PROJECT_SOURCE_DIR}/include	${PROJECT_BINARY_DIR}/include)


set (SOURCES ${SOURCES}
	${CMAKE_CURRENT_SOURCE_DIR}/src
	${UTILS_DIR}/stringutils/stringutils.cpp
	${UTILS_DIR}/macsalogger/macsalogger.cpp
	${UTILS_DIR}/threadsmap/threadsmap.cpp
	${UTILS_DIR}/base64/base64.c
)

set(HEADERS ${HEADERS})

if (${ENABLE_TESTS})
#    set(SRC_TEST ${SRC_TEST})
#	set(HDRS_TEST ${HDRS_TEST})
endif()

####################  TARGETS  #############################

#Create a virtual target to avoid multiple compilation of sources
add_library(${PROJECT_NAME}_lib OBJECT ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME}_lib
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/include
		${UTILS_DIR}/include
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/src
	)

if(NOT BUILD_SHARED_LIBS)
	message("lib  ${PROJECT_NAME} v${PROJECT_VERSION} creating static library")
	message("-- STATIC Public dependencies: ${STATIC_DEPENDENCIES} ${EXTERNAL_LIBS}")
	add_library(${PROJECT_NAME} STATIC $<TARGET_OBJECTS:${PROJECT_NAME}_lib>)
	target_link_directories(${PROJECT_NAME} PUBLIC ${CMAKE_BINARY_DIR}/lib)
	target_link_libraries(${PROJECT_NAME} PUBLIC ${EXTERNAL_LIBS} ${STATIC_DEPENDENCIES})
	install(DIRECTORY ${CMAKE_BINARY_DIR}/lib/ DESTINATION ${INSTALL_DIR}/lib FILES_MATCHING PATTERN "*.so*")
else()
	message("lib  ${PROJECT_NAME} v${PROJECT_VERSION} creating dynamic library")
	message("-- SHARED Public dependencies: ${SHARED_DEPENDENCIES} ${EXTERNAL_LIBS}")
	set_property(TARGET ${PROJECT_NAME}_lib PROPERTY POSITION_INDEPENDENT_CODE 1)
	add_library(${PROJECT_NAME} SHARED $<TARGET_OBJECTS:${PROJECT_NAME}_lib>)
	set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION}
										  SOVERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR})
	target_link_directories(${PROJECT_NAME} PUBLIC ${CMAKE_BINARY_DIR}/lib)
	target_link_libraries(${PROJECT_NAME} PUBLIC ${EXTERNAL_LIBS} ${SHARED_DEPENDENCIES})
endif()

if (${ENABLE_TESTS})
	message("Adding ${PROJECT_NAME} tests dir ${PROJECT_BINARY_DIR}" )
	set(PROJECT_TEST_NAME ${PROJECT_NAME}Tests)
	add_executable(${PROJECT_TEST_NAME} ${SRC_TEST} ${HDRS_TEST})
	target_link_directories(${PROJECT_TEST_NAME} PUBLIC ${CMAKE_BINARY_DIR}/lib)
	target_link_libraries(${PROJECT_TEST_NAME} ${GTEST_LIBS} ${EXTERNAL_LIBS} ${SHARED_DEPENDENCIES} ${PROJECT_NAME})
	add_test(${PROJECT_NAME} ${PROJECT_TEST_NAME})
endif()
