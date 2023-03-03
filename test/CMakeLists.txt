#############################
#  DOT Messages DOM Project #
#############################
## Project configuration
cmake_minimum_required(VERSION 3.10)
include_guard(GLOBAL)
cmake_policy(SET CMP0048 NEW)

project(DotMessageTester VERSION 0.0.0)

set (PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/..)
set(EXECUTABLE_DIR ${PROJECT_SOURCE_DIR}/test)
message("\n## Configuring ${PROJECT_NAME} v${PROJECT_VERSION}")

#####################  VERSION DEFINITION  #############################
add_definitions(-DDOM_TESTER_VERSION_MAJOR=${PROJECT_VERSION_MAJOR})
add_definitions(-DDOM_TESTER_VERSION_MINOR=${PROJECT_VERSION_MINOR})
add_definitions(-DDOM_TESTER_VERSION_BUILD=${PROJECT_VERSION_PATCH})
add_definitions(-DDOM_TESTER_VERSION="${PROJECT_VERSION}")

##################  LOADING MODULES  ###########################
include(${PROJECT_SOURCE_DIR}/cmake/dependencies.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/CMakeRC.cmake)

option(STANDALONE "Build as standalone executable" OFF)

####################  SOURCES AND HEADERS  #############################

set(SOURCES)
set(HEADERS)

set(SOURCES ${SOURCES}
    ${UTILS_DIR}/macsalogger/macsalogger.cpp
	${UTILS_DIR}/threadsmap/threadsmap.cpp
    ${EXECUTABLE_DIR}/main.cpp
    )

cmrc_add_resource_library(domTesterFiles
	NAMESPACE dot
	WHENCE rc
	PREFIX messages
	rc/CQ.nisx
	rc/MENSAJE3.NISX
	rc/MENSAJE5.NISX
	rc/TEST_BARCODES.nisx
	rc/TEST_III.nisx
	rc/TEST_II.nisx
	rc/TEST_I.nisx
	rc/TEST_IV.nisx
	rc/TEST.nisx
	rc/TEST_VI.nisx
	rc/TEST_V.nisx
	rc/testParserNisx.nisx
	rc/GALLO.nisx
	)

####################  TARGETS  #############################
if(STANDALONE) 
	 ## Add windows OS support
	set(DEPENDENCIES
		${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/libdotmessage.a
		)
else()
	set(DEPENDENCIES 
		dotmessage
		)
endif()

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME}
	PUBLIC
		${PROJECT_SOURCE_DIR}/include
		${UTILS_DIR}/include
	)

#linking dependencies
target_link_libraries(${PROJECT_NAME} PUBLIC ${DEPENDENCIES} PRIVATE domTesterFiles)
target_link_directories(${PROJECT_NAME} PUBLIC ${LIB_PREFIX}/lib ${CMAKE_BINARY_DIR}/lib)
