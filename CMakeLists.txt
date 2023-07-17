#############################
#  DOT Messages DOM Project #
#############################
## Project configuration
cmake_minimum_required(VERSION 3.10)
include_guard(GLOBAL)
cmake_policy(SET CMP0048 NEW)

project(dotmessage VERSION 1.0.0)

set (PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
message("\n## Configuring ${PROJECT_NAME} v${PROJECT_VERSION}")

#####################  VERSION DEFINITION  #############################
add_definitions(-DDOT_MESSAGE_LIB_VERSION_MAJOR=${PROJECT_VERSION_MAJOR})
add_definitions(-DDOT_MESSAGE_LIB_VERSION_MINOR=${PROJECT_VERSION_MINOR})
add_definitions(-DDOT_MESSAGE_LIB_VERSION_BUILD=${PROJECT_VERSION_PATCH})
add_definitions(-DDOT_MESSAGE_LIB_VERSION="${PROJECT_VERSION}")
add_definitions(-DDOT_MESSAGE_LIB_NAME="${PROJECT_NAME}")

##################  LOADING MODULES  ###########################
include(${PROJECT_SOURCE_DIR}/cmake/dependencies.cmake)


####################  SOURCES AND HEADERS  #############################
option(BUILD_SHARED_LIBS "Build Shared libraries" ON)
option(BUILD_TEST_EXECUTABLE "Build Test application" OFF)
option(RASTERIZATION "Enable use of rasterization classes" ON)
option(BACKEND_QT  "Use Qt based generator" ON)
option(BACKEND_SDL2 "Use SDL2 based generator" OFF)

if (RASTERIZATION)
if (BACKEND_QT)
    ## Zint library options
    set(ZINT_VERSION zint-2.8.0)
    option(USE_ZINT_PNG "Enable png for zint" OFF)
    if (NOT USE_ZINT_PNG)
	add_definitions (-DNO_PNG) #required for ARM
    endif()
    option(BACKEND_QT_NATIVE  "Use Qt based generator natively" OFF)
endif()
else()
    set(BACKEND_QT OFF CACHE BOOL "Use Qt based generator" FORCE)
    set(BACKEND_SDL2 OFF CACHE BOOL "Use SDL2 based generator" FORCE)
endif()

## Add Macsa utilities library
add_subdirectory(${UTILS_DIR}/libutils       ${PROJECT_BINARY_DIR}/libutils)
add_subdirectory(${UTILS_DIR}/tinyxml2       ${PROJECT_BINARY_DIR}/tinyxml2)

set(SOURCES)
set(HEADERS)

add_subdirectory(${PROJECT_SOURCE_DIR}/src	    ${PROJECT_BINARY_DIR}/src)
add_subdirectory(${PROJECT_SOURCE_DIR}/include	${PROJECT_BINARY_DIR}/include)

if (${BUILD_TEST_EXECUTABLE})
        add_subdirectory(test)
endif()

if (RASTERIZATION)
        set(BACKEND_LIBS)
    if (BACKEND_QT)
	        message("Using Qt backend")
		include(${UTILS_DIR}/cmake/qt.cmake)
		if(BACKEND_QT_NATIVE)
		        add_definitions(-DBACKEND_QT_NATIVE)
		endif()
		add_subdirectory(${UTILS_DIR}/${ZINT_VERSION}   ${PROJECT_BINARY_DIR}/${ZINT_VERSION})
		include_directories(${UTILS_DIR}/${ZINT_VERSION})
		set(BACKEND_LIBS ${BACKEND_LIBS} ${QT_LIBS})
		add_definitions(-DQT_BACKEND=TRUE)
    elseif(BACKEND_SDL2)
	        message("Using SDL backend")
		find_package(SDL2 REQUIRED)
		include_directories(${SDL2_INCLUDE_DIRS})
		set(BACKEND_LIBS ${BACKEND_LIBS} SDL2 SDL2_image SDL2_ttf SDL2_gfx)
		add_definitions(-DSDL2_BACKEND=TRUE)
    endif()

    if (NOT BACKEND_QT AND NOT BACKEND_SDL2)
	    message(FATAL_ERROR "No backend provided!!")
	endif()
	set(EXTERNAL_LIBS ${EXTERNAL_LIBS} ${BACKEND_LIBS})
endif()

set(EXTERNAL_LIBS ${EXTERNAL_LIBS} macsautils tinyxml2)


set(HEADERS ${HEADERS})

link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
if(WIN32)
        link_directories(${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endif()

####################  TARGETS  #############################

#Create a virtual target to avoid multiple compilation of sources

add_library(${PROJECT_NAME}_lib OBJECT ${SOURCES} ${HEADERS})

set(DOTMESSAGE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/include
	CACHE FILEPATH "DotMessage include directory" FORCE)

target_include_directories(${PROJECT_NAME}_lib
        PUBLIC
		${DOTMESSAGE_INCLUDE_DIRECTORIES}
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/src
		${UTILS_INCLUDE_DIRECTORY}
		${TINYXML2_INCLUDE_DIRECTORY}
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
	set_target_properties(${PROJECT_NAME}
		PROPERTIES VERSION ${PROJECT_VERSION}
		SOVERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR})
	target_link_directories(${PROJECT_NAME} PUBLIC ${CMAKE_BINARY_DIR}/lib)
	target_link_libraries(${PROJECT_NAME} PUBLIC ${EXTERNAL_LIBS} ${SHARED_DEPENDENCIES})
endif()
